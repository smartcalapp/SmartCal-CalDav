//
// Created by Garrett Battaglia on 9/4/18.
//

#include "config.h"

Config config;

#pragma clang diagnostic push
#pragma ide diagnostic ignored "readability-container-size-empty"
Config::Config(std::string path) {
	std::ifstream configFile;
	configFile.open(path);
	std::string temp;
	while (configFile) {
		configFile >> temp;
		if (temp == "postgress_server") {
			configFile >> temp >> postgress_server;
			continue;
		}
		if (temp == "postgress_port") {
			configFile >> temp >> postgress_port;
			continue;
		}
		if (temp == "postgress_database") {
			configFile >> temp >> postgress_database;
			continue;
		}
		if (temp == "postgress_username") {
			configFile >> temp >> postgress_username;
			continue;
		}
		if (temp == "postgress_password") {
			configFile >> temp >> postgress_password;
			continue;
		}
		if (temp == "webdav_port") {
			configFile >> temp >> webdav_port;
			continue;
		}
	}
	if (postgress_server == "") {
		postgress_server = "localhost";
	}
	if (postgress_port == -1) {
		postgress_port = 5432;
	}
	if (postgress_database == "") {
		postgress_database = "SmartCal";
		//TODO check on
	}
	if (postgress_username == "") {
		postgress_username = "SmartCal";
	}
	if (postgress_password == "") {
		postgress_password = "@SuperHardP@ss0rd";
	}
	if (webdav_port == -1) {
		webdav_port = 80;
	}
}
#pragma clang diagnostic pop

const std::string &Config::getPostgress_server() const {
	return postgress_server;
}

int Config::getPostgress_port() const {
	return postgress_port;
}

const std::string &Config::getPostgress_database() const {
	return postgress_database;
}

const std::string &Config::getPostgress_username() const {
	return postgress_username;
}

const std::string &Config::getPostgress_password() const {
	return postgress_password;
}

uint16_t Config::getWebdav_port() const {
	return static_cast<uint16_t>(webdav_port);
}

const std::string &Config::getConfigPath() const {
	return configPath;
}
