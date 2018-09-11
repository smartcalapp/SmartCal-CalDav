//
// Created by Garrett Battaglia on 8/31/18.
//

#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include "webDavCon.h"

//TODO refactor

static const std::string SUBS_TABLE = "users_organizations_subscriptions_pivot";
static const std::string SUBS_TABLE_ORG_ROW = "orgination_id";
static const std::string SUBS_TABLE_USER_UUID_ROW = "foobar";
static const std::string EVENTS_TABLE = "events";
static const std::string EVENTS_TABLE_ORG_ROW = "parent_organization";
static const std::string EVENTS_TABLE_START_TIME_ROW = "start_time";
static const std::string EVENTS_TABLE_END_TIME_ROW = "end_time";
static const std::string EVENTS_TABLE_NAME_ROW = "name";
static const std::string SQL_SELECT_EVENTS =
				"SELECT * FROM " + EVENTS_TABLE + " INNER JOIN " + SUBS_TABLE + " ON " + SUBS_TABLE + "." +
				SUBS_TABLE_ORG_ROW + " = " + EVENTS_TABLE + "." + EVENTS_TABLE_ORG_ROW + " WHERE " + SUBS_TABLE + "." +
				SUBS_TABLE_USER_UUID_ROW + " = %1";
static const std::string USERS_TABLE = "users";
static const std::string USERS_TABLE_ID_ROW = "id";
static const std::string USERS_TABLE_UUID_ROW = "uuid";
static const std::string SQL_SELECT_USER_ID_FROM_UUID =
				"SELECT " + USERS_TABLE_ID_ROW + " FROM " + USERS_TABLE + " WHERE " + USERS_TABLE_UUID_ROW + " = %1";
static const std::string HTTP_LINE_BREAK = "\r\n";
static const std::string GET_OK_RESPONSE_HEADER =
				"HTTP/1.1 200 OK" + HTTP_LINE_BREAK + "Connection: close" + HTTP_LINE_BREAK +
				"Content-type: text/calendar" + HTTP_LINE_BREAK + HTTP_LINE_BREAK;

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

	if (PQntuples(sqlRes)) {
		std::cout << "too many results returned, bailing out" << std::endl;
		return false;
	}
	auto idRowNum = PQfnumber(sqlRes, USERS_TABLE_ID_ROW.c_str());
	_id = atoi(PQgetvalue(sqlRes, 0, idRowNum));
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
	for (int i = 0; i < PQntuples(sqlRes); i++) {
		auto startTime = PQgetvalue(sqlRes, i, startTimeColNum);
		auto endTime = PQgetvalue(sqlRes, i, endTimeColNum);
		auto name = PQgetvalue(sqlRes, i, nameColNum);
		auto startTimeInt = atol(startTime);
		auto endTimeInt = atol(endTime);
		_cal.add(startTimeInt, endTimeInt, name);
	}
	PQclear(sqlRes);
	return true;
}

bool WebDavCon::sendCal() {
	std::stringstream toSendSS;
	toSendSS << GET_OK_RESPONSE_HEADER;
	toSendSS << _cal;
	auto toSend = toSendSS.str().c_str();
	auto res = write(_socket, toSend, strlen(toSend));
	if (res < 0){

		return false;
	}
	return true;
}

bool WebDavCon::closeCon() {
	shutdown(_socket, SHUT_WR);
	close(_socket);
	PQfinish(_sqlCon);
	return true;
}
