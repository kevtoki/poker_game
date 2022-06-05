#include <gtk/gtk.h>
#include <stdlib.h>
#include "GUI.h"
#include "Client.h"


#define WIDTH 640
#define HEIGHT 480

GameWindow *CreateGameWindow(ClientGame *game){
	GameWindow *window = (GameWindow *) malloc(sizeof(GameWindow));

    window->windowGTK = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    gtk_window_set_title(GTK_WINDOW(window->windowGTK), "Pocket Aces");

    gtk_window_set_default_size(GTK_WINDOW(window->windowGTK), WIDTH, HEIGHT);

	g_signal_connect(window->windowGTK, "destroy", G_CALLBACK(gtk_main_quit), NULL);

	window->table = gtk_table_new(3, 5, TRUE);
	gtk_container_add(GTK_CONTAINER(window->windowGTK), window->table);

	window->dealerCard1 = gtk_image_new_from_file("assets/images/back.jpg");
	gtk_table_attach_defaults(GTK_TABLE(window->table), window->dealerCard1, 0, 1, 0, 1);

	window->dealerCard2 = gtk_image_new_from_file("assets/images/back.jpg");
	gtk_table_attach_defaults(GTK_TABLE(window->table), window->dealerCard2, 1, 2, 0, 1);

	window->dealerCard3 = gtk_image_new_from_file("assets/images/back.jpg");
	gtk_table_attach_defaults(GTK_TABLE(window->table), window->dealerCard3, 2, 3, 0, 1);

	window->dealerCard4 = gtk_image_new_from_file("assets/images/back.jpg");
	gtk_table_attach_defaults(GTK_TABLE(window->table), window->dealerCard4, 3, 4, 0, 1);

	window->dealerCard5 = gtk_image_new_from_file("assets/images/back.jpg");
	gtk_table_attach_defaults(GTK_TABLE(window->table), window->dealerCard5, 4, 5, 0, 1);

	window->playerCard1 = gtk_image_new_from_file("assets/images/back.jpg");
	gtk_table_attach_defaults(GTK_TABLE(window->table), window->playerCard1, 1, 2, 1, 2);

	window->playerCard2 = gtk_image_new_from_file("assets/images/back.jpg");
	gtk_table_attach_defaults(GTK_TABLE(window->table), window->playerCard2, 3, 4, 1, 2);

	window->refreshAlign = gtk_alignment_new(0.5, 0.5, 0, 0);
	window->refreshBtn = gtk_button_new_with_label("Refresh");
    gtk_widget_set_size_request(window->refreshBtn, 100, 60);
    gtk_container_add(GTK_CONTAINER(window->refreshAlign), window->refreshBtn);
    gtk_table_attach_defaults(GTK_TABLE(window->table), window->refreshAlign, 2, 3, 2, 3);

	g_signal_connect(window->refreshBtn, "clicked", G_CALLBACK(RefreshGameWindow), window);

	gtk_widget_show_all(window->windowGTK);

	window->game = game;

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

	HandlePacket(gameWindow->game, gameWindow->game->user, gameWindow->game->user->connection);

}


void Call(GameWindow *window){


}


void Raise(GameWindow *gameWindow){


	GtkWidget *window;
	GtkWidget *table;
	GtkWidget *entry;    
	GtkWidget *label;

	g_print("Raise\n");
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "Raise");
	gtk_window_set_default_size(GTK_WINDOW(window), 200, 120);
	table = gtk_table_new(2, 1, TRUE);
	label = gtk_label_new("Please enter the amount you want to raise.\n");
	entry = gtk_entry_new();
	gtk_container_add(GTK_CONTAINER(window), table);
	gtk_table_attach_defaults(GTK_TABLE(table), label, 0, 1, 0, 1);
	gtk_table_attach_defaults(GTK_TABLE(table), entry, 0, 1, 1, 2);

	gtk_widget_show_all(window);

	int raise_amount = atoi(gtk_entry_get_text(GTK_ENTRY(entry)));

	SendPacket(gameWindow->game, 'r', raise_amount);
}


void Fold(GameWindow *gameWindow){



}
