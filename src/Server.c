#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "Server.h"

Connection *CreateConnection(int portno){
	Connection *conn = malloc(sizeof(Connection));
	conn->portno = portno;

    conn->sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (conn->sockfd < 0) 
       printf("ERROR opening socket\n");
    bzero((char *) &conn->serv_addr, sizeof(conn->serv_addr));
    conn->serv_addr.sin_family = AF_INET;
    conn->serv_addr.sin_addr.s_addr = INADDR_ANY;
    conn->serv_addr.sin_port = htons(conn->portno);
    if (bind(conn->sockfd, (struct sockaddr *) &conn->serv_addr, sizeof(conn->serv_addr)) < 0) 
    	printf("ERROR on binding\n");
    
	return conn; 

}


void OpenConnection(Connection *conn){
	listen(conn->sockfd, 5);
	conn->clilen = sizeof(conn->cli_addr);
	conn->newsockfd = accept(conn->sockfd, (struct sockaddr *) &conn->cli_addr, &conn->clilen);
	if (conn->newsockfd < 0){
		printf("ERROR on accept");
	}
	bzero(conn->buffer, 256);
}


const char *ReadConnection(Connection *conn){
	int n = read(conn->newsockfd, conn->buffer, 256);

	if (n < 0){
		printf("ERROR reading from socket\n");
	}
	return conn->buffer;
}


void WriteConnection(Connection *conn, const char *msg){
	bzero(conn->buffer, 256);
	int n = write(conn->newsockfd, msg, 256);
	if (n < 0){
		printf("ERROR writing to socket\n");
	}

	printf("Sending data through port %d\n", ntohs(conn->serv_addr.sin_port));
}


void DeleteConnection(Connection *conn){
	close(conn->newsockfd);
	close(conn->sockfd);
	free(conn);
}
