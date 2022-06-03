#include <gtk/gtk.h>

void createWindow(int argc, char *argv[]) {
	
	GtkWidget *window;

	// last row, contains user options
	GtkWidget *callbutton;
	GtkWidget *raisebutton;
	GtkWidget *foldbutton;
	GtkWidget *inputbox;
	
	// first row, contains cards on the table
	GtkWidget *cardone;
	GtkWidget *cardframeone;
	GtkWidget *cardtwo;
	GtkWidget *cardframetwo;
	GtkWidget *cardthree;
	GtkWidget *cardframethree;
	GtkWidget *cardfour;
	GtkWidget *cardframefour;
	GtkWidget *cardfive;
	GtkWidget *cardframefive;
	GtkWidget *cardbox;

	// second row, contains the points of each player
	GtkWidget *playeronepoints;
	GtkWidget *playeronepointsframe;
	GtkWidget *playertwopoints;
	GtkWidget *playertwopointsframe;
	GtkWidget *playerthreepoints;
	GtkWidget *playerthreepointsframe;
	GtkWidget *pointsbox;

	// third row, contains player information
	GtkWidget *playerpoints;
	GtkWidget *playerpointsframe;
	GtkWidget *playercardone;
	GtkWidget *playercardoneframe;
	GtkWidget *playercardtwo;
	GtkWidget *playercardtwoframe;
	GtkWidget *playercardbox;
	GtkWidget *playerbox;
	
	GtkWidget *guiBox;
	
	gtk_init(&argc, &argv);
	
	//creats the set of 5 cards
	cardbox = gtk_hbox_new(GTK_ORIENTATION_HORIZONTAL, 3);
	
	cardframeone = gtk_frame_new("Card One");
	cardone = gtk_label_new("");
	gtk_container_add(GTK_CONTAINER(cardframeone), cardone);

	cardframetwo = gtk_frame_new("Card Two");
	cardtwo = gtk_label_new("");

	gtk_container_add(GTK_CONTAINER(cardframetwo), cardtwo);

	cardframethree = gtk_frame_new("Card Three");
	cardthree = gtk_label_new("");
	gtk_container_add(GTK_CONTAINER(cardframethree), cardthree);

	cardframefour = gtk_frame_new("Card Four");
	cardfour = gtk_label_new("");
	gtk_container_add(GTK_CONTAINER(cardframefour), cardfour);

	cardframefive = gtk_frame_new("Card Five");
	cardfive = gtk_label_new("");
	gtk_container_add(GTK_CONTAINER(cardframefive), cardfive);

	gtk_box_pack_start(GTK_BOX(cardbox), cardframeone, TRUE, TRUE, 10);
	gtk_box_pack_start(GTK_BOX(cardbox), cardframetwo, TRUE, TRUE, 10);
	gtk_box_pack_start(GTK_BOX(cardbox), cardframethree, TRUE, TRUE, 10);
	gtk_box_pack_start(GTK_BOX(cardbox), cardframefour, TRUE, TRUE, 10);
	gtk_box_pack_start(GTK_BOX(cardbox), cardframefive, TRUE, TRUE, 10);

	//creats the row for point values of each player
	pointsbox = gtk_hbox_new(GTK_ORIENTATION_HORIZONTAL, 3);
	
	playeronepointsframe = gtk_frame_new("P1 Points");
	playeronepoints = gtk_label_new("");
	gtk_container_add(GTK_CONTAINER(playeronepointsframe), playeronepoints);

	playertwopointsframe = gtk_frame_new("P2 Points");
	playertwopoints = gtk_label_new("");
	gtk_container_add(GTK_CONTAINER(playertwopointsframe), playertwopoints);
	
	playerthreepointsframe = gtk_frame_new("P3 Points");
	playerthreepoints = gtk_label_new("");
	gtk_container_add(GTK_CONTAINER(playerthreepointsframe), playerthreepoints);
	
	gtk_box_pack_start(GTK_BOX(pointsbox), playeronepointsframe, TRUE, TRUE, 10);
	gtk_box_pack_start(GTK_BOX(pointsbox), playertwopointsframe, TRUE, TRUE, 10);
	gtk_box_pack_start(GTK_BOX(pointsbox), playerthreepointsframe, TRUE, TRUE, 10);
	
	//contains player info
	playercardbox = gtk_hbox_new(GTK_ORIENTATION_HORIZONTAL, 3);
	
	playercardoneframe = gtk_frame_new("My Card 1");
	playercardone = gtk_label_new("");
	gtk_container_add(GTK_CONTAINER(playercardoneframe), playercardone);
	
	playercardtwoframe = gtk_frame_new("My Card 2");
	playercardtwo = gtk_label_new("");
	gtk_container_add(GTK_CONTAINER(playercardtwoframe), playercardtwo);
	
	gtk_box_pack_start(GTK_BOX(playercardbox), playercardoneframe, TRUE, TRUE, 10);
	gtk_box_pack_start(GTK_BOX(playercardbox), playercardtwoframe, TRUE, TRUE, 10);

	playerpointsframe = gtk_frame_new("My Points");
	playerpoints = gtk_label_new("");
	gtk_container_add(GTK_CONTAINER(playerpointsframe), playerpoints);

	playerbox = gtk_hbox_new(GTK_ORIENTATION_HORIZONTAL, 3);
	gtk_box_pack_start(GTK_BOX(playerbox), playercardbox, TRUE, TRUE, 10);
	gtk_box_pack_start(GTK_BOX(playerbox), playerpointsframe, TRUE, TRUE, 10);
	
	inputbox = gtk_hbox_new(GTK_ORIENTATION_HORIZONTAL, 3);
	
	//makes the window
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "Texas Holdem");
	gtk_window_set_default_size(GTK_WINDOW(window), 900, 700);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

	//makes all the buttons for user input
	callbutton = gtk_button_new_with_label("Call");
	g_signal_connect(G_OBJECT(callbutton), "clicked", G_CALLBACK(callButton), (gpointer) "0");
	raisebutton = gtk_button_new_with_label("Raise");
	g_signal_connect(G_OBJECT(raisebutton), "clicked", G_CALLBACK(raiseButton), (gpointer) "0");
	foldbutton = gtk_button_new_with_label("Fold");
	g_signal_connect(G_OBJECT(foldbutton), "clicked", G_CALLBACK(foldButton), (gpointer) "0"); 
	

	gtk_box_pack_start(GTK_BOX(inputbox), callbutton, TRUE, TRUE, 10);
	gtk_box_pack_start(GTK_BOX(inputbox), raisebutton, TRUE, TRUE, 10);
	gtk_box_pack_start(GTK_BOX(inputbox), foldbutton, TRUE, TRUE, 10);
	
	//stacks each row of information
	guiBox = gtk_vbox_new(GTK_ORIENTATION_VERTICAL, 3);
	gtk_box_pack_start(GTK_BOX(guiBox), cardbox, TRUE, TRUE, 10);
	gtk_box_pack_start(GTK_BOX(guiBox), pointsbox, TRUE, TRUE, 10);
	gtk_box_pack_start(GTK_BOX(guiBox), playerbox, TRUE, TRUE, 10);
	gtk_box_pack_start(GTK_BOX(guiBox), inputbox, TRUE, TRUE, 10);

	gtk_container_add(GTK_CONTAINER(window), guiBox);
	
	gtk_widget_show_all(window);

	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

	gtk_main();
}

void updateCards() {
 // using gtk_label_set_text, update the cards the dealer has
}

void updateEnemyPoints() {
 // using gtk_label_set_text, update the points the enemies have bet
}

void updatePlayerInfo() {
 // using gtk_label_set_text, update the info of the player 
}

void callButton(GtkWidget *widget, gpointer data) {
 // call function
}

void raiseButton(GtkWidget *widget, gpointer data) {
 // raise function
}

void holdButton(GtkWidget *widget, gpointer data) {
 // hold function
}
