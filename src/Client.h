#ifndef CLIENT_H
#define CLIENT_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

typedef struct sockaddr_in Sockaddr_in;
typedef struct hostent Host;

typedef struct {
	int sockfd, portno;
	char buffer [256];
	Sockaddr_in serv_addr;
	Host *server;

} ServerConnection;


ServerConnection *CreateServerConnection(const char *hostname, int portno);

const char *ReadServerConnection(ServerConnection *conn);

void WriteServerConnection(ServerConnection *conn, const char *msg);

void DeleteServerConnection(ServerConnection *conn);

#endif
