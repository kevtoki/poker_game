#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "Client.h"

ServerConnection *CreateServerConnection(const char *hostname, int portno){
	ServerConnection *conn = malloc(sizeof(ServerConnection));

	conn->server = malloc(sizeof(Host));

	conn->portno = portno;
	conn->sockfd = socket(AF_INET, SOCK_STREAM, 0);
	conn->server = gethostbyname(hostname);
	if (conn->server == NULL){
		printf("ERROR, no such host\n");
		return NULL;
	}
	bzero((char *) &conn->serv_addr, sizeof(conn->serv_addr));
	conn->serv_addr.sin_family = AF_INET;
	bcopy((char *) conn->server->h_addr_list[0], (char *)&conn->serv_addr.sin_addr.s_addr, conn->server->h_length);
	conn->serv_addr.sin_port = htons(portno);
	if (connect(conn->sockfd, (struct sockaddr *) &conn->serv_addr, sizeof(conn->serv_addr)) < 0){
		printf("ERROR connecting\n");
	}


	return conn;
}


const char *ReadConnection(ServerConnection *conn){
	int n = read(conn->sockfd, conn->buffer, 255);
	if (n < 0){
		printf("ERROR reading from socket\n");
	}
	return conn->buffer;
}


void WriteConnection(ServerConnection *conn, const char *msg){
	bzero(conn->buffer, 256);
	int n = write(conn->sockfd, msg, strlen(msg));
	if (n < 0){
		printf("ERROR writing to socket\n");
	}
}


void DeleteServerConnection(ServerConnection *conn){
	close(conn->sockfd);
	free(conn->server);
	conn->server = NULL;
	free(conn);
	conn = NULL;


}
