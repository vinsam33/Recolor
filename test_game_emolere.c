#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "game.h"

typedef unsigned int uint;

bool test_game_set_max_moves(uint max){
  game g = game_new_empty();
  if (!g){
    fprintf(stderr,"Error : invalid game");
    return false;
  }
  game_set_max_moves(g, max);
  if (game_nb_moves_max(g) != max){
    fprintf(stderr,"Error : too much number of moves" );
    return false;
  }
  return true;
}


int main(void){
    color cells [144] = {0,0,0,2,0,2,1,0,1,0,3,0,0,3,3,1,1,1,1,3,2,0,1,0,1,0,1,2,3,2,3,2,0,3,3,2,2,3,1,0,3,2,1,1,1,2,2,0,2,1,2,3,3,3,3,2,0,1,0,0,0,3,3,0,1,1,2,3,3,2,1,3,1,1,2,2,2,0,0,1,3,1,1,2,1,3,1,3,1,0,1,0,1,3,3,3,0,3,0,1,0,0,2,1,1,1,3,0,1,3,1,0,0,0,3,2,3,1,0,0,1,3,3,1,1,2,2,3,2,0,0,2,2,0,2,3,0,1,1,1,2,3,0,1};
    game g = game_new(cells, 12);
    printf(" Game_set_max_moves\n");
    bool daccord= test_game_set_max_moves(g, nb_max_moves);
    if (daccord){
      fprintf(stderr,"Execution of game_set_max_moves : Success");
    }else{
      fprintf(stderr,"Execution of game_set_max_moves : Denied");
    }

    return EXIT_SUCCESS;
}
