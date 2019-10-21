#include <stdlib.h>
#include <stdio.h>
#include "game.h"
#include "game_io.h"


bool test_game_new(color *cells, unsigned int nb_moves_max){
    game g= game_new(cells,nb_moves_max);
    if (g == NULL){
        return false;
    }
    if (nb_moves_max <= 0){
        return false;
    }
    for(unsigned int x=0 ; x<nb_moves_max ; x++){
        for(unsigned int y=0 ; y<nb_moves_max ; y++){
            if (game_cell_current_color(g, x, y) != *cells){
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
    unsigned int nb_max = game_nb_moves_max(g);
    if (nb_max < 0){
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
    return EXIT_SUCCESS;
 }