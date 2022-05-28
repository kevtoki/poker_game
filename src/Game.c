#include "Game.h"
#include "PlayerList.h"
#include "Player.h"
#include "Deck.h"
#include "Server.h"
#include <stdlib.h>
#include <stdio.h>

Game *CreateGame(){
	Game *game = (Game *) malloc(sizeof(Game));

	game->players = CreatePlayerList();

	game->boardCards = CreateDeck();

	game->betPoints = 0;

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


void InitializeGameConnections(Game *game, int activeConnections){
	for (int i = 0; i < activeConnections; i++){
		printf("Creating and opening connection on port %d\n", 10190 + i);
		Connection *conn = CreateConnection(10190 + i);
		OpenConnection(conn);
		Player *player = CreatePlayer(i, PLAYER);
		BindPlayerConnection(player, conn);
		AppendPlayerEntry(game->players, player);

		printf("Player registered on port %d with id %d\n", 10190 + i, i);
	}

}


void GameLoop(int playerCount){
	Game *game = CreateGame();

	InitializeGameConnections(game, playerCount);

	GameRound(game);

	DeleteGame(game);
}


void GameRound(Game *game){
	FillDeck(game->players->Dealer->deck);

	ShuffleDeck(game->players->Dealer->deck);
	DealCards(game);
	DealCards(game);

	TransferCard(game->players->Dealer->deck, game->boardCards, 0);
	TransferCard(game->players->Dealer->deck, game->boardCards, 0);
	TransferCard(game->players->Dealer->deck, game->boardCards, 0);

	ProcessUserActions(game);

	LastManStanding(game);

	TransferCard(game->players->Dealer->deck, game->boardCards, 0);

	ProcessUserActions(game);

	LastManStanding(game);

	TransferCard(game->players->Dealer->deck, game->boardCards, 0);

	ProcessUserActions(game);

	LastManStanding(game);

	EvaluateHands(game);


	PENTRY *pEntry = game->players->First;
	for (int i = 0; i < game->players->Length; i++){
		EmptyDeck(pEntry->Player->deck);
		pEntry->Player->p_state = PLAYING;
		pEntry = pEntry->Next;
	}

	EmptyDeck(game->boardCards);
}


int BetPoints(Game *game, Player *player, int points){
	if (player->points < points){
		return 0;
	}

	player->points -= points;

	game->betPoints += points;

	return 1;
}


void ProcessUserActions(Game *game){
	PENTRY *pEntry = game->players->First;
	for (int i = 0; i < game->players->Length; i++){
		if (pEntry->Player->type != DEALER){
			GetUserInput(game, pEntry->Player);
		}

		pEntry = pEntry->Next;
	}
}


void GetUserInput(Game *game, Player *player){
	const char *input = ReadConnection(player->connection);
}


Player *EvaluateHands(Game *game){




	return NULL;
}


Player *LastManStanding(Game *game){
	int playersIn = game->players->Length;
	Player *playerIn;
	PENTRY *pEntry = game->players->First;
	for (int i = 0; i < game->players->Length; i++){
		if (pEntry->Player->p_state == FOLDED){
			playersIn--;
		}
		else {
			playerIn = pEntry->Player;
		}

		pEntry = pEntry->Next;
	}

	if (playersIn == 1){
		return playerIn;
	}
	else {
		return NULL;
	}
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
