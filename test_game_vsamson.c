#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "game_io.h"

bool test_game_new_empty() {
  game g = game_new_empty();
  if (g == NULL) {
    game_delete(g);
    return false;
  } //verif dimensions
  if(!game_is_over(g)){
    fprintf(stderr, "ERROR : GAME_IS_OVER\n\n");
    game_delete(g);
    return false;
  }//verif moves
  if(game_nb_moves_cur(g) !=0 || game_nb_moves_max(g) != 0 ){
    fprintf(stderr, "ERROR : MOVE\n\n");
    game_delete(g);
    return false;
  }
  for (unsigned int y = 0; y < game_height(g); y++) {
    for (unsigned int x = 0; x < game_width(g); x++) {
      if (game_cell_current_color(g, x, y) != RED) {
        game_delete(g);
        return false;
      }
    }
  }
  game_delete(g);
  return true;
}

bool test_game_cell_current_color() {
  game g = game_new_empty();
  if (!g) {
    fprintf(stderr,"ERROR\n\n");
    game_delete(g);
    return false;
  }
  for (uint y = 0; y < game_height(g); y++) {
    for (uint x = 0; x < game_width(g); x++) {
      game_set_cell_init(g, x, y, BLUE);
      if (game_cell_current_color(g, x, y) != BLUE) {
        game_delete(g);
        return false;
      }
    }
  }
  game_delete(g);
  return true;
}

bool test_game_delete() {
  color cells[144] = {
      0, 0, 0, 2, 0, 2, 1, 0, 1, 0, 3, 0, 0, 3, 3, 1, 1, 1, 1, 3, 2, 0, 1, 0,
      1, 0, 1, 2, 3, 2, 3, 2, 0, 3, 3, 2, 2, 3, 1, 0, 3, 2, 1, 1, 1, 2, 2, 0,
      2, 1, 2, 3, 3, 3, 3, 2, 0, 1, 0, 0, 0, 3, 3, 0, 1, 1, 2, 3, 3, 2, 1, 3,
      1, 1, 2, 2, 2, 0, 0, 1, 3, 1, 1, 2, 1, 3, 1, 3, 1, 0, 1, 0, 1, 3, 3, 3,
      0, 3, 0, 1, 0, 0, 2, 1, 1, 1, 3, 0, 1, 3, 1, 0, 0, 0, 3, 2, 3, 1, 0, 0,
      1, 3, 3, 1, 1, 2, 2, 3, 2, 0, 0, 2, 2, 0, 2, 3, 0, 1, 1, 1, 2, 3, 0, 1};
  game g = game_new(cells, 10);
  if (g == NULL) {
    exit(EXIT_FAILURE);
  }
  game_delete(g);
  return true;
}
bool test_game_height(){
  game g = game_new_empty_ext(5, 5, true);
    if (g==NULL){
      fprintf(stderr,"error pointer\n");
      game_delete(g);
      return false;
    }
    if (game_height(g)!=5){
        fprintf(stderr,"ERROR HEIGHT\n");
        game_delete(g);
        return false;
    }game_delete(g);

    return true;
}

int main(void) {
  bool nouveaux = test_game_new_empty();
  if (nouveaux == true) {
    fprintf(stderr, "EXECUTING OF game_new_empty IS : SUCCESS\n\n ");
  } else {
    fprintf(stderr, "EXECUTING OF game_new_empty IS : FAILURE\n\n ");
    return EXIT_FAILURE;
  }
  bool color = test_game_cell_current_color();
  if (color == true) {
    fprintf(stderr, "EXECUTING OF game_cell_current_color IS : SUCCESS\n\n");
  } else {
    fprintf(stderr, "EXECUTING OF game_cell_current_color IS : FAILURE\n\n ");
    return EXIT_FAILURE;
  }
  bool supr = test_game_delete();
  if (supr == true) {
    fprintf(stderr, "EXECUTING OF game_delete IS : SUCCESS\n\n ");

  } else {
    fprintf(stderr, "EXECUTING OF game_delete IS : FAILURE\n\n ");
    return EXIT_FAILURE;
  }
  bool height = test_game_height();
  if(height==true){
    fprintf(stderr, "EXECUTING OF height IS : SUCCESS\n\n ");
  }else{
    fprintf(stderr, "EXECUTING OF height IS : FAILURE\n\n ");
  }
  return EXIT_SUCCESS;
}
