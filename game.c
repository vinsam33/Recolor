#include <stdio.h>
#include <stdlib.h>

#include "game.h"

struct game_s{
    int x;
};

#define SIZE 12

typedef unsigned int uint;
typedef const struct game_s *cgame;
//typedef enum color_e {RED, GREEN, BLUE, YELLOW, NB_COLORS} color;



typedef struct game_s *game;



game game_new(color *cells, uint nb_moves_max){
    return NULL;

}



game game_new_empty(){
     return NULL;

}

void game_set_cell_init(game g, uint x, uint y, color c){

}


void game_set_max_moves(game g, uint nb_max_moves){

}


uint game_nb_moves_max(cgame g){
     return 0;

}


color game_cell_current_color(cgame g, uint x, uint y){
     return RED;

}


uint game_nb_moves_cur(cgame g){
     return 0;

}


void game_play_one_move(game g, color c){

}

game game_copy(cgame g){
     return NULL;

}


void game_delete(game g){

}


bool game_is_over(cgame g){
     return true;

}


void game_restart(game g){

}

