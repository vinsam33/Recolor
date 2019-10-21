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

bool test_game_play_one_move (color c){
  game g = game_new_empty();
  if (!g){
    fprintf(stderr,"Error : invalid game");
    return false;
  }
  game_play_one_move(g,c);
  if (c>=NB_COLORS || c<=NB_COLORS){
    fprintf(stderr,"Error : invalid game");
    return false;
  }
  return true; 
}

bool test_game_restart (game g){
  game_restart(g);
  unsigned int x=0, y=0;
  color c= RED; 
  while (x<SIZE){
    while (y<SIZE){
      game_set_cell_init(g,x,y,c);
      if (game_cell_current_color(g,x,y) != RED){
        fprintf(stderr,"Error : Bad color, game_restart failed");
        return false;
      }y++; 
    }x++; 
  }
  if (game_nb_moves_cur(g) != 0){
    fprintf(stderr,"Error : Number of moves different from 0");
    return false;
  }else{
    fprintf(stderr,"Error : too much number of moves");
    return false;
  }
  return true; 
}

int main(void){
    color cells [144] = {0,0,0,2,0,2,1,0,1,0,3,0,0,3,3,1,1,1,1,3,2,0,1,0,1,0,1,2,3,2,3,2,0,3,3,2,2,3,1,0,3,2,1,1,1,2,2,0,2,1,2,3,3,3,3,2,0,1,0,0,0,3,3,0,1,1,2,3,3,2,1,3,1,1,2,2,2,0,0,1,3,1,1,2,1,3,1,3,1,0,1,0,1,3,3,3,0,3,0,1,0,0,2,1,1,1,3,0,1,3,1,0,0,0,3,2,3,1,0,0,1,3,3,1,1,2,2,3,2,0,0,2,2,0,2,3,0,1,1,1,2,3,0,1};
    unsigned int max=12;
    game g = game_new(cells, max);
    printf(" Game_set_max_moves\n");
    bool daccord= test_game_set_max_moves(max);
    if (daccord){
      fprintf(stderr,"Execution of game_set_max_moves : Success");
    }else{
      fprintf(stderr,"Execution of game_set_max_moves : Denied");
      return EXIT_FAILURE; 
    }

    bool ok= test_game_play_one_move(RED);
    if (ok){
      fprintf(stderr,"Execution of test_game_play_one_move : Success");
    }else{
      fprintf(stderr,"Execution of test_game_play_one_move : Denied");
      return EXIT_FAILURE; 
    }

    bool okay= test_game_restart(g);
    if(okay){
      fprintf(stderr,"Execution of game_restart : Success");
    }else{
      fprintf(stderr,"Execution of game_restart : Denied");
      return EXIT_FAILURE; 
    }

    return EXIT_SUCCESS;
}
