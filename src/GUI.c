#include <gtk/gtk.h>
#include "GUI.h"

#define WIDTH 640
#define HEIGHT 480

Window *CreateWindow(){
	Window *window = (Window *) malloc(sizeof(Window));

    window->windowGTK = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    gtk_window_set_title(GTK_WINDOW(window->windowGTK), "Pocket Aces");

    gtk_window_set_default_size(GTK_WINDOW(window->windowGTK), WIDTH, HEIGHT);

	g_signal_connect(window->windowGTK, "destroy", G_CALLBACK(gtk_main_quit), NULL);

	window->table = gtk_table_new(2, 5, TRUE);
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

	gtk_widget_show_all(window->windowGTK);

	return window;
}
