//
// Created by Garrett Battaglia on 8/31/18.
//

#ifndef SMARTCAL_CALDAV_WEBDAV_H
#define SMARTCAL_CALDAV_WEBDAV_H

//TODO abs path
#include "../calender/Calender.h"
#include "../config/config.h"
#include <libpq-fe.h>
//#include <iosfwd>
#include <sstream>

class WebDavCon
{
		private:
				int _socket;
				PGconn *_sqlCon;
				Calender _cal;
				std::string _conString;

				WebDavCon()
				{

				}

		public:
				WebDavCon(int file)
				{
					_socket = file;
					std::stringstream conStringS;
					conStringS << "postgresql://" << config.getPostgress_username() << ":"
					           << config.getPostgress_password() << "@" << config.getPostgress_server() << ":"
					           << config.getPostgress_port() << "/" << config.getPostgress_database();
					_conString = conStringS.str();
					//open SQL con
					_sqlCon = PQconnectdb(_conString.c_str());
					//build calender
				}

};


#endif //SMARTCAL_CALDAV_WEBDAV_H
