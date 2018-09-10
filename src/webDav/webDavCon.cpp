//
// Created by Garrett Battaglia on 8/31/18.
//

#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include "webDavCon.h"

//TODO replace with real values
static const std::string SUBS_TABLE = "foo";
static const std::string SUBS_TABLE_ORG_ROW = "bar";
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


bool WebDavCon::accept() {
	//TODO parse UUID
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
	bzero(buffer, 8192);
	_uuid = URI.substr(1);
	return true;
}

bool WebDavCon::buildCal() {
	const char *uuidArr[1];
	uuidArr[0] = _uuid.c_str();
	if (PQstatus(_sqlCon) != CONNECTION_OK) {
		std::cout << "postgres connection closed while needed, bailing out" << std::endl;
		return false;
	}
	auto sqlRes = PQexecParams(_sqlCon, SQL_SELECT_EVENTS.c_str(), 1, nullptr, uuidArr, nullptr, nullptr, 0);
	if (PQresultStatus(sqlRes) != PGRES_TUPLES_OK) {
		std::cout << "error (" << PQresultErrorMessage(sqlRes) << ")selecting events, bailing out" << std::endl;
		PQclear(sqlRes);
		//TODO exit nicely
	}
	//TODO parse sql res
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
		//TODO create event and add to calender
	}
	//TODO build cal object
	PQclear(sqlRes);
	return true;
}

bool WebDavCon::sendCal() {
	//TODO
	return false;
}

bool WebDavCon::closeCon() {
	shutdown(_socket, SHUT_WR);
	close(_socket);
	PQfinish(_sqlCon);
	return true;
}
