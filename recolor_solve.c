#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "game_io.h"
#include "string.h"
#include "time.h"

#define MAXLINELEN 4096

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
  for (uint x = 0; x < game_width(g); x++) {
    for (uint y = 0; y < game_height(g); y++) {
      c = game_cell_current_color(g, x, y);
      uint a = 0;
      for (a = 0; a < i; a++) {
        if (tab[a] == c) {
          break;
        }
        if (a == i) {
          tab[i] = c;
          i++;
        }
      }
    }
  }
  return tab;
}

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
  color last_color = game_cell_current_color(g, 0, 0);
  uint cpt = 0;
  if (game_is_over(g)) {
    return 1;
  }
  if (game_nb_moves_cur(g) >= game_nb_moves_max(g)) {
    return 0;
  }

  for (color i = 0; i < nbcolors; i++) {
    if (i != last_color) {
      game g2 = game_copy(g);
      game_play_one_move(g2, i);
      cpt = cpt + NB_SOL_AUX(g2, nbcolors);
      game_delete(g2);
    }
  }
  return cpt;
}

/**
 * @brief this fonction call NB_SOL_AUX and save_nbsol
 * return number of possible solution when you win.
 * g is the game.
 * file is the name of game load.
 * nbcolors is the maximum number of colors in the game.
 **/
void NB_SOL(game g, char* file, uint nbcolors) {
  uint cpt = NB_SOL_AUX(g, nbcolors);
  save_nbsol(g, strcat(file, ".nbsol"), cpt);
  printf("nb_sol = %u\n", cpt);
}

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
      if(i > nb_max){
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
      if(j != i){
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

void FIND_MIN(char* fichier_pb, char* fichier_sol) {
  /*if (fichier_pb == NULL || fichier_sol==NULL){
    fprintf(stderr, "NULL pointer");
    exit(EXIT_FAILURE);
  }*/
  /*FIND_ONE (fichier_pb, fichier_sol, 5); // Call FIND_ONE to know if there are
  solutions, if not it's not necessary to apply this function FILE *f =
  fopen(fichier_sol, "r");  // Open fichier_sol only in read to verify if there
  are solutions if (f == NULL) { fprintf(stderr, "error f\n");
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

int main(int argc, char* argv[]) {
  if (argc != 4) {
    fprintf(stderr, "error");
    return EXIT_FAILURE;
  }
  game g = game_load(argv[2]);
  if (g == NULL) {
    fprintf(stderr, "ERROR : load %s", argv[2]);
    exit(EXIT_FAILURE);
  }
  if (strcmp(argv[1], "FIND_ONE") == 0) {
    FIND_ONE(argv[2], argv[3], nb_colors(g), colors_present(g));
  } else if (strcmp(argv[1], "NB_SOL") == 0) {
    NB_SOL(g, argv[2], nb_colors(g));

  } else if (strcmp(argv[1], "FIND_MIN") == 0) {
    FIND_MIN(argv[2], argv[3]);
  }
  game_delete(g);

  return EXIT_SUCCESS;
}