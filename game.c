#include <stdio.h>
#include <stdlib.h>

#include "game.h"



typedef unsigned int uint;
typedef const struct game_s *cgame;

struct game_s{
    color *tab; 
    uint nb_max;
    uint nb_curr; 
    game initgame; 
};

typedef struct game_s *game;

#define SIZE 12


//typedef enum color_e {RED, GREEN, BLUE, YELLOW, NB_COLORS} color;







game game_new(color *cells, uint nb_moves_max){
    return NULL;

}



game game_new_empty(){
    for (uint y=0;y<SIZE;y++){
        for (uint x=0; x<SIZE;x++){
            game_set_cell_init(g->tab[y*SIZE+x], x,y, RED);
            game_nb_moves_max(g)=0;
        }
    }

}

void game_set_cell_init(game g, uint x, uint y, color c){

}


void game_set_max_moves(game g, uint nb_max_moves){
    if (g==NULL){
        fprintf(stderr,"g can't be NULL");
        exit(EXIT_FAILURE); 
    }
    g->initgame->nb_max=nb_max_moves; 
    g->nb_max=nb_max_moves; 
    }


uint game_nb_moves_max(cgame g){
     return 0;

}


color game_cell_current_color(cgame g, uint x, uint y){
    if (g==NULL){
        return ;
    }
    return g->tab[y*SIZE+x];

}


uint game_nb_moves_cur(cgame g){
     return 0;

}


void game_play_one_move(game g, color c){
    if (g==NULL){
        fprintf(stderr, "g can't be null");
        exit(EXIT_FAILURE); 
    }
    
    firt_case=game_cell_current_color(g, 0, 0); 
    uint y=1, x=1; 
    cell_y=game_cell_current_color(g,0,y); 
    cell_x=game_cell_current_color(g,x,0); 

    while (first_case==cell_y && y<SIZE-1){
       cell_y=game_cell_current_color(g,0,y+1); 
       g->tab[0][y]=c;  
    }

    while (first_case==cell_x && x<SIZE-1){
        cell_x=game_cell_current_color(g,x+1,0); 
        g->tab[x][0]=c;
    }
    g->tab[0][0]=c; 
}

game game_copy(cgame g){
     return NULL;

}


void game_delete(game g){
    if (g==NULL){
        return;
    }
    free(g->tab);
    free(g);

}


bool game_is_over(cgame g){
     return true;

}


void game_restart(game g){

}

