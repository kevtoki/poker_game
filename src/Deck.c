#include "Deck.h"
#include "Card.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>


DECK *CreateDeck(){
	DECK *deck = (DECK *) malloc(sizeof(DECK));
	deck->First = NULL;
	deck->Last = NULL;
	deck->Length = 0;
	return deck;
}

void DeleteDeck(DECK *deck){
	EmptyDeck(deck);
	
	deck->Last = NULL;
	deck->First = NULL;	
	free(deck);
}

void FillDeck(DECK *deck){
	Rank rank = ACE;
	Suit suit = SPADE;  
	
	for (int i = 0; i < 13; i++){
		for (int j = 0; j < 4; j++){
			AppendDeckEntry(deck, CreateCard(suit + i, rank + j));
		}
	}
}

void ShuffleDeck(DECK *deck){
	int shuffleDepth = 100;
	srand((unsigned) time(NULL));

	for (int i = 0; i < shuffleDepth; i++){
		int rand1 = rand() % deck->Length;
		int rand2 = rand() % deck->Length;

		SwapDeckEntryPositions(deck, rand1, rand2);
	}
}

void EmptyDeck(DECK *deck){
	int tempLength = deck->Length;

	for (int i = 0; i < tempLength; i++){
		DeleteDeckEntry(deck, 0);
	}

}

void AppendDeckEntry(DECK *deck, Card *card){
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

void DeleteDeckEntry(DECK *deck, int index){
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

void SwapDeckEntryPositions(DECK *deck, int index1, int index2){
	if (index1 < 0 || index1 >= deck->Length){
		return;
	}

	if (index2 < 0 || index2 >= deck->Length){
		return;
	}

	if (index1 == index2){
		return;
	}

	DENTRY *entry1 = deck->First;
	DENTRY *entry2 = deck->First;
	
	for (int i = 0; i < index1; i++){
		entry1 = entry1->Next;
	}

	for (int i = 0; i < index2; i++){
		entry2 = entry2->Next;
	}

	{
		DENTRY *temp = entry2->Next;
		entry2->Next = entry1->Next;
		entry1->Next = temp;

		temp = entry2->Prev;
		entry2->Prev = entry1->Prev;
		entry1->Prev = temp;
	
	}

	if (index1 == 0){
		deck->First = entry2;
	}
	else if (index1 == (deck->Length - 1)){
		deck->Last = entry2;
	}

	if (index2 == 0){
		deck->Last = entry1;
	}
	else if (index2 == (deck->Length - 1)){
		deck->Last = entry1;
	}

}


Card *GetCard(DECK *deck, int index){
	DENTRY *entry = deck->First;

	if (index < 0 || index >= deck->Length){
		return NULL;
	}


	for (int i = 0; i < index; i++){
		entry = entry->Next;
	}

	return entry->Card;
}


void TransferCard(DECK *from, DECK *to, int index){
	Card *card = GetCard(from, index);
	Card *clone = CloneCard(card);

	DeleteDeckEntry(from, index);

	AppendDeckEntry(to, clone);
}

