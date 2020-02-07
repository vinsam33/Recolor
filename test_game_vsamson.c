#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "game_io.h"

#define MAXLINELEN 4096
/**
 *@brief : teste la fonction  game_new_empty.
 *@return false s'il y a une erreur ou si la couleur n'est pas 0 ,sinon true.
 **/
bool test_game_new_empty() {
  game g = game_new_empty();
  if (g == NULL) {  // verif si le pointer n'est pas NULL.
    game_delete(g);
    return false;
  }  // verif dimensions

  if (!game_is_over(g)) {
    fprintf(stderr, "ERROR : GAME_IS_OVER\n\n");
    game_delete(g);
    return false;
  }  // verif moves

  if (game_nb_moves_cur(g) != 0 || game_nb_moves_max(g) != 0) {
    fprintf(stderr, "ERROR : MOVE\n\n");
    game_delete(g);
    return false;
  }  // verif si on a dans une case ,une couleur differente de 0.

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
 *@brief : teste la fonction  game_cell_current_color.
 *@return false s'il y a une erreur ou ce n'est pas la bonne couleur,sinon true.
 **/
bool test_game_cell_current_color() {
  game g = game_new_empty_ext(5, 5, true);
  if (!g) {  // verif si le pointer n'est pas NULL.
    fprintf(stderr, "ERROR POINTER\n\n");
    game_delete(g);
    return false;
  }  // verif si on a les mêmes couleurs dans les deux fonctions et à la bonne
     // case.

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
 * @brief teste la fonction game_delete.
 *
 * @return true  si le jeu est detruit.
 * @return false s'il y a un probleme de memoire.
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
  if (g == NULL) {  // verif si le pointer n'est pas NULL.
    fprintf(stderr, "ERROR POINTER\n");
    exit(EXIT_FAILURE);
  }  // supprime le jeu.
  game_delete(g);
  return true;
}
/**
 * @brief teste la fonction game_height.
 *
 * @return true si c'est la bonne dimension et aucun problème.
 * @return false si ce n'est pas la  bonne taille.
 **/
bool test_game_height() {
  game g = game_new_empty_ext(5, 5, true);
  if (g == NULL) {  // verif si le pointer n'est pas NULL.
    fprintf(stderr, "ERROR POINTER\n");
    game_delete(g);
    return false;
  }
  if (game_height(g) != 5) {  // verif si on a la bonne height.
    fprintf(stderr, "ERROR HEIGHT\n");
    game_delete(g);
    return false;
  }
  game_delete(g);

  return true;
}

/**
 * @brief teste la fonction game_save dans le fichier game_io.c
 * @return false si la fonction a un problème
 * @return true sinon
 **/
bool test_game_save() {
  color cells[144] = {
      0, 0, 0, 2, 0, 2, 1, 0, 1, 0, 3, 0, 0, 3, 3, 1, 1, 1, 1, 3, 2, 0, 1, 0,
      1, 0, 1, 2, 3, 2, 3, 2, 0, 3, 3, 2, 2, 3, 1, 0, 3, 2, 1, 1, 1, 2, 2, 0,
      2, 1, 2, 3, 3, 3, 3, 2, 0, 1, 0, 0, 0, 3, 3, 0, 1, 1, 2, 3, 3, 2, 1, 3,
      1, 1, 2, 2, 2, 0, 0, 1, 3, 1, 1, 2, 1, 3, 1, 3, 1, 0, 1, 0, 1, 3, 3, 3,
      0, 3, 0, 1, 0, 0, 2, 1, 1, 1, 3, 0, 1, 3, 1, 0, 0, 0, 3, 2, 3, 1, 0, 0,
      1, 3, 3, 1, 1, 2, 2, 3, 2, 0, 0, 2, 2, 0, 2, 3, 0, 1, 1, 1, 2, 3, 0, 1};
  // test avec version wrapping
  game g = game_new_ext(12, 12, cells, 10, true);
  if (g == NULL) {
    game_delete(g);
    return false;
  }
  game_save(g, "test.rec");  // sauvegarde la partie directement au debut
  game g2 = game_load(
      "test.rec");  // charge la partie et on verifie que l'on a bien sauvegardé
  if (g2 == NULL) {
    game_delete(g);
    game_delete(g2);
  }
  if (game_is_wrapping(g) == true) {  // verif paramètre si wrapping
    if (game_width(g) != game_width(g2) || game_height(g) != game_height(g2) ||
        game_nb_moves_max(g) != game_nb_moves_max(g2) ||
        game_is_wrapping(g) != game_is_wrapping(g2)) {
      game_delete(g);
      game_delete(g2);
      return false;
    }
  }
  // verif les positions des cellules
  for (uint x = 0; x < game_width(g); x++) {
    for (uint y = 0; y < game_height(g); y++) {
      if (game_cell_current_color(g, x, y) !=
          game_cell_current_color(g2, x, y)) {
        game_delete(g);
        game_delete(g2);
        return false;
      }
    }
  }
  game_delete(g);
  game_delete(g2);

  // test avec sans wrapping
  game g3 = game_new_ext(12, 12, cells, 10, false);
  if (g3 == NULL) {
    game_delete(g3);
    return false;
  }
  game_save(g3, "test2.rec");  // sauvegarde la partie directement au debut
  game g4 = game_load("test2.rec");  // charge la partie et on verifie que l'on
                                     // a bien sauvegardé
  if (g4 == NULL) {
    game_delete(g3);
    game_delete(g4);
  }
  if (game_width(g3) != game_width(g4) || game_height(g3) != game_height(g4) || game_nb_moves_max(g3) != game_nb_moves_max(g4)) {
    game_delete(g3);
    game_delete(g4);
    return false;
  }
  // verif les positions des cellules
  for (uint x = 0; x < game_width(g3); x++) {
    for (uint y = 0; y < game_height(g3); y++) {
      if (game_cell_current_color(g3, x, y) != game_cell_current_color(g3, x, y)) {
        game_delete(g3);
        game_delete(g4);
        return false;
      }
    }
  }
  game_delete(g3);
  game_delete(g4);
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

  return EXIT_SUCCESS;
}
