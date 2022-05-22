#ifndef CARD_H
#define CARD_H

typedef enum {SPADE, CLUBS, DIAMONDS, HEARTS} Suit;
typedef enum {ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING} Rank;

typedef struct
{
	Suit suit;
	Rank rank;
} Card;



Card *CreateCard(Suit suit, Rank rank);

void DestroyCard(Card *card);

#endif
