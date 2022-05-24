#include "Card.h"
#include <stdlib.h>


Card *CreateCard(Suit suit, Rank rank){
	Card *card = malloc(sizeof(Card));
	card->suit = suit;
	card->rank = rank;

	return card;
}

Card *CloneCard(Card *card){
	Card *clone = CreateCard(card->suit, card->rank);
	return clone;
}

void DeleteCard(Card *card){
	free(card);

	card = NULL;
}
