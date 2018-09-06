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

int handleNewConnection(int file);

void openMasterSocket() {
	openMasterSocket(config.getWebdav_port());
}

//todo refactor
void openMasterSocket(int port) {
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(port);
	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
		std::cout << "error binding to socket";
		exit(-1);
	}
	listen(sockfd, 5);

	struct sockaddr_in cli_addr;
	socklen_t cli_len = sizeof(cli_addr);
	auto error = false;
	while (!error) {
		int newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &cli_len);
		if (newsockfd < 0) {
			error = true;
			std::cout << "error establishing connection";
		} else {
			auto conErr = handleNewConnection(newsockfd);
			if (conErr < 0) {
				std::cout << "error handing connection";
			}
		}

	}
	close(sockfd);
	exit(-2);
}

int handleNewConnection(int file) {
	int forkRet = fork();
	if (forkRet < 0) {
		std::cout << "fork error";
		return -1;
	} else if (forkRet == 0) {
		//child
		WebDavCon con(file);
		//todo do the rest
		auto res = con.accept();
		if (!res) {
			//todo blow up
		}
		res = con.buildCal();
		if (!res) {
			//todo blow up
		}
		res = con.sendCal();
		if (!res) {
			//todo blow up
		}
		res = con.close();
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