#include "Game.h"
#include "PlayerList.h"
#include "Player.h"
#include "Deck.h"
#include "Server.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>


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

	free(game->boardCards);

	game->boardCards = NULL;

	DeletePlayer(game->Dealer);

	game->Dealer = NULL;

	free(game);
}


void DealCards(Game *game){
	Player *dealer = game->Dealer;
	PENTRY *pEntry = game->players->First;
	for (int i = 0; i < game->players->Length; i++){
		TransferCard(dealer->deck, pEntry->Player->deck, 0);

		pEntry = pEntry->Next;
	}
}


void SelectDealer(Game *game){
	srand((unsigned) time(0));

	int dealerIndex = rand() % game->players->Length;

	Player *dealer = PopPlayerEntry(game->players, dealerIndex);

	dealer->type = DEALER;

	game->Dealer = dealer;
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

	SelectDealer(game);
}


void GameLoop(int playerCount){
	Game *game = CreateGame();

	InitializeGameConnections(game, playerCount);

	SendPacket(game, game->players->First->Player, 1, 1);
	SendPacket(game, game->Dealer, 1, 1);

	GameRound(game);

	DeleteGame(game);
}


void GameRound(Game *game){
	FillDeck(game->Dealer->deck);

	ShuffleDeck(game->Dealer->deck);
	DealCards(game);
	DealCards(game);

	TransferCard(game->Dealer->deck, game->boardCards, 0);
	TransferCard(game->Dealer->deck, game->boardCards, 0);
	TransferCard(game->Dealer->deck, game->boardCards, 0);


	BroadcastPackets(game, 0, 0);

	// ProcessUserActions(game);

	// LastManStanding(game);

	TransferCard(game->Dealer->deck, game->boardCards, 0);

	// ProcessUserActions(game);

	// LastManStanding(game);

	TransferCard(game->Dealer->deck, game->boardCards, 0);

	// ProcessUserActions(game);

	// LastManStanding(game);

	// EvaluateHands(game);


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
		GetUserInput(game, pEntry->Player);

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


void SendPacket(Game *game, Player *player, int newRound, int needsInput){

	// Server Packet Encoding Protocol
	// msg[0] - new round indicator, if this is one the Client's cards get wiped for the new round
	// msg[1] - input key, if this is one then the user gets prompted for input
	// msg[2] to msg[5] - card data for player
	// msg[6] - the number of points the player has
	// msg[7] - the jackpot value (points)
	// msg[16] - number of players in the match
	// msg[17] - player's id (numbers ascending from 0)
	// msg[18] - player's state (playing or folded)
	// msg[19] - player's number of points
	// msg[20] - next player's id
	// ...

	char msg[256] = {0};

	msg[0] = newRound;
	msg[1] = needsInput;

	if (player->deck->Length == 2){
		DENTRY *entry = player->deck->First;

		msg[2] = entry->Card->suit;
		msg[3] = entry->Card->rank;

		entry = entry->Next;

		msg[4] = entry->Card->suit;
		msg[5] = entry->Card->rank;
	}

	msg[6] = player->points;
	msg[7] = game->betPoints;

	msg[16] = game->players->Length - 1;

	PENTRY *entry = game->players->First;
	for (int i = 0; i < game->players->Length; i++){
		if (entry->Player != player){
			msg[17 + (i * 3)] = entry->Player->id;
			msg[18 + (i * 3)] = entry->Player->p_state;
			msg[19 + (i * 3)] = entry->Player->points;
		}
		entry = entry->Next;
	}

	WriteConnection(player->connection, msg);

}

void BroadcastPackets(Game *game, int newRound, int needsInput){

	PENTRY *entry = game->players->First;
	for (int i = 0; i < game->players->Length; i++){
		SendPacket(game, entry->Player, newRound, needsInput);
		entry = entry->Next;
	}



}
