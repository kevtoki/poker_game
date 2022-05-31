#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "Client.h"
#include "Card.h"
#include "Deck.h"


#define PACKET_SIZE 256

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
	int n = read(conn->sockfd, conn->buffer, PACKET_SIZE);
	if (n < 0){
		printf("ERROR reading from socket\n");
	}
	return conn->buffer;
}


void WriteServerConnection(ServerConnection *conn, const char *msg){
	bzero(conn->buffer, PACKET_SIZE);
	int n = write(conn->sockfd, msg, PACKET_SIZE);
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


void HandleUserInput(ClientGame *game, ClientPlayer *player){
	int input = 0;
	int betAmount = 0;
	int canRaise = (player->points > game->minimumBet) ? 1 : 0;

	printf("You have %d points. The minimum bet is %d points.\n", player->points, game->minimumBet);

	while ((input < 1 || input > 3) || (!canRaise && input == 2)){
		printf("What would you like to do?\n");
		printf("1 - Call\n");
		printf("2 - Raise\n");
		printf("3 - Fold\n\n");
		printf("Enter your input here: ");
		scanf("%d", &input);
	}

	if (input == 2){
		while (betAmount < game->minimumBet && betAmount > player->points){
			printf("\nHow much would you like to bet?\n");
			printf("Enter amount here (%d - %d): ", game->minimumBet, player->points);
			scanf("%d", &betAmount);
		}
	}

	char inputChar;
	switch (input){
		case 1:
			inputChar = 'c';
			break;

		case 2:
			inputChar = 'r';
			break;

		case 3:
			inputChar = 'f';
			break;

		default:
			inputChar = 'f';
			break;
	}

	SendPacket(player, inputChar, betAmount);
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
	// msg[8] - minimum bet value (points)
	// msg[32] to msg[41] - board card data
	// msg[64] - number of players in the match
	// msg[65] - player's id (numbers ascending from 0)
	// msg[66] - player's state (playing or folded)
	// msg[67] - player's number of points
	// msg[68] - next player's id
	// ...


	int newRound = msg[0];
	int needsInput = msg[1];

	player->points = msg[6];
	game->betPoints = msg[7];
	game->minimumBet = msg[8];


	if (newRound){
		if (player->card1 != NULL){
			DeleteCard(player->card1);
		}

		if (player->card2 != NULL){
			DeleteCard(player->card2);
		}
		player->card1 = NULL;
		player->card2 = NULL;

		EmptyDeck(game->boardCards);
	}

	for (int i = 0; i < 5; i++){
		int suit = msg[32 + (i * 2)];
		int rank = msg[33 + (i * 2)];
		if (suit == 0){
			continue;
		}

		if (HasCard(game->boardCards, suit, rank)){
			continue;
		}

		AppendDeckEntry(game->boardCards, CreateCard(suit, rank));
	}


	if (player->card1 == NULL && msg[2] != 0){
		player->card1 = CreateCard(msg[2], msg[3]);
		player->card2 = CreateCard(msg[4], msg[5]);
	}

	game->playerData[0] = msg[64];

	for (int i = 0; i < msg[64]; i++){
		game->playerData[1 + i] = msg[65 + i];
	}

	game->gameOver = msg[255];

	/*
	for (int i = 0; i < 256; i++){
		printf("%d ", msg[i]);
	}
	printf("\n");
	*/

	if (needsInput){
		HandleUserInput(game, player);
	}

}


void SendPacket(ClientPlayer *player, char action, int betAmount){
	char msg[256] = {0};

	// Client Packet Encoding Protocol
	// msg[0] - action indicator
	// msg[1] - bet amount (if any)

	msg[0] = action;

	msg[1] = betAmount;


	WriteServerConnection(player->connection, msg);

}


ClientGame *CreateClientGame(){
	ClientGame *game = malloc(sizeof(ClientGame));

	game->gameOver = 0;

	game->boardCards = CreateDeck();

	return game;
}


void DeleteClientGame(ClientGame *game){
	DeleteClientPlayer(game->user);
	DeleteDeck(game->boardCards);
	game->boardCards = NULL;
	free(game);
}
