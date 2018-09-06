#include <iostream>
#include "net/socket.h"
#include "config/config.h"


int main(int argc, char **argv) {
	if (argc != 2) {
		std::cout << "please only specify path to config file" << std::endl;
		exit(-1);
	}
	config = Config(argv[1]);
	openMasterSocket();
}