#include "Player.h"
#include "PlayerList.h"
#include <stdlib.h>
#include <time.h>

PLIST *CreatePlayerList(){
	PLIST *pList = (PLIST *) malloc(sizeof(PLIST));

	pList->Length = 0;
	pList->First = NULL;
	pList->Last = NULL;

	return pList;
}

void DeletePlayerList(PLIST *pList){
	int tempLength = pList->Length;

	for (int i = 0; i < tempLength; i++){
		DeletePlayerEntry(pList, 0);
	}

	pList->Last = NULL;
	pList->First = NULL;

	free(pList);
}

void AppendPlayerEntry(PLIST *pList, Player *player){

	PENTRY *pEntry = (PENTRY *) malloc(sizeof(PENTRY));


	pEntry->pList = pList;

	pList->Length++;

	pEntry->Player = player;

	pEntry->Next = NULL;


	if (pList->Length == 1){
		pEntry->Prev = NULL;
		pList->First = pEntry;
	}
	else {
		pEntry->Prev = pList->Last;
		pList->Last->Next = pEntry;
	}

	pList->Last = pEntry;
}


Player *PopPlayerEntry(PLIST *pList, int index){
	PENTRY *entry = pList->First;

	if (index < 0 || index >= pList->Length){
		return NULL;
	}

	for (int i = 0; i < index; i++){
		entry = entry->Next;
	}

	PENTRY *entryprev = entry->Prev;
	PENTRY *entrynext = entry->Next;

	if (pList->Length == 1){
		pList->Last = NULL;
		pList->First = NULL;
	}
	else if (index == 0){
		pList->First = entry->Next;
		entrynext->Prev = NULL;
	}
	else if (index == pList->Length - 1){
		pList->Last = entry->Prev;
		entryprev->Next = NULL;
	}
	else {
		entryprev->Next = entrynext;
		entrynext->Prev = entryprev;
	}

	entry->Next = NULL;
	entry->Prev = NULL;

	Player *player = entry->Player;

	entry->Player = NULL;

	entry->pList = NULL;

	free(entry);

	pList->Length--;


	return player;
}


void DeletePlayerEntry(PLIST *pList, int index){
	PENTRY *entry = pList->First;

	if (index < 0 || index >= pList->Length){
		return;
	}

	for (int i = 0; i < index; i++){
		entry = entry->Next;
	}

	PENTRY *entryprev = entry->Prev;
	PENTRY *entrynext = entry->Next;

	if (pList->Length == 1){
		pList->Last = NULL;
		pList->First = NULL;
	}
	else if (index == 0){
		pList->First = entry->Next;
		entrynext->Prev = NULL;
	}
	else if (index == pList->Length - 1){
		pList->Last = entry->Prev;
		entryprev->Next = NULL;
	}
	else {
		entryprev->Next = entrynext;
		entrynext->Prev = entryprev;
	}

	entry->Next = NULL;
	entry->Prev = NULL;

	if (entry->Player != NULL){
		DeletePlayer(entry->Player);
		entry->Player = NULL;
	}

	entry->pList = NULL;

	free(entry);

	pList->Length--;
}


PENTRY *GetPlayerEntry(PLIST *pList, int index){
	PENTRY *entry = pList->First;

	if (index < 0 || index >= pList->Length){
		return NULL;
	}

	for (int i = 0; i < index; i++){
		entry = entry->Next;
	}

	return entry;
}




