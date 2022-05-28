#include <stdio.h>
#include <stdlib.h>
#include "Client.h"


int main(){

	ServerConnection *conn = ConnectToServer("crystalcove.eecs.uci.edu", 10190);

	DeleteServerConnection(conn);
	return 0;
}
