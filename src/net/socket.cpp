//
// Created by Garrett Battaglia on 8/31/18.
//

#include "socket.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
//TODO change to abs path
#include "../webDav/webDavCon.h"
#include "../config/config.h"

int handleNewConnection(uint_fast16_t file);

void openMasterSocket() {
	openMasterSocket(config.getWebdav_port());
}

//todo refactor
void openMasterSocket(uint_fast16_t port) {
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in serv_addr; // NOLINT(cppcoreguidelines-pro-type-member-init)
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(port);
	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
		std::cout << "error binding to socket";
		exit(-1);
	}
	listen(sockfd, 5);

	struct sockaddr_in cli_addr; // NOLINT(cppcoreguidelines-pro-type-member-init)
	socklen_t cli_len = sizeof(cli_addr);
	auto error = false;
	while (!error) {
		auto newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &cli_len);
		if (newsockfd < 0) {
			error = true;
			std::cout << "error establishing connection";
		} else {
			auto conErr = handleNewConnection(static_cast<uint_fast16_t>(newsockfd));
			if (conErr < 0) {
				std::cout << "error handing connection";
			}
		}

	}
	close(sockfd);
	exit(-2);
}

int handleNewConnection(uint_fast16_t file) {
	int forkRet = fork();
	if (forkRet < 0) {
		std::cout << "fork error";
		return -1;
	} else if (forkRet == 0) {
		//child
		WebDavCon con(file);
		auto res = con.accept();
		if (!res) {
			con.closeCon();
			//todo that should work
		}
		res = con.buildCal();
		if (!res) {
			con.closeCon();
			//todo that should work
		}
		res = con.sendCal();
		if (!res) {
			//todo blow up HTTP
			con.closeCon();
		}
		res = con.closeCon();
		if (!res) {
			//todo blow up
		}
		exit(0);
	} else if (forkRet > 0) {
		//parent
		return 0;
	}
	return -2;
}