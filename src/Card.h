#ifndef CARD_H
#define CARD_H

typedef enum {SPADE = 1, CLUBS, DIAMONDS, HEARTS} Suit;
typedef enum {TWO = 2, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE} Rank;

typedef struct {
	Suit suit;
	Rank rank;
} Card;



Card *CreateCard(Suit suit, Rank rank);

Card *CloneCard(Card *card);

void DeleteCard(Card *card);


#endif
