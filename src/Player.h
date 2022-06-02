#ifndef PLAYER_H
#define PLAYER_H
#include "Deck.h"
#include "Server.h"

typedef enum {PLAYER, DEALER} TYPE;

typedef enum {PLAYING, FOLDED} P_STATE;


typedef struct {
	int id;
	TYPE type;
	P_STATE p_state;
	DECK *deck;
	int points;
	int totalBetPoints;
	Connection *connection;

} Player;


Player *CreatePlayer(int id, TYPE type);

void BindPlayerConnection(Player *player, Connection *conn);

void DeletePlayer(Player *player);

#endif
