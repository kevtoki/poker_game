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

	GtkWidget *points;
	GtkWidget *bet;
	GtkWidget *pot;

	GtkWidget *checkCallBtn;
	GtkWidget *checkCallAlign;
	GtkWidget *raiseBtn;
    GtkWidget *raiseAlign;
	GtkWidget *foldBtn;
    GtkWidget *foldAlign;

} Window;

int Raise();

Window *CreateWindow();

#endif
