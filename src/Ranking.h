#ifndef RANKING_H
#define RANKING_H

#include "Card.h"
#include "Deck.h"
#include "Player.h"

int RankHand(DECK *boardCards, Player *player);

int RoyalFlush(DECK *deck1, DECK *deck2);

int StraightFlush(DECK *deck1, DECK *deck2);

int FourOfAKind(DECK *deck1, DECK *deck2);

int FullHouse(DECK *deck1, DECK *deck2);

int Flush(DECK *deck1, DECK *deck2);

int Straight(DECK *deck1, DECK *deck2);

int ThreeOfAKind(DECK *deck1, DECK *deck2);

int TwoPair(DECK *deck1, DECK *deck2);

int OnePair(DECK *deck1, DECK *deck2);

int HighCard(DECK *deck1);

int *GenerateFrequencyListSuit(DECK *deck1, DECK *deck2);

int *GenerateFrequencyListRank(DECK *deck1, DECK *deck2);

void DeleteFrequencyList(int *frequencyList);

#endif
