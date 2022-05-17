#ifndef CARD_H
#define CARD_H

enum Suit{spade, clubs, diamonds, hearts};
enum Rank{ace, two, three, four, five, six, seven, eight, nine, ten, jack, queen, king};
struct Card
{
	Suit suit;
	Rank rank;
}


#endif
