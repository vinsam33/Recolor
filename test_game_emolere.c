#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "game_io.h"
#include "game.h"

bool test_game_set_max_moves(uint max) {
  game(g) = game_new_empty_ext(12, 12, false); 
  if (!g) {
    fprintf(stderr, "Error : invalid game\n\n");
    game_delete(g);
    return false;
  }

  game_set_max_moves(g, max);
  if (g->nb_max != max) {
    fprintf(stderr, "Error : too much number of moves\n\n");
    game_delete(g);
    return false;
  }
  game_delete(g);
  return true;
}

bool test_game_play_one_move(color c) {
  game g = game_new_empty_ext(12, 12, false); 
  if (!g) {
    fprintf(stderr, "Error : invalid game\n\n");
    game_delete(g);
    return false;
  }

  game_play_one_move(g, c);
  for (unsigned int y = 0; y < game_height(g); y++) {
    for (unsigned int x = 0; x < game_width(g); x++) {
      if (game_cell_current_color(g, x, y) != c) {
        game_delete(g);
        return false;
      }
    }
  }
  if (c <= 0) {
    fprintf(stderr, "Error : invalid game\n\n");
    game_delete(g);
    return false;
  }
  game_delete(g);
  return true;
}

bool test_game_restart() {
  color cells[144] = {
      0, 0, 0, 2, 0, 2, 1, 0, 1, 0, 3, 0, 0, 3, 3, 1, 1, 1, 1, 3, 2, 0, 1, 0,
      1, 0, 1, 2, 3, 2, 3, 2, 0, 3, 3, 2, 2, 3, 1, 0, 3, 2, 1, 1, 1, 2, 2, 0,
      2, 1, 2, 3, 3, 3, 3, 2, 0, 1, 0, 0, 0, 3, 3, 0, 1, 1, 2, 3, 3, 2, 1, 3,
      1, 1, 2, 2, 2, 0, 0, 1, 3, 1, 1, 2, 1, 3, 1, 3, 1, 0, 1, 0, 1, 3, 3, 3,
      0, 3, 0, 1, 0, 0, 2, 1, 1, 1, 3, 0, 1, 3, 1, 0, 0, 0, 3, 2, 3, 1, 0, 0,
      1, 3, 3, 1, 1, 2, 2, 3, 2, 0, 0, 2, 2, 0, 2, 3, 0, 1, 1, 1, 2, 3, 0, 1};
  game(g) = game_new_ext(12, 12, cells, 12, false);
  game_play_one_move(g, 2);
  game_restart(g);

  if (game_nb_moves_cur(g) != 0) {
    fprintf(stderr, "Error : Number of moves different from 0\n\n");
    game_delete(g);
    return false;
  }
  if (game_cell_current_color(g, 0, 0) != cells[0]) {
    fprintf(stderr, "Error : game_cell_current_color different from cells[0]\n\n");
    game_delete(g);
    return false;
  }
  else {
    game_delete(g);
    return true;
  }
}

bool test_game_new_empty_ext(uint width, uint height, bool wrapping){
  game g = game_new_empty_ext(width, height, wrapping);
  if (game_is_wrapping(g)!=wrapping){
    fprintf(stderr, "Error : Different Wrapping \n\n");
    game_delete(g); 
    return false;
  }
  if (g == NULL || game_nb_moves_max(g) != 0 || width == 0 || height == 0){
    fprintf(stderr, "Error : creation fault\n\n");
    game_delete(g);
    return false;
  }
  for (unsigned int x = 0; x < width; x++) {
    for (unsigned int y = 0; y < height; y++) {
      if (game_cell_current_color(g, x, y) != 0){
        game_delete(g);
        return false;
      }
    }
  }
  game_delete(g); 
  return true;
}

/*** ***** MAIN ***** ***/

int main(void) {
  
  printf("-- Start test of game_set_max_moves --\n");
  bool Agree = test_game_set_max_moves(12);
  if (Agree) {
    fprintf(stderr, "Execution of game_set_max_moves : Success\n\n");
  } else {
    fprintf(stderr, "Execution of game_set_max_moves : Denied\n\n");
    return EXIT_FAILURE;
  }

  printf("--Start test of game_play_one_move --\n");
  Agree = test_game_play_one_move(BLUE);
  if (Agree) {
    fprintf(stderr, "Execution of game_play_one_move : Success\n\n");
  } else {
    fprintf(stderr, "Execution of game_play_one_move : Denied\n\n");
    return EXIT_FAILURE;
  }
  
  printf("--Start test of game_restart --\n");
  Agree = test_game_restart();
  if (Agree) {
    fprintf(stderr, "Execution of game_restart : Success\n\n");
  } else {
    fprintf(stderr, "Execution of game_restart : Denied\n\n");
    return EXIT_FAILURE;
  }
  
  printf("-- Start test of game_new_empty_ext --\n");
  Agree = test_game_new_empty_ext(12, 12, false);
  if (Agree) {
    fprintf(stderr, "Execution of game_new_empty_ext : Success\n\n");
  } else {
    fprintf(stderr, "Execution of game_new_empty_ext : Denied\n\n");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
