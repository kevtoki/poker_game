#ifndef GUI_H
#define GUI_H

#include <gtk/gtk.h>

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
} Window;

Window *CreateWindow();

#endif
