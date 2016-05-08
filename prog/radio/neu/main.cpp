#define demo

#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <time.h>

#ifndef demo
#include <wiringPi.h>
#endif

#define width 320
#define hight 240

#ifndef demo
#define BUTTONBACKLIGHT		17
#define BUTTONBLACKSCREEN	22
#define BACKLIGHTAUS()  system("sudo sh -c 'echo '0' > /sys/class/gpio/gpio508/value'");
#define BACKLIGHTAN()   system("sudo sh -c 'echo '1' > /sys/class/gpio/gpio508/value'");
#endif
bool LICHTAN;
bool OFFSCREEN;

static void button_play(GtkWidget *widget, gpointer data);
static void button_stop(GtkWidget *widget, gpointer data);
static void button_next(GtkWidget *widget, gpointer data);

static gboolean update_trackscreen(gpointer data);
static gboolean update_datescreen(gpointer data);

char* asct(const struct tm *timeptr, int auswahl);

//objects for global aces
GtkBuilder	*builder_main;
GObject		*window_main, *button, *label_track, *label_date;
GObject		*window_off, *label_off_dat, *label_off_uhr;
GObject		*window_black;

GdkRGBA black = {0, 0, 0, 1};
GdkRGBA white = {1, 1, 1, 1};

int main(int argc, char* argv[])
{
	//start using Backlight and turning it on
#ifndef demo
	wiringPiSetupGpio();
	pinMode (BUTTONBACKLIGHT, INPUT);
	pullUpDnControl(BUTTONBACKLIGHT,PUD_UP);
	pinMode (BUTTONBLACKSCREEN, INPUT);
	pullUpDnControl(BUTTONBLACKSCREEN,PUD_UP);
	system("sudo sh -c 'echo 508 > /sys/class/gpio/export'");
	system("sudo sh -c 'echo 'out' > /sys/class/gpio/gpio508/direction'");
	BACKLIGHTAN();
	LICHTAN 	= true;
	OFFSCREEN	= false;

	system("mpc volume 97");	//set volume to best value
	system("mpc repeat");		//turn repeating on
#endif

	system("mkdir -p /tmp/piradio");
	system("chmod 777 /tmp/piradio");
	system("echo \"\n\ntest\n\n\" > /tmp/piradio/stat.txt");

	gtk_init(&argc,&argv);

	
	//load Builderfile and start buildung window
	builder_main = gtk_builder_new();
	gtk_builder_add_from_file(builder_main, "layout_radio.glade", NULL);
	
	window_main	= gtk_builder_get_object(builder_main, "main_radio");
	g_signal_connect(window_main, "destroy", G_CALLBACK(gtk_main_quit),NULL);

	button		= gtk_builder_get_object(builder_main, "button_play");
	g_signal_connect(button, "clicked", G_CALLBACK(button_play),NULL);
	
	button		= gtk_builder_get_object(builder_main, "button_stop");
	g_signal_connect(button, "clicked", G_CALLBACK(button_stop),NULL);

	button		= gtk_builder_get_object(builder_main, "button_next");
	g_signal_connect(button, "clicked", G_CALLBACK(button_next),NULL);

	label_track		= gtk_builder_get_object(builder_main, "label_track");
	label_date		= gtk_builder_get_object(builder_main, "label_date");
	label_off_dat	= gtk_builder_get_object(builder_main, "label_off_dat");
	label_off_uhr	= gtk_builder_get_object(builder_main, "label_off_uhr");

	window_off		= gtk_builder_get_object(builder_main, "window_off");

	window_black 	= gtk_builder_get_object(builder_main, "window_black");

	//Screen update functions
	g_timeout_add(100, update_trackscreen,NULL);
	g_timeout_add(1000, update_datescreen,NULL);

//#ifndef demo
	//gtk_window_fullscreen(GTK_WINDOW(window_main));
	//gtk_widget_show_all(window);
	GdkCursor *mouse;
	mouse 	= gdk_cursor_new(GDK_BLANK_CURSOR);
	gdk_window_set_cursor(gtk_widget_get_window(GTK_WIDGET(window_main)),mouse);	

	gtk_widget_show(GTK_WIDGET(window_off));
	gtk_widget_override_background_color(GTK_WIDGET(window_off), GTK_STATE_FLAG_NORMAL, &black);
	gtk_widget_override_color(GTK_WIDGET(label_off_uhr), GTK_STATE_FLAG_NORMAL, &white);
	gtk_widget_override_color(GTK_WIDGET(label_off_dat), GTK_STATE_FLAG_NORMAL, &white);
	gdk_window_set_cursor(gtk_widget_get_window(GTK_WIDGET(window_off)),mouse);	
	gtk_widget_hide(GTK_WIDGET(window_off));
	
	gtk_widget_show(GTK_WIDGET(window_black));
	gtk_widget_override_background_color(GTK_WIDGET(window_black), GTK_STATE_FLAG_NORMAL, &black);
	
//#endif

	gtk_main();
	return 0;
}

//Buttons
static void button_play(GtkWidget *widget, gpointer data){
#ifndef demo
	system("mpc status | grep \"playing\" > /tmp/piradio/testplay.txt ");
	FILE *file;
	char *buffer;
	buffer = (char *) malloc(sizeof(char));
	buffer[0]=' ';
	file = fopen("/tmp/piradio/testplay.txt", "r");
	fread(buffer, 1, 1, file);
	if(buffer[0] == '['){
		system("mpc stop");
	}
	else{
		system("/usr/scripte/wetter.sh radio");
	}
	free(buffer);
	fclose(file);
#else
	//system("/usr/scripte/wetter.sh");	
	system("echo play");
#endif
}	
static void button_stop(GtkWidget *widget, gpointer data){
#ifndef demo
	system("mpc stop");
#else
	system("echo stop");
	gtk_widget_show(GTK_WIDGET(window_off));
#endif
}
static void button_next(GtkWidget *widget, gpointer data){
#ifndef demo
	system("mpc next");
#else
	gtk_widget_hide(GTK_WIDGET(window_off));
	system("echo next");
#endif
}

//Screenupdate funktion
static gboolean update_trackscreen(gpointer data){
#ifndef demo
	static bool pressed = false;
	static bool pressed1 = false;
	system("mpc current > /tmp/piradio/stat.txt");
	//check for light button
	if(!digitalRead(BUTTONBACKLIGHT) && LICHTAN && !pressed){
		pressed = true;
	}
	else if (digitalRead(BUTTONBACKLIGHT) && LICHTAN && pressed){
		pressed = false;
		BACKLIGHTAUS();
		gtk_widget_hide(GTK_WIDGET(window_off));
		gtk_widget_hide(GTK_WIDGET(window_black));
		LICHTAN = false;
	}
	else if (!digitalRead(BUTTONBACKLIGHT) && !LICHTAN && !pressed ){
		pressed = true;
	}
	else if (digitalRead(BUTTONBACKLIGHT) && !LICHTAN && pressed ){
		pressed = false;
		BACKLIGHTAN();
		gtk_widget_hide(GTK_WIDGET(window_off));
		gtk_widget_show(GTK_WIDGET(window_black));
		LICHTAN = true;
	}
	//Check if screen off Button pressed
	if(!digitalRead(BUTTONBLACKSCREEN) && LICHTAN && !pressed1 && !OFFSCREEN){
		pressed1 = true;
	}
	else if (digitalRead(BUTTONBLACKSCREEN) && LICHTAN && pressed1 && !OFFSCREEN){
		pressed1 = false;
		gtk_widget_hide(GTK_WIDGET(window_black));
		gtk_widget_show(GTK_WIDGET(window_off));
		OFFSCREEN = true;
	}
	else if (!digitalRead(BUTTONBLACKSCREEN) && LICHTAN && !pressed1 && OFFSCREEN){
		pressed1 = true;
	}
	else if (digitalRead(BUTTONBLACKSCREEN) && LICHTAN && pressed1 && OFFSCREEN){
		pressed1 = false;
		gtk_widget_hide(GTK_WIDGET(window_black));
		gtk_widget_hide(GTK_WIDGET(window_off));
		OFFSCREEN = false;
	}

#endif
	FILE *file;
	long filesize;
	file = fopen("/tmp/piradio/stat.txt", "r");
	if (file != NULL){
		fseek(file, 0, SEEK_END);
		filesize = ftell(file);
		rewind(file);
		char *buffer;
		buffer = (char *) malloc(sizeof(char)*filesize);
		buffer[0]='\0';
		fread(buffer, 1, filesize, file);
		for(int i=0; i<filesize; i++){
			if(buffer[i]=='|' || buffer[i]==':' || buffer[i]=='-'){
				buffer[i+1]='\n';
			}
		}
		buffer[filesize-1]='\0';

		if(buffer[0]!='\0'){
			/*
			const char *format = "<span font_desc=\"Sans 12\">\%s</span>";
			char *markup;
			markup = g_markup_printf_escaped (format, buffer);
			gtk_label_set_markup (GTK_LABEL(data), markup);
			g_free (markup);
			*/
			gtk_label_set_text(GTK_LABEL(label_track),buffer);

		}
		else{
			/*
			const char *format = "<span font_desc=\"Sans 12\">\%s</span>";
			char *markup;
			markup = g_markup_printf_escaped (format, "\nRadio\n");
			gtk_label_set_markup (GTK_LABEL(data), markup);
			g_free (markup);
			*/
			gtk_label_set_text(GTK_LABEL(label_track),"\n\nradio\n\n");
		}
		fclose(file);
		free(buffer);
	}
	else{
		printf("Fehler mit stat.txt\n");
	}
	return true;
}
static gboolean update_datescreen(gpointer data){
	time_t timer;
	struct tm *local;
	time(&timer);
	local = localtime(&timer);
	/*	
	const char *format = "<span font_desc=\"18\">\%s</span>";
	char *markup;

	markup = g_markup_printf_escaped (format, asct(local));
	gtk_label_set_markup (GTK_LABEL(data), markup);
	g_free (markup);
	*/
	gtk_label_set_text(GTK_LABEL(label_date),asct(local,0));
	gtk_label_set_text(GTK_LABEL(label_off_uhr),asct(local,2));
	gtk_label_set_text(GTK_LABEL(label_off_dat),asct(local,1));
	
	return true;
}


//hilfsfunktionen
char* asct(const struct tm *timeptr, int auswahl)
{
  static const char wday_name[][3] = {
    "So", "Mo", "Di", "Mi", "Do", "Fr", "Sa"
  };
  static const char mon_name[][4] = {
    "Jan", "Feb", "Mar", "Apr", "May", "Jun",
    "Jul", "Aug", "Sep", "Okt", "Nov", "Dez"
  };
  static char result[24];
	if(auswahl == 0){
		sprintf(result, "%.2s %2d.%.3s.%4d %.2d:%.2d:%.2d",
			wday_name[timeptr->tm_wday],
			timeptr->tm_mday,
			mon_name[timeptr->tm_mon],
			1900 + timeptr->tm_year,
			timeptr->tm_hour,
			timeptr->tm_min, 
			timeptr->tm_sec);
	}
	else if (auswahl == 1){
		sprintf(result, "%.2s %2d.%.3s.%4d",
			wday_name[timeptr->tm_wday],
			timeptr->tm_mday,
			mon_name[timeptr->tm_mon],
			1900 + timeptr->tm_year);
	}
	else if (auswahl == 2){
		sprintf(result, "%.2d:%.2d", 
			timeptr->tm_hour,
			timeptr->tm_min);
	}
  return result;
}
