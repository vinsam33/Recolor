#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "game_io.h"
#include "recolor_solve.h"


#define MAXLINELEN 4096


/// Test Game set max moves : 

bool test_game_set_max_moves(uint max) {
  game g = game_new_empty_ext(12, 12, false); 
  if (!g) {
    fprintf(stderr, "Error : invalid game\n\n");
    game_delete(g);
    return false;
  }

  game_set_max_moves(g, max); // On appelle game_set_max_moves pour dÃ©finir un nb de mouvements maximum pour le jeu g et on vÃ©rifie que le nombre maximum de mouvements de g est bien max
  if (game_nb_moves_max(g) != max) {
    fprintf(stderr, "Error : too much number of moves\n\n");
    game_delete(g);
    return false;
  }
  game_delete(g);
  return true;
}

/// Test Game play one move :

bool test_game_play_one_move(color c) {
  
  /** Verification play_one_move en wrapping = true **/

  //Initialisation d'une grille de jeu spÃ©ciale test wrapping :
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

  /** Verification play_one_move en wrapping = false **/

  game ga = game_new_empty_ext(12, 12, false);
  game_play_one_move(ga, c); // Comme toutes les cases ont pour valeur 0 aprÃ¨s avoir jouÃ© un mouvement de la couleur c toutes les cases doivent avoir pour valeur la couleur c
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

/// Test game restart : 

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
      if (game_cell_current_color(g, x, y) != cells[y * game_width(g) +x]) { // AprÃ¨s un restart chaque case du jeu doit Ãªtre identique Ã  la case d'indice correspondant dans cells, car cells correpond au tableau de valeurs de dÃ©part
        fprintf(stderr, "Error : game_cell_current_color different from cells\n\n");
        game_delete(g);
        return false;
      }
    }
  }
  game_delete(g);
  return true;
}

/// Test Game new empty ext :  

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
  for (unsigned int x = 0; x < width; x++) { // La valeur de chaque case du tableau doit Ãªtre 0
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

/// Test Game load : 

bool test_game_load(){
  game g = game_load("testemolere/default_game.rec.txt"); // Wrapping en true
  FILE * f = fopen("testemolere/default_game.rec.txt","r");
  
  char *s = malloc(sizeof (char)*MAXLINELEN);
  if(s==NULL){
    fprintf(stderr, "Null pointer\n");
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
  if (*d=='N') wrapping=false;
  
  if (game_is_wrapping(g) != wrapping || game_height(g) != h || game_width(g) != w || game_nb_moves_max(g) != nb_max){
    free(s);
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
        game_delete(g);
        fclose(f);
        return false;
      }
    }
  }
  free(s);
  free(cells);
  game_delete(g);
  fclose(f);
  game g2 = game_load("testemolere/horizontal_game2N.rec.txt"); // Wrapping en false
  FILE * f2 = fopen("testemolere/horizontal_game2N.rec.txt","r");
  
  char *s2 = malloc(sizeof (char)*MAXLINELEN);
  if(s2==NULL){
    fprintf(stderr, "Null pointer\n");
    game_delete(g2);
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
  if (*d2=='N') wrapping2=false;  

  if(game_is_wrapping(g2) != wrapping2 || game_height(g2) != h2 || game_width(g2) != w2 || game_nb_moves_max(g2) != nb_max2){
    free(s2);
    game_delete(g2);
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
      if (game_cell_current_color(g2, x, y) != cells2[y * w2 + x]){
        free(s2);
        free(cells2);
        game_delete(g2);
        fclose(f2);
        return false;
      }
    }
  }
  free(s2);
  free(cells2);
  game_delete(g2);
  fclose(f2);
  return true;
}


/// Test nb_colors et colors_present : 

bool test_nb_colors(){
  color cells[10] = {
    0, 0, 1, 2, 3, 
    4, 5, 0, 3, 1}; //6 couleurs : [0,1,2,3,4,5]
  game g = game_new_ext(5, 2, cells, 5, true); 
  uint cpt = nb_colors(g); 
  if(cpt!=6){
    return false;
  }
  /*color *colors_possible = colors_present(g);
  if ((colors_possible[0] !=0) || (colors_possible[1] !=1) || (colors_possible[2] !=2) || (colors_possible[3] !=3) || (colors_possible[4] != 4) || (colors_possible[5] != 5)){
    return false; 
  }*/
  return true; 
}

/// Test find min : 

bool test_find_min(game g,char *f_sol){
  uint nbcolors=nb_colors(g); 
  color *color_possible = colors_present(g);
  if (color_possible == NULL){
    fprintf(stderr, "Alloc Error");
    return false;
  }
  
  find_min(g, f_sol);
  FILE *f = fopen(f_sol,"r");
  uint z=0; 
  color *solf = malloc(sizeof(color)*MAXLINELEN);
  if (solf == NULL){
    fprintf(stderr, "Alloc Error");
    free(color_possible);
    return false;
  }

  game g2 = game_copy(g); 
  while(!feof(f)){
      fscanf(f,"%u",&solf[z]);
      z++;
  }
  uint i=0;
  for (i=0 ; i<z-2 ; i++){
    game_play_one_move(g2,solf[i]);
      if (game_is_over(g2)){
        free(solf);
        free(color_possible);
        fclose(f);
        return false; 
      }
  }
  game_play_one_move(g2, solf[i]); 
  if(!game_is_over(g2)){
    free(solf);
    free(color_possible);
    fclose(f);
    return false; 
  }
  free(solf);
  fclose(f);
  uint *tab = malloc(i*sizeof(uint)); 
  if (tab==NULL){
    fprintf(stderr, "Alloc Error"); 
    free(color_possible);
    return false; 
  }
  uint *tabn = malloc(i*sizeof(uint)); 
  if (tabn==NULL){
    fprintf(stderr, "Alloc Error");
    free(color_possible);
    free(tab); 
    return false; 
  }
  uint cpt =0;
  uint nbmax = i;
  find_min_aux(g, nbcolors, &color_possible[nbcolors], &nbmax , tab, tabn, cpt);
  if (cpt!=0){
    free(tab);
    free(tabn);
    free(color_possible);
    return false;
  }
  free(tab); 
  free(tabn);
  free(color_possible);
  return true; 
}


/*** ***** MAIN ***** ***/

int main(void) {

  printf("\n-- Start test of game_set_max_moves --\n");
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
  bool Agree2 = test_game_new_empty_ext(12, 12, true);
  if (Agree && Agree2) {
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

  printf("-- Start test of nb_colors and colors_present --\n"); 
  Agree = test_nb_colors(); 
  if (Agree) {
    fprintf(stderr, "Execution of b_colors and colors_present : Success\n\n");
  } else{
    fprintf(stderr, "Execution of b_colors and colors_present : Failure\n\n");
    return EXIT_FAILURE; 
  }

  printf("-- Start test of find_min --\n");
  game g = game_load("testemolere/default_game.rec.txt");
  Agree = test_find_min(g, "testemolere/default_game.sol"); 
  if (Agree) {
    fprintf(stderr, "Execution of find_min : Success\n\n");
  } else{
    fprintf(stderr, "Execution of find_min : Failure\n\n");
    return EXIT_FAILURE; 
  }

  /*printf(" -- Start 1000 tests \n"); 
  uint i =0; 
  while (i<1000){
    bool A= test_game_set_max_moves(12);
    if (!A) return EXIT_FAILURE; 
    A= test_game_play_one_move(BLUE);
    if (!A) return EXIT_FAILURE; 
    A = test_game_restart();
    if (!A) return EXIT_FAILURE; 
    A = test_game_new_empty_ext(12, 12, false);
    if (!A) return EXIT_FAILURE; 
    A = test_game_load(); 
    if (!A) return EXIT_FAILURE; 
    A = test_nb_colors(); 
    if (!A) return EXIT_FAILURE; 
    i++;
  }
  printf(" -- 1000 tests succed \n");
  */
  return EXIT_SUCCESS;
}