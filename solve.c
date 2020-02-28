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
  printf("color = %u\n", i);
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

//-----------------------------------------------------------------------NB_SOL-------------------------------------------------
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
 * this fonction was called by NB_SOL
 **/
uint NB_SOL_AUX(game g, uint nbcolors) {
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
      cpt = cpt + NB_SOL_AUX(g2, nbcolors);//restart the game and add 1 more solution if I win. 
      game_delete(g2);
    }
  }
  return cpt;//it's the number of solution.
}

/**
 * @brief this fonction call NB_SOL_AUX and save_nbsol
 * return number of possible solution when you win.
 * g is the game.
 * file is the name of game load.
 * nbcolors is the maximum number of colors in the game.
 **/
void NB_SOL(game g, char* file, uint nbcolors) {
  uint cpt = NB_SOL_AUX(g, nbcolors);//call recursif NB_SOL_AUX.
  save_nbsol(g, strcat(file, ".nbsol"), cpt);//save the posible number of solution. 
  printf("nb_sol = %u\n", cpt);
}
//-----------------------------------------------------------------------------------------FIND_ONE-------------------------------------------------------

void FIND_ONE(char* game_curr, char* sol, uint nb_color, color color_possible[]) {
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
  if(NB_SOL_AUX(g,nb_color) == 0){
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
          fprintf(f,"%d ",t_sol[j]);
      }
      else{
          fprintf(f,"%d\n",t_sol[j]);
      }
  }
  free(t_sol);
  fclose(f);
  game_delete(g);
}

//---------------------------------------------------------------------------------------------FIND_MIN----------------------------------------------------------------

void find_min(){
    return;
}