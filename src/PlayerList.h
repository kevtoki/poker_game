#ifndef PLAYERLIST_H
#define PLAYERLIST_H
#include "Player.h"

typedef struct PlayerList PLIST;
typedef struct PlayerEntry PENTRY;



struct PlayerList{
	PENTRY *First;
	PENTRY *Last;
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

Player *PopPlayerEntry(PLIST *pList, int index);

void DeletePlayerEntry(PLIST *pList, int index);

PENTRY *GetPlayerEntry(PLIST *pList, int index);

#endif
