#include "Player.h"
#include "Deck.h"
#include "Player.h"
#include <stdlib.h>


Player *CreatePlayer(int id, TYPE type){
	Player *player = (Player *) malloc(sizeof(Player));

	player->id = id;
	player->type = type;
	player->p_state = PLAYING;

	player->deck = CreateDeck();

	player->points = 100;

	return player;
}


void BindPlayerConnection(Player *player, Connection *conn){
	player->connection = conn;

}


void DeletePlayer(Player *player){
	if (player->deck != NULL){
		DeleteDeck(player->deck);
	}

	DeleteConnection(player->connection);

	free(player);
	player = NULL;
}


