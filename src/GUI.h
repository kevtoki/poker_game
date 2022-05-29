#ifndef GUI_H
#define GUI_H

// creates the window where each part of the game info is printed on
void createWindow(int argc, char *argv[]);

// updates the cards the dealer has
void updateCards();

// updates the amount of points each rival player has
void updateEnemyPoints();

// updates the cards and the amount of points the player has
void updatePlayerPoints();

// the callback function for the call button (performs call)
void callButton(GtkWidget *widget, gpointer data);

// the callback function for the raise button (performs raise)
void raiseButton(GtkWidget *widget, gpointer data);

// the callback function for the hold button (performs hold)
void holdButton(GtkWidget *widget, gpointer data);

#endif
