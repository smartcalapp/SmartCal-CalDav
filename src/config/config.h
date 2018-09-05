 //
// Created by Garrett Battaglia on 9/4/18.
//

#ifndef SMARTCAL_CALDAV_CONFIG_H
#define SMARTCAL_CALDAV_CONFIG_H


#include <string>
#include <fstream>

 class Config
{
	private:
		std::string postgress_server = "";
		int postgress_port = -1;
		std::string postgress_database = "";
		std::string postgress_username = "";
		std::string postgress_password = "";
		int webdav_port = -1;
		std::string configPath = "";
	public:
		Config(){

		}
		Config(std::string path);

				 const std::string &getPostgress_server() const;

				 int getPostgress_port() const;

				 const std::string &getPostgress_database() const;

				 const std::string &getPostgress_username() const;

				 const std::string &getPostgress_password() const;

				 int getWebdav_port() const;

				 const std::string &getConfigPath() const;
 };

Config config;

#endif //SMARTCAL_CALDAV_CONFIG_H
