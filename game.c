#include <stdio.h>
#include <stdlib.h>

#include "game.h"

typedef unsigned int uint;
typedef const struct game_s *cgame;

struct game_s {
  color **tab; //grille de jeu 
  uint nb_max; //nombre de mouvements maximums autorisés pour gagner
  uint nb_curr; //nombre de mouvements actuels 
  uint height; //hauteur du jeu
  uint width; //largeur du jeu
  bool wrapping; //est ou non wrapping 
  color **init_game; //jeu initial
};

typedef struct game_s *game;

//#define SIZE 12

// typedef enum color_e {RED, GREEN, BLUE, YELLOW, NB_COLORS} color;



game game_new(color *cells, uint nb_moves_max) {

  return game_new_ext(SIZE, SIZE, cells, nb_moves_max, false); 

  /*game g = malloc(sizeof(struct game_s));
  if (g == NULL) {
    fprintf(stderr, "Problem allocation memory\n");
    exit(EXIT_FAILURE);
  }
  g->tab = (color **)malloc(SIZE * sizeof(color *));
  if (g->tab == NULL) {
    free(g);
    fprintf(stderr, "Problem allocation memory\n");
    exit(EXIT_FAILURE);
  }
  g->init_game = (color **)malloc(SIZE * sizeof(color *));
  if (g->init_game == NULL) {
    free(g->tab);
    free(g);
    fprintf(stderr, "Problem allocation memory\n");
    exit(EXIT_FAILURE);
  }
  for (uint i = 0; i < SIZE; i++) {
    g->tab[i] = (color *)malloc(SIZE * sizeof(color));
    if (g->tab[i] == NULL) {
      free(g->tab);
      free(g->init_game);
      free(g);
      fprintf(stderr, "Problem allocation memory\n");
      exit(EXIT_FAILURE);
    }
    g->init_game[i] = (color *)malloc(SIZE * sizeof(color));
    if (g->init_game[i] == NULL){
      for (uint i = 0; i < SIZE; i++) {
        free(g->tab[i]);
      }
      free(g->tab);
      free(g->init_game);
      free(g);
      fprintf(stderr, "Problem allocation memory\n");
      exit(EXIT_FAILURE);
    }
  }
  for (uint i = 0; i < SIZE; i++) {
    for (uint j = 0; j < SIZE; j++) {
      g->tab[i][j] = cells[j * SIZE + i];
      g->init_game[i][j] = cells[j * SIZE + i];
    }
  }
  if (nb_moves_max <= 0) {
    for (uint i = 0; i < SIZE; i++) {
        free(g->tab[i]);
        free(g->init_game[i]);
    }
    free(g->tab);
    free(g->init_game);
    free(g);
    fprintf(stderr, "Nb_max_moves less or egal than 0\n");
    exit(EXIT_FAILURE);
  }
  g->nb_max = nb_moves_max;
  g->nb_curr = 0;
  return g;
  */
}

game game_new_empty() {
  return game_new_empty_ext(SIZE,SIZE,false);
}

void game_set_cell_init(game g, uint x, uint y, color c) {
  if (g == NULL) {
    fprintf(stderr, "Error: do not game null\n");
    exit(EXIT_FAILURE);
  }
  if ((x < game_width(g)) && (y < game_height(g)) && (0 <= c)) {
    g->tab[x][y] = c;
  }
}

void game_set_max_moves(game g, uint nb_max_moves) {
  if (g == NULL || nb_max_moves == 0) {
    fprintf(stderr, "Parameters error\n");
    exit(EXIT_FAILURE);
  }
  g->nb_max = nb_max_moves;
}

uint game_nb_moves_max(cgame g) {
  if (g == NULL) {
    fprintf(stderr, "Problem allocation memory moves_max\n");
    exit(EXIT_FAILURE);
  }
  return g->nb_max;
}

color game_cell_current_color(cgame g, uint x, uint y) {
  if (g == NULL || g->tab == NULL /*|| g->init_game == NULL*/) {
    fprintf(stderr, "Problem allocation memory curr_color\n");
    exit(EXIT_FAILURE);
  }
  if (x >= game_width(g) || y >= game_height(g)) {
    fprintf(stderr, "Problem size curr_color\n");
    exit(EXIT_FAILURE);
  }
  return g->tab[x][y];
}

uint game_nb_moves_cur(cgame g) {
  if (g == NULL) {
    fprintf(stderr, "Error: do not game null\n");
    exit(EXIT_FAILURE);
  }
  return g->nb_curr;
}

void remplissage(game g, color cible, color rep, uint x, uint y) {
  if (!game_is_wrapping(g)){
    if (g == NULL) {
      fprintf(stderr, "g can't be null\n");
      exit(EXIT_FAILURE);
    }
    if (game_cell_current_color(g, x, y) == cible) {
      g->tab[x][y] = rep;
      if (y > 0) {
        remplissage(g, cible, rep, x, y - 1);  // Remplissage au nord
      }
      if (y < game_height(g) - 1) {
        remplissage(g, cible, rep, x, y + 1);  // Remplissage au sud
      }
      if (x < game_width(g) - 1) {
        remplissage(g, cible, rep, x + 1, y);  // Remplissage à l'est
      }
      if (x > 0) {
        remplissage(g, cible, rep, x - 1, y);  // Remplissage à l'ouest
      }
    }
  }
   else{ //game_is_wrapping
    if (g == NULL) {
      fprintf(stderr, "g can't be null\n");
      exit(EXIT_FAILURE);
    }
    if (game_cell_current_color(g, x, y) == cible) {
      g->tab[x][y] = rep;
      if (y > 0) {
        remplissage(g, cible, rep, x, y - 1);  // Remplissage au nord
      }
      if (y < game_height(g) - 1) {
        remplissage(g, cible, rep, x, y + 1);  // Remplissage au sud
      }
      if (x < game_width(g) - 1) {
        remplissage(g, cible, rep, x + 1, y);  // Remplissage à l'est
      }
      if (x > 0) {
        remplissage(g, cible, rep, x - 1, y);  // Remplissage à l'ouest
      }
      if (y = game_height(g) -1){
        remplissage(g, cible, rep, x, 0);     // Remplissage en Wrapping bas/haut
      }
      if (x = game_width(g) - 1){
        remplissage(g, cible, rep, 0, y);     // Remplissage en Wrapping droite/gauche
      }
    }
  }
}

void game_play_one_move(game g, color c) {
  if (g == NULL) {
    fprintf(stderr, "g can't be null\n");
    exit(EXIT_FAILURE);
  }
  color first_case = game_cell_current_color(g, 0, 0);
  if (first_case != c) {
    if (0 <= c && c < NB_COLORS){
      remplissage(g, first_case, c, 0, 0);
      g->nb_curr++;
    }
  }
}

game game_copy(cgame g) {
  if (g == NULL) {
    fprintf(stderr, "Problem allocation memory\n");
    exit(EXIT_FAILURE);
  }
  game g2 = malloc(sizeof(struct game_s));
  if (g2 == NULL) {
    fprintf(stderr, "Problem allocation memory\n");
    exit(EXIT_FAILURE);
  }
  g2->tab = (color **)malloc(game_width(g) * sizeof(color *));
  if (g2->tab == NULL) {
    free(g2);
    fprintf(stderr, "Problem allocation memory\n");
    exit(EXIT_FAILURE);
  }
  g2->init_game = (color **)malloc(game_width(g)* sizeof(color *));
  if (g2->init_game == NULL) {
    free(g2->tab);
    free(g2);
    fprintf(stderr, "Problem allocation memory\n");
    exit(EXIT_FAILURE);
  }
  for (uint i = 0; i < game_width(g); i++) {
    g2->tab[i] = (color *)malloc(game_height(g)* sizeof(color));
    if (g2->tab[i] == NULL) {
      for(uint x=0 ; x<i ; x++){
        free(g2->tab[x]);
      }
      free(g2->tab);
      free(g2->init_game);
      free(g2);
      fprintf(stderr, "Problem allocation memory\n");
      exit(EXIT_FAILURE);
    }
    g2->init_game[i] = (color *)malloc(game_height(g) * sizeof(color));
    if (g2->init_game[i] == NULL) {
      for(uint x=0 ; x<game_width(g) ; x++){
        free(g2->tab[x]);
      }
      for(uint y=0 ; y<i ; y++){
        free(g2->init_game[y]);
      }
      free(g2->init_game);
      free(g2->tab);
      free(g2);
      fprintf(stderr, "Problem allocation memory\n");
      exit(EXIT_FAILURE);
    }
  }
  for (uint i = 0; i < game_width(g); i++) {
    for (uint j = 0; j < game_height(g); j++) {
      g2->tab[i][j] = g->tab[i][j];
      g2->init_game[i][j] = g->init_game[i][j];
    }
  }
  g2->nb_max = g->nb_max;
  g2->nb_curr = g->nb_curr;
  g2->height = g->height;
  g2->width = g->width;
  g2->wrapping = g->wrapping;
  return g2;
}

void game_delete(game g) {
  if (g == NULL) {
    return;
  }
  for (uint x = 0; x < game_width(g); x++) {
    free(g->tab[x]);
    free(g->init_game[x]);
  }
  free(g->init_game);
  free(g->tab);
  free(g);
}

bool game_is_over(cgame g) {
  if (g == NULL) {
    fprintf(stderr, "Error: do not game null\n");
    exit(EXIT_FAILURE);
  }
  color c = game_cell_current_color(g, 0, 0);
  if (g->nb_curr <= g->nb_max) {
    for (uint x = 0; x < game_width(g); x++) {
      for (uint y = 0; y < game_height(g); y++) {
        if (c != game_cell_current_color(g, x, y)) {
          return false;
        }
      }
    }
    return true;
  }
  return false;
}

void game_restart(game g) {
  if (g == NULL || g->tab == NULL || g->init_game == NULL) {
    fprintf(stderr, "Error: do not game null\n");
    exit(EXIT_FAILURE);
  }
  g->nb_curr = 0;
  for (unsigned int i = 0; i < game_width(g); i++) {
    for (unsigned int j = 0; j < game_height(g); j++) {
      g->tab[i][j] = g->init_game[i][j];
    }
  }
}

///V2//

bool game_is_wrapping(cgame g){
  if(g == NULL){
        fprintf(stderr, "Null pointer !\n");
        exit(EXIT_FAILURE);
    }

    return g->wrapping;
}

game game_new_empty_ext(uint width, uint height, bool wrapping){

  /*game g = malloc(sizeof(game));
  if (g == NULL) {
    fprintf(stderr, "Problem allocation memory\n");
    exit(EXIT_FAILURE);
  }
  
  g->tab = (color **)malloc(width*sizeof(color *));
  if (g->tab == NULL) {
    free(g);
    fprintf(stderr, "Problem allocation memory\n");
    exit(EXIT_FAILURE);
  }
  
  g->init_game = (color **)malloc(width*sizeof(color *));
  if (g->init_game == NULL) {
    free(g->tab);
    free(g);
    fprintf(stderr, "Problem allocation memory\n");
    exit(EXIT_FAILURE);
  }
  
  for (uint i = 0; i < width; i++) {
    g->tab[i] =(color *)malloc(height* sizeof(color));
    if (g->tab[i] == NULL) {
      for(uint x=0; x<i; x++){
        free(g->tab[x]); 
      }  
      free(g->tab);
      free(g->init_game);
      free(g);
      fprintf(stderr, "Problem allocation memory\n");
      exit(EXIT_FAILURE);
    }
  }  

  for (uint i = 0; i < width; i++) {
    g->init_game[i] = (color *)malloc(height* sizeof(color));
    if (g->init_game[i] == NULL) {
      for(uint x=0; x<width; x++){
        free(g->tab[x]);
      }
      for(uint y=0; y<i; y++){
        free(g->init_game[y]); 
      }
      free(g->tab);
      free(g->init_game);
      free(g);
      fprintf(stderr, "Problem allocation memory\n");
      exit(EXIT_FAILURE);
    }
  }
  
  for (uint x = 0; x < width ; x++) {
    for (uint y = 0; y < height; y++) {
      // game_set_cell_init(g, x,y, RED);
      g->tab[x][y] = 0;
      g->init_game[x][y] = 0;
    }
  }
  g->nb_max = 0;
  g->nb_curr = 0;
  return g;*/
  uint size_of_tab = height*width;
  color *cells = calloc(size_of_tab,sizeof(color)); //initialiser à 0.
  if(cells==NULL){
    fprintf(stderr,"ERROR : memory\n");
    exit(EXIT_FAILURE);
  }
  game g =game_new_ext(width,height,cells,0,wrapping); //reutilisation de la fonction game_new_ext avec le calloc 
  
  free(cells);
  return g;
}

game game_new_ext(uint width, uint height, color *cells, uint nb_moves_max,  bool wrapping){

  game g = malloc(sizeof(struct game_s));
  if (g == NULL) {
    fprintf(stderr, "Problem allocation memory\n");
    exit(EXIT_FAILURE);
  }

  g->wrapping = wrapping; 
  g->nb_max = nb_moves_max; 
  g->nb_curr = 0;
  g->width = width; 
  g->height = height; 

  g->tab = (color **)malloc(width * sizeof(color *));
  if (g->tab == NULL) {
    free(g);
    fprintf(stderr, "Problem allocation memory\n");
    exit(EXIT_FAILURE);
  }

  g->init_game = (color **)malloc(width * sizeof(color *));
  if (g->init_game == NULL) {
    free(g->tab);
    free(g);
    fprintf(stderr, "Problem allocation memory\n");
    exit(EXIT_FAILURE);
  }

  for (uint i = 0; i < width; i++) {
    g->tab[i] = (color *)malloc(height * sizeof(color));
    if (g->tab[i] == NULL) {
      for (uint x=0; x<i; x++){
        free(g->tab[x]); 
      } 
      free(g->tab);
      free(g->init_game);
      free(g);
      fprintf(stderr, "Problem allocation memory\n");
      exit(EXIT_FAILURE);
    }
  }

  for (uint i = 0; i < width; i++) {
    g->init_game[i] = (color *)malloc(height * sizeof(color));
    if (g->init_game[i] == NULL){
      for (uint x = 0; x < width; x++) {
        free(g->tab[x]);
      }
      for(uint y=0; y<i; y++){
        free(g->init_game[y]); 
      }
      free(g->tab);
      free(g->init_game);
      free(g);
      fprintf(stderr, "Problem allocation memory\n");
      exit(EXIT_FAILURE);
    }
  }
  for (uint x = 0; x < width; x++) {
    for (uint y = 0; y < height; y++) {
      g->tab[x][y] = cells[y * width + x]; //Remplissage de tab pour chacun de ses indices avec l'indice corespondant dans cells (tableau des couleurs)
      g->init_game[x][y] = cells[y * width + x]; //Remplissage d'init_game pour chacun de ses indices avec l'indice corespondant dans cells (tableau des couleurs)
    }
  }
  return g;
}


uint game_height(cgame game){
  if(game == NULL){
    fprintf(stderr,"Problem allocation memory\n");
    exit(EXIT_FAILURE);
  }
  return game->height;
}

uint game_width(cgame game){
  if(game == NULL){
        fprintf(stderr, "Null pointer !\n");
        exit(EXIT_FAILURE);
  }
  return game->width;
}