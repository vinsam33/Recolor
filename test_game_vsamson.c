#include <stdlib.h>
#include <stdio.h>
#include "game.h"
#include "game_io.h"

bool test_game_is_over(){
    game g = game_new(cells, 12)
    if(game_nb_moves_cur(g) <= game_nb_moves_max(g){
        return true;

    }else{
        return false;
    }
}