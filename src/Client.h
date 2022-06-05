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
#include "Deck.h"

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
	int totalBetPoints;
	PLAYERSTATE p_state;
	int type;
	Card *card1;
	Card *card2;	
	ServerConnection *connection;
	

} ClientPlayer;


typedef struct {
	char playerData[256];
	int betPoints;
	int minimumBet;
	int canRefresh;
	ClientPlayer *user;
	int gameOver;
	int idOfWinner;
	const char *connectionBuffer;

	DECK *boardCards;

} ClientGame;


// ServerConnection functions

ServerConnection *CreateServerConnection(const char *hostname, int portno);

const char *ReadServerConnection(ServerConnection *conn);

void WriteServerConnection(ServerConnection *conn, const char *msg);

void DeleteServerConnection(ServerConnection *conn);


// ClientPlayer functions

ClientPlayer *CreateClientPlayer(ClientGame *game, ServerConnection *conn);

void DeleteClientPlayer(ClientPlayer *player);

void HandleUserInput(ClientGame *game, ClientPlayer *player);

void HandlePacket(ClientGame *game, ClientPlayer *player, ServerConnection *conn);

void DecodePacket(ClientGame *game, ClientPlayer *player, const char *msg);

void SendPacket(ClientGame *game, char action, int betAmount);


// ClientGame functions

ClientGame *CreateClientGame();

void DeleteClientGame(ClientGame *game);


// Other functions

void PrintGameData(ClientGame *game);

#endif
