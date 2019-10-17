CC= gcc
CFLAGS = -g -Wall -std=c99
CPPFLAGS = -I.
LDFLAGS= -lgame -L.

all: recolor_text test_emolere.o test_vsamson.o test_elhdiallo.o test_slascostes.o

test_slascostes.o : test_game_slascostes.c game.h
test_slascostes : test_slascostes.o
test_vsamson.o : test_game_vsamson.c game.h
test_vsamson : test_vsamson.o

test_elhdiallo.o : test_game_elhdiallo.c game.h
test_elhdiallo : test_elhdiallo.o
test_emolere.o : test_game_emolere.c game.h
test_emolere : test_emolere.o


libgame.a: game_io.o game.o game_io.h  game.h
	ar rcs  $@ $^

recolor_text.o: recolor_text.c game_io.h  game.h

recolor_text: recolor_text.o libgame.a
	$(CC) $(CFLAGS) $(CPPFLAGS)  -o $@ $< $(LDFLAGS)

.PHONY: clean

test:
	./test_slascostes game_new
	./test_vsamson game_new_empty
	./test_elhdiallo game_set_cell_init
	./test_emolere game_set_max_moves

	./test_slascostes game_nb_moves_max
	./test_vsamson game_cell_current_color
	./test_elhdiallo game_nb_moves_cur
	./test_emolere game_play_one_move

	./test_slascostes game_copy
	./test_vsamson game_delete
	./test_elhdiallo game_is_over
	./test_emolere game_restart

clean:
	rm libgame.a recolor_text.o recolor_text test_elhdiallo test_emolere test_slascostes test_vsamson test_elhdiallo.o test_emolere.o test_slascostes.o test_vsamson.o
