#include "Game.h"
#include "PlayerList.h"
#include "Player.h"
#include "Deck.h"
#include "Server.h"
#include "Ranking.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

#define MINIMUM_BET 1



Game *CreateGame(){
	Game *game = (Game *) malloc(sizeof(Game));

	game->players = CreatePlayerList();

	game->boardCards = CreateDeck();

	game->betPoints = 0;

	game->minimumBet = MINIMUM_BET;

	game->roundWinner = NULL;

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

	game->roundWinner = NULL;

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

	printf("Player with id %d selected as dealer.\n", game->Dealer->id);
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

	while (PlayersWithPoints(game) > 1){
		GameRound(game);
	}

	BroadcastPackets(game, 0, 0, 1);

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

	BroadcastPackets(game, 0, 0, 0);

	ProcessUserActions(game);

	game->roundWinner = LastManStanding(game);

	if (game->roundWinner != NULL){
		GameRoundEnd(game);
		return;
	}

	TransferCard(game->Dealer->deck, game->boardCards, 0);

	BroadcastPackets(game, 0, 0, 0);

	ProcessUserActions(game);

	game->roundWinner = LastManStanding(game);

	if (game->roundWinner != NULL){
		GameRoundEnd(game);
		return;
	}

	TransferCard(game->Dealer->deck, game->boardCards, 0);

	BroadcastPackets(game, 0, 0, 0);

	ProcessUserActions(game);

	game->roundWinner = LastManStanding(game);

	if (game->roundWinner != NULL){
		GameRoundEnd(game);
		return;
	}

	game->roundWinner = EvaluateHands(game);



	GameRoundEnd(game);
}


void GameRoundEnd(Game *game){
	if (game->roundWinner != NULL){
		game->roundWinner->points += game->betPoints;
		game->betPoints = 0;

	}

	game->minimumBet = MINIMUM_BET;

	PENTRY *pEntry = game->players->First;
	for (int i = 0; i < game->players->Length; i++){
		EmptyDeck(pEntry->Player->deck);
		pEntry->Player->p_state = PLAYING;
		pEntry->Player->totalBetPoints = 0;
		pEntry = pEntry->Next;
	}

	EmptyDeck(game->boardCards);

	BroadcastPackets(game, 1, 0, 0);
}

int BetPoints(Game *game, Player *player, int points){
	if (player->points < points || points < game->minimumBet){
		return 0;
	}

	player->points -= points;

	player->totalBetPoints += points;

	game->betPoints += points;

	if (game->minimumBet < player->totalBetPoints){
		game->minimumBet = player->totalBetPoints;
	}

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
	SendPacket(game, player, 0, 1, 0);
	HandlePacket(game, player);
}


Player *EvaluateHands(Game *game){
	PENTRY *entry = game->players->First;
	Player *highest = game->players->First->Player;
	for (int i = 0; i < game->players->Length; i++){
		if (RankHand(game->boardCards, entry->Player) > RankHand(game->boardCards, highest)){
			highest = entry->Player;
		}

		entry = entry->Next;
	}

	return highest;
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


int PlayersWithPoints(Game *game){
	PENTRY *entry = game->players->First;

	int playersWithPoints = 0;
	
	for (int i = 0; i < game->players->Length; i++){
		if (entry->Player->points > 0){
			playersWithPoints++;
		}
		entry = entry->Next;
	}

	return playersWithPoints;
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


void SendPacket(Game *game, Player *player, int newRound, int needsInput, int gameOver){

	// Server Packet Encoding Protocol
	// msg[0] - new round indicator, if this is one the Client's cards get wiped for the new round
	// msg[1] - input key, if this is one then the user gets prompted for input
	// msg[2] to msg[5] - card data for player
	// msg[6] - the number of points the player has
	// msg[7] - the jackpot value (points)
	// msg[8] - minimum bet value (points)
	// msg[9] - the total bet of the player (points)
	// msg[10] - id of the player that wo the round
	// msg[11] - the type of the user (PLAYER or DEALER)
	// msg[32] to msg[41] - board card data
	// msg[63] - number of players still playing (not folded)
	// msg[64] - number of players in the match
	// msg[65] - player's id (numbers ascending from 0)
	// msg[66] - player's state (playing or folded)
	// msg[67] - player's number of points
	// msg[68] - next player's id
	// msg[255] - game over indicator, program exits if this is 1
	// ...

	char msg[256] = {[0 ... 255] = 0};

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
	msg[8] = game->minimumBet;
	msg[9] = player->totalBetPoints;
	if (game->roundWinner != NULL){
		msg[10] = game->roundWinner->id;
	}

	msg[11] = player->type;

	{
		DENTRY *entry = game->boardCards->First;
		for (int i = 0; i < game->boardCards->Length; i++){
			msg[32 + (i * 2)] = entry->Card->suit;
			msg[33 + (i * 2)] = entry->Card->rank;
			entry = entry->Next;
		}
	}

	if (player->type == DEALER){
		msg[64] = game->players->Length;
	}
	else {
		msg[64] = game->players->Length - 1;
	}

	int activePlayers = 0;

	PENTRY *entry = game->players->First;
	for (int i = 0; i < game->players->Length; i++){
		if (entry->Player->p_state == PLAYING){
			activePlayers++;
		}

		if (entry->Player != player){
			msg[65 + (i * 3)] = entry->Player->id;
			msg[66 + (i * 3)] = entry->Player->p_state;
			msg[67 + (i * 3)] = entry->Player->points;
		}
		entry = entry->Next;
	}

	msg[63] = activePlayers;

	msg[255] = gameOver;

	WriteConnection(player->connection, msg);

}

void BroadcastPackets(Game *game, int newRound, int needsInput, int gameOver){

	PENTRY *entry = game->players->First;
	for (int i = 0; i < game->players->Length; i++){
		SendPacket(game, entry->Player, newRound, needsInput, gameOver);
		entry = entry->Next;
	}

	SendPacket(game, game->Dealer, newRound, needsInput, gameOver);

}


void DecodePacket(Game *game, Player *player, const char *msg){
	char action = msg[0];
	int betAmount = msg[1];

	switch (action){
		case 'c':
			BetPoints(game, player, betAmount);
			break;

		case 'b':
			BetPoints(game, player, betAmount);
			break;

		case 'f':
			player->p_state = FOLDED;
			break;

		default:
			break;
	}
}


void HandlePacket(Game *game, Player *player){
	DecodePacket(game, player, ReadConnection(player->connection));
}
