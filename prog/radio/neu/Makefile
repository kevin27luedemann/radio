NAME=main
ENDUNG=exe
CFLAGS=-g -Wall -o $(NAME).$(ENDUNG)
GTKFLAGS=-export-dynamic `pkg-config --cflags --libs gtk+-3.0`
SRCS=main.cpp
CC=g++
WIRINGFLAG=-I/usr/local/include -L/usr/local/lib -lwiringPi

all: $(NAME).$(ENDUNG)

  
$(NAME).$(ENDUNG): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) $(GTKFLAGS) $(WIRINGFLAG)

install: $(NAME).$(ENDUNG)
	mv $(NAME).$(ENDUNG) radio;
	mkdir -p /usr/bin/piradio/;
	cp -p ./ress/*.jpg /usr/bin/piradio/;
	#cp -p layout_radio.glade /usr/bin/piradio/;
	cp radio /usr/bin/;
	rm -f radio;
	mkdir -p /tmp/piradio/;
	chmod 777 /tmp/piradio/;
	echo "test radio" > /tmp/piradio/stat.txt;
	chmod 777 /tmp/piradio/stat.txt; 

installTTS:
	mkdir -p /usr/scripte/;
	cp -p ../TTS/pico/sprich.sh /usr/scripte/;
	chmod 755 /usr/scripte/sprich.sh;
	cp -P ../TTS/pico/wetter.sh /usr/scripte/wetter.sh
	chmod 755 /usr/scripte/wetter.sh;

clean:
	/bin/rm -f $(NAME).exe
