//
// Created by Garrett Battaglia on 8/31/18.
//

#ifndef SMARTCAL_CALDAV_WEBDAV_H
#define SMARTCAL_CALDAV_WEBDAV_H

//TODO abs path
#include "../calender/Calender.h"
#include "../config/config.h"
#include <libpq-fe.h>
#include <sstream>

class WebDavCon {
	private:
		int _socket;
		PGconn *_sqlCon;
		std::string _conString;
		std::string _uuid;
		Calender _cal;

		WebDavCon()  = default;

	public:
		WebDavCon(int file) {
			_socket = file;
			//build string to connect to DB
			std::stringstream conStringS;
			conStringS << "postgresql://" << config.getPostgress_username() << ":"
			           << config.getPostgress_password() << "@" << config.getPostgress_server() << ":"
			           << config.getPostgress_port() << "/" << config.getPostgress_database();
			_conString = conStringS.str();
			//open SQL con
			_sqlCon = PQconnectdb(_conString.c_str());
			if (PQstatus(_sqlCon) != CONNECTION_OK) {
				//todo blow up
			}
		}

		bool accept();

		bool buildCal();

		bool sendCal();

		bool closeCon();

};


#endif //SMARTCAL_CALDAV_WEBDAV_H
