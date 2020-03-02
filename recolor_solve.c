#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "game_io.h"
#include "string.h"
#include "time.h"

#define MAXLINELEN 4096

uint max(game g){
  if (g==NULL){
    exit(EXIT_FAILURE);
  }
  uint c = game_cell_current_color(g, 0, 0);
  for (uint x = 0; x < game_width(g); x++) {
    for (uint y = 0; y < game_height(g); y++) {
      if (c < game_cell_current_color(g, x, y)){
        c = game_cell_current_color(g, x, y);
      }
    }
  }
  printf("nb_color = %u\n",c+1);
  return c+1;
}

/**
 * @brief give number max color in the game
 * @return number max color
 * g is the game.
 **/
uint nb_colors(game g) {
  uint i = 0;
  color* tab = malloc(sizeof(color) * 16);
  color c;
  for (uint x = 0; x < game_width(g); x++) {
    for (uint y = 0; y < game_height(g); y++) {
      c = game_cell_current_color(g, x, y);
      uint a = 0;
      for (a = 0; a < i; a++) {
        if (tab[a] == c) {
          break;
        }
      }
      if (a == i) {
        tab[i] = c;
        i++;
      }
    }
  }
  free(tab);
  return i;
}

/**
 * @brief give colors present at least one time.
 * @return colors present
 * g is the game.
 **/
color* colors_present(game g) {
  uint i = 0;
  color* tab = malloc(sizeof(color) * nb_colors(g));
  color c;
  bool is_in = false;
  for (uint y = 0; y < game_height(g); y++) {
    for (uint x = 0; x < game_width(g); x++) {
      c = game_cell_current_color(g, x, y);
      uint a = 0;
      is_in = false;
      for (a = 0; a <= i; a++) {
        if (tab[a] == c) {
          is_in = true;
          break;
        }
      }
      if(!(is_in)){
        tab[i] = c;
        i++;
      }
    }
  }
  return tab;
}

//-----------------------------------------------------------------------nb_sol-------------------------------------------------
/**
 *@brief save and print the result
 * g is the game
 * file is the file in order to convert to 'file'.nbsol
 * cpt is number of solution
 **/
void save_nbsol(game g, char* file, uint cpt) {
  if (g == NULL || file == NULL) {
    exit(EXIT_FAILURE);
  }
  FILE* f = fopen(file, "w");
  if (f == NULL) {
    exit(EXIT_FAILURE);
  }
  fprintf(f, "NB_SOL = %u\n", cpt);
  fclose(f);
}

/**
 * @brief this function counts the number of possible solutions in a game by
 *browsing the grid if the game is winner.
 * @return the number of solution if you win else 0 solution .
 * g is the game
 * this fonction was called by nb_sol
 **/
uint nb_sol_aux(game g, uint nbcolors) {
  color last_color = game_cell_current_color(g, 0, 0);//last color for don't repeat.
  uint cpt = 0;// actual number solution
  if (game_is_over(g)) {//if I win at the first movement.
    return 1;
  }
  if (game_nb_moves_cur(g) >= game_nb_moves_max(g)) {//if I lose the game, the solution is 0.
    return 0;
  }

  for (color i = 0; i < nbcolors; i++) {
    if (i != last_color) {
      game g2 = game_copy(g);//copy the game (more detail in game.c for this function).
      game_play_one_move(g2, i);//move a color (more detail in game for this function).
      cpt = cpt + nb_sol_aux(g2, nbcolors);//restart the game and add 1 more solution if I win. 
      game_delete(g2);
    }
  }
  return cpt;//it's the number of solution.
}

/**
 * @brief this fonction call nb_sol_aux and save_nbsol
 * return number of possible solution when you win.
 * g is the game.
 * file is the name of game load.
 * nbcolors is the maximum number of colors in the game.
 **/
void nb_sol(game g, char* file, uint nbcolors) {
  uint cpt = nb_sol_aux(g, nbcolors);//call recursif nb_sol_aux.
  save_nbsol(g, strcat(file, ".nbsol"), cpt);//save the posible number of solution. 
  printf("nb_sol = %u\n", cpt);
}
//-----------------------------------------------------------------------------------------find_one-------------------------------------------------------
/*void find_one(char* game_curr, char* sol, uint nb_color) {
  if(game_curr == NULL || sol == NULL){
      fprintf(stderr, "Pointer is null\n");
      exit(EXIT_FAILURE);
  }
  game g = game_load(game_curr);
  FILE *f = fopen(sol,"w");
  if(f == NULL){
      fprintf(stderr, "Pointer is null\n");
      exit(EXIT_FAILURE);
  }
  if(nb_sol_aux(g,nb_color) == 0){// if I don't have solution.
      fprintf(f,"NO SOLUTION\n");
      fclose(f);
      game_delete(g);
      return;
  }
  uint nb_max = game_nb_moves_max(g);
  color * t_sol = malloc(nb_max*sizeof(color));//tab to display the number  I choose during the game.
  color last_color = game_cell_current_color(g,0,0);//position last_color and don't repeat.
  if(t_sol == NULL){
      fprintf(stderr, "Problem allocation memory\n");
      exit(EXIT_FAILURE);
  }
  srand(time(NULL));//initialize random number generator for rand() function.
  uint i = 0;

  while(i<nb_max){
    Continue:
     t_sol[i] = rand()%nb_color;//random number beetween 0 to nb_color. 
      while (last_color == t_sol[i]){//if last_color = t_sol[i].
        t_sol[i] = rand()%nb_color;
      }
    printf("%d ",t_sol[i]);
    
    
    game_play_one_move(g,t_sol[i]);
    last_color = game_cell_current_color(g,0,0);
    if (game_is_over(g) == true){
      printf("\nLa solution est : ");
      for (uint j = 0 ; j< i + 1; j++){
        if (j == i){
          printf("%d\n",t_sol[j]);          
          fprintf(f,"%d",t_sol[j]);//border line
        }else{
          printf("%d ",t_sol[j]);
          fprintf(f,"%d ",t_sol[j]);
        }

      }
      break;
      
    }
    i++;

  }
  if(i >= nb_max && game_is_over(g)==false){//restart the game.
    printf("pas gagne on recommence\n");
    game_restart(g);
    i=0;
    goto Continue;
  }
  free(t_sol);
  fclose(f);
  game_delete(g);
}*/

void find_one(game g, char* sol, uint nb_color, color color_possible[]) {
  if(g == NULL || sol == NULL){
      fprintf(stderr, "Pointer is null\n");
      exit(EXIT_FAILURE);
  }
  FILE *f = fopen(sol,"w");
  if(f == NULL){
      fprintf(stderr, "Pointer is null\n");
      exit(EXIT_FAILURE);
  }
  if(nb_sol_aux(g,nb_color) == 0){
      fprintf(f,"NO SOLUTION\n");
      fclose(f);
      game_delete(g);
      return;
  }
  uint nb_max = game_nb_moves_max(g);
  color * t_sol = malloc(nb_max*sizeof(color));
  if(t_sol == NULL){
      fprintf(stderr, "Problem allocation memory\n");
      exit(EXIT_FAILURE);
  }
  srand(time(NULL));
  uint i = 0;
  while(game_is_over(g) != true){
      if(i == nb_max){
          game_restart(g);
          i = 0;
      }
      color last_color = game_cell_current_color(g,0,0);
      uint x = rand()%nb_color;
      t_sol[i] = color_possible[x];
      while (t_sol[i] == last_color){
        x = rand()%nb_color;
        t_sol[i] = color_possible[x];
      }
      game_play_one_move(g,t_sol[i]);
      i++;
  }
  for(uint j=0 ; j<i ; j++){
      if(j != i-1){
          fprintf(f,"%u ",t_sol[j]);
      }
      else{
          fprintf(f,"%u\n",t_sol[j]);
      }
  }
  free(t_sol);
  fclose(f);
}

//---------------------------------------------------------------------------------------------find_min----------------------------------------------------------------

void find_min_aux(game g, uint nbcolors,  color color_possible[], uint *nb_max , uint *tab, uint *tabn, uint cpt) {
  if (game_is_over(g)) {//if I win at the first movement.
    if(game_nb_moves_cur(g) < *nb_max){
      *nb_max = game_nb_moves_cur(g); 
      for (uint z=0; z < game_nb_moves_cur(g); z++){
        tabn[z]=tab[z];
        cpt++;
      }
    }
    return;
  }

  if(game_nb_moves_cur(g) >= *nb_max){
    return;
  }
  color last_color = game_cell_current_color(g, 0, 0);//last color for don't repeat.
  color c = 0; 
  for (uint i = 0; i < nbcolors; i++){
    if (color_possible[i] != last_color) {
      c = color_possible[i]; 
      game g2 = game_copy(g);//copy the game (more detail in game.c for this function).
      game_play_one_move(g2, c);//move a color (more detail in game for this function).
      tab[game_nb_moves_cur(g)] = c;
      find_min_aux(g2, nbcolors, color_possible, nb_max, tab, tabn, cpt);//restart the game and add 1 more solution if I win. 
      game_delete(g2);
    }
  }
  return; 
}


void find_min(game g, char* fichier_sol/*, color color_possible[]*/){
  if (g == NULL || fichier_sol==NULL){
    fprintf(stderr, "NULL pointer");
    exit(EXIT_FAILURE);
  }
  uint nb_max = game_nb_moves_max(g)+1; 
  uint *tab = malloc(nb_max*sizeof(uint)); 
  if (tab==NULL){
    fprintf(stderr, "Alloc Error"); 
    exit(EXIT_FAILURE); 
  }
  uint *tabn = malloc(nb_max*sizeof(uint)); 
  if (tabn==NULL){
    fprintf(stderr, "Alloc Error"); 
    exit(EXIT_FAILURE); 
  }
  uint nbcolors = nb_colors(g);
  FILE *f = fopen(fichier_sol,"w");
  if(f == NULL){
    fprintf(stderr, "Pointer is null\n");
    exit(EXIT_FAILURE);
  }
  uint cpt =0;
  color *color_possible = colors_present(g);
  find_min_aux(g, nbcolors, color_possible, &nb_max, tab, tabn, cpt);
  if (nb_max > game_nb_moves_max(g))
  {
    fprintf(f,"NO SOLUTION\n");
  }
  else
  {
    for(uint j=0 ; j < nb_max ; j++){
      if(j != nb_max-1){
        fprintf(f,"%u ",tabn[j]);
      }
      else{
        fprintf(f,"%u\n",tabn[j]);
      }
    }
  }
  fclose(f);
}

/*
{
    game g = game_load(fichier_pb); 
    find_one (fichier_pb, fichier_sol,nb_colors(g)); // Call find_one to know if there are solutions, if not it's not necessary to apply this function
    FILE *f = fopen(fichier_sol, "r"); // Open fichier_sol only in read to verify if there are solutions
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
  color *t = malloc(game_nb_moves_max(g) * sizeof(color));
  int x=-1;
  color c = 5;
  uint nbmax = i-1;
  MIDDLE:
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
        }else{
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
  }while (x<nb_max){
    fprintf(f, "%c", cells[x]); 
  }
  fclose(f); 
  free(cells); 
  free(t); 
  game_delete(g); }
}*/


int main(int argc, char* argv[]) {
  if (argc != 4) {
    fprintf(stderr, "error argument\n");
    return EXIT_FAILURE;
  }
  game g = game_load(argv[2]);
  if (g == NULL) {
    fprintf(stderr, "ERROR : load %s", argv[2]);
    exit(EXIT_FAILURE);
  }
  if (strcmp(argv[1], "FIND_ONE") == 0) {
    find_one(g,strcat(argv[3],".sol"),nb_colors(g),colors_present(g));
    //find_one(argv[2], argv[3], max(g));
  } else if (strcmp(argv[1], "NB_SOL") == 0) {
    nb_sol(g, argv[3], max(g));

  } else if (strcmp(argv[1], "FIND_MIN") == 0) {
    //find_min(argv[2], argv[3]);
    find_min(g,strcat(argv[3],".sol")/*, colors_present(g)*/); 
  }else{ 
    fprintf(stderr,"ERROR: FILE OR  FUNCTION NAME INCORRECT\n");
    exit(EXIT_FAILURE);
  }
  game_delete(g);

  return EXIT_SUCCESS;
}