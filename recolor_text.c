#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "game_io.h"
#include "string.h"
#include "time.h"
#include "game_rand.h"

void affichage_grille(game g) {
  color c;
  for (unsigned int y = 0; y < game_height(g); y++) {
    for (unsigned int x = 0; x < game_width(g); x++) {
      c = game_cell_current_color(g, x,
                                  y);  // We look at each color of the grid
      if (c >= 10) {  // If they are> = to 10 we replace them with their alphabetical value
        c = 'A' + (c - 10);
        printf("%c", c);  // We display the alphabetical value
      } else {
        printf("%u", c);  // Otherwise we display the figure
      }
    }
    printf("\n");
  }
}

int main(int argc, char *argv[]) {
  game g;
  if (argc != 2 && argc != 6 && argc!= 4 && argc != 5 ) {
    color cells[144] = {
        0, 0, 0, 2, 0, 2, 1, 0, 1, 0, 3, 0, 0, 3, 3, 1, 1, 1, 1, 3, 2, 0, 1, 0,
        1, 0, 1, 2, 3, 2, 3, 2, 0, 3, 3, 2, 2, 3, 1, 0, 3, 2, 1, 1, 1, 2, 2, 0,
        2, 1, 2, 3, 3, 3, 3, 2, 0, 1, 0, 0, 0, 3, 3, 0, 1, 1, 2, 3, 3, 2, 1, 3,
        1, 1, 2, 2, 2, 0, 0, 1, 3, 1, 1, 2, 1, 3, 1, 3, 1, 0, 1, 0, 1, 3, 3, 3,
        0, 3, 0, 1, 0, 0, 2, 1, 1, 1, 3, 0, 1, 3, 1, 0, 0, 0, 3, 2, 3, 1, 0, 0,
        1, 3, 3, 1, 1, 2, 2, 3, 2, 0, 0, 2, 2, 0, 2, 3, 0, 1, 1, 1, 2, 3, 0, 1};
    g = game_new(cells, 12);
  } else if (argc == 2) {
    g = game_load(argv[1]);
  }

  else {
    int w=0;       // width
    int h=0;       // height
    bool state=false;  // wrapping
    int nb_max=0; //nb_max_move    
    int nb=0;      // nb_colors
    
    if (atoi(argv[1]) == 0) {
      printf("Argument largeur invalide\n");
    } else {
      w = atoi(argv[1]);
    }
    
    if (atoi(argv[2]) == 0) {
      printf("Argument hauteur invalide\n");
    } else {
      h = atoi(argv[2]);
    }
    if (atoi(argv[3])==0){
      printf("Invalid mb_max_move\n");
    }else{
      nb_max=atoi(argv[3]);
    }
    if (argc== 5 || argc ==6){
      if (atoi(argv[4]) == 0 || atoi(argv[4]) > 16) {
        printf("Invalid number of colors argument\n");
        printf("So we go to nb_colors = 4\n");
        nb= 4;
    } else {
        nb = atoi(argv[4]);
    }
    }else{
      nb= 3;
    }
    if (argc==6){
      if (strcmp(argv[5], "S") == 0) {
      state = true;
    } else if (strcmp(argv[5], "N") == 0) {
        state = false;
    } 

    }else{
      state = false;
    }
    
    
    
  
    srand(time(NULL));  // initialisation de rand

    g = game_random_ext(w, h, state, nb, nb_max);
  }
  /*if (argc != 1 && argc != 2 && argc != 5) {
    printf(
        "Nombre d'arguments incorrects, arguments attendus  pour v1 : "
        "./recolor_text \n");
    printf("pour v2: ./recolor_text  [wrapping] [height] [width] [nb_color]\n");
    printf("pour load: ./recolor_text fichier_load.rec\n");
    exit(EXIT_FAILURE);
  }*/
  printf("nb coups joués : %u ; nb coups max : %u\n", game_nb_moves_cur(g),
         game_nb_moves_max(g));
  affichage_grille(g);
  printf("Jouer un coup: (");
  printf("0,1,2,3,4,5,6,7,8,9,A,B,C,D,E,F");
  printf(" ou r ou q ; r pour redémarrer ou q pour quitter)\n");

  while (game_is_over(g) == false) {
    int c = getchar();
    if (c == EOF) {
      exit(EXIT_SUCCESS);
    }
    if (c == 'q') {  // leave the game
      if (argc == 2) {
        game_save(g, argv[1]);  // save the game when you leave the game
      }
      if (argc == 6||argc ==5 || argc == 4) {
        game_save(g, "recolor_v2.rec");  // save game a v2
      }
      if (argc != 6 && argc != 2 && argc != 5) {
        game_save(g, "recolor_v1.rec");  // save game a v1 
      }
      break;
    }
    if (c == 'r') {  // restart the game
      game_restart(g);
      printf("nb coups joués : %u ; nb coups max : %u\n", game_nb_moves_cur(g),
             game_nb_moves_max(g));
      affichage_grille(g);
      printf("Jouer un coup: (");
      printf("0,1,2,3,4,5,6,7,8,9,A,B,C,D,E,F");
      printf(" ou r ou q ; r pour redémarrer ou q pour quitter)\n");
    }
    if (c >= '0' && c <= '9') {  // Game with digital color
      game_play_one_move(g, c - 48);
      printf("nb coups joués : %u ; nb coups max : %u\n", game_nb_moves_cur(g), game_nb_moves_max(g));
      affichage_grille(g);
      printf(
          "Jouer un coup: (num couleur ou r pour redemarrer ou q pour "
          "quitter)\n");
    }
    if (c >= 'A' && c <= 'F') {  // Game with an alphabetical color
      game_play_one_move(g, c - 55);
      printf("nb coups joués : %u ; nb coups max : %u\n", game_nb_moves_cur(g),game_nb_moves_max(g));
      affichage_grille(g);
      printf(
          "Jouer un coup: (num couleur ou r pour redemarrer ou q pour "
          "quitter)\n");
    }
  }

  if (game_is_over(g) &&
      game_nb_moves_cur(g) <=
          game_nb_moves_max(g)) {  // Displays whether the game is won or not
    printf("BRAVO\n");
  } else {
    printf("DOMMAGE\n");
  }
  game_delete(g);
  return EXIT_SUCCESS;
}