# Compiler flags for GTK usage
GTKINC  = `pkg-config --cflags gtk+-2.0`
GTKLIBS = `pkg-config --libs gtk+-2.0`


# Variables
VERSION = Beta
SOURCE_PATH = ./src/
COMPILE_PATH = ./bin/
COPTIONS = gcc -Wall -std=c11 $(GTKINC)
LOPTIONS = gcc -Wall -std=c11 $(GTKLIBS) -lm
CFLAGS = -g


# Default Target
.DEFAULT_GOAL := all


########## Generate object files ##########
# Target for pkaces_server.o
$(COMPILE_PATH)pkaces_server.o: $(SOURCE_PATH)pkaces_server.c
	$(COPTIONS) $(CFLAGS) -c $(SOURCE_PATH)pkaces_server.c -o $(COMPILE_PATH)pkaces_server.o

# Target for pkaces_client.o
$(COMPILE_PATH)pkaces_client.o: $(SOURCE_PATH)pkaces_client.c
	$(COPTIONS) $(CFLAGS) -c $(SOURCE_PATH)pkaces_client.c -o $(COMPILE_PATH)pkaces_client.o

# Target for Card.o
$(COMPILE_PATH)Card.o: $(SOURCE_PATH)Card.c
	$(COPTIONS) $(CFLAGS) -c $(SOURCE_PATH)Card.c -o $(COMPILE_PATH)Card.o

# Target for Deck.o
$(COMPILE_PATH)Deck.o: $(SOURCE_PATH)Deck.c
	$(COPTIONS) $(CFLAGS) -c $(SOURCE_PATH)Deck.c -o $(COMPILE_PATH)Deck.o

# Target for Player.o
$(COMPILE_PATH)Player.o: $(SOURCE_PATH)Player.c
	$(COPTIONS) $(CFLAGS) -c $(SOURCE_PATH)Player.c -o $(COMPILE_PATH)Player.o

# Target for Game.o
$(COMPILE_PATH)Game.o: $(SOURCE_PATH)Game.c
	$(COPTIONS) $(CFLAGS) -c $(SOURCE_PATH)Game.c -o $(COMPILE_PATH)Game.o

# Target for PlayerList.o
$(COMPILE_PATH)PlayerList.o: $(SOURCE_PATH)PlayerList.c
	$(COPTIONS) $(CFLAGS) -c $(SOURCE_PATH)PlayerList.c -o $(COMPILE_PATH)PlayerList.o

# Target for Server.o
$(COMPILE_PATH)Server.o: $(SOURCE_PATH)Server.c
	$(COPTIONS) $(CFLAGS) -c $(SOURCE_PATH)Server.c -o $(COMPILE_PATH)Server.o

# Target for Client.o
$(COMPILE_PATH)Client.o: $(SOURCE_PATH)Client.c
	$(COPTIONS) $(CFLAGS) -c $(SOURCE_PATH)Client.c -o $(COMPILE_PATH)Client.o

# Target for Ranking.o
$(COMPILE_PATH)Ranking.o: $(SOURCE_PATH)Ranking.c
	$(COPTIONS) $(CFLAGS) -c $(SOURCE_PATH)Ranking.c -o $(COMPILE_PATH)Ranking.o

# Target for GUI.o
$(COMPILE_PATH)GUI.o: $(SOURCE_PATH)GUI.c
	$(COPTIONS) $(CFLAGS) -c $(SOURCE_PATH)GUI.c -o $(COMPILE_PATH)GUI.o


########## Generate the executable ########
# Target for pkaces_server
server: $(COMPILE_PATH)pkaces_server.o $(COMPILE_PATH)Card.o $(COMPILE_PATH)Deck.o $(COMPILE_PATH)Player.o $(COMPILE_PATH)Game.o $(COMPILE_PATH)PlayerList.o $(COMPILE_PATH)Server.o $(COMPILE_PATH)Ranking.o
	$(LOPTIONS) $(CFLAGS) $(COMPILE_PATH)pkaces_server.o $(COMPILE_PATH)Card.o $(COMPILE_PATH)Deck.o $(COMPILE_PATH)Player.o $(COMPILE_PATH)Game.o $(COMPILE_PATH)PlayerList.o $(COMPILE_PATH)Server.o $(COMPILE_PATH)Ranking.o -o $(COMPILE_PATH)pkaces_server
	make obj_clean

# Target for pkaces_client
client: $(COMPILE_PATH)pkaces_client.o $(COMPILE_PATH)Client.o $(COMPILE_PATH)Card.o $(COMPILE_PATH)Deck.o $(COMPILE_PATH)GUI.o
	$(LOPTIONS) $(CFLAGS) $(COMPILE_PATH)pkaces_client.o $(COMPILE_PATH)Client.o $(COMPILE_PATH)Card.o $(COMPILE_PATH)Deck.o $(COMPILE_PATH)GUI.o -o $(COMPILE_PATH)pkaces_client
	make obj_clean


########## Other functions ################
#Target to make both server and client
all:
	make server
	make client

# Target for clean up
clean:
	make obj_clean
	rm -f $(COMPILE_PATH)pkaces_server

# Target for object file clean up
obj_clean:
	rm -f $(COMPILE_PATH)pkaces_server.o
	rm -f $(COMPILE_PATH)pkaces_client.o
	rm -f $(COMPILE_PATH)Card.o
	rm -f $(COMPILE_PATH)Deck.o
	rm -f $(COMPILE_PATH)Player.o
	rm -f $(COMPILE_PATH)Game.o
	rm -f $(COMPILE_PATH)PlayerList.o
	rm -f $(COMPILE_PATH)Server.o
	rm -f $(COMPILE_PATH)Client.o
	rm -f $(COMPILE_PATH)GUI.o
	rm -f $(COMPILE_PATH)Ranking.o

# Target for tar
tar:
	tar -czvf ../Poker_$(VERSION)_src.tar.gz .

# Target for tar user
tar_user:
	tar --exclude='./src' --exclude='./doc/Poker_SoftwareSpec.pdf' --exclude='./Makefile' -czvf ../Poker_$(VERSION).tar.gz .
