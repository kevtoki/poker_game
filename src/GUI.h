#ifndef GUI_H
#define GUI_H

#include <gtk/gtk.h>
#include "Client.h"

typedef struct {
	GtkWidget *windowGTK;
	GtkWidget *table;

	GtkWidget *dealerCard1;
	GtkWidget *dealerCard2;
	GtkWidget *dealerCard3;
	GtkWidget *dealerCard4;
	GtkWidget *dealerCard5;

	GtkWidget *playerCard1;
	GtkWidget *playerCard2;

	GtkWidget *refreshBtn;
    GtkWidget *refreshAlign;

	ClientGame *game;
} GameWindow;

GameWindow *CreateGameWindow(ClientGame *game);

void DeleteGameWindow(GameWindow *window);

void RefreshGameWindow(GtkButton *button, gpointer user_data);

void Call(GameWindow *window);

void Raise(GameWindow *window);

void Fold(GameWindow *window);

#endif
