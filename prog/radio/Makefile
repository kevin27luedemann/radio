NAME=main
CFLAGS=-g -Wall -o $(NAME)
GTKFLAGS=-export-dynamic `pkg-config --cflags --libs gtk+-3.0`
SRCS=main.cpp
CC=g++
WIRINGFLAG=-I/usr/local/include -L/usr/local/lib -lwiringPi

all: $(NAME)

  
main: $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) $(GTKFLAGS) $(WIRINGFLAG)
 
clean:
	/bin/rm -f $(NAME)
