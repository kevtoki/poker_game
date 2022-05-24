#ifndef PLAYERLIST_H
#define PLAYERLIST_H
#include "Player.h"

typedef struct PlayerList PLIST;
typedef struct PlayerEntry PENTRY;



struct PlayerList{
	PENTRY *First;
	PENTRY *Last;
	Player *Dealer;
	int Length;

};

struct PlayerEntry {
	PLIST *pList;
	PENTRY *Next;
	PENTRY *Prev;

	Player *Player;

};


PLIST *CreatePlayerList();

void DeletePlayerList(PLIST *pList);

void AppendPlayerEntry(PLIST *pList, Player *player);

void DeletePlayerEntry(PLIST *pList, int index);



#endif
