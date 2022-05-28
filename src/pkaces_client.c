#include <stdio.h>
#include <stdlib.h>
#include "Client.h"


int main(int argc, char *argv[]){

	if (argc != 3){
		printf("ERROR not enough arguments\n");
		printf("Program shoudl be run with arguments <server> <portno>\n");

		return 0;
	}


	ServerConnection *conn = CreateServerConnection(argv[1], atoi(argv[2]));

	DeleteServerConnection(conn);
	return 0;
}
