#ifndef GAME_H
#define GAME_H
#include "PlayerList.h"

typedef struct {
	PLIST *players;
		


} Game;


Game *CreateGame();

void DeleteGame(Game *game);

#endif
