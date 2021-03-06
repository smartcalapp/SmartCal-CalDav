//
// Created by Garrett Battaglia on 8/31/18.
//

#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include "webDavCon.h"
#include "sqlDefs.h"
#include "../calender/epoch.h"

//TODO refactor

bool WebDavCon::accept() {
	uint8_t buffer[8192];
	bzero(buffer, 8192);
	auto res = read(_socket, buffer, 8192);
	if (res < 0 || res == 8192) {
		std::cout << "error reading socket or get request too long, bailing out" << std::endl;
		return false;
	}

	std::stringstream getReq;
	getReq << buffer;
	std::string temp;
	std::string URI;
	std::string host;
	//         GET    URI    HTTP/1.1 Host:  hostname
	getReq >> temp >> URI >> temp >> temp >> host;

	_uuid = URI.substr(1);

	const char *uuidArr[1];
	uuidArr[0] = _uuid.c_str();

	if (PQstatus(_sqlCon) != CONNECTION_OK) {
		std::cout << "postgres connection closed while needed, bailing out" << std::endl;
		return false;
	}

	auto sqlRes = PQexecParams(_sqlCon, SQL_SELECT_USER_ID_FROM_UUID.c_str(), 1, nullptr, uuidArr, nullptr, nullptr, 0);
	if (PQresultStatus(sqlRes) != PGRES_TUPLES_OK) {
		std::cout << "error (" << PQresultErrorMessage(sqlRes) << ")selecting events, bailing out" << std::endl;
		PQclear(sqlRes);
		return false;
	}

	auto idRowNum = PQfnumber(sqlRes, USERS_TABLE_ID_ROW.c_str());
	_id = PQgetvalue(sqlRes, 0, idRowNum);
	return true;
}

bool WebDavCon::buildCal() {

	const char *uuidArr[1];
	uuidArr[0] = _id.c_str();
	if (PQstatus(_sqlCon) != CONNECTION_OK) {
		std::cout << "postgres connection closed while needed, bailing out" << std::endl;
		return false;
	}
	auto sqlRes = PQexecParams(_sqlCon, SQL_SELECT_EVENTS.c_str(), 1, nullptr, uuidArr, nullptr, nullptr, 0);
	if (PQresultStatus(sqlRes) != PGRES_TUPLES_OK) {
		std::cout << "error (" << PQresultErrorMessage(sqlRes) << ")selecting events, bailing out" << std::endl;
		PQclear(sqlRes);
		return false;
	}
	_cal = Calender(PQntuples(sqlRes));
	auto startTimeColNum = PQfnumber(sqlRes, EVENTS_TABLE_START_TIME_ROW.c_str());
	auto endTimeColNum = PQfnumber(sqlRes, EVENTS_TABLE_END_TIME_ROW.c_str());
	auto nameColNum = PQfnumber(sqlRes, EVENTS_TABLE_NAME_ROW.c_str());
	auto createStampColNum = PQfnumber(sqlRes, EVENTS_TABLE_CREATE_ROW.c_str());
	auto uuidColNum = PQfnumber(sqlRes, EVENTS_TABLE_UUID_ROW.c_str());
	for (int i = 0; i < PQntuples(sqlRes); i++) {
		auto createStamp = PQgetvalue(sqlRes, i, createStampColNum);
		auto startTime = PQgetvalue(sqlRes, i, startTimeColNum);
		auto endTime = PQgetvalue(sqlRes, i, endTimeColNum);
		auto name = PQgetvalue(sqlRes, i, nameColNum);
		auto uuid = PQgetvalue(sqlRes, i, uuidColNum);
		auto startTimeInt = atol(startTime);
		auto endTimeInt = atol(endTime);
		auto createStampInt = atol(createStamp);
		auto createTimeTm = SecondsSinceEpochToDateTime(new tm, createStampInt);
		auto startTimeTm = SecondsSinceEpochToDateTime(new tm, startTimeInt);
		auto endTimeTm = SecondsSinceEpochToDateTime(new tm, endTimeInt);
		_cal.add(createTimeTm, startTimeTm, endTimeTm, name, uuid);
	}
	PQclear(sqlRes);
	return true;
}

bool WebDavCon::sendCal() {
	std::stringstream toSendSS;
	std::stringstream calSS;
	calSS << _cal;
	toSendSS << GET_OK_RESPONSE_HEADER << calSS.str().length() << HTTP_LINE_BREAK << HTTP_LINE_BREAK;
	toSendSS << calSS.str();
	auto res = write(_socket, toSendSS.str().c_str(), strlen(toSendSS.str().c_str()));
	std::cout << "sent";
	return res >= 0;
}

bool WebDavCon::closeCon() {
	closeSocket();
	PQfinish(_sqlCon);
	return true;
}

bool WebDavCon::closeSocket(){
	shutdown(_socket, SHUT_WR);
	close(_socket);
	return true;
}
