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

	int portno = atoi(argv[2]);

	ServerConnection *conn = CreateServerConnection(argv[1], portno);

	if (conn == NULL){
		return 0;
	}

	ClientGame *game = CreateClientGame();

	CreateClientPlayer(game, conn);

	game->user->id = portno - 10190;


	char name[50];

	printf("Please enter your username: ");

	scanf("%s", name);

	game->user->username = name;

	GameWindow *window = CreateGameWindow(game);

	gtk_main();

	DeleteGameWindow(window);

	DeleteClientGame(game);

	return 0;
}
