CC= gcc
CFLAGS = -g -Wall -std=c99
CPPFLAGS = -I.
LDFLAGS= -lgame -L.

all: recolor_text test_game_emolere test_game_vsamson test_game_elhdiallo test_game_slascostes

recolor_text: recolor_text.o libgame.a
	$(CC) $(CFLAGS) $(CPPFLAGS)  -o $@ $< $(LDFLAGS)

test_game_slascostes : test_game_slascostes.o libgame.a
	$(CC) $(CFLAGS) $(CPPFLAGS)  -o $@ $< $(LDFLAGS)
test_game_vsamson : test_game_vsamson.o libgame.a
	$(CC) $(CFLAGS) $(CPPFLAGS)  -o $@ $< $(LDFLAGS)
test_game_elhdiallo : test_game_elhdiallo.o libgame.a
	$(CC) $(CFLAGS) $(CPPFLAGS)  -o $@ $< $(LDFLAGS)
test_game_emolere : test_game_emolere.o libgame.a
	$(CC) $(CFLAGS) $(CPPFLAGS)  -o $@ $< $(LDFLAGS)

libgame.a: game_io.o game.o game_io.h game.h
	ar rcs  $@ $^

recolor_text.o: recolor_text.c game_io.h game.h

test_game_slascostes.o : test_game_slascostes.c game.h
test_game_vsamson.o : test_game_vsamson.c game.h
test_game_elhdiallo.o : test_game_elhdiallo.c game.h
test_game_emolere.o : test_game_emolere.c game.h

.PHONY: clean

clean:
	rm -f libgame.a recolor_text.o recolor_text test_elhdiallo test_emolere test_slascostes test_vsamson test_elhdiallo.o test_emolere.o test_slascostes.o test_vsamson.o

test: test_game_slascostes test_game_elhdiallo test_game_vsamson test_game_emolere
	./test_game_slascostes
	./test_game_elhdiallo
	./test_game_vsamson
	./test_game_emolere

test_slascostes: test_game_slascostes
	./test_game_slascostes

test_elhdiallo: test_game_elhdiallo
	./test_game_elhdiallo 

test_vsamson: test_game_vsamson
	./test_game_vsamson

test_emolere: test_game_emolere
	./test_game_emolere
