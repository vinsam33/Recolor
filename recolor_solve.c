#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "game_io.h"
#include "string.h"
#include "time.h"
#include <math.h>

/*#define FILE_SIZE 300
typedef enum { FIND_ONE, NB_SOL, FIND_MIN }e_fonctions;
FILE* my_file = NULL;
//fonction qui permet de trouver une solution

color* FIND_ONE(cgame g){
    const uint nb_moves_max = nb_move_max(g);
    color cell_cur = game_cell_current_color(g, 0, 0);
    uint genere_solution;
    color* solutions= malloc(nb_moves_max* sizeof(color));
    if( solutions == NULL){
        fprintf(stderr, "Problem allocation memory \n");
        exit(EXIT_FAILURE);
    }
    uint max_col = ... // si on a une fonction qui genere le max de couleur.pour l'instant je vois pas trop.
    time_t temps;
    srand((unsigned) time(&temps));

    NEW_GENERATE:
    game_restart(g);

    for(uint i=0; i < nb_moves_max; i++){
        // j'utilise do while parce que je pense qu'il faut jouer au moins une fois
        do {
            genere_solution= rand () % (max_col+1);
        } while (genere_solution == cell_cur);
        game_play_one_move(g, genere_solution);
        cell_cur = genere_solution;
        solutions[i] = genere_solution;

        if( game_is_over(g) ){
            break;
        }
    }
    if(!game_is_over(g) ){
        goto NEW_GENERATE;
    
        return solutions;
    }
}*/
void NB_SOL();

void FIND_MIN (char* fichier_pb, char* fichier_sol){
  if (fichier_pb == NULL || fichier_sol==NULL){
    fprintf(stderr, "NULL pointer");
    exit(EXIT_FAILURE);
  }
  FIND_ONE (fichier_pb, fichier_sol); // Call FIND_ONE to know if there are solutions, if not it's not necessary to apply this function
  FILE *f = fopen(fichier_sol, "r");  // Open fichier_sol only in read to verify if there are solutions
  if (f == NULL) {
    fprintf(stderr, "error f\n");
    exit(EXIT_FAILURE);
  }
  char *s = malloc(sizeof(char) * MAXLINELEN);
  if (s == NULL) {
    fprintf(stderr, "Null pointer\n");
    fclose(f);
    exit(EXIT_FAILURE);
  }
  color *cells = malloc(sizeof(color) * MAXLINELEN);
  int i = 0;
  s = fgets(s, MAXLINELEN, f);
  char *d = strtok(s, " \n");
  if (d=="N"){
    d = strtok(NULL, " \n");
    if (d=="O"){
      fprintf(stderr,"No solution in this game");
      free(d); 
      free(s);
      fclose(f);
      exit(EXIT_FAILURE);
    }
  }
  printf("They are solution(s)"); //// So apply the function
  cells[i] = d ;
  i++ ;
  while (fgets(s, MAXLINELEN, f) != NULL) {
    char *tok = strtok(s, " \n");
    while (tok != NULL) {
      cells[i] = tok;
      i++;
      tok = strtok(NULL, " \n");
    }
  }
  free(d);
  free(s);
  fclose(f);
  game g = game_load("fichier_pb");
  uint cpt = 0;
  color *t = malloc(game_nb_moves_max * sizeof(color));
  uint x=-1;
  color c = 5;
  uint nbmax = i-1;
  MIDDLE;
  while (cpt != 32){
    while (x+1 <= game_nb_moves_max(g)){
      srand(time(NULL));
      c = rand() % 16;
      game_play_one_move(g, c);
      x++;
      t[x] = c;
      if (game_is_over(g)){
        if (x+1 < nb_max){
          nb_max = x+1;
          game_nb_moves_max(g) = nb_max; //
          free(cells); 
          color *cells = malloc(sizeof(color) * nb_max);
          for (uint u=0; u<x+1; u++){
            cells[u]=t[u];
          }
          cpt=0; 
          game_restart(g); 
          goto MIDDLE; 
        }
        else{
          cpt++;
          game_restart(g); 
          goto MIDDLE; 
        }
      }
    }
    x = -1;
    game_restart(g); 
    goto MIDDLE; 
  } 
  x=0; 
  FILE *f = fopen(fichier_sol, "w"); 
  if (f==NULL){
    fprintf(stderr, "NULL pointer"); 
    exit(EXIT_FAILURE); 
  }
  while (x<nb_max){
    fprintf(f, "%c", cells[x]); 
  }
  fclose(f); 
  free(cells); 
  free(t); 
  game_delete(g); 
}  

int main(int argc, char* argv[]){
    if(argc !=4){
        fprintf(stderr,"error");
        return EXIT_FAILURE;
    }
    game g = game_load(argv[2]);
    if (g==NULL){
        fprintf(stderr,"ERROR : load %s",argv[2]);
        exit(EXIT_FAILURE);
    }
    if (strcmp(argv[1],"FIND_ONE")==0){
        FIND_ONE();
    }else if(strcmp(argv[1],"NB_SOL")==0){
        uint cpt =0 ;
        NB_SOL(g,game_cell_current_color(g,0,0),argv[3],10,1);
          
    }else if (strcmp(argv[1],"FIND_MIN")==0){
        FIND_MIN();
            
    }
    game_delete(g);
    
    return EXIT_SUCCESS;
}