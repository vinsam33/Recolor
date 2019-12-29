#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "game_io.h"

bool test_game_new(color *cells, unsigned int nb_moves_max) {
  game g = game_new(cells, nb_moves_max);
  if (g == NULL) {
    game_delete(g);//
    return false;
  }
  unsigned int nb_max = game_nb_moves_max(g);
  if (nb_moves_max != nb_max) {
    game_delete(g);//
    return false;
  }
  for (unsigned int y = 0; y < SIZE; y++) {
    for (unsigned int x = 0; x < SIZE; x++) {
      if (game_cell_current_color(g, x, y) != cells[y * SIZE + x]) {
        game_delete(g);//
        return false;
      }
    }
  }
  return true;
}

bool test_game_nb_moves_max() {
  color cells[144] = {
      0, 0, 0, 2, 0, 2, 1, 0, 1, 0, 3, 0, 0, 3, 3, 1, 1, 1, 1, 3, 2, 0, 1, 0,
      1, 0, 1, 2, 3, 2, 3, 2, 0, 3, 3, 2, 2, 3, 1, 0, 3, 2, 1, 1, 1, 2, 2, 0,
      2, 1, 2, 3, 3, 3, 3, 2, 0, 1, 0, 0, 0, 3, 3, 0, 1, 1, 2, 3, 3, 2, 1, 3,
      1, 1, 2, 2, 2, 0, 0, 1, 3, 1, 1, 2, 1, 3, 1, 3, 1, 0, 1, 0, 1, 3, 3, 3,
      0, 3, 0, 1, 0, 0, 2, 1, 1, 1, 3, 0, 1, 3, 1, 0, 0, 0, 3, 2, 3, 1, 0, 0,
      1, 3, 3, 1, 1, 2, 2, 3, 2, 0, 0, 2, 2, 0, 2, 3, 0, 1, 1, 1, 2, 3, 0, 1};
  game g = game_new(cells, 11);
  if (g == NULL) {
    game_delete(g);
    return false;
  }
  if (game_nb_moves_max(g) != 11) {
    game_delete(g);
    return false;
  }
  game_set_max_moves(g, 10);
  if (game_nb_moves_max(g) != 10) {
    game_delete(g);
    return false;
  }
  game_delete(g);
  return true;
}

bool test_game_copy() {
  color cells[144] = {
      0, 0, 0, 2, 0, 2, 1, 0, 1, 0, 3, 0, 0, 3, 3, 1, 1, 1, 1, 3, 2, 0, 1, 0,
      1, 0, 1, 2, 3, 2, 3, 2, 0, 3, 3, 2, 2, 3, 1, 0, 3, 2, 1, 1, 1, 2, 2, 0,
      2, 1, 2, 3, 3, 3, 3, 2, 0, 1, 0, 0, 0, 3, 3, 0, 1, 1, 2, 3, 3, 2, 1, 3,
      1, 1, 2, 2, 2, 0, 0, 1, 3, 1, 1, 2, 1, 3, 1, 3, 1, 0, 1, 0, 1, 3, 3, 3,
      0, 3, 0, 1, 0, 0, 2, 1, 1, 1, 3, 0, 1, 3, 1, 0, 0, 0, 3, 2, 3, 1, 0, 0,
      1, 3, 3, 1, 1, 2, 2, 3, 2, 0, 0, 2, 2, 0, 2, 3, 0, 1, 1, 1, 2, 3, 0, 1};
  game g = game_new(cells, 11);
  if (g == NULL) {
    game_delete(g);
    return false;
  }
  game g2 = game_copy(g);
  if (g2 == NULL) {
    game_delete(g);
    game_delete(g2);
    return false;
  }
  if (game_is_over(g) != game_is_over(g2)) {
    game_delete(g);
    game_delete(g2);
    return false;
  }
  if (game_nb_moves_max(g) != game_nb_moves_max(g2)) {
    game_delete(g);
    game_delete(g2);
    return false;
  }
  if (game_nb_moves_cur(g) != game_nb_moves_cur(g2)) {
    game_delete(g);
    game_delete(g2);
    return false;
  }
  for (unsigned int x = 0; x < SIZE; x++) {
    for (unsigned int y = 0; y < SIZE; y++) {
      if (game_cell_current_color(g2, y, x) !=
          game_cell_current_color(g, y, x)) {
        game_delete(g);
        game_delete(g2);
        return false;
      }
    }
  }
  game_delete(g);
  game_delete(g2);
  return true;
}

bool test_game_new_ext(uint width, uint height, color *cells, uint nb_moves_max,  bool wrapping){
  game g = game_new_ext(width,height,cells,nb_moves_max,wrapping);
  if(g == NULL){
    game_delete(g);
    return g;
  }
  unsigned int nb_max = game_nb_moves_max(g);
  if (nb_moves_max != nb_max) {
    game_delete(g);//
    return false;
  }
  for (unsigned int y = 0; y < SIZE; y++) {
    for (unsigned int x = 0; x < SIZE; x++) {
      if (game_cell_current_color(g, x, y) != cells[y * SIZE + x]) {
        game_delete(g);//
        return false;
      }
    }
  }
  if (width != game_width(g)){
    game_delete(g);//
    return false;
  }
  if (height != game_height(g)){
    game_delete(g);//
    return false;
  }
  if (wrapping != game_is_wrapping(g)){
    game_delete(g);//
    return false;
  }
  return true;
}

void usage(int argc, char *argv[]) {
  fprintf(stderr, "Usage: %s <testname> [<...>]\n", argv[0]);
  exit(EXIT_FAILURE);
}

/* ********** MAIN ROUTINE ********** */

int main(int argc, char *argv[]) {
  if (argc == 1) usage(argc, argv);
  color cells[144] = {
      0, 0, 0, 2, 0, 2, 1, 0, 1, 0, 3, 0, 0, 3, 3, 1, 1, 1, 1, 3, 2, 0, 1, 0,
      1, 0, 1, 2, 3, 2, 3, 2, 0, 3, 3, 2, 2, 3, 1, 0, 3, 2, 1, 1, 1, 2, 2, 0,
      2, 1, 2, 3, 3, 3, 3, 2, 0, 1, 0, 0, 0, 3, 3, 0, 1, 1, 2, 3, 3, 2, 1, 3,
      1, 1, 2, 2, 2, 0, 0, 1, 3, 1, 1, 2, 1, 3, 1, 3, 1, 0, 1, 0, 1, 3, 3, 3,
      0, 3, 0, 1, 0, 0, 2, 1, 1, 1, 3, 0, 1, 3, 1, 0, 0, 0, 3, 2, 3, 1, 0, 0,
      1, 3, 3, 1, 1, 2, 2, 3, 2, 0, 0, 2, 2, 0, 2, 3, 0, 1, 1, 1, 2, 3, 0, 1};

  // start test
  fprintf(stderr, "=> Start test \"%s\"\n", argv[1]);
  bool ok = false;
  if (strcmp("game_new", argv[1]) == 0)
    ok = test_game_new(cells, 11);
  else if (strcmp("game_nb_moves_max", argv[1]) == 0)
    ok = test_game_nb_moves_max();
  else if (strcmp("game_copy", argv[1]) == 0)
    ok = test_game_copy();
  else if (strcmp("game_new_ext", argv[1]) == 0)
    ok = test_game_new_ext(11,11,cells,11,false);
  else {
    fprintf(stderr, "Error: test \"%s\" not found!\n", argv[1]);
    exit(EXIT_FAILURE);
  }

  // print test result
  if (ok) {
    fprintf(stderr, "Test \"%s\" finished: SUCCESS\n", argv[1]);
    return EXIT_SUCCESS;
  } else {
    fprintf(stderr, "Test \"%s\" finished: FAILURE\n", argv[1]);
    return EXIT_FAILURE;
  }
}