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
#include "Card.h"

typedef struct sockaddr_in Sockaddr_in;
typedef struct hostent Host;

typedef enum {PLAYING, FOLDED} PLAYERSTATE;

typedef struct {
	int sockfd, portno;
	char buffer [256];
	Sockaddr_in serv_addr;
	Host *server;

} ServerConnection;


typedef struct {
	int points;
	PLAYERSTATE p_state;
	Card *card1;
	Card *card2;	
	ServerConnection *connection;


} ClientPlayer;


typedef struct {
	char playerData[256];
	int betPoints;
	ClientPlayer *user;
	int gameOver;

} ClientGame;


// ServerConnection functions

ServerConnection *CreateServerConnection(const char *hostname, int portno);

const char *ReadServerConnection(ServerConnection *conn);

void WriteServerConnection(ServerConnection *conn, const char *msg);

void DeleteServerConnection(ServerConnection *conn);


// ClientPlayer functions

ClientPlayer *CreateClientPlayer(ClientGame *game, ServerConnection *conn);

void DeleteClientPlayer(ClientPlayer *player);

void HandlePacket(ClientGame *game, ClientPlayer *player, ServerConnection *conn);

void DecodePacket(ClientGame *game, ClientPlayer *player, const char *msg);

void SendPacket(ClientPlayer *player, char action, int betAmount);


// ClientGame functions

ClientGame *CreateClientGame();

void DeleteClientGame(ClientGame *game);


#endif
