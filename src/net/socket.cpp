//
// Created by Garrett Battaglia on 8/31/18.
//

#include "socket.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>

int openMasterSocket(){
openMasterSocket(DEFAULT_PORT);
}

int openMasterSocket(int port){
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(port);
	if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		std::cout << "error binding to socket";
	}
	listen(sockfd, 5);

	struct sockaddr_in cli_addr;
	socklen_t cli_len = sizeof(cli_addr);
	auto error = false;
	while (!error)
	{
		int newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &cli_len);
		if (newsockfd < 0)
		{
			error = true;
			std::cout << "error establishing connection";
		}
		//handle connection

	}
	close(sockfd);
}