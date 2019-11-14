#include <stdio.h>
#include <stdlib.h>

#include "game.h"



typedef unsigned int uint;
typedef const struct game_s *cgame;

struct game_s{
    color **tab;
    uint nb_max;
    uint nb_curr;
    color **initgame;
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
        fprintf(stderr, "Problem allocation memory\n");
        exit(EXIT_FAILURE);
    }
    g->tab=malloc(sizeof(color*));
    if(g->tab==NULL){
        free(g);
        fprintf(stderr, "Problem allocation memory\n");
        exit(EXIT_FAILURE);
    }for (uint i=0;i<SIZE;i++){
        g->tab[i]=malloc(SIZE*sizeof(color));
            if (g->tab[i]==NULL){
                free(g);
                fprintf(stderr, "Problem allocation memory\n");
                exit(EXIT_FAILURE);
            }

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
    if(g==NULL){
        fprintf(stderr, "Error: do not game null");
        exit(EXIT_FAILURE);
    }
    if((x<SIZE)&& (y<SIZE) && (0<= c)&& (c <  NB_COLORS)){
        g->tab[x][y]=c;
        /*g->initgame[x][y]=c;*/
    }
    return ;
}

void game_set_max_moves(game g, uint nb_max_moves){
    if (g==NULL){
        fprintf(stderr,"g can't be NULL");
        exit(EXIT_FAILURE);
    }
    //g->initgame->nb_max=nb_max_moves;
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
        fprintf(stderr, "Problem allocation memory\n");
        exit(EXIT_FAILURE);
    }
    return g->tab[x][y];
}


uint game_nb_moves_cur(cgame g){
    if(g==NULL){
        fprintf(stderr, "Error: do not game null");
        exit(EXIT_FAILURE);
    }
    return g->nb_curr;
}

void remplissage(game g, color cible, color rep, uint x, uint y){
    if(g==NULL){
        fprintf(stderr, "g can't be null");
        exit(EXIT_FAILURE);
    }
    if(game_cell_current_color(g, x, y) == cible){
        g->tab[x][y] = rep;
        if(y-1 >= 0){
            remplissage(g, cible, rep, x, y-1); // Remplissage au nord
        }
        if(y+1 <= SIZE-1){
            remplissage(g, cible, rep, x, y+1); // Remplissage au sud
        }
        if(x+1 <= SIZE-1){
            remplissage(g, cible, rep, x+1, y); // Remplissage à l'est
        }
        if(x-1 >= 0){
            remplissage(g, cible, rep, x-1, y); // Remplissage à l'ouest
        }
    }
}

void game_play_one_move(game g, color c){
    /*if (g==NULL){
        fprintf(stderr, "g can't be null");
        exit(EXIT_FAILURE);
    }

    color firt_case=game_cell_current_color(g, 0, 0);
    uint y=1, x=1;
    color cell_y=game_cell_current_color(g,0,y);
    color cell_x=game_cell_current_color(g,x,0);

    while (first_case==cell_y && y<SIZE-1){
       cell_y=game_cell_current_color(g,0,y+1);
       g->tab[0][y]=c;
    }

    while (first_case==cell_x && x<SIZE-1){
        cell_x=game_cell_current_color(g,x+1,0);
        g->tab[x][0]=c;
    }
    g->tab[0][0]=c;*/
    if(g==NULL){
        fprintf(stderr, "g can't be null");
        exit(EXIT_FAILURE);
    }
    color first_case = game_cell_current_color(g, 0, 0);
    if(first_case != c){
        remplissage(g, first_case, c, 0, 0);
    }
}

game game_copy(cgame g){
    if (g == NULL){
        fprintf(stderr, "Problem allocation memory\n");
        exit(EXIT_FAILURE);
    }
    game g2;
    g2->tab = (color**) malloc(SIZE*sizeof(color*));
    if (g2->tab == NULL){
        free(g2);
        fprintf(stderr, "Problem allocation memory\n");
        exit(EXIT_FAILURE);
    }
    for (uint i=0 ; i<SIZE ; i++){
        g2->tab[i] = (color*) malloc(SIZE*sizeof(color));
        if (g2->tab[i] == NULL){
            free(g2->tab);
            free(g2);
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
    for (uint x=0; x<SIZE;x++){
        free(g->tab[x]);
    }
    free(g->tab);
    free(g);

}

bool game_is_over(cgame g){
    if(g==NULL){
        fprintf(stderr, "Error: do not game null");
        exit(EXIT_FAILURE);
    }
    color c = game_cell_current_color(g,0,0);
    if(g->nb_max==g->nb_curr){
        for (int x=0; x<SIZE; x++){
            for( int y=0; y<SIZE; y++){
                if(c != game_cell_current_color(g,x,y) ){
                    return false;
                }
            }
        }
	return true;
    }
}


void game_restart(game g){

}

