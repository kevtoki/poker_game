#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "Client.h"
#include "GUI.h"


int main(int argc, char *argv[]){

	gtk_init(NULL, NULL);

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

	CreateClientPlayer(game, conn);

	GameWindow *window = CreateGameWindow(game);

	gtk_main();

	DeleteGameWindow(window);

	DeleteClientGame(game);

	return 0;
}
