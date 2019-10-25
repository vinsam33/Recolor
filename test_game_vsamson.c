#include <stdlib.h>
#include <stdio.h>
#include "game.h"
#include "game_io.h"

typedef unsigned int uint;


bool test_game_new_empty(){
    color cells [144] = {0,0,0,2,0,2,1,0,1,0,3,0,0,3,3,1,1,1,1,3,2,0,1,0,1,0,1,2,3,2,3,2,0,3,3,2,2,3,1,0,3,2,1,1,1,2,2,0,2,1,2,3,3,3,3,2,0,1,0,0,0,3,3,0,1,1,2,3,3,2,1,3,1,1,2,2,2,0,0,1,3,1,1,2,1,3,1,3,1,0,1,0,1,3,3,3,0,3,0,1,0,0,2,1,1,1,3,0,1,3,1,0,0,0,3,2,3,1,0,0,1,3,3,1,1,2,2,3,2,0,0,2,2,0,2,3,0,1,1,1,2,3,0,1};
    game g = game_new(cells, 10);
    if(g==NULL){
        return false;
    }
    game_new_empty();
    return true;
}
bool test_game_cell_current_color(){
    game g = game_new_empty();
    if(!g){
        return false;
    }for (uint y=0; y < SIZE; y++){
        for (uint x=0; x < SIZE ; x++){
            game_set_cell_init(g,x,y, BLUE);
            if (game_cell_current_color(g,x,y) != BLUE){
                return false;
            }
        }
    }
    return true;
}

bool test_game_delete(){   
    color cells [144] = {0,0,0,2,0,2,1,0,1,0,3,0,0,3,3,1,1,1,1,3,2,0,1,0,1,0,1,2,3,2,3,2,0,3,3,2,2,3,1,0,3,2,1,1,1,2,2,0,2,1,2,3,3,3,3,2,0,1,0,0,0,3,3,0,1,1,2,3,3,2,1,3,1,1,2,2,2,0,0,1,3,1,1,2,1,3,1,3,1,0,1,0,1,3,3,3,0,3,0,1,0,0,2,1,1,1,3,0,1,3,1,0,0,0,3,2,3,1,0,0,1,3,3,1,1,2,2,3,2,0,0,2,2,0,2,3,0,1,1,1,2,3,0,1};
    game g = game_new(cells, 10);
    if( g == NULL ){
        exit(EXIT_FAILURE);
    }
    game_delete(g);
    return true;
}


int main(void){
    color cells [144] = {0,0,0,2,0,2,1,0,1,0,3,0,0,3,3,1,1,1,1,3,2,0,1,0,1,0,1,2,3,2,3,2,0,3,3,2,2,3,1,0,3,2,1,1,1,2,2,0,2,1,2,3,3,3,3,2,0,1,0,0,0,3,3,0,1,1,2,3,3,2,1,3,1,1,2,2,2,0,0,1,3,1,1,2,1,3,1,3,1,0,1,0,1,3,3,3,0,3,0,1,0,0,2,1,1,1,3,0,1,3,1,0,0,0,3,2,3,1,0,0,1,3,3,1,1,2,2,3,2,0,0,2,2,0,2,3,0,1,1,1,2,3,0,1};
    game g = game_new(cells, 10);
    bool nouveaux = test_game_new_empty();
    if(nouveaux==true){
        fprintf(stderr,"EXECUTING OF game_new_empty IS : REUSSITE\n\n ");
    }else{
        fprintf(stderr,"EXECUTING OF game_new_empty IS : FAILURE\n\n ");
        return EXIT_FAILURE;
    }
    bool color = test_game_cell_current_color(g,2,SIZE-1);
    if (color ==true){
        fprintf(stderr,"EXECUTING OF game_cell_current_color IS : REUSSITE\n\n");
    }else{
        fprintf(stderr,"EXECUTING OF game_cell_current_color IS : FAILURE\n\n ");
        return EXIT_FAILURE;
    }
    bool supr = test_game_delete();
    if(supr==true){
        fprintf(stderr,"EXECUTING OF game_delete IS : REUSSITE\n\n ");

    }else{
        fprintf(stderr,"EXECUTING OF game_delete IS : FAILURE\n\n ");
        return EXIT_FAILURE;

    }
    return EXIT_SUCCESS;
}