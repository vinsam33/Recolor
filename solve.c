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
  //printf("nb_color = %u\n",c+1);
  return c+1;
}


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


color* colors_present(game g) {
  uint i = 0;
  color* tab = malloc(sizeof(color) * nb_colors(g));
  color c;
  bool is_in = false;
  for (uint x = 0; x < game_width(g); x++) {
    for (uint y = 0; y < game_height(g); y++) {
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


void nb_sol(game g, char* file, uint nbcolors) {
  uint cpt = nb_sol_aux(g, nbcolors);//call recursif nb_sol_aux.
  save_nbsol(g, strcat(file, ".nbsol"), cpt);//save the posible number of solution. 
  //printf("nb_sol = %u\n", cpt);
}
//-----------------------------------------------------------------------------------------find_one-------------------------------------------------------


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

void find_min(game g, char* fichier_sol, color color_possible[]){
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
  uint cpt=0;
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

