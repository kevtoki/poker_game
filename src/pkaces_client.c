#include <stdio.h>
#include <stdlib.h>
#include "Client.h"


int main(){

	ServerConnection *conn = CreateServerConnection("crystalcove.eecs.uci.edu", 10190);

	char msg[256];
	scanf("%s", msg);

	WriteServerConnection(conn, msg);
	DeleteServerConnection(conn);
	return 0;
}
