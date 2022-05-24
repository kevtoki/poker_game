# Variables
VERSION = Alpha
SOURCE_PATH = ./src/
COMPILE_PATH = ./bin/
OPTIONS = gcc -Wall -std=c11
CFLAGS = -g


# Default Target
.DEFAULT_GOAL := $(COMPILE_PATH)pkaces


########## Generate object files ##########
# Target for pkaces.o
$(COMPILE_PATH)pkaces.o: $(SOURCE_PATH)pkaces.c
	$(OPTIONS) $(CFLAGS) -c $(SOURCE_PATH)pkaces.c -o $(COMPILE_PATH)pkaces.o

# Target for Card.o
$(COMPILE_PATH)Card.o: $(SOURCE_PATH)Card.c
	$(OPTIONS) $(CFLAGS) -c $(SOURCE_PATH)Card.c -o $(COMPILE_PATH)Card.o

# Target for Deck.o
$(COMPILE_PATH)Deck.o: $(SOURCE_PATH)Deck.c
	$(OPTIONS) $(CFLAGS) -c $(SOURCE_PATH)Deck.c -o $(COMPILE_PATH)Deck.o

# Target for Player.o
$(COMPILE_PATH)Player.o: $(SOURCE_PATH)Player.c
	$(OPTIONS) $(CFLAGS) -c $(SOURCE_PATH)Player.c -o $(COMPILE_PATH)Player.o

# Target for Game.o
$(COMPILE_PATH)Game.o: $(SOURCE_PATH)Game.c
	$(OPTIONS) $(CFLAGS) -c $(SOURCE_PATH)Game.c -o $(COMPILE_PATH)Game.o

# Target for PlayerList.o
$(COMPILE_PATH)PlayerList.o: $(SOURCE_PATH)PlayerList.c
	$(OPTIONS) $(CFLAGS) -c $(SOURCE_PATH)PlayerList.c -o $(COMPILE_PATH)PlayerList.o


########## Generate the executable ########
# Target for pkaces
$(COMPILE_PATH)pkaces: $(COMPILE_PATH)pkaces.o $(COMPILE_PATH)Card.o $(COMPILE_PATH)Deck.o $(COMPILE_PATH)Player.o $(COMPILE_PATH)Game.o $(COMPILE_PATH)PlayerList.o
	$(OPTIONS) $(CFLAGS) $(COMPILE_PATH)pkaces.o $(COMPILE_PATH)Card.o $(COMPILE_PATH)Deck.o $(COMPILE_PATH)Player.o $(COMPILE_PATH)Game.o $(COMPILE_PATH)PlayerList.o -o $(COMPILE_PATH)pkaces
	make obj_clean


########## Other functions ################
# Target for clean up
clean:
	make obj_clean
	rm -f $(COMPILE_PATH)pkaces

# Target for object file clean up
obj_clean:
	rm -f $(COMPILE_PATH)pkaces.o
	rm -f $(COMPILE_PATH)Card.o
	rm -f $(COMPILE_PATH)Deck.o
	rm -f $(COMPILE_PATH)Player.o
	rm -f $(COMPILE_PATH)Game.o
	rm -f $(COMPILE_PATH)PlayerList.o

# Target for tar
tar:
	tar -czvf ../Poker_$(VERSION)_src.tar.gz .

# Target for tar user
tar_user:
	tar --exclude='./src' --exclude='./doc/Poker_SoftwareSpec.pdf' --exclude='./Makefile' -czvf ../Poker_$(VERSION).tar.gz .
