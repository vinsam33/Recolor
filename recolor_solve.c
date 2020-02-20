#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "game_io.h"
#include "string.h"
#include "time.h"
#include <math.h>

#define MAXLINELEN 4096

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


uint nb_colors (game g){
  uint i=0; 
  color *tab = malloc (sizeof(color)*16);
  color c;
  for (uint x=0; x < game_width(g); x++){
    for(uint y=0; y < game_height(g); y++){
      c = game_cell_current_color(g,x,y);
      uint a=0; 
      for (a=0; a < i; a++){
        if (tab[a]==c){
          break; 
        }
        if(a==i){
          tab[i]=c; 
          i++; 
        }
      }
    }
  }
  return i; 
}


color *colors_present (game g){
  uint i =0;
  color *tab = malloc (sizeof(color)*nb_colors[g]);
  color c;
  for (uint x=0; x < game_width(g); x++){
    for(uint y=0; y < game_height(g); y++){
      c = game_cell_current_color(g,x,y);
      uint a=0; 
      for (a=0; a < i; a++){
        if (tab[a]==c){
          break; 
        }
        if(a==i){
          tab[i]=c; 
          i++; 
        }
      }
    }
  }
  return tab; 
}

void FIND_ONE(char * game_curr, char * sol, uint nb_color){
    /*if(game_curr == NULL || sol == NULL){
        fprintf(stderr, "Pointer is null\n");
        exit(EXIT_FAILURE);
    }
    game g = game_load(game_curr);
    FILE *f = fopen(sol,"w");
    if(f == NULL){
        fprintf(stderr, "Pointer is null\n");
        exit(EXIT_FAILURE);
    }
    if(NB_SOL(g,game_curr,nb_color) == 0){
        fprintf(f,"NO SOLUTION\n");
        return;
    }
    uint nb_max = game_nb_moves_max(g);
    uint * t_sol = malloc(nb_max*sizeof(uint));
    if(t_sol == NULL){
        fprintf(stderr, "Problem allocation memory\n");
        exit(EXIT_FAILURE);
    }
    srand(time(NULL));
    uint i = 0;
    while(game_is_over(g) != true){
        if(i == nb_max-1){
            game_restart(g);
            i = 0;
        }
        t_sol[i] = rand() %nb_color;
        i++;
        game_play_move_one(g,t_sol[i]);
    }
    for(uint j=0 ; j<i ; j++){
        if(j != i){
            fprintf(f,"%d ",t_sol[j]);
        }
        else{
            fprintf(f,"%d\n",t_sol[j]);
        }
    }
    free(t_sol);
    fclose(f);
    game_delete(g);*/
    return; 
}

void save_nbsol (game g,char * file,uint cpt){
    if (g == NULL||file == NULL){
        exit(EXIT_FAILURE);
    }
    FILE * f =fopen(file, "w");
    if (f == NULL){
        exit(EXIT_FAILURE);
    }
    fprintf(f,"NB_SOL = %u\n",cpt);
    fclose(f);
    
}
uint NB_SOL_AUX(game g,uint nbcolors,game g2){
    color last_color = game_cell_current_color(g2,0,0);
    uint cpt = 0;
    if (game_is_over(g2)){
        return 1;
    }
    if(game_nb_moves_cur(g2) >= game_nb_moves_max(g2)){
        return 0;
    }
    
    for (color i = 0; i < nbcolors;i++){
        if( i != last_color ){
            g2=game_copy(g);
            game_play_one_move(g2,i);
            cpt = cpt + NB_SOL_AUX(g2,nbcolors,g2);
            game_delete(g2);
        }
    } 
    return cpt;
}
uint NB_SOL(game g, char * file, uint nbcolors){
    game g2 = game_copy(g);
    uint cpt = NB_SOL_AUX(g,nbcolors,g2);
    save_nbsol(g,strcat(file,".nbsol"),cpt);
    printf("nb_sol =%u\n",cpt);
    return cpt; 
}

void FIND_MIN (char* fichier_pb, char* fichier_sol){
  /*if (fichier_pb == NULL || fichier_sol==NULL){
    fprintf(stderr, "NULL pointer");
    exit(EXIT_FAILURE);
  }*/
  /*FIND_ONE (fichier_pb, fichier_sol, 5); // Call FIND_ONE to know if there are solutions, if not it's not necessary to apply this function
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
  char w=*d; 
  if (w=="N"){
    d = strtok(NULL, " \n");
    w=d; 
    if (w=="O"){
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
  color *t = malloc(game_nb_moves_max(g) * sizeof(color));
  uint x=-1;
  color c = 5;
  uint nbmax = i-1;
  while (cpt != 32){
    while (x+1 <= game_nb_moves_max(g)){
      srand(time(NULL));
      c = rand() % 16;
      game_play_one_move(g, c);
      x++;
      t[x] = c;
      if (game_is_over(g)){
        if (x+1 < nbmax){
          nbmax = x+1;
          game_set_max_moves(g, nbmax);//
          free(cells); 
          color *cells = malloc(sizeof(color) * nbmax);
          for (uint u=0; u<x+1; u++){
            cells[u]=t[u];
          }
          cpt=0; 
          game_restart(g); 
        }
        else{
          cpt++;
          game_restart(g); 
        }
      }
    }
    x = -1;
    game_restart(g); 
  } 
  x=0; 
  FILE *f2 = fopen(fichier_sol, "w"); 
  if (f2==NULL){
    fprintf(stderr, "NULL pointer"); 
    exit(EXIT_FAILURE); 
  }
  while (x<nbmax){
    fprintf(f2, "%c", cells[x]); 
  }
  fclose(f2); 
  free(cells); 
  free(t); 
  game_delete(g); */
  return; 
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
        FIND_ONE(argv[2], argv[3],5);
    }else if(strcmp(argv[1],"NB_SOL")==0){
        NB_SOL(g,argv[2],5); 
          
    }else if (strcmp(argv[1],"FIND_MIN")==0){
        FIND_MIN(argv[2], argv[3]);
            
    }
    game_delete(g);
    
    return EXIT_SUCCESS;
}