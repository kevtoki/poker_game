#ifndef GAME_H
#define GAME_H
#include "PlayerList.h"
#include "Deck.h"
#include "Player.h"


typedef struct {
	PLIST *players;
	DECK *boardCards;
	int betPoints;


} Game;


Game *CreateGame();

void DeleteGame(Game *game);

void DealCards(Game *game);

void InitializeGameConnections(Game *game, int activeConnections);

void GameLoop();

void GameRound(Game *game);

int BetPoints(Game *game, Player *player, int points);

void ProcessUserActions(Game *game);

void GetUserInput(Game *game, Player *player);

Player *EvaluateHands(Game *game);

Player *LastManStanding(Game *game);

void PrintPlayerData(Game *game);

#endif
