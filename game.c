#include <stdio.h>
#include <stdlib.h>

#include "game.h"



typedef unsigned int uint;
typedef const struct game_s *cgame;

struct game_s{
    color **tab; 
    uint nb_max;
    uint nb_curr; 
    game initgame; 
};

typedef struct game_s *game;

#define SIZE 12


//typedef enum color_e {RED, GREEN, BLUE, YELLOW, NB_COLORS} color;







game game_new(color *cells, uint nb_moves_max){
    game g = malloc(sizeof(struct game_s));
    if (g == NULL){
        fprintf(stderr, "Problem allocation memory\n");
        exit(EXIT_FAILURE);
    }
    g->tab = (color**) malloc(SIZE*sizeof(color*));
    if (g->tab == NULL){
        free(g);
        fprintf(stderr, "Problem allocation memory\n");
        exit(EXIT_FAILURE);
    }
    for (uint i=0 ; i<SIZE ; i++){
        g->tab[i] = (color*) malloc(SIZE*sizeof(color));
        if (g->tab[i] == NULL){
            free(g->tab);
            free(g);
            fprintf(stderr, "Problem allocation memory\n");
            exit(EXIT_FAILURE);
        }
    }
    for (uint i=0 ; i<SIZE ; i++){
        for (uint j=0 ; j<SIZE ; j++){
            g->tab[i][j] = (*cells);
        }
    }
    if (nb_moves_max <= 0){
        for (uint i=0 ; i<SIZE ; i++){
            for (uint j=0 ; j<SIZE ; j++){
                free(g->tab[i]);
            }
        free(g->tab);
        free(g);
        fprintf(stderr, "Nb_max_moves less or egal than 0\n");
        exit(EXIT_FAILURE);
        }
    }
    g->nb_max = nb_moves_max;
    return g;
}



game game_new_empty(){
    game g = malloc (sizeof(game));
    if (g==NULL){
        return;
    }
    g->tab=malloc(sizeof(color));
    if(g->tab==NULL){
        return;
    }
    for (uint y=0;y<SIZE;y++){
        for (uint x=0; x<SIZE;x++){
            game_set_cell_init(g, x,y, RED);
            game_set_max_moves(g,0);
        }
    }
    return g;

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
    if (g == NULL){
        fprintf(stderr, "Problem allocation memory\n");
        exit(EXIT_FAILURE);
    }
    return g->nb_max;
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
    if (g == NULL){
        fprintf(stderr, "Problem allocation memory\n");
        exit(EXIT_FAILURE);
    }
    game g2;
    g2->tab = (color**) malloc(SIZE*sizeof(color*));
    if (g2->tab == NULL){
        free(g);
        fprintf(stderr, "Problem allocation memory\n");
        exit(EXIT_FAILURE);
    }
    for (uint i=0 ; i<SIZE ; i++){
        g2->tab[i] = (color*) malloc(SIZE*sizeof(color));
        if (g2->tab[i] == NULL){
            free(g->tab);
            free(g);
            fprintf(stderr, "Problem allocation memory\n");
            exit(EXIT_FAILURE);
        }
    }
    for (uint i=0 ; i<SIZE ; i++){
        for (uint j=0 ; j<SIZE ; j++){
            g2->tab[i][j] = g->tab[i][j];
        }
    }
    return g2;
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

