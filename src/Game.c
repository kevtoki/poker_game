#include "Game.h"
#include "PlayerList.h"
#include "Player.h"
#include "Deck.h"
#include <stdlib.h>
#include <stdio.h>

Game *CreateGame(){
	Game *game = (Game *) malloc(sizeof(Game));

	game->players = CreatePlayerList();

	game->boardCards = CreateDeck();

	return game;
}




void DeleteGame(Game *game){
	if (game->players != NULL){
		DeletePlayerList(game->players);
	}

	game->players = NULL;

	free(game);
}


void DealCards(Game *game){
	Player *dealer = game->players->Dealer;
	PENTRY *pEntry = game->players->First;
	for (int i = 0; i < game->players->Length; i++){
		TransferCard(dealer->deck, pEntry->Player->deck, 0);
		pEntry = pEntry->Next;
	}
}


void GameLoop(){
	Game *game = CreateGame();

	AppendPlayerEntry(game->players, CreatePlayer(0, DEALER));
	AppendPlayerEntry(game->players, CreatePlayer(1, PLAYER));
	AppendPlayerEntry(game->players, CreatePlayer(2, PLAYER));
	AppendPlayerEntry(game->players, CreatePlayer(3, PLAYER));
	AppendPlayerEntry(game->players, CreatePlayer(4, PLAYER));


	ShuffleDeck(game->players->Dealer->deck);
	DealCards(game);
	DealCards(game);

	PrintPlayerData(game);

	DeleteGame(game);
}



void PrintPlayerData(Game *game){
	printf("Suit | Spade = 1, Clubs = 2, Diamonds = 3, Hearts = 4\n");
	printf("Rank | Ace = 1, ..., King = 13");

	PENTRY *pEntry = game->players->First;
	for (int i = 0; i < game->players->Length; i++){
		printf("\n\nPlayer | ID: %d, Type: %d\n", pEntry->Player->id, pEntry->Player->type);

		DENTRY *dEntry = pEntry->Player->deck->First;
		for (int j = 0; j < pEntry->Player->deck->Length; j++){
			printf("	Card | Suit: %d, Rank: %d\n", dEntry->Card->suit, dEntry->Card->rank);
			dEntry = dEntry->Next;
		}

		pEntry = pEntry->Next;
	}
}
