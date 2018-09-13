#include <iostream>
#include <signal.h>
#include "net/socket.h"
#include "config/config.h"

void signalHandler( int signum ) {
	(void) signum;
	printf("clearing child");
	fflush(stdout);
	wait(NULL);
}

int main(int argc, char **argv) {
	signal(SIGCHLD, signalHandler);

	if (argc != 2) {
		std::cout << "please only specify path to config file" << std::endl;
		exit(-1);
	}
	config = Config(argv[1]);
	openMasterSocket();
}