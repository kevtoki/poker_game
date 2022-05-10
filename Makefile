# Variables
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


########## Generate the executable ########
# Target for pkaces
$(COMPILE_PATH)pkaces: $(COMPILE_PATH)pkaces.o
	$(OPTIONS) $(CFLAGS) $(COMPILE_PATH)pkaces.o -o $(COMPILE_PATH)pkaces


########## Other functions ################
# Target for clean up
clean:
	rm -f $(COMPILE_PATH)pkaces.o
	rm -f $(COMPILE_PATH)pkaces


# Target for tar
tar:
	tar -czvf ../Poker_Alpha.tar.gz .
