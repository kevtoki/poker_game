#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "GUI.h"
#include "Client.h"
#include "Card.h"

#define WIDTH 640
#define HEIGHT 480

GameWindow *CreateGameWindow(ClientGame *game){
	GameWindow *window = (GameWindow *) malloc(sizeof(GameWindow));

	char *path = (char *) malloc(1000);

	bzero(path, 1000);

    window->windowGTK = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    gtk_window_set_title(GTK_WINDOW(window->windowGTK), "Pocket Aces");

    gtk_window_set_default_size(GTK_WINDOW(window->windowGTK), WIDTH, HEIGHT);

	g_signal_connect(window->windowGTK, "destroy", G_CALLBACK(gtk_main_quit), NULL);

	window->table = gtk_table_new(3, 5, TRUE);
	gtk_container_add(GTK_CONTAINER(window->windowGTK), window->table);

	CardToFilePath(path, GetCard(game->boardCards, 0));

	window->dealerCard1 = gtk_image_new_from_file(path);
	gtk_table_attach_defaults(GTK_TABLE(window->table), window->dealerCard1, 0, 1, 0, 1);

	bzero(path, 1000);

	CardToFilePath(path, GetCard(game->boardCards, 1));

	window->dealerCard2 = gtk_image_new_from_file(path);
	gtk_table_attach_defaults(GTK_TABLE(window->table), window->dealerCard2, 1, 2, 0, 1);

	bzero(path, 1000);

	CardToFilePath(path, GetCard(game->boardCards, 2));

	window->dealerCard3 = gtk_image_new_from_file(path);
	gtk_table_attach_defaults(GTK_TABLE(window->table), window->dealerCard3, 2, 3, 0, 1);

	bzero(path, 1000);

	CardToFilePath(path, GetCard(game->boardCards, 3));

	window->dealerCard4 = gtk_image_new_from_file(path);
	gtk_table_attach_defaults(GTK_TABLE(window->table), window->dealerCard4, 3, 4, 0, 1);

	bzero(path, 1000);

	CardToFilePath(path, GetCard(game->boardCards, 4));

	window->dealerCard5 = gtk_image_new_from_file(path);
	gtk_table_attach_defaults(GTK_TABLE(window->table), window->dealerCard5, 4, 5, 0, 1);

	bzero(path, 1000);

	CardToFilePath(path, game->user->card1);

	window->playerCard1 = gtk_image_new_from_file(path);
	gtk_table_attach_defaults(GTK_TABLE(window->table), window->playerCard1, 1, 2, 1, 2);

	bzero(path, 1000);

	CardToFilePath(path, game->user->card2);

	window->playerCard2 = gtk_image_new_from_file(path);
	gtk_table_attach_defaults(GTK_TABLE(window->table), window->playerCard2, 3, 4, 1, 2);

	window->refreshAlign = gtk_alignment_new(0.5, 0.5, 0, 0);
	window->refreshBtn = gtk_button_new_with_label("Refresh");
    gtk_widget_set_size_request(window->refreshBtn, 100, 60);
    gtk_container_add(GTK_CONTAINER(window->refreshAlign), window->refreshBtn);
    gtk_table_attach_defaults(GTK_TABLE(window->table), window->refreshAlign, 2, 3, 2, 3);

	g_signal_connect(window->refreshBtn, "clicked", G_CALLBACK(RefreshGameWindow), window);

	gtk_widget_show_all(window->windowGTK);

	window->game = game;

	free(path);

	return window;
}


void DeleteGameWindow(GameWindow *window){
	gtk_widget_destroy(window->table);
	free(window);
}

void RefreshGameWindow(GtkButton *button, gpointer user_data){

	GameWindow *gameWindow = user_data;

	if (gameWindow->game->canRefresh != 1){
		return;
	}

	
	char *path = (char *) malloc(1000);
	
	bzero(path, 1000);

	HandlePacket(gameWindow->game, gameWindow->game->user, gameWindow->game->user->connection);

	CardToFilePath(path, GetCard(gameWindow->game->boardCards, 0));

	gtk_image_set_from_file(GTK_IMAGE(gameWindow->dealerCard1), path);

	bzero(path, 1000);

	CardToFilePath(path, GetCard(gameWindow->game->boardCards, 1));

	gtk_image_set_from_file(GTK_IMAGE(gameWindow->dealerCard2), path);

	bzero(path, 1000);

	CardToFilePath(path, GetCard(gameWindow->game->boardCards, 2));

	gtk_image_set_from_file(GTK_IMAGE(gameWindow->dealerCard3), path);

	bzero(path, 1000);

	CardToFilePath(path, GetCard(gameWindow->game->boardCards, 3));

	gtk_image_set_from_file(GTK_IMAGE(gameWindow->dealerCard4), path);

	bzero(path, 1000);

	CardToFilePath(path, GetCard(gameWindow->game->boardCards, 4));

	gtk_image_set_from_file(GTK_IMAGE(gameWindow->dealerCard5), path);
	
	bzero(path, 1000);

	CardToFilePath(path, gameWindow->game->user->card1);

	gtk_image_set_from_file(GTK_IMAGE(gameWindow->playerCard1), path);

	bzero(path,1000);

	CardToFilePath(path, gameWindow->game->user->card2);

	gtk_image_set_from_file(GTK_IMAGE(gameWindow->playerCard2), path);

	free(path);
	
	gtk_widget_show_all(gameWindow->windowGTK);

	if (gameWindow->game->connectionBuffer[1] == 1){
		HandleUserInput(gameWindow->game, gameWindow->game->user);
	}

}


void CardToFilePath(char *path, Card *card){
	char *basePathDefault = "assets/images/back.jpg";
	char *basePathStart = "assets/images/";
	char *basePathEnd = ".jpg";
	char *suitStr = (char *) malloc(1000);
	char *rankStr = (char *) malloc(1000);

	bzero(suitStr, 1000);
	bzero(rankStr, 1000);


	if (card == NULL){
		path = strcpy(path, basePathDefault);
		return;
	}

	switch (card->suit){
		case 1:
			suitStr = "spades";			
			break;

		case 2:
			suitStr = "clubs";
			break;

		case 3:
			suitStr = "diamonds";
			break;

		case 4:
			suitStr = "hearts";
			break;

		default:
			suitStr = "null";
			break;
	}

	switch (card->rank){
		case 2:
			rankStr = "2";
			break;

		case 3:
			rankStr = "3";
			break;

		case 4:
			rankStr = "4";
			break;

		case 5:
			rankStr = "5";
			break;

		case 6:
			rankStr = "6";
			break;

		case 7:
			rankStr = "7";
			break;

		case 8:
			rankStr = "8";
			break;

		case 9:
			rankStr = "9";
			break;

		case 10:
			rankStr = "10";
			break;

		case 11:
			rankStr = "jack";
			break;

		case 12:
			rankStr = "queen";
			break;

		case 13:
			rankStr = "king";
			break;

		case 14:
			rankStr = "ace";
			break;

		default:
			rankStr = "null";
			break;
	}

	strcat(path, basePathStart);
	strcat(path, rankStr);
	strcat(path, "_");
	strcat(path, "of");
	strcat(path, "_");
	strcat(path, suitStr);
	strcat(path, basePathEnd);


	printf("%s\n", path);
}
