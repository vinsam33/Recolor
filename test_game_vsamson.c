#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "game_io.h"
#include "solve.h"

/**
 *@brief : test the game_new_empty function
 *@return false if there is an error or if the color is not 0,else true.
 **/
bool test_game_new_empty() {
  game g = game_new_empty();
  if (g == NULL) {  // check if the pointer is not NULL.
    game_delete(g);
    return false;
  }  // check dimensions

  if (!game_is_over(g)) {
    fprintf(stderr, "ERROR : GAME_IS_OVER\n\n");
    game_delete(g);
    return false;
  }  // check moves

  if (game_nb_moves_cur(g) != 0 || game_nb_moves_max(g) != 0) {
    fprintf(stderr, "ERROR : MOVE\n\n");
    game_delete(g);
    return false;
  }  // check if we have in a box of a color different from 0.

  for (unsigned int y = 0; y < game_height(g); y++) {
    for (unsigned int x = 0; x < game_width(g); x++) {
      if (game_cell_current_color(g, x, y) != 0) {
        game_delete(g);
        return false;
      }
    }
  }

  game_delete(g);
  return true;
}

/**
 *@brief : test the game_cell_current_color function.
 *@return false if there is an error or it is the wrong color,sinon true.
 **/
bool test_game_cell_current_color() {
  game g = game_new_empty_ext(5, 5, true);
  if (!g) {  // verif si le pointer n'est pas NULL.
    fprintf(stderr, "ERROR POINTER\n\n");
    game_delete(g);
    return false;
  }  // check if we have the same colors in both functions and in the right box.

  for (uint y = 0; y < game_height(g); y++) {
    for (uint x = 0; x < game_width(g); x++) {
      game_set_cell_init(g, x, y, 2);
      if (game_cell_current_color(g, x, y) != 2) {
        game_delete(g);
        return false;
      }
    }
  }

  game_delete(g);
  return true;
}

/**
 * @brief test the game_delete function.
 *
 * @return true if the game is destroyed.
 * @return false if there is a memory problem.
 **/
bool test_game_delete() {
  color cells[144] = {
      0, 0, 0, 2, 0, 2, 1, 0, 1, 0, 3, 0, 0, 3, 3, 1, 1, 1, 1, 3, 2, 0, 1, 0,
      1, 0, 1, 2, 3, 2, 3, 2, 0, 3, 3, 2, 2, 3, 1, 0, 3, 2, 1, 1, 1, 2, 2, 0,
      2, 1, 2, 3, 3, 3, 3, 2, 0, 1, 0, 0, 0, 3, 3, 0, 1, 1, 2, 3, 3, 2, 1, 3,
      1, 1, 2, 2, 2, 0, 0, 1, 3, 1, 1, 2, 1, 3, 1, 3, 1, 0, 1, 0, 1, 3, 3, 3,
      0, 3, 0, 1, 0, 0, 2, 1, 1, 1, 3, 0, 1, 3, 1, 0, 0, 0, 3, 2, 3, 1, 0, 0,
      1, 3, 3, 1, 1, 2, 2, 3, 2, 0, 0, 2, 2, 0, 2, 3, 0, 1, 1, 1, 2, 3, 0, 1};
  game g = game_new_ext(12, 12, cells, 10, true);
  if (g == NULL) {  // check if the pointer is not NULL.
    fprintf(stderr, "ERROR POINTER\n");
    exit(EXIT_FAILURE);
  }  // delete the game.
  game_delete(g);
  return true;
}
/**
 * @brief test the game_height function.
 *
 * @return true if it's the right size and no problem.
 * @return false if it is not the right size.
 **/
bool test_game_height() {
  game g = game_new_empty_ext(5, 5, true);
  if (g == NULL) {  // check if the pointer is not NULL.
    fprintf(stderr, "ERROR POINTER\n");
    game_delete(g);
    return false;
  }
  if (game_height(g) != 5) {  // check if we have the right height.
    fprintf(stderr, "ERROR HEIGHT\n");
    game_delete(g);
    return false;
  }
  game_delete(g);

  return true;
}

/**
 * @brief test the game_save function in the game_io.c file.
 * @return false if the function has a problem.
 * @return true else.
 **/
bool test_game_save(){
  color cells[144] = {
      0, 0, 0, 2, 0, 2, 1, 0, 1, 0, 3, 0, 0, 3, 3, 1, 1, 1, 1, 3, 2, 0, 1, 0,
      1, 0, 1, 2, 3, 2, 3, 2, 0, 3, 3, 2, 2, 3, 1, 0, 3, 2, 1, 1, 1, 2, 2, 0,
      2, 1, 2, 3, 3, 3, 3, 2, 0, 1, 0, 0, 0, 3, 3, 0, 1, 1, 2, 3, 3, 2, 1, 3,
      1, 1, 2, 2, 2, 0, 0, 1, 3, 1, 1, 2, 1, 3, 1, 3, 1, 0, 1, 0, 1, 3, 3, 3,
      0, 3, 0, 1, 0, 0, 2, 1, 1, 1, 3, 0, 1, 3, 1, 0, 0, 0, 3, 2, 3, 1, 0, 0,
      1, 3, 3, 1, 1, 2, 2, 3, 2, 0, 0, 2, 2, 0, 2, 3, 0, 1, 1, 1, 2, 3, 0, 1};
  // test with  wrapping version
  game g = game_new_ext(12, 12, cells, 10, true);
  if (g == NULL) {
    game_delete(g);
    return false;
  }
  game_save(g, "test.rec");  // save the game directly at the start
  FILE *f = fopen("test.rec", "r");
  if (!f) {
    fprintf(stderr, "NULL pointer");
    game_delete(g);
    exit(EXIT_FAILURE);
  }char wrap[2];
  uint w1;
  uint h1;
  uint nx1;
  fscanf(f,"%2u %2u %2u %1s\n",&h1,&w1,&nx1,wrap);
  if (h1!= 12){
    printf("erreur game_height is %u et non 12\n",game_width(g));
    fclose(f);
    game_delete(g);
    return false;
  }
  if(w1!=12){
    printf("erreur game_width is %u et non 12\n",game_height(g));
    fclose(f);
    game_delete(g);
    return false;
  }
  if(nx1!=10){
    printf("erreur game_nb_max is %u et non 10\n",game_nb_moves_max(g));
    fclose(f);
    game_delete(g);
    return false;
  }
  if(strcmp(wrap, "N") == 0){
    printf("erreur game_width is %u et non 10\n",game_nb_moves_max(g));
    fclose(f);
    game_delete(g);
    return false;
  }

for (uint x = 0; x < game_width(g); x++) {
    for (uint y = 0; y < game_height(g); y++) {
        if (game_cell_current_color(g,x,y)!= cells[y * game_width(g) + x]){
          printf("erreur coordonée x = %u y = %u , %u et non %u\n",x,y,cells[y * game_width(g) + x],game_cell_current_color(g,x,y));
          fclose(f);
          game_delete(g);
          return false;
        }
      }
  }
  fclose(f);
  game_delete(g);


  game g2 = game_new_ext(12, 12, cells, 10, false);
    if (g2 == NULL) {
    game_delete(g2);
    return false;
  }
  game_save(g2, "test2.rec");  // save the game directly at the start
  FILE *f_2 = fopen("test2.rec", "r");
  if (!f_2) {
    fprintf(stderr, "NULL pointer");
    game_delete(g2);
    exit(EXIT_FAILURE);
  }char wrapi[2];
  uint w;
  uint h;
  uint nx;
  fscanf(f_2,"%2u %2u %2u %1s\n",&h, &w, &nx,wrapi);
  if (h != 12){
    printf("erreur game_height is %u et non 12\n",h);
    fclose(f_2);
    game_delete(g2);
    return false;
  }
  if(w!=12){
    printf("erreur game_width is %u et non 12\n",w);
    fclose(f_2);
    game_delete(g2);
    return false;
  }
  if(nx!=10){
    printf("erreur game_nb_max is %u et non 10\n",nx);
    fclose(f_2);
    game_delete(g2);
    return false;
  }
  if((game_is_wrapping(g2) == false ) && strcmp(wrapi, "S") == 0){
    printf("erreur malloc");
    fclose(f_2);
    game_delete(g2);
    return false;
  }

for (uint i = 0; i < game_width(g2); i++) {
    for (uint j = 0; j < game_height(g2); j++) {
        if (game_cell_current_color(g2,i,j)!= cells[j * game_width(g2) + i]){
          printf("erreur coordonée x = %u y = %u , %u et non %u\n",i,j,cells[j * game_width(g) + i],game_cell_current_color(g2,i,j));
          fclose(f_2);
          game_delete(g2);
          return false;
        }
      }
  }
  fclose(f_2);
  game_delete(g2);


  return true;

}

/**
 * @brief test if nb_sol is correct or not and if the save is correct or not.
 * @return true if the number of solution is correct and if the number and the sentense are correct.
 * @return false else.
 */
bool test_nb_sol(){
  color cells[4] = {1,0,0,0};    
  game g = game_new_ext(2,2,cells,1,false);
  if (g == NULL){
    game_delete(g);
    return false;
  }
  char file[13]= "test_nb_sol";//file 
  char str1[13];
  nb_sol(g,file,max(g));//function
  FILE *f = fopen(file,"r");
  int sol;
  //rewind(f);
  fscanf(f,"%7s = %d",str1,&sol);//extract sentense and number.
  fclose(f);
  if((strcmp(str1,"NB_SOL")<0)||(strcmp(str1,"NB_SOL")>0)){ //test is the file has written wel at th beginning  "NB_SOL" or not.
    printf("ce n'est pas NB_SOL\n");
    game_delete(g);
    return false;
  }
  if(sol !=1){//test if the sol is 156 in the file.
    printf("c'est pas 1 mais %d\n",sol);
    game_delete(g);
    return false;
  } 
  
  game_delete(g);
	return true;

}

int main(void) {  // start tests.
  printf("----------------Start test_new_empty----------------\n\n");

  bool nouveaux = test_game_new_empty();
  if (nouveaux == true) {
    fprintf(stderr, "EXECUTING OF game_new_empty IS : SUCCESS\n\n ");
  } else {
    fprintf(stderr, "EXECUTING OF game_new_empty IS : FAILURE\n\n ");
    return EXIT_FAILURE;
  }

  printf(
      "----------------Start test_game_cell_current_color----------------\n\n");

  bool color = test_game_cell_current_color();
  if (color == true) {
    fprintf(stderr, "EXECUTING OF game_cell_current_color IS : SUCCESS\n\n");
  } else {
    fprintf(stderr, "EXECUTING OF game_cell_current_color IS : FAILURE\n\n ");
    return EXIT_FAILURE;
  }

  printf("----------------Start test_game_delete----------------\n\n");

  bool supr = test_game_delete();
  if (supr == true) {
    fprintf(stderr, "EXECUTING OF game_delete IS : SUCCESS\n\n ");

  } else {
    fprintf(stderr, "EXECUTING OF game_delete IS : FAILURE\n\n ");
    return EXIT_FAILURE;
  }

  printf("----------------Start test_game_height----------------\n\n");

  bool height = test_game_height();
  if (height == true) {
    fprintf(stderr, "EXECUTING OF height IS : SUCCESS\n\n ");
  } else {
    fprintf(stderr, "EXECUTING OF height IS : FAILURE\n\n ");
  }

  printf("----------------Start test_game_save----------------\n\n");
  bool save = test_game_save();
  if (save == true) {
    fprintf(stderr, "EXECUTING OF save IS : SUCCESS\n\n");
  } else {
    fprintf(stderr, "EXECUTING OF save IS : FAILURE\n\n ");
  }
  printf("----------------Start test_nb_sol----------------\n\n");
  bool nb_sol_test = test_nb_sol();
  if (nb_sol_test == true) {
    fprintf(stderr, "EXECUTING OF nb_sol IS : SUCCESS\n\n");
  } else {
    fprintf(stderr, "EXECUTING OF nb_sol IS : FAILURE\n\n ");
  }
  return EXIT_SUCCESS;
}
