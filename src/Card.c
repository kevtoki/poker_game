#include "Card.h"
#include <stdlib.h>


Card *CreateCard(Suit suit, Rank rank){
	Card *card = malloc(sizeof(Card));
	card->suit = suit;
	card->rank = rank;

	return card;
}

void DeleteCard(Card *card){
	free(card);

	card = NULL;
}
