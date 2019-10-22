#include <stdlib.h>
#include <stdio.h>
#include "game.h"
#include "game_io.h"


bool test_game_new(color *cells, unsigned int nb_moves_max){
    game g= game_new(cells,nb_moves_max);
    if (g == NULL){
        return false;
    }
    unsigned int nb_max = game_nb_moves_max(g);
    if (nb_moves_max != nb_max){
        return false;
    }
    for(unsigned int y=0 ; y<SIZE ; y++){
        for(unsigned int x=0 ; x<SIZE ; x++){
            if (game_cell_current_color(g, x, y) != cells[y*SIZE + x]){
                return false;
            }
        }
    }
    return true;
}

bool test_game_nb_moves_max(){
    game g = game_new_empty();
    if (g == NULL){
        return false;
    }
    if (game_nb_moves_max(g) != 0){
        return false;
    }
    game_set_max_moves(g, 10);
    if (game_nb_moves_max(g) != 10){
        return false;
    }
    return true;
}

bool test_game_copy(cgame g){
    if (g == NULL){
        return false;
    }
    cgame g2 = game_copy(g);
    if (g2 == NULL){
        return false;
    }
    unsigned int nb_max = game_nb_moves_max(g);
    if (test_game_nb_moves_max() == true){
        for(unsigned int x=0 ; x<nb_max ; x++){
            for(unsigned int y=0 ; y<nb_max ; y++){
                if (game_cell_current_color(g2, x, y) != game_cell_current_color(g, x, y) ){
                    return false;
                }
            }
        }
        return true;
    }
    else{
        return false;
    }
}

int main (){
    color cells [144] = {0,0,0,2,0,2,1,0,1,0,3,0,0,3,3,1,1,1,1,3,2,0,1,0,1,0,1,2,3,2,3,2,0,3,3,2,2,3,1,0,3,2,1,1,1,2,2,0,2,1,2,3,3,3,3,2,0,1,0,0,0,3,3,0,1,1,2,3,3,2,1,3,1,1,2,2,2,0,0,1,3,1,1,2,1,3,1,3,1,0,1,0,1,3,3,3,0,3,0,1,0,0,2,1,1,1,3,0,1,3,1,0,0,0,3,2,3,1,0,0,1,3,3,1,1,2,2,3,2,0,0,2,2,0,2,3,0,1,1,1,2,3,0,1};
    game g = game_new(cells, 11);
    if(test_game_new(cells,11)){
        fprintf(stderr, "The execution of test_game_new is a SUCCESS\n");
    }else{
        fprintf(stderr, "The execution of test_game_new is a FAILURE\n");
        return EXIT_FAILURE;
    }
    if(test_game_nb_moves_max()){
        fprintf(stderr, "The execution of test_game_nb_moves_max is a SUCCESS\n");
    }else{
        fprintf(stderr, "The execution of test_game_nb_moves_max is a FAILURE\n");
        return EXIT_FAILURE;
    }
    if(test_game_copy(g)){
        fprintf(stderr, "The execution of test_game_copy is a SUCCESS\n");
    }else{
        fprintf(stderr, "The execution of test_game_copy is a FAILURE\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
 }