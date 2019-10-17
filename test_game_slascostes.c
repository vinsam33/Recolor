#include <stdlib.h>
#include <stdio.h>
#include "game.h"
#include "game_io.h"

bool test_game_new(){
    game g= game_new(color *cells,nb_moves_max);
    if (g == NULL){
        return false;
    }
    if (nb_max_moves <= 0){
        return false;
    }
    for(unsigned int x=0 ; x<12 ; x++){
        for(unsigned int y=0 ; y<12; y++){
            if (game_cell_current_color(g, x, y) != cells){
                return false;
            }
        }
    }
    return true;
}
