//#define demo

#include <gtk/gtk.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <time.h>
#include <wiringPi.h>

#define width 320
#define hight 240

#define BUTTONBACKLIGHT 17
#define BACKLIGHTAUS()  system("sudo sh -c 'echo '0' > /sys/class/gpio/gpio508/value'");
#define BACKLIGHTAN()   system("sudo sh -c 'echo '1' > /sys/class/gpio/gpio508/value'");
bool LICHTAN;

#ifndef demo
	#define playstr "/usr/bin/piradio/play.jpg"
	#define stopstr "/usr/bin/piradio/stop.jpg"
	#define nextstr "/usr/bin/piradio/next.jpg"
#else
	#define playstr "./ress/play.jpg"
	#define stopstr "./ress/stop.jpg"
	#define nextstr "./ress/next.jpg"
#endif

static void button_play(GtkWidget *widget, gpointer data);
static void button_stop(GtkWidget *widget, gpointer data);
static void button_next(GtkWidget *widget, gpointer data);

static gboolean update_trackscreen(gpointer data);
static gboolean update_datescreen(gpointer data);


char* asct(const struct tm *timeptr);

int main(int argc, char* argv[])
{

	//start using Backlight and turning it on
	wiringPiSetupGpio();
	pinMode (BUTTONBACKLIGHT, INPUT);
	pullUpDnControl(BUTTONBACKLIGHT,PUD_UP);
	system("sh -c 'echo 508 > /sys/class/gpio/export'");
	system("sudo sh -c 'echo 'out' > /sys/class/gpio/gpio508/direction'");
	BACKLIGHTAN();
	LICHTAN = true;

#ifndef demo
	system("mpc volume 83");	//set volume to best value
	system("mpc repeat");		//turn repeating on
#endif
	system("mkdir -p /tmp/piradio");
	system("echo test > /tmp/piradio/stat.txt");

	gtk_init(&argc,&argv);
	
		//Hauptfenster einstellungen	
		GtkWidget *window;
		window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
		gtk_widget_set_size_request(window,width,hight);
		gtk_window_set_resizable(GTK_WINDOW(window),false);
		g_signal_connect(window,"delete-event",G_CALLBACK(gtk_main_quit),NULL);
	#ifdef demo
		gtk_window_set_decorated(GTK_WINDOW(window),false);
	#endif

			//Layout erstellen
			GtkWidget *cont;
			cont = gtk_box_new(GTK_ORIENTATION_VERTICAL,0);
		
				//Layout horizontal for the Buttons
				GtkWidget *hbox;
				hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);

					//Image Button for play
					GtkWidget *im_play, *ev_play, *la_play, *vb_play;
	
					vb_play = gtk_box_new(GTK_ORIENTATION_VERTICAL,0);
					la_play = gtk_label_new("Play");
					im_play = gtk_image_new_from_file(playstr);
	
					gtk_box_pack_start(GTK_BOX(vb_play),im_play,false,true,0);
					gtk_box_pack_start(GTK_BOX(vb_play),la_play,false,false,0);
	
					ev_play = gtk_event_box_new();
					gtk_container_add(GTK_CONTAINER(ev_play),vb_play);
					g_signal_connect(G_OBJECT(ev_play),"button-press-event",G_CALLBACK(button_play),NULL);
	
					//Image Button for stop
					GtkWidget *im_stop, *ev_stop, *la_stop, *vb_stop;
						
					vb_stop = gtk_box_new(GTK_ORIENTATION_VERTICAL,0);
					la_stop = gtk_label_new("Stop");
					im_stop = gtk_image_new_from_file(stopstr);
		
					gtk_box_pack_start(GTK_BOX(vb_stop),im_stop,false,true,0);
					gtk_box_pack_start(GTK_BOX(vb_stop),la_stop,false,false,0);
	
					ev_stop = gtk_event_box_new();
					gtk_container_add(GTK_CONTAINER(ev_stop),vb_stop);
					g_signal_connect(G_OBJECT(ev_stop),"button-press-event",G_CALLBACK(button_stop),NULL);
		
					//Image Button for next
					GtkWidget *im_next, *ev_next, *la_next, *vb_next;
		
					vb_next = gtk_box_new(GTK_ORIENTATION_VERTICAL,0);
					la_next = gtk_label_new("Next");
					im_next = gtk_image_new_from_file(nextstr);
	
					gtk_box_pack_start(GTK_BOX(vb_next),im_next,false,true,0);
					gtk_box_pack_start(GTK_BOX(vb_next),la_next,false,false,0);
		
					ev_next = gtk_event_box_new();
					gtk_container_add(GTK_CONTAINER(ev_next),vb_next);
					g_signal_connect(G_OBJECT(ev_next),"button-press-event",G_CALLBACK(button_next),NULL);
					
				//Layout der Bottons einbauen
				gtk_box_pack_start(GTK_BOX(hbox),ev_play,true,true,0);
				gtk_box_pack_start(GTK_BOX(hbox),ev_stop,true,true,0);
				gtk_box_pack_start(GTK_BOX(hbox),ev_next,true,true,0);
				
				//Label for showing the text
				GtkWidget *la_text;
				la_text = gtk_label_new("dummy sender");
				
				//Label for showing the date
				GtkWidget *la_date;
				la_date = gtk_label_new("03.04.2016 13:34:35");

			//layout to total Box for window
			gtk_box_pack_start(GTK_BOX(cont),la_date,false,true,0);
			gtk_box_pack_start(GTK_BOX(cont),la_text,true,true,0);
			gtk_box_pack_start(GTK_BOX(cont),hbox,true,true,0);

		//add container to window
		gtk_box_pack_start(GTK_BOX(cont),la_text,true,true,0);
		gtk_container_add(GTK_CONTAINER(window),cont);
	
		//update timer starten
		g_timeout_add(100, update_trackscreen,(gpointer) la_text);
		g_timeout_add(1000, update_datescreen,(gpointer) la_date);

		//make window Fullscreen
	#ifdef demo
		gtk_window_fullscreen(GTK_WINDOW(window));
	#endif
		gtk_widget_show_all(window);

	#ifndef demo	
		GdkCursor *mouse;
		mouse = gdk_cursor_new(GDK_BLANK_CURSOR);
		gdk_window_set_cursor(gtk_widget_get_window(window),mouse);	
	#endif

	gtk_main();
	return 0;
}

//Buttons
static void button_play(GtkWidget *widget, gpointer data){
#ifndef demo
	//system("mpc play");
	system("/usr/scripte/wetter.sh radio");
#else
	system("/usr/scripte/wetter.sh");	
	system("echo play");
#endif
}	
static void button_stop(GtkWidget *widget, gpointer data){
#ifndef demo
	system("mpc stop");
#else
	system("echo stop");
#endif
}
static void button_next(GtkWidget *widget, gpointer data){
#ifndef demo
	system("mpc next");
#else
	system("echo next");
#endif
}

//Screenupdate funktion
static gboolean update_trackscreen(gpointer data){
static bool pressed = false;
#ifndef demo
	system("mpc current > /tmp/piradio/stat.txt");
	//check for light button
	if(!digitalRead(BUTTONBACKLIGHT) && LICHTAN && !pressed){
		pressed = true;
	}
	else if (digitalRead(BUTTONBACKLIGHT) && LICHTAN && pressed){
		pressed = false;
		BACKLIGHTAUS();
		LICHTAN = false;
	}
	else if (!digitalRead(BUTTONBACKLIGHT) && !LICHTAN && !pressed ){
		pressed = true;
	}
	else if (digitalRead(BUTTONBACKLIGHT) && !LICHTAN && pressed ){
		pressed = false;
		BACKLIGHTAN();
		LICHTAN = true;
	}
#endif
	std::ifstream f;
	f.open("/tmp/piradio/stat.txt");
	char buffer[128];
	char ausgabe[128];
	int i = 0;
	
	while(!f.eof()){
		f >> buffer[i];
		if(buffer[i]==':' || buffer[i]=='|'){
			ausgabe[i]='\n';
		}
		else{
			ausgabe[i]=buffer[i];
		}
		i++;
	}

	for (int j=i-1;j<128;j++){
		ausgabe[j]='\0';
	}
	//g_print(ausgabe);
	//g_print("\n");
	if(ausgabe[0]!='\0'){
		const char *format = "<span font_desc=\"Sans 13\">\%s</span>";
		char *markup;

		markup = g_markup_printf_escaped (format, ausgabe);
		gtk_label_set_markup (GTK_LABEL(data), markup);
		g_free (markup);
//		gtk_label_set_text(GTK_LABEL(data),ausgabe);
	}
	else{
		const char *format = "<span font_desc=\"Sans 13\">\%s</span>";
		char *markup;

		markup = g_markup_printf_escaped (format, "\nRadio\n");
		gtk_label_set_markup (GTK_LABEL(data), markup);
		g_free (markup);
//		gtk_label_set_text(GTK_LABEL(data),"\nRadio\n");
	}	
	f.close();
	return true;
}
static gboolean update_datescreen(gpointer data){
	time_t timer;
	struct tm *local;
	time(&timer);
	local = localtime(&timer);
	
	const char *format = "<span font_desc=\"18\">\%s</span>";
	char *markup;

	markup = g_markup_printf_escaped (format, asct(local));
	gtk_label_set_markup (GTK_LABEL(data), markup);
	g_free (markup);
	
	return true;
}


//hilfsfunktionen
char* asct(const struct tm *timeptr)
{
  static const char wday_name[][4] = {
    "So", "Mo", "Di", "Mi", "Do", "Fr", "Sa"
  };
  static const char mon_name[][4] = {
    "Jan", "Feb", "Mar", "Apr", "May", "Jun",
    "Jul", "Aug", "Sep", "Okt", "Nov", "Dez"
  };
  static char result[26];
  sprintf(result, "%.2s %3d.%.3s.%d %.2d:%.2d:%.2d",
	wday_name[timeptr->tm_wday],
	timeptr->tm_mday,
	mon_name[timeptr->tm_mon],
	1900 + timeptr->tm_year,
	timeptr->tm_hour,
	timeptr->tm_min, 
	timeptr->tm_sec);
  return result;
}
