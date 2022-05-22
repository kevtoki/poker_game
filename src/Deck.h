#ifndef DECK_H
#define DECK_H
#include "Card.h"

typedef struct Deck DECK;
typedef struct DeckEntry DENTRY;


struct Deck {
	DENTRY *First;
	DENTRY *Last;
	int Length;
};


struct DeckEntry {
	Card *Card;
	DECK *Deck;
	DENTRY *Next;
	DENTRY *Prev;
};


DECK *CreateDeck();

void DeleteDeck(DECK *deck);

void FillDeck(DECK *deck);

void ShuffleDeck(DECK *deck);

void AppendEntry(DECK *deck, Card *card);

void DeleteEntry(DECK *deck, int index);



#endif
