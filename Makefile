CC= gcc
CFLAGS = -g -Wall -std=c99
CPPFLAGS = -I.
LDFLAGS= -lgame -L.

all: recolor_text

libgame.a: game_io.o game.o game_io.h  game.h
	ar rcs  $@ $^

recolor_text.o: recolor_text.c game_io.h  game.h

recolor_text: recolor_text.o libgame.a
	$(CC) $(CFLAGS) $(CPPFLAGS)  -o $@ $< $(LDFLAGS)


.PHONY: clean

clean:
	rm libgame.a recolor_text.o recolor_text
