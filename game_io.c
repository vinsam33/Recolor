
#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include "game_io.h"

#define MAXLINELEN 4096

game game_load(char *filename) {
    if (filename==NULL){
        fprintf(stderr, "Null pointer\n"); 
        exit(EXIT_FAILURE);
    }
    FILE * f = fopen("filename","r");
    if (f == NULL){
        exit(EXIT_FAILURE); 
    }
    char *s = malloc(sizeof (char)*MAXLINELEN); 
    if(s==NULL){
        fprintf(stderr, "Null pointer\n"); 
        fclose(f); 
        exit(EXIT_FAILURE);
    }
    char * g = fgets(s, MAXLINELEN, f);
    if(g==NULL) {
        fprintf(stderr, "Null pointer\n"); 
        fclose(f); 
        exit(EXIT_FAILURE);
    }
    color *cells=NULL; 
    for (uint i=6; s[i]!='\n'; i++){
        cells[i-6] = s[i]; 
    }
    game ga = game_new_ext(s[4], s[3], cells, s[5], s[2]); 
    //game_new_empty_ext(s[0], s[1], s[2]); 
    fclose(f); 
    return ga; 
    //return NULL; 
}



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
