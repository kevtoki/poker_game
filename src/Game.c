#include "Game.h"
#include "PlayerList.h"
#include <stdlib.h>

Game *CreateGame(){
	Game *game = (Game *) malloc(sizeof(Game));

	game->players = CreatePlayerList();

	return game;
}




void DeleteGame(Game *game){
	if (game->players != NULL){
		DeletePlayerList(game->players);
	}

	game->players = NULL;

	free(game);
}
