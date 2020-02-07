#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "game_io.h"
#include "game_io.h"

#define MAXLINELEN 4096

bool test_game_set_max_moves(uint max) {
  game g = game_new_empty_ext(12, 12, false); 
  if (!g) {
    fprintf(stderr, "Error : invalid game\n\n");
    game_delete(g);
    return false;
  }

  game_set_max_moves(g, max); // On appelle game_set_max_moves pour définir un nb de mouvements maximum pour le jeu g et on vérifie que le nombre maximum de mouvements de g est bien max
  if (game_nb_moves_max(g) != max) {
    fprintf(stderr, "Error : too much number of moves\n\n");
    game_delete(g);
    return false;
  }
  game_delete(g);
  return true;
}

bool test_game_play_one_move(color c) {
  
  /** Vérification play_one_move en wrapping = true **/

  //Initialisation d'une grille de jeu spéciale test wrapping :
  color cells[144] = {
      1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1};
  game g = game_new_ext(12, 12, cells, 12, true);
  if (!g) {
    fprintf(stderr, "Error : invalid game\n\n");
    game_delete(g);
    return false;
  }
  game_play_one_move(g,0);
  for (unsigned int y = 0; y < game_height(g); y++) {
    for (unsigned int x = 0; x < game_width(g); x++) {
      if (game_cell_current_color(g, x, y) != 0) {
        game_delete(g);
        return false;
      }
    }
  }
  game_delete(g);

  /** Vérification play_one_move en wrapping = false **/

  game ga = game_new_empty_ext(12, 12, false);
  game_play_one_move(ga, c); // Comme toutes les cases ont pour valeur 0 après avoir joué un mouvement de la couleur c toutes les cases doivent avoir pour valeur la couleur c
  if (c <= 0) {
    fprintf(stderr, "Error : invalid game\n\n");
    game_delete(ga);
    return false;
  }
  for (unsigned int y = 0; y < game_height(ga); y++) {
    for (unsigned int x = 0; x < game_width(ga); x++) {
      if (game_cell_current_color(ga, x, y) != c) {
        game_delete(ga);
        return false;
      }
    }
  }
  game_delete(ga);
  return true;
}

bool test_game_restart() {
  color cells[144] = {
      0, 0, 0, 2, 0, 2, 1, 0, 1, 0, 3, 0, 0, 3, 3, 1, 1, 1, 1, 3, 2, 0, 1, 0,
      1, 0, 1, 2, 3, 2, 3, 2, 0, 3, 3, 2, 2, 3, 1, 0, 3, 2, 1, 1, 1, 2, 2, 0,
      2, 1, 2, 3, 3, 3, 3, 2, 0, 1, 0, 0, 0, 3, 3, 0, 1, 1, 2, 3, 3, 2, 1, 3,
      1, 1, 2, 2, 2, 0, 0, 1, 3, 1, 1, 2, 1, 3, 1, 3, 1, 0, 1, 0, 1, 3, 3, 3,
      0, 3, 0, 1, 0, 0, 2, 1, 1, 1, 3, 0, 1, 3, 1, 0, 0, 0, 3, 2, 3, 1, 0, 0,
      1, 3, 3, 1, 1, 2, 2, 3, 2, 0, 0, 2, 2, 0, 2, 3, 0, 1, 1, 1, 2, 3, 0, 1};
  game(g) = game_new_ext(12, 12, cells, 12, false);
  game_play_one_move(g, 2);
  game_restart(g);

  if (game_nb_moves_cur(g) != 0) {
    fprintf(stderr, "Error : Number of moves different from 0\n\n");
    game_delete(g);
    return false;
  }
  for (uint x = 0; x < game_width(g); x++) {
    for (uint y = 0; y < game_height(g); y++) {
      if (game_cell_current_color(g, x, y) != cells[y * game_width(g) +x]) { // Après un restart chaque case du jeu doit être identique à la case d'indice correspondant dans cells, car cells correpond au tableau de valeurs de départ
        fprintf(stderr, "Error : game_cell_current_color different from cells\n\n");
        game_delete(g);
        return false;
      }
    }
  }
  game_delete(g);
  return true;
}

bool test_game_new_empty_ext(uint width, uint height, bool wrapping){
  game g = game_new_empty_ext(width, height, wrapping);
  if (game_is_wrapping(g)!=wrapping){
    fprintf(stderr, "Error : Different Wrapping \n\n");
    game_delete(g); 
    return false;
  }
  if (g == NULL || game_nb_moves_max(g) != 0){
    fprintf(stderr, "Error : creation fault\n\n");
    game_delete(g);
    return false;
  }
  for (unsigned int x = 0; x < width; x++) { // La valeur de chaque case du tableau doit être 0
    for (unsigned int y = 0; y < height; y++) {
      if (game_cell_current_color(g, x, y) != 0){
        game_delete(g);
        return false;
      }
    }
  }
  game_delete(g); 
  return true;
}

bool test_game_load(){
  color cells[144] = {
      0, 0, 0, 2, 0, 2, 1, 0, 1, 0, 3, 0, 0, 3, 3, 1, 1, 1, 1, 3, 2, 0, 1, 0,
      1, 0, 1, 2, 3, 2, 3, 2, 0, 3, 3, 2, 2, 3, 1, 0, 3, 2, 1, 1, 1, 2, 2, 0,
      2, 1, 2, 3, 3, 3, 3, 2, 0, 1, 0, 0, 0, 3, 3, 0, 1, 1, 2, 3, 3, 2, 1, 3,
      1, 1, 2, 2, 2, 0, 0, 1, 3, 1, 1, 2, 1, 3, 1, 3, 1, 0, 1, 0, 1, 3, 3, 3,
      0, 3, 0, 1, 0, 0, 2, 1, 1, 1, 3, 0, 1, 3, 1, 0, 0, 0, 3, 2, 3, 1, 0, 0,
      1, 3, 3, 1, 1, 2, 2, 3, 2, 0, 0, 2, 2, 0, 2, 3, 0, 1, 1, 1, 2, 3, 0, 1};
  // test avec version wrapping
  game g2 = game_new_ext(12, 12, cells, 10, true);
  if (g2 == NULL) {
    game_delete(g2);
    return false;
  }
  game_save(g2, "default_game.rec.txt");  // sauvegarde la partie directement au debut
  game g = game_load("default_game.rec.txt");  // charge la partie et on verifie que l'on a bien sauvegardé
  if (g == NULL) {
    game_delete(g2);
    game_delete(g);
  }
  if ("default_game.rec.txt"==NULL){
    fprintf(stderr, "Null pointer\n");
    exit(EXIT_FAILURE);
  }
  FILE * f = fopen("default_game.rec.txt","r");
  if (f == NULL){
    game_delete(g2);
    game_delete(g);
    exit(EXIT_FAILURE);
  }
  char *s = malloc(sizeof (char)*MAXLINELEN);
  if(s==NULL){
    fprintf(stderr, "Null pointer\n");
    game_delete(g2);
    game_delete(g);
    fclose(f);
    exit(EXIT_FAILURE);
  }
  s = fgets(s, MAXLINELEN, f);
  char *d = strtok(s, " \n");
  uint w = atoi(d);

  d = strtok(NULL, " \n");
  uint h = atoi(d); 

  d = strtok(NULL, " \n");
  uint nb_max = atoi(d); 

  d = strtok(NULL, " \n");
  bool wrapping = true;
  if (d=='N') wrapping = false;

  if(game_is_wrapping(g) != wrapping || game_height(g) != h || game_width(g) != w || game_nb_moves_max(g) != nb_max){
    free(s);
    game_delete(g2);
    game_delete(g);
    fclose(f);
    return false;
  }

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
  for (uint x=0; x < w; x++){
    for (uint y=0; y < h; y++){
      if (game_cell_current_color(g, x, y) != cells[y * w + x]){
        free(s);
        free(cells);
        game_delete(g2);
        game_delete(g);
        fclose(f);
        return false;
      }
    }
  }
  free(s);
  free(cells);
  game_delete(g2);
  game_delete(g);
  fclose(f);

  color cells[144] = {
      0, 0, 0, 2, 0, 2, 1, 0, 1, 0, 3, 0, 0, 3, 3, 1, 1, 1, 1, 3, 2, 0, 1, 0,
      1, 0, 1, 2, 3, 2, 3, 2, 0, 3, 3, 2, 2, 3, 1, 0, 3, 2, 1, 1, 1, 2, 2, 0,
      2, 1, 2, 3, 3, 3, 3, 2, 0, 1, 0, 0, 0, 3, 3, 0, 1, 1, 2, 3, 3, 2, 1, 3,
      1, 1, 2, 2, 2, 0, 0, 1, 3, 1, 1, 2, 1, 3, 1, 3, 1, 0, 1, 0, 1, 3, 3, 3,
      0, 3, 0, 1, 0, 0, 2, 1, 1, 1, 3, 0, 1, 3, 1, 0, 0, 0, 3, 2, 3, 1, 0, 0,
      1, 3, 3, 1, 1, 2, 2, 3, 2, 0, 0, 2, 2, 0, 2, 3, 0, 1, 1, 1, 2, 3, 0, 1};
  // test avec version non wrapping
  game g3 = game_new_ext(12, 12, cells, 10, false);
  if (g3 == NULL) {
    game_delete(g3);
    return false;
  }
  game_save(g3, "default_game.rec.txt");  // sauvegarde la partie directement au debut
  game g4 = game_load("default_game.rec.txt");  // charge la partie et on verifie que l'on a bien sauvegardé
  if (g4 == NULL) {
    game_delete(g3);
    game_delete(g4);
  }
  game g4 = game_load("horizontal_game2N.rec.txt"); // Wrapping en false
  if ("horizontal_game2N.rec.txt"==NULL){
    fprintf(stderr, "Null pointer\n");
    exit(EXIT_FAILURE);
  }
  FILE * f2 = fopen("horizontal_game2N.rec.txt","r");
  if (f2 == NULL){
    game_delete(g3);
    game_delete(g4); 
    exit(EXIT_FAILURE);
  }
  char *s2 = malloc(sizeof (char)*MAXLINELEN);
  if(s2==NULL){
    fprintf(stderr, "Null pointer\n");
    game_delete(g3);
    game_delete(g4); 
    fclose(f2);
    exit(EXIT_FAILURE);
  }
  s2 = fgets(s2, MAXLINELEN, f2);
  char *d2 = strtok(s2, " \n");
  uint w2 = atoi(d2);

  d2 = strtok(NULL, " \n");
  uint h2 = atoi(d2);

  d2 = strtok(NULL, " \n");
  uint nb_max2 = atoi(d2);

  d2 = strtok(NULL, " \n");
  bool wrapping2 = true;
  if (d2=='N') wrapping2 = false;

  if(game_is_wrapping(g4) != wrapping2 || game_height(g4) != h2 || game_width(g4) != w2 || game_nb_moves_max(g4) != nb_max2){
    free(s2);
    game_delete(g3);
    game_delete(g4); 
    fclose(f2);
    return false;
  }

  color *cells2 = malloc(sizeof(color)*MAXLINELEN);
  uint i2 = 0;
  while (fgets(s2, MAXLINELEN, f2) != NULL){
    char *tok = strtok(s2, " \n");
    while (tok != NULL){
      int n = atoi(tok);
      cells2[i2] = n;
      i2++;
      tok = strtok(NULL, " \n");
    }
  }
  for (uint x=0; x < w2; x++){
    for (uint y=0; y < h2; y++){
      if (game_cell_current_color(g4, x, y) != cells2[y * w2 + x]){
        free(s2);
        free(cells2);
        game_delete(g3);
        game_delete(g4); 
        fclose(f2);
        return false;
      }
    }
  }
  free(s2);
  free(cells2);
  game_delete(g3);
  game_delete(g4); 
  fclose(f2);
  return true;
}

/*** ***** MAIN ***** ***/

int main(void) {
  
  printf("-- Start test of game_set_max_moves --\n");
  bool Agree = test_game_set_max_moves(12);
  if (Agree) {
    fprintf(stderr, "Execution of game_set_max_moves : Success\n\n");
  } else {
    fprintf(stderr, "Execution of game_set_max_moves : Denied\n\n");
    return EXIT_FAILURE;
  }

  printf("--Start test of game_play_one_move --\n");
  Agree = test_game_play_one_move(BLUE);
  if (Agree) {
    fprintf(stderr, "Execution of game_play_one_move : Success\n\n");
  } else {
    fprintf(stderr, "Execution of game_play_one_move : Failuren\n");
    return EXIT_FAILURE;
  }
  
  printf("--Start test of game_restart --\n");
  Agree = test_game_restart();
  if (Agree) {
    fprintf(stderr, "Execution of game_restart : Success\n\n");
  } else {
    fprintf(stderr, "Execution of game_restart : Failure\n\n");
    return EXIT_FAILURE;
  }
  
  printf("-- Start test of game_new_empty_ext --\n");
  Agree = test_game_new_empty_ext(12, 12, false);
  if (Agree) {
    fprintf(stderr, "Execution of game_new_empty_ext : Success\n\n");
  } else {
    fprintf(stderr, "Execution of game_new_empty_ext : Failure\n\n");
    return EXIT_FAILURE;
  }

  printf("-- Start test of game_load --\n"); 
  Agree = test_game_load(); 
  if (Agree) {
    fprintf(stderr, "Execution of game_load : Success\n\n");
  } else{
    fprintf(stderr, "Execution of game_load : Failure\n\n");
    return EXIT_FAILURE; 
  }
  return EXIT_SUCCESS;
}
