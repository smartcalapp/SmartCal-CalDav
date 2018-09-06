//
// Created by Garrett Battaglia on 8/31/18.
//

#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include "webDavCon.h"

#define SQL_SELECT_EVENTS "SELECT * FROM events INNER JOIN subscriptions_pivot ON subscriptions_pivot.subscription = \
events.parent_org WHERE subscriptions_pivot.uuid = %1"

bool WebDavCon::accept() {
	//TODO parse UUID
	return true;
}

bool WebDavCon::buildCal() {
	//TODO
	char *uuidArr[1];
	uuidArr[0] = _uuid;
	if (PQstatus(_sqlCon) != CONNECTION_OK) {
		std::cout << "postgres connection closed while needed, bailing out" << std::endl;
		return false;
	}
	auto sqlRes = PQexecParams(_sqlCon, SQL_SELECT_EVENTS, 1, nullptr, uuidArr, nullptr, nullptr, 0);
	if (PQresultStatus(sqlRes) != PGRES_TUPLES_OK) {
		std::cout << "error (" << PQresultErrorMessage(sqlRes) << ")selecting events, bailing out" << std::endl;
		PQclear(sqlRes);
		//TODO exit nicely
	}
	//TODO parse sql res
	//TODO build cal object
	PQclear(sqlRes);
	return true;
}

bool WebDavCon::sendCal() {

}

bool WebDavCon::closeCon() {
	shutdown(_socket, SHUT_WR);
	close(_socket);
	PQfinish(_sqlCon);
	return true;
}
