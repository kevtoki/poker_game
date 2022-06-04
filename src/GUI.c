#include <gtk/gtk.h>
#include <stdlib.h>
#include "GUI.h"

#define WIDTH 640
#define HEIGHT 480

int Raise(){                                       
	GtkWidget *window;
	GtkWidget *table;
	GtkWidget *entry;    
	GtkWidget *label;

	g_print("Raise\n");
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "Raise");
	gtk_window_set_default_size(GTK_WINDOW(window), 200, 120);
	table = gtk_table_new(2, 1, TRUE);
	label = gtk_label_new("Please enter the amount you want to raise:\n");
	entry = gtk_entry_new();
	gtk_container_add(GTK_CONTAINER(window), table);
	gtk_table_attach_defaults(GTK_TABLE(table), label, 0, 1, 0, 1);
	gtk_table_attach_defaults(GTK_TABLE(table), entry, 0, 1, 1, 2);

	gtk_widget_show_all(window);

	int raise_amount = atoi(gtk_entry_get_text(GTK_ENTRY(entry)));

	return(raise_amount);
}


Window *CreateWindow(){
	Window *window = (Window *) malloc(sizeof(Window));

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

	window->checkCallAlign = gtk_alignment_new(0.5, 0.5, 0, 0);
	window->checkCallBtn = gtk_button_new_with_label("Check/Call");
	gtk_widget_set_size_request(window->checkCallBtn, 100, 60);
	gtk_container_add(GTK_CONTAINER(window->checkCallAlign), window->checkCallBtn);
	gtk_table_attach_defaults(GTK_TABLE(window->table), window->checkCallAlign, 1, 2, 2, 3);

	window->raiseAlign = gtk_alignment_new(0.5, 0.5, 0, 0);
	window->raiseBtn = gtk_button_new_with_label("Raise");
    gtk_widget_set_size_request(window->raiseBtn, 100, 60);
    gtk_container_add(GTK_CONTAINER(window->raiseAlign), window->raiseBtn);
    gtk_table_attach_defaults(GTK_TABLE(window->table), window->raiseAlign, 2, 3, 2, 3);

	window->foldAlign = gtk_alignment_new(0.5, 0.5, 0, 0);
	window->foldBtn = gtk_button_new_with_label("Fold");
    gtk_widget_set_size_request(window->foldBtn, 100, 60);
    gtk_container_add(GTK_CONTAINER(window->foldAlign), window->foldBtn);
    gtk_table_attach_defaults(GTK_TABLE(window->table), window->foldAlign, 3, 4, 2, 3);

	g_signal_connect(window->raiseBtn, "clicked", G_CALLBACK(Raise), NULL);

	window->points = gtk_label_new("Your current points: 20");
	gtk_table_attach_defaults(GTK_TABLE(window->table), window->points, 4, 5, 2, 3);

	window->bet = gtk_label_new("The current bet is: 0");
	gtk_table_attach_defaults(GTK_TABLE(window->table), window->bet, 4, 5, 1, 2);

	window->pot = gtk_label_new("The current pot is: 0");
	gtk_table_attach_defaults(GTK_TABLE(window->table), window->pot, 0, 1, 2, 3);	

	gtk_widget_show_all(window->windowGTK);

	return window;
}

