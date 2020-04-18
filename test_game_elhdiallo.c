//author: DIALLO Elhadj Mamadou
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
typedef unsigned int uint;
//Functions tested: 
//game_set_cell_init, game_nb_moves_cur, game_is_over, game_is_wrapping, game_width
/**
 * @brief : test the nb_moves_cur function()
 * @return : return false if there an error,else true.
 **/
bool test_nb_moves_cur() {
  game g = game_new_empty_ext(12, 12, false);
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
  game_play_one_move(g, 3);

  if (game_nb_moves_cur(g) ==0) {
    game_delete(g);
    return false;
  }
  game_delete(g);
  return true;
}
/**
 *@brief : test the  game_set_cell_init() function
 *@return return false if there are an error,else true.
 **/
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
  game_delete(g);
  return true;
}
//It checks if the grid is uniform
bool is_grid_red(game g) {
  for (uint x = 0; x < game_width(g); x++) {
    for (uint y = 0; y < game_height(g); y++) {
      if (game_cell_current_color(g, x, y) != RED) {
        game_delete(g);
        return false;
      }
    }
  }
  
  return true;
}
/**
 *@brief : test the  game_is_over() function
 *@return return false if there are an error,else true.
 **/
bool test_game_is_over() {

  // All cells of the same color and nbCoupJoué < nbMax
  game t1 = game_new_empty_ext(12, 12, false);
  if (t1 == NULL){
      fprintf(stderr,"Error: Null pointer \n");
      game_delete(t1);
      return false;
  }
  game_set_max_moves(t1, 3);
  game_set_cell_init(t1, 0, 0, BLUE);
  if (game_is_over(t1)) {
    fprintf(stderr, "echec game_is_over: censé returner jeux non terminé \n");
    game_delete(t1);
    return false;
  }
  game_play_one_move(t1, RED);
  if (!game_is_over(t1)) {
    fprintf(stderr, "echec game_is_over: censé retourner jeux terminé \n");
    game_delete(t1);
    return false;
  }
  if (game_nb_moves_cur(t1) >= 3) {
    fprintf(stderr, "echec game_is_over: nbCoupjoués>=nbMax \n");
    game_delete(t1);
  }
  if (game_is_over(t1) && is_grid_red(t1) == false) {
    fprintf(stderr, "echec test de game_is_over: grille non uniforment rouge");
    game_delete(t1);
  }
  // free the memory
  game_delete(t1);
  return true;
}
/**
 *@brief : test the game_is_wrapping() function
 *@return return false if there are an error, else it return true,else true.
 **/
bool test_game_is_wrapping(){
    game g = game_new_empty_ext(2, 5, true);
    if (g==NULL){
      fprintf(stderr,"Error: NULL pointer \n");
      game_delete(g);
      return false;
    }
    if (game_is_wrapping(g)!=true){
        fprintf(stderr,"Error: check game_witdh() \n");
        game_delete(g);
        return false;
    }
    game_delete(g);
    return true;
}
/**
 *@brief : test the  game_width() function
 *@return return false if there are an error,else true.
 **/
bool test_game_width(){
    game g = game_new_empty_ext(2, 5, true);
    if (g==NULL){
      fprintf(stderr,"Error: NULL pointer \n");
      game_delete(g);
      return false;
    }
    if (game_width(g)!=2){
        fprintf(stderr,"Error: check game_witdh() \n");
        game_delete(g);
        return false;
    }
    game_delete(g);
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
  }else if (((strcmp("game_width", argv[1]) == 0))) {
    ok = test_game_width();
  }else if (((strcmp("game_is_wrapping", argv[1]) == 0))) {
   ok = test_game_is_wrapping();
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
