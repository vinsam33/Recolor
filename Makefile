CC = gcc
CFLAGS = -g -std=c99 -Wall
LDFLAGS = -lgame -L.
CPPFLAGS = -I.


all: recolor_text

libgame.a : game_io.o game.o game_io.h game.h
	ar rcs $@ $^

recolor_text.o : recolor_text.c game.h game_io.h

recolor_text : recolor_text.o libgame.a
	$(CC) $(CFLAGS) $(CPPFLAGS) $^ -o $@ $(LDFLAGS)

.PHONY : clean
clean : 
	rm libgame.a recolor_text.o recolor_text
