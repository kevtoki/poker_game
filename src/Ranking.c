#include "Ranking.h"
#include "Card.h"
#include "Deck.h"
#include "Player.h"

int RankHand(DECK *boardCards, Player *player){
	DECK *playerDeck = player->deck;
	if (RoyalFlush(boardCards, playerDeck)){
		return 100;
	}
	if (StraightFlush(boardCards, playerDeck)){
		return 95;
	}
	if (FourOfAKind(boardCards, playerDeck)){
		return 90;
	}
	if (FullHouse(boardCards, playerDeck)){
		return 85;
	}
	if (Flush(boardCards, playerDeck)){
		return 80;
	}
	if (Straight(boardCards, playerDeck)){
		return 75;
	}
	if (ThreeOfAKind(boardCards, playerDeck)){
		return 70;
	}
	if (TwoPair(boardCards, playerDeck)){
		return 65;
	}
	if (OnePair(boardCards, playerDeck)){
		return 60;
	}


	return HighCard(playerDeck);
}


int RoyalFlush(DECK *deck1, DECK *deck2){
	int *frequencyListRank = GenerateFrequencyListRank(deck1, deck2);
	int *frequencyListSuit = GenerateFrequencyListSuit(deck1, deck2);

	int isEligible = 0;

	for (int i = 0; i < 4; i++){
		if (frequencyListSuit[i] > 4){
			isEligible = 1;
		}
	}

	if (!isEligible){
		return 0;
	}

	if (frequencyListRank[8] && frequencyListRank[9] && frequencyListRank[10] && frequencyListRank[11] && frequencyListRank[12]){
		DeleteFrequencyList(frequencyListRank);
		DeleteFrequencyList(frequencyListSuit);
		return 1;
	}

	DeleteFrequencyList(frequencyListRank);
	DeleteFrequencyList(frequencyListSuit);
	
	return 0;
}


int StraightFlush(DECK *deck1, DECK *deck2){
	int *frequencyListRank = GenerateFrequencyListRank(deck1, deck2);
	int *frequencyListSuit = GenerateFrequencyListSuit(deck1, deck2);

	int isEligible = 0;

	for (int i = 0; i < 4; i++){
		if (frequencyListSuit[i] > 4){
			isEligible = 1;
		}
	}

	if (!isEligible){
		return 0;
	}

	for (int i = 0; i < 9; i++){
		if (frequencyListRank[i] && frequencyListRank[i + 1] && frequencyListRank[i + 2] && frequencyListRank[i + 3] && frequencyListRank[i + 4]){
			DeleteFrequencyList(frequencyListRank);
			DeleteFrequencyList(frequencyListSuit);
			return 1;
		}
	}

	DeleteFrequencyList(frequencyListRank);
	DeleteFrequencyList(frequencyListSuit);
	
	return 0;
}


int FourOfAKind(DECK *deck1, DECK *deck2){
	int *frequencyListRank = GenerateFrequencyListRank(deck1, deck2);


	for (int i = 0; i < 13; i++){
		if (frequencyListRank[i] > 3){
			DeleteFrequencyList(frequencyListRank);
			return 1;
		}
	}

	DeleteFrequencyList(frequencyListRank);
	return 0;
}


int FullHouse(DECK *deck1, DECK *deck2){
	int *frequencyListRank = GenerateFrequencyListRank(deck1, deck2);

	for (int i = 0; i < 13; i++){
		for (int j = 0; j < 13; j++){
			if (frequencyListRank[i] == 3 && frequencyListRank[j] == 2){
				return 1;
			}
		}
	}

	return 0;
}


int Flush(DECK *deck1, DECK *deck2){
	int *frequencyListSuit = GenerateFrequencyListSuit(deck1, deck2);

	for (int i = 0; i < 4; i++){
		if (frequencyListSuit[i] > 4){
			DeleteFrequencyList(frequencyListSuit);
			return 1;
		}
	}

	DeleteFrequencyList(frequencyListSuit);
	return 0;
}


int Straight(DECK *deck1, DECK *deck2){
	int *frequencyListRank = GenerateFrequencyListRank(deck1, deck2);

	for (int i = 0; i < 9; i++){
		if (frequencyListRank[i] && frequencyListRank[i + 1] && frequencyListRank[i + 2] && frequencyListRank[i + 3] && frequencyListRank[i + 4]){
			DeleteFrequencyList(frequencyListRank);
			return 1;
		}
	}

	DeleteFrequencyList(frequencyListRank);
	
	return 0;

}


int ThreeOfAKind(DECK *deck1, DECK *deck2){
	int *frequencyListRank = GenerateFrequencyListRank(deck1, deck2);


	for (int i = 0; i < 13; i++){
		if (frequencyListRank[i] > 2){
			DeleteFrequencyList(frequencyListRank);
			return 1;
		}
	}

	DeleteFrequencyList(frequencyListRank);
	return 0;
}


int TwoPair(DECK *deck1, DECK *deck2){
	int *frequencyListRank = GenerateFrequencyListRank(deck1, deck2);

	int pairs = 0;

	for (int i = 0; i < 13; i++){
		if (frequencyListRank[i] > 1){
			pairs++;
		}
	}

	if (pairs == 2){
		DeleteFrequencyList(frequencyListRank);
		return 1;
	}

	DeleteFrequencyList(frequencyListRank);
	return 0;
}


int OnePair(DECK *deck1, DECK *deck2){
	int *frequencyListRank = GenerateFrequencyListRank(deck1, deck2);


	for (int i = 0; i < 13; i++){
		if (frequencyListRank[i] > 1){
			DeleteFrequencyList(frequencyListRank);
			return 1;
		}
	}

	DeleteFrequencyList(frequencyListRank);
	return 0;
}


int HighCard(DECK *deck1){
	int highValue = 0;

	DENTRY *entry = deck1->First;

	for (int i = 0; i < deck1->Length; i++){
		if (entry->Card->rank > highValue){
			highValue = entry->Card->rank;
		}

		entry = entry->Next;
	}

	return highValue;
}


int *GenerateFrequencyListSuit(DECK *deck1, DECK *deck2){
	int *frequencyList = (int *) malloc((sizeof(int) * 4));

	memset(frequencyList, 0, sizeof(frequencyList) / sizeof(int));


	DENTRY *entry = deck1->First;

	for (int i = 0; i < deck1->Length; i++){
		frequencyList[entry->Card->suit - 1]++;
		entry = entry->Next;
	}

	entry = deck2->First;

	for (int i = 0; i < deck2->Length; i++){
		frequencyList[entry->Card->suit]++;
		entry = entry->Next;
	}

	return frequencyList;
}


int *GenerateFrequencyListRank(DECK *deck1, DECK *deck2){
	int *frequencyList = (int *) malloc((sizeof(int) * 13));

	memset(frequencyList, 0, sizeof(frequencyList) / sizeof(int));


	DENTRY *entry = deck1->First;

	for (int i = 0; i < deck1->Length; i++){
		frequencyList[entry->Card->rank - 2]++;
		entry = entry->Next;
	}

	entry = deck2->First;

	for (int i = 0; i < deck2->Length; i++){
		frequencyList[entry->Card->rank - 2]++;
		entry = entry->Next;
	}

	return frequencyList;
}


void DeleteFrequencyList(int *frequencyList){

	free(frequencyList);
}
