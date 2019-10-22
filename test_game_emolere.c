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
    fprintf(stderr,"Error : invalid game\n\n");
    return false;
  }
  game_set_max_moves(g, max);
  if (game_nb_moves_max(g) != max){
    fprintf(stderr,"Error : too much number of moves\n\n" );
    return false;
  }
  return true;
}

bool test_game_play_one_move (color c){
  game g = game_new_empty();
  if (!g){
    fprintf(stderr,"Error : invalid game\n\n");
    return false;
  }
  game_play_one_move(g,c);
  if (c>=NB_COLORS || c<=0){
    fprintf(stderr,"Error : invalid game\n\n");
    return false;
  }
  return true; 
}

bool test_game_restart (){
  color cells [144] = {0,0,0,2,0,2,1,0,1,0,3,0,0,3,3,1,1,1,1,3,2,0,1,0,1,0,1,2,3,2,3,2,0,3,3,2,2,3,1,0,3,2,1,1,1,2,2,0,2,1,2,3,3,3,3,2,0,1,0,0,0,3,3,0,1,1,2,3,3,2,1,3,1,1,2,2,2,0,0,1,3,1,1,2,1,3,1,3,1,0,1,0,1,3,3,3,0,3,0,1,0,0,2,1,1,1,3,0,1,3,1,0,0,0,3,2,3,1,0,0,1,3,3,1,1,2,2,3,2,0,0,2,2,0,2,3,0,1,1,1,2,3,0,1};
  game(g)=game_new(cells,12); 
  game_play_one_move(g,2);
  game_restart(g);
  
  if (!game_new_empty()){
    fprintf(stderr,"Error : Bad color, game_restart failed\n\n");
    return false; 
  }
  if (game_nb_moves_cur(g) != 0){
    fprintf(stderr,"Error : Number of moves different from 0\n\n");
    return false;
  }
  if (game_cell_current_color(g,0,0) != 0 ){
    fprintf(stderr,"Error : game_cell_current_color different from 0\n\n");
    return false;
  }else{
    return true;
  } 
}

int main(void){
    unsigned int max=12;
    printf("-- Start test of Game_set_max_moves\n");
    bool daccord= test_game_set_max_moves(max);
    if (daccord){
      fprintf(stderr,"Execution of game_set_max_moves : Success\n\n");
    }else{
      fprintf(stderr,"Execution of game_set_max_moves : Denied\n\n");
      return EXIT_FAILURE; 
    }

    printf("--Start test of game_play_one_move\n");
    bool ok= test_game_play_one_move(BLUE);
    if (ok){
      fprintf(stderr,"Execution of test_game_play_one_move : Success\n\n");
    }else{
      fprintf(stderr,"Execution of test_game_play_one_move : Denied\n\n");
      return EXIT_FAILURE; 
    }
    printf("--Start test of game_restart\n");
    bool okay= test_game_restart();
    if(okay){
      fprintf(stderr,"Execution of game_restart : Success\n\n");
    }else{
      fprintf(stderr,"Execution of game_restart : Denied\n\n");
      return EXIT_FAILURE; 
    }

    return EXIT_SUCCESS;
}
