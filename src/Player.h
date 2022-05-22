#ifndef PLAYER_H
#define PLAYER_H
#include "Deck.h"

typedef enum {PLAYER, DEALER} TYPE;

typedef struct {
	int id;
	TYPE type;
	DECK *deck;

} Player;


Player *CreatePlayer(int id, TYPE type);

void DeletePlayer(Player *player);


#endif
