#include <gtk/gtk.h>

#define width 320
#define hight 240

//Callbackfunktion fuer die Buttons
static void button_clicked(GtkWidget *widget, gpointer data){
	//einfache consolenausgabe
	g_print("%s\n",gtk_entry_get_text(GTK_ENTRY(data)));

	/*
	//testausgabe in ein entry	
	gtk_entry_set_text(GTK_ENTRY(data),"Text printed");
	*/

	//select text					startpoint	endpoint (-1=all)
	gtk_editable_select_region(GTK_EDITABLE(data),	0,		-1);
	//coppy selected to clipboard (past und cut und andere sachen)
	gtk_editable_copy_clipboard(GTK_EDITABLE(data));

	/*
	//inhalt eines Label aender, das uebergeben wurde
	gtk_label_set_text(GTK_LABEL(data),"you clicked the button");
	*/
}

static void check_state(GtkWidget *widget, gpointer data){
	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget))){
		g_print("Toggle activated\n");
	}
	else{
		g_print("Toggle inactive\n");
		//toggle Button activieren
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(widget),true);
	}
}

int main(int argc, char* argv[]){
	
	//immer als erste Funktion ausfuehren
	gtk_init(&argc,&argv);

	//initialliesiere der einzelnel Widgets
	GtkWidget *window, *button, *label;

	//window einstellungen
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	//Window groesse andern
	//andert nur, wenn moeglich
	gtk_widget_set_size_request(window,width,hight);
	//Window title andern
	gtk_window_set_title(GTK_WINDOW(window),"nicht Main");
	//window signals connect und das label wird uebergeben
	g_signal_connect(window,"delete-event",G_CALLBACK(gtk_main_quit),NULL);
	
	//init Widgets ausser Window
	label = gtk_label_new("Einfaches Label");
		//gtk_label_set_text(GTK_LABEL(label),"Welt Hallo");	
	button = gtk_button_new_with_label("CLick me");
	
	//Signale von button einbinden
	g_signal_connect(button,"clicked",G_CALLBACK(button_clicked),label);
	
	/*
 	GtkWidget *hbox;
	//box einfuhren
	//			size	space between widgets
	hbox = gtk_hbox_new(	false,	5);
	//von links nach rechts (end reverse)	extend?	add spacings?	spacing
	gtk_box_pack_start(GTK_BOX(hbox),label,	false,	false,		0);
	gtk_box_pack_start(GTK_BOX(hbox),button,true,true,0);
	*/
	
	//Tables verwenden anstat boxes
	
	GtkWidget *table;
	//			#rows	#colums	#homogen?
	table = gtk_table_new(	2,	2,	0);

	//neue Widgets
	GtkWidget *toggle, *label2;
	//Toggle Button hinzufuegen
	toggle = gtk_toggle_button_new_with_mnemonic("_Toggle 1");
	label2 = gtk_label_new("neues Label");
	
	//signal hinzu wenn toggled
	g_signal_connect(toggle,"toggled",G_CALLBACK(check_state),NULL);

	//zu tabel hinzufuegen
	//attachment					left (from to)	down (from to)	fill?		extand?
	gtk_table_attach(GTK_TABLE(table),label2,	0,1,		0,1,		GTK_FILL,	GTK_FILL,	0,0);
	gtk_table_attach(GTK_TABLE(table),toggle,	1,2,		0,1,		GTK_FILL,	GTK_FILL,	0,0);

	
	GtkWidget *button2;
	button2 = gtk_button_new_with_mnemonic("B_utton");
	//Eingabebox einbauen
	GtkWidget *entry;
	entry = gtk_entry_new();
	gtk_table_attach(GTK_TABLE(table),entry,	1,2,		1,2,		GTK_FILL,	GTK_FILL,	0,0);
	gtk_table_attach(GTK_TABLE(table),button2,	0,1,		1,2,		GTK_FILL,	GTK_FILL,	0,0);

	//fuer textuebergabe
	g_signal_connect(button2,"clicked",G_CALLBACK(button_clicked),entry);

	//ertry ausgabe per enter taste	
	g_signal_connect(entry,"activate",G_CALLBACK(button_clicked),entry);

	//Widgets verbinden
	gtk_container_add(GTK_CONTAINER(window),table);

	//alle widgets anzeigen
	gtk_widget_show_all(window);

	//main Funktion fuer GTK
	gtk_main();
	return 0;
}
