#include "Deck.h"
#include "Card.h"
#include <stdlib.h>



DECK *CreateDeck(){
	DECK *deck = (DECK *) malloc(sizeof(DECK));
	deck->First = NULL;
	deck->Last = NULL;
	deck->Length = 0;
	return deck;
}

void DeleteDeck(DECK *deck){
	int tempLength = deck->Length;

	for (int i = 0; i < tempLength; i++){
		DeleteEntry(deck , 0);
	}

	
	deck->Last = NULL;
	deck->First = NULL;	
	free(deck);
}

void FillDeck(DECK *deck){
	Rank rank = ACE;
	Suit suit = SPADE;  
	
	for (int i = 0; i < 13; i++){
		for (int j = 0; j < 4; j++){
			AppendEntry(deck, CreateCard(suit + i, rank + j));
		}
	}
}

void ShuffleDeck(DECK *deck){


}

void AppendEntry(DECK *deck, Card *card){
	DENTRY *dEntry = (DENTRY *) malloc(sizeof(DENTRY));

	dEntry->Deck = deck;

	deck->Length++;

	dEntry->Card = card;

	dEntry->Next = NULL;

	if (deck->Length == 1){
		dEntry->Prev = NULL;
		deck->First = dEntry;
	}
	else {
		dEntry->Prev = deck->Last;
		deck->Last->Next = dEntry;
	}


	deck->Last = dEntry;
}

void DeleteEntry(DECK *deck, int index){
	DENTRY *entry = deck->First;

	if (index < 0 || index >= deck->Length){
		return;
	}


	for (int i = 0; i < index; i++){
		entry = entry->Next;
	}

	DENTRY *entryprev = entry->Prev;
	DENTRY *entrynext = entry->Next;

	if (deck->Length == 1){
		deck->Last = NULL;
		deck->First = NULL;
	}
	else if (index == 0){
		deck->First = entry->Next;
		entrynext->Prev = NULL;
	}
	else if (index == deck->Length - 1){
		deck->Last = entry->Prev;
		entryprev->Next = NULL;
	}
	else {
		entryprev->Next = entrynext;
		entrynext->Prev = entryprev;
	}

	entry->Next = NULL;
	entry->Prev = NULL;

	if (entry->Card != NULL){
		DeleteCard(entry->Card);
		entry->Card = NULL;
	}

	entry->Deck = NULL;

	free(entry);

	deck->Length--;
}






