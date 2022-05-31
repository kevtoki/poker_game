#include <stdio.h>
#include <stdlib.h>
#include "Client.h"


int main(int argc, char *argv[]){

	if (argc != 3){
		printf("ERROR not enough arguments\n");
		printf("Program should be run with arguments <hostname> <hostport>\n");

		return 0;
	}


	ServerConnection *conn = CreateServerConnection(argv[1], atoi(argv[2]));

	if (conn == NULL){
		return 0;
	}

	ClientGame *game = CreateClientGame();

	ClientPlayer *player = CreateClientPlayer(game, conn);

	while (!game->gameOver){
		HandlePacket(game, player, conn);
	}

	

	DeleteClientGame(game);

	return 0;
}
