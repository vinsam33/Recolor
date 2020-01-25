
#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include "game_io.h"

game game_load(char *filename) { return NULL; }

void game_save(cgame g, char *filename) {
    if ( filename==NULL ){
        fprintf(stderr, "NULL pointer");
        exit(EXIT_FAILURE);
    }
    FILE * f=fopen(filename, "r");
    if(f==NULL){
        fprintf(stderr, "NULL pointer");
        exit(EXIT_FAILURE);
    } 
    fprintf(f, "%d %d %d %d \n", game_width(g), game_height(g), g->nb_max, game_is_wrapping(g));
    for(uint x=0; x < game_width(g); x++){
        for(uint y=0; game_height(g); y++){
            fprintf(f, "%d ", g->tab[x][y]);
        }
    }
    fclose(f);
}
int main(void) { return EXIT_SUCCESS; }
