#ifndef SERVER_H
#define SERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

struct sockaddr_in;

typedef struct sockaddr_in Sockaddr_in;


typedef struct {
	Sockaddr_in serv_addr;
	Sockaddr_in cli_addr;
	socklen_t clilen;
	int sockfd, newsockfd, portno;
	char buffer[256];


} Connection;


Connection *CreateConnection(int portno);

void OpenConnection(Connection *conn);

const char *ReadConnection(Connection *conn);

void WriteConnection(Connection *conn, const char *msg);

void DeleteConnection(Connection *conn);

#endif
