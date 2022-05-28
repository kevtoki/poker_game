#include <stdio.h>
#include "Game.h"
#include "PlayerList.h"
#include "Deck.h"
#include "Server.h"

int main(){
	Connection *conn = CreateConnection(10190);
	OpenConnection(conn);
	printf("%s", ReadConnection(conn));
	DeleteConnection(conn);
	// GameLoop();
	return 0;
}
