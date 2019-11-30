

// game_set_cell_init
// game_nb_moves_cur
// game_is_over
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
typedef unsigned int uint;

// 1ere fonction
bool test_nb_moves_cur() {
  game g = game_new_empty();
  if ( g==NULL){
    game_delete(g);
    return false;
  }

  game_nb_moves_cur(g);
  if (game_nb_moves_cur(g) != 0) {
    fprintf(stderr, " game_nb_moves_cur est censé retourné 0");
    game_delete(g);
    return false;
  }
  /*for(uint i=0; i<x; i++){
      game_play_one_move(g, 3);
  }*/
  game_play_one_move(g, 3);

  if (game_nb_moves_cur(g) ==0) {
    game_delete(g);
    return false;
  }
  return true;
}
// 2eme fonction
bool test_game_set_cell_init(game g, uint x, uint y) {
  // game g=game_new_empty();
  if (g == NULL) {
    game_delete(g);
    return false;
  }
  game_set_cell_init(g, 4, 2, 3);
  game_set_cell_init(g, 4, 6, 2);

  if (game_cell_current_color(g, 4, 2) != 3 ||
      game_cell_current_color(g, 4, 6) != 2) {
    fprintf(stderr, "Voir game_set_cell_init ");
    game_delete(g);
    return false;
  }
  return true;
}

// 3eme fonction

// test grille uniforme
bool is_grid_red(game g) {
  for (uint x = 0; x < SIZE; x++) {
    for (uint y = 0; y < SIZE; y++) {
      if (game_cell_current_color(g, x, y) != RED) {
        game_delete(g);
        return false;
      }
    }
  }
  return true;
}

bool test_game_is_over() {
  // premier test , cas toutes les cellules de même coul et nbCoupJoué < nbMax
  game t1 = game_new_empty();
  if (t1 == NULL){
    return false;
  }
  game_set_max_moves(t1, 3);
  game_set_cell_init(t1, 0, 0, BLUE);
  if (game_is_over(t1)) {
    fprintf(stderr, "echec game_is_over: censé returner jeux non terminé \n");
    return false;
  }
  game_play_one_move(t1, RED);
  if (!game_is_over(t1)) {
    fprintf(stderr, "echec game_is_over: censé retourner jeux terminé \n");
    return false;
  }

  if (game_nb_moves_cur(t1) >= 3) {
    fprintf(stderr, "echec game_is_over: nbCoupjoués>=nbMax \n");
  }
  if (game_is_over(t1) && is_grid_red(t1) == false) {
    fprintf(stderr, "echec test de game_is_over: grille non uniforment rouge");
  }
  // liberer la mémoire
  game_delete(t1);
  return true;
}

void usage(int argc, char *argv[]) {
  fprintf(stderr, "Usage: %s <testname> [<...>]\n", argv[0]);
  exit(EXIT_FAILURE);
}
int main(int argc, char *argv[]) {
  if (argc == 1) usage(argc, argv);
  game g = game_new_empty();

  //  start test
  fprintf(stderr, "=> Start test \"%s\"\n", argv[1]);
  bool ok = false;

  if (strcmp("nb_moves_cur", argv[1]) == 0) {
    ok = test_nb_moves_cur();
  } else if ((strcmp("game_set_cell_init", argv[1]) == 0)) {
    ok = test_game_set_cell_init(g, 5, 6);
  } else if (((strcmp("game_is_over", argv[1]) == 0))) {
    ok = test_game_is_over();
  }
  if (ok) {
    fprintf(stderr, "Test \"%s\" finished: SUCCESS\n", argv[1]);
    return EXIT_SUCCESS;
  } else {
    fprintf(stderr, "Test \"%s\" finished: FAILURE\n", argv[1]);
    return EXIT_FAILURE;
  }
}
