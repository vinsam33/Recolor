#include <stdio.h>
#include <stdlib.h>
#include "game.h"



struct game_s {
  color **tab; //game grid
  uint nb_max; //maximum number of moves allowed to win
  uint nb_curr; //number of current movements
  uint height; //game height
  uint width; //game width
  bool wrapping; //is or not wrapping
  color **init_game; // initial game
};

game game_new(color *cells, uint nb_moves_max) {
  return game_new_ext(SIZE, SIZE, cells, nb_moves_max, false);
}

game game_new_empty() {
  return game_new_empty_ext(SIZE,SIZE,false);
}

void game_set_cell_init(game g, uint x, uint y, color c) {
  if (g == NULL) {
    fprintf(stderr, "Error: do not game null\n");
    exit(EXIT_FAILURE);
  }if(g->tab==NULL || g->init_game==NULL){
    fprintf(stderr, "Error: do not game null\n");
    exit(EXIT_FAILURE);
  }
  if ((x < game_width(g)) && (y < game_height(g))) {
    g->tab[x][y] = c;
    g->init_game[x][y]=c;
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
  if (g == NULL || g->tab == NULL) {
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
  if (g == NULL) {
    fprintf(stderr, "g can't be null\n");
    exit(EXIT_FAILURE);
  }
  if (game_cell_current_color(g, x, y) == cible) {
    g->tab[x][y] = rep;
    if (y > 0) {
      remplissage(g, cible, rep, x, y - 1);  // North filling
    }
    if (y < game_height(g) - 1) {
      remplissage(g, cible, rep, x, y + 1);  // south filling
    }
    if (x < game_width(g) - 1) {
      remplissage(g, cible, rep, x + 1, y);  // Filling in the east
    }
    if (x > 0) {
      remplissage(g, cible, rep, x - 1, y);  // filling in the west
    }
    if (g->wrapping == true ){
      if (y == 0){
        remplissage(g, cible, rep, x, game_height(g) -1);     // Wrapping filling low / high
      }
      if (x == 0){
        remplissage(g, cible, rep, game_width(g) - 1, y);     // Wrapping filling right / left
      }
    }
  }
}

void game_play_one_move(game g, color c) {
  if (g == NULL) {
    fprintf(stderr, "g can't be null\n");
    game_delete(g);
    exit(EXIT_FAILURE);
  }if(c > 15){
    game_delete(g);
    exit(EXIT_FAILURE);
  }
  color first_case = game_cell_current_color(g, 0, 0);
  g->nb_curr++;
  if (first_case != c) {
      remplissage(g, first_case, c, 0, 0);
  }
}

game game_copy(cgame g) {
  if (g == NULL) {
    fprintf(stderr, "Problem allocation memory\n");
    exit(EXIT_FAILURE);
  }
  game g2 = malloc(sizeof(struct game_s)); // We allocate a new structure and the two new arrays
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
  for (uint i = 0; i < game_width(g); i++) { // We copy the old tables in the new structure
      for (uint j = 0; j < game_height(g); j++) {
      g2->tab[i][j] = g->tab[i][j];
      g2->init_game[i][j] = g->init_game[i][j];
    }
  }
  g2->nb_max = g->nb_max; // We copy the old structure field to field
  g2->nb_curr = g->nb_curr;
  g2->height = g->height;
  g2->width = g->width;
  g2->wrapping = g->wrapping;
  return g2;
}

void game_delete(game g) {
  if (g != NULL) {
    for (uint x = 0; x < game_width(g); x++) {
        if (g->tab != NULL){
          free(g->tab[x]);
        }
        if(g->init_game!=NULL){
            free(g->init_game[x]);
        }
      }
  free(g->init_game);
  free(g->tab);
  free(g);
  }
}

bool game_is_over(cgame g) {
  if (g == NULL|| g->tab == NULL || g->init_game == NULL) {
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
    game_delete(g);
    exit(EXIT_FAILURE);
  }
  g->nb_curr = 0;
  for (unsigned int i = 0; i < game_width(g); i++) { // We reset each value of the game grid tab by its starting value contained in init_game
    for (unsigned int j = 0; j < game_height(g); j++) {
      g->tab[i][j] = g->init_game[i][j];
    }
  }
}

//**************************************************V2*************************************************************//

bool game_is_wrapping(cgame g){
  if(g == NULL){
        fprintf(stderr, "Null pointer !\n");
        exit(EXIT_FAILURE);
    }
    return g->wrapping;
}

game game_new_empty_ext(uint width, uint height, bool wrapping){
  uint size_of_tab = height*width;
  color *cells = calloc(size_of_tab,sizeof(color)); // initialization of all values of * cells to 0.
  if(cells==NULL){
    fprintf(stderr,"ERROR : memory\n");
    exit(EXIT_FAILURE);
  }
  game g =game_new_ext(width,height,cells,0,wrapping); // reuse of the game_new_ext function with the calloc
  free(cells);
  return g;
}

game game_new_ext(uint width, uint height, color *cells, uint nb_moves_max,  bool wrapping){

  game g = malloc(sizeof(struct game_s)); // We allocate a new structure
  if (g == NULL) {
    fprintf(stderr, "Memory allocation problem\n");
    exit(EXIT_FAILURE);
  }

  g->wrapping = wrapping; // We fill this structure field by field
  g->nb_max = nb_moves_max;
  g->nb_curr = 0;
  g->width = width;
  g->height = height;
  g->tab = (color **)malloc(width * sizeof(color *)); // We allocate the table ** tab
  if (g->tab == NULL) {
    free(g);
    fprintf(stderr, "Memory allocation problem\n");
    exit(EXIT_FAILURE);
  }

  g->init_game = (color **)malloc(width * sizeof(color *)); // We allocate the table ** init_game
  if (g->init_game == NULL) {
    free(g->tab);
    free(g);
    fprintf(stderr, "Memory allocation problem\n");
    exit(EXIT_FAILURE);
  }

  for (uint i = 0; i < width; i++) {
    g->tab[i] = (color *)malloc(height * sizeof(color));  //We allocate the table * tab[i]
    if (g->tab[i] == NULL) {
      for (uint x=0; x<i; x++){
        free(g->tab[x]);
      }
      free(g->tab);
      free(g->init_game);
      free(g);
      fprintf(stderr, "Memory allocation problem\n");
      exit(EXIT_FAILURE);
    }
  }

  for (uint i = 0; i < width; i++) {
    g->init_game[i] = (color *)malloc(height * sizeof(color)); // We allocate the table * init_game[i]
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
      fprintf(stderr, "Memory allocation problem\n");
      exit(EXIT_FAILURE);
    }
  }
  for (uint x = 0; x < width; x++) {
    for (uint y = 0; y < height; y++) {
      g->tab[x][y] = cells[y * width + x]; // Filling of tab for each of its indices with the corresponding index in cells (color table)
      g->init_game[x][y] = cells[y * width + x]; // Filling init_game for each of its indices with the corresponding index in cells (color table)
    }
  }
  return g;
}


uint game_height(cgame game){
  if(game == NULL){
    fprintf(stderr,"Memory allocation problem\n");
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