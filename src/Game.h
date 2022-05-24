#ifndef GAME_H
#define GAME_H
#include "PlayerList.h"
#include "Deck.h"

typedef struct {
	PLIST *players;
	DECK *boardCards;

} Game;


Game *CreateGame();

void DeleteGame(Game *game);

void DealCards(Game *game);

void GameLoop();

void PrintPlayerData(Game *game);

#endif
