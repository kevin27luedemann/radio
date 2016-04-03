NAME=main
CFLAGS=-g -Wall -std=c++11 -o $(NAME)
GTKFLAGS=-export-dynamic `pkg-config --cflags --libs gtk+-3.0`
SRCS=main.cpp
CC=g++

all: $(NAME)

  
main: $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) $(GTKFLAGS)
 
clean:
	/bin/rm -f $(NAME)
