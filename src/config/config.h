//
// Created by Garrett Battaglia on 9/4/18.
//

#ifndef SMARTCAL_CALDAV_CONFIG_H
#define SMARTCAL_CALDAV_CONFIG_H


#include <string>
#include <fstream>

class Config {
	private:
		std::string postgress_server = "";
		int postgress_port = -1;
		std::string postgress_database = "";
		std::string postgress_username = "";
		std::string postgress_password = "";
		int_fast16_t webdav_port = -1;
		std::string configPath = "";
	public:
		Config() = default;
		/**
		 * read config file
		 * @param path path of config file
		 */
		Config(std::string path);
		/**
 		* get the postgres server address from config
 		* @return host with postgres server
 		*/
		const std::string &getPostgress_server() const;
		/**
		 * get port postgres is working on from config
		 * @return port postgres is on
		 */
		int getPostgress_port() const;
		/**
		 * get database smartcal should work with
		 * @return database
		 */
		const std::string &getPostgress_database() const;

		/**
		 * get username to postgres server
		 * @return username
		 */
		const std::string &getPostgress_username() const;

		/**
		 * get password to postgres server
		 * @return password
		 */
		const std::string &getPostgress_password() const;

		/**
		 * get port to host on
		 * @return port
		 */
		uint16_t getWebdav_port() const;

		/**
		 * get path to config
		 * @return path
		 */
		const std::string &getConfigPath() const;
};

extern Config config;

#endif //SMARTCAL_CALDAV_CONFIG_H
