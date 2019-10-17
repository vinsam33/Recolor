CC= gcc
CFLAGS = -g -Wall -std=c99
CPPFLAGS = -I.
LDFLAGS= -lgame -L.

all: recolor_text test_emolere.o test_vsamson.o test_elhdiallo.o test_slascostes.o

test_slascostes.o : test_game_slascostes.c game.h

test_vsamson.o : test_game_vsamson.c game.h

test_elhdiallo.o : test_game_elhdiallo.c game.h

test_emolere.o : test_game_emolere.c game.h


libgame.a: game_io.o game.o game_io.h  game.h
	ar rcs  $@ $^

recolor_text.o: recolor_text.c game_io.h  game.h

recolor_text: recolor_text.o libgame.a
	$(CC) $(CFLAGS) $(CPPFLAGS)  -o $@ $< $(LDFLAGS)


.PHONY: clean

clean:
	rm libgame.a recolor_text.o recolor_text
