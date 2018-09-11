//
// Created by Garrett Battaglia on 9/10/18.
//

#ifndef SMARTCAL_CALDAV_SQLDEFS_H
#define SMARTCAL_CALDAV_SQLDEFS_H

#include <string>

static const std::string SUBS_TABLE = "users_organizations_subscriptions_pivot";
static const std::string SUBS_TABLE_ORG_ROW = "organization_id";
static const std::string SUBS_TABLE_USER_UUID_ROW = "user_id";
static const std::string EVENTS_TABLE = "events";
static const std::string EVENTS_TABLE_ORG_ROW = "organization_id";
static const std::string EVENTS_TABLE_START_TIME_ROW = "start_time";
static const std::string EVENTS_TABLE_END_TIME_ROW = "end_time";
static const std::string EVENTS_TABLE_NAME_ROW = "name";
static const std::string SQL_SELECT_EVENTS =
				"SELECT * FROM " + EVENTS_TABLE + " INNER JOIN " + SUBS_TABLE + " ON " + SUBS_TABLE + "." +
				SUBS_TABLE_ORG_ROW + " = " + EVENTS_TABLE + "." + EVENTS_TABLE_ORG_ROW + " WHERE " + SUBS_TABLE + "." +
				SUBS_TABLE_USER_UUID_ROW + " = $1";
static const std::string USERS_TABLE = "users";
static const std::string USERS_TABLE_ID_ROW = "id";
static const std::string USERS_TABLE_UUID_ROW = "uuid";
static const std::string SQL_SELECT_USER_ID_FROM_UUID =
				"SELECT " + USERS_TABLE_ID_ROW + " FROM " + USERS_TABLE + " WHERE " + USERS_TABLE_UUID_ROW + " = $1";
static const std::string HTTP_LINE_BREAK = "\r\n";
static const std::string GET_OK_RESPONSE_HEADER =
				"HTTP/1.1 200 OK" + HTTP_LINE_BREAK + "Connection: close" + HTTP_LINE_BREAK +
				"Content-type: text/calendar" + HTTP_LINE_BREAK + HTTP_LINE_BREAK;

#endif //SMARTCAL_CALDAV_SQLDEFS_H
