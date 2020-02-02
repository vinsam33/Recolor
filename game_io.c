
#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include "game_io.h"
#include <string.h>

#define MAXLINELEN 4096

game game_load(char *filename) {
    if (filename==NULL){
        fprintf(stderr, "Null pointer\n");
        exit(EXIT_FAILURE);
    }
    FILE * f = fopen(filename,"r");
    if (f == NULL){
        fprintf(stderr,"error f\n");
        exit(EXIT_FAILURE);
    }
    char *s = malloc(sizeof (char)*MAXLINELEN);
    if(s==NULL){
        fprintf(stderr, "Null pointer\n");
        fclose(f);
        exit(EXIT_FAILURE);
    }
    s = fgets(s, MAXLINELEN, f);
    //int w,h;
    char *d = strtok(s, " \n");
    uint w=atoi(d); 

    d = strtok(NULL, " \n");
    uint h=atoi(d); 

    d = strtok(NULL, " \n");
    uint nb_max=atoi(d); 

    d = strtok(NULL, " \n");
    bool wrapping = d; 

    color *cells = malloc(sizeof(color)*MAXLINELEN);
    int i = 0;
    while (fgets(s, MAXLINELEN, f) != NULL){
        char *tok = strtok(s, " \n");
        while (tok != NULL){
            int n = atoi(tok);
            cells[i] = n;
            i++;
            tok = strtok(NULL, " \n"); 
        }
    }
    //game ga = game_new_ext(s[4], s[3], cells, s[5], s[2]);
    game ga = game_new_ext(w, h, cells, nb_max, wrapping); 
    free(s); 
    free(cells); 
    fclose(f);
    return ga;
}



void game_save(cgame g, char *filename) {
    if ( filename==NULL ){
        fprintf(stderr, "NULL pointer");
        exit(EXIT_FAILURE);
    }
    FILE * f=fopen(filename, "w");
    if(f==NULL){
        fprintf(stderr, "NULL pointer");
        exit(EXIT_FAILURE);
    }

    if ( game_is_wrapping(g)){
        fprintf(f, "%d %d %d %s \n", game_width(g), game_height(g), game_nb_moves_max(g), "S");
    }
    else {
        fprintf(f, "%d %d %d %s \n", game_width(g), game_height(g), game_nb_moves_max(g), "N");
    }
    for(uint y=0; y < game_height(g); y++){
        for(uint x=0; x < game_width(g); x++){
            fprintf(f, "%d ", game_cell_current_color(g,x,y));
        }
        fprintf(f,"\n");
    }
    fclose(f);
}



/*void game_save(cgame g, char *filename) {
    if ( filename==NULL ){
        fprintf(stderr, "NULL pointer");
        exit(EXIT_FAILURE);
    }
    FILE * f=fopen(filename, "w");
    if(f==NULL){
        fprintf(stderr, "NULL pointer");
        exit(EXIT_FAILURE);
    }
    char *c;
    c[1] = game_width(g);
    c[2] = game_height(g);
    c[3] = game_nb_moves_max(g);
    c[4] = game_is_wrapping(g);
    for (uint y=0; y<game_height(g);y++){
        for (uint x=0; x < game_width(g); x++){
            c[y * game_width(g) + x + 5] = game_cell_current_color(g, x, y);
        } 
    }
    fputs(c, f); 
    fclose(f);
}*/

//int main(void) { return EXIT_SUCCESS; }