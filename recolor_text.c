#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "game_io.h"

void affichage_grille(game g) {
  for (unsigned int y = 0; y < game_height; y++) {
    for (unsigned int x = 0; x < game_width; x++) {
      printf("%d", game_cell_current_color(g, x, y));
    }
    printf("\n");
  }
}

int main(void) {
  color cells[144] = {
      0, 0, 0, 2, 0, 2, 1, 0, 1, 0, 3, 0, 0, 3, 3, 1, 1, 1, 1, 3, 2, 0, 1, 0,
      1, 0, 1, 2, 3, 2, 3, 2, 0, 3, 3, 2, 2, 3, 1, 0, 3, 2, 1, 1, 1, 2, 2, 0,
      2, 1, 2, 3, 3, 3, 3, 2, 0, 1, 0, 0, 0, 3, 3, 0, 1, 1, 2, 3, 3, 2, 1, 3,
      1, 1, 2, 2, 2, 0, 0, 1, 3, 1, 1, 2, 1, 3, 1, 3, 1, 0, 1, 0, 1, 3, 3, 3,
      0, 3, 0, 1, 0, 0, 2, 1, 1, 1, 3, 0, 1, 3, 1, 0, 0, 0, 3, 2, 3, 1, 0, 0,
      1, 3, 3, 1, 1, 2, 2, 3, 2, 0, 0, 2, 2, 0, 2, 3, 0, 1, 1, 1, 2, 3, 0, 1};
  game g = game_new(cells, 12);
  printf("nb coups joués : %d ; nb coups max : %d\n", game_nb_moves_cur(g),
         game_nb_moves_max(g));
  affichage_grille(g);
  printf(
      "Jouer un coup: (0,1,2,3,r ou q ;  r pour redémarrer ou q pour "
      "quitter)\n");
  while (game_is_over(g) == false) {
    int c = getchar();
    if (c == EOF) {
      exit(EXIT_SUCCESS);
    }
    if (c == 'q') {
      break;
    }
    if (c == 'r') {
      game_restart(g);
      printf("nb coups joués : %d ; nb coups max : %d\n", game_nb_moves_cur(g),
             game_nb_moves_max(g));
      affichage_grille(g);
      printf(
          "Jouer un coup: (0,1,2,3,r ou q ;  r pour redémarrer ou q pour "
          "quitter)\n");
    }
    if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'F')){
      game_play_one_move(g, c - 48);
      printf("nb coups joués : %d ; nb coups max : %d\n", game_nb_moves_cur(g),
             game_nb_moves_max(g));
      affichage_grille(g);
      printf(
          "Jouer un coup: (num couleur ou r pour redemarrer ou q pour "
          "quitter)\n");
    }
  }

  if (game_is_over(g) && game_nb_moves_cur(g) <= game_nb_moves_max(g)) {
    printf("BRAVO\n");
  } else {
    printf("DOMMAGE\n");
  }
  game_delete(g);
  return EXIT_SUCCESS;
}
