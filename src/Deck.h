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

void EmptyDeck(DECK *deck);

void AppendDeckEntry(DECK *deck, Card *card);

void DeleteDeckEntry(DECK *deck, int index);

void SwapDeckEntryPositions(DECK *deck, int index1, int index2);

Card *GetCard(DECK *deck, int index);

void TransferCard(DECK *from, DECK *to, int index);

#endif
