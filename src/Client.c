#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "Client.h"
#include "Card.h"

ServerConnection *CreateServerConnection(const char *hostname, int portno){
	ServerConnection *conn = malloc(sizeof(ServerConnection));

	conn->sockfd = 0;

	conn->portno = portno;
	conn->sockfd = socket(AF_INET, SOCK_STREAM, 0);
	conn->server = gethostbyname(hostname);
	if (conn->server == NULL){
		printf("ERROR, no such host\n");
		DeleteServerConnection(conn);
		return NULL;
	}

	bzero((char *) &conn->serv_addr, sizeof(conn->serv_addr));
	conn->serv_addr.sin_family = AF_INET;
	bcopy((char *) conn->server->h_addr_list[0], (char *)&conn->serv_addr.sin_addr.s_addr, conn->server->h_length);
	conn->serv_addr.sin_port = htons(portno);
	if (connect(conn->sockfd, (struct sockaddr *) &conn->serv_addr, sizeof(conn->serv_addr)) < 0){
		printf("ERROR connecting\n");
		DeleteServerConnection(conn);
		return NULL;
	}


	return conn;
}


const char *ReadServerConnection(ServerConnection *conn){
	int n = read(conn->sockfd, conn->buffer, 255);
	if (n < 0){
		printf("ERROR reading from socket\n");
	}
	return conn->buffer;
}


void WriteServerConnection(ServerConnection *conn, const char *msg){
	bzero(conn->buffer, 256);
	int n = write(conn->sockfd, msg, strlen(msg));
	if (n < 0){
		printf("ERROR writing to socket\n");
	}
}


void DeleteServerConnection(ServerConnection *conn){
	close(conn->sockfd);
	conn->server = NULL;
	free(conn);
	conn = NULL;
}



ClientPlayer *CreateClientPlayer(ClientGame *game, ServerConnection *conn){
	ClientPlayer *player = malloc(sizeof(ClientPlayer));

	player->card1 = NULL;
	player->card2 = NULL;

	player->connection = conn;

	game->user = player;

	HandlePacket(game, player, conn);

	return player;

}


void DeleteClientPlayer(ClientPlayer *player){
	if (player->card1 != NULL){
		DeleteCard(player->card1);
	}

	if (player->card2 != NULL){
		DeleteCard(player->card2);
	}

	player->card1 = NULL;
	player->card2 = NULL;

	DeleteServerConnection(player->connection);

	free(player);
	player = NULL;
}


void HandlePacket(ClientGame *game, ClientPlayer *player, ServerConnection *conn){
	DecodePacket(game, player, ReadServerConnection(conn));
}


void DecodePacket(ClientGame *game, ClientPlayer *player, const char* msg){

	// Server Packet Encoding Protocol
	// msg[0] - new round indicator, if this is one the Client's cards get wiped for the new round
	// msg[1] - input key, if this is one then the user gets prompted for input
	// msg[2] to msg[5] - card data for player
	// msg[6] - the number of points the player has
	// msg[7] - the jackpot value (points)
	// msg[16] - number of players in the match
	// msg[17] - player's id (numbers ascending from 0)
	// msg[18] - player's state (playing or folded)
	// msg[19] - player's amount bet (if any)
	// msg[20] - next player's id
	// ...


	int newRound = msg[0];
	int needsInput = msg[1];

	player->points = msg[6];
	game->betPoints = msg[7];

	if (newRound){
		DeleteCard(player->card1);
		DeleteCard(player->card1);
		player->card1 = NULL;
		player->card2 = NULL;
	}

	if (player->card1 == NULL && msg[2] != 0){
		player->card1 = CreateCard(msg[2], msg[3]);
		player->card2 = CreateCard(msg[4], msg[5]);
	}

	game->playerData[0] = msg[16];

	for (int i = 0; i < msg[16]; i++){
		game->playerData[1 + i] = msg[17 + i];
	}
}


void SendPacket(ClientPlayer *player, char action, int betAmount){
	char msg[256] = {0};

	// Client Packet Encoding Protocol
	// msg[0] - action indicator



	WriteServerConnection(player->connection, msg);

}


ClientGame *CreateClientGame(){
	ClientGame *game = malloc(sizeof(ClientGame));

	return game;
}


void DeleteClientGame(ClientGame *game){
	DeleteClientPlayer(game->user);
	free(game);
}
