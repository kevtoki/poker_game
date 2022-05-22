#include "Deck.h"
#include "Card.h"
#include <stdlib.h>



DECK *CreateDeck(){
	DECK *deck = malloc(sizeof(DECK));
	deck->First = NULL;
	deck->Last = NULL;
	deck->Length = 0;
	return deck;
}

void DeleteDeck(DECK *deck){
	

}

void FillDeck(DECK *deck){


}

void ShuffleDeck(DECK *deck){


}

void AppendEntry(Card *card){


}

void RemoveEntry(int index){


}
