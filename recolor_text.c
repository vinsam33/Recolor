#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "game_io.h"
#include "string.h"

void affichage_grille(game g) {
  color c;
  for (unsigned int y = 0; y < game_height(g); y++) {
    for (unsigned int x = 0; x < game_width(g); x++) {
      c = game_cell_current_color(g, x, y);
      if (c >= 10){
        c = 'A' + (c-10);
        printf("%c",c);
      }
      else{
        printf("%u",c);
      }
    }
    printf("\n");
  }
}

int main(int argc, char *argv[]) {
  if(argc != 5){
    printf("Nombre d'arguments incorrects\n");
    exit(EXIT_FAILURE);
  }
  bool state;
  int h;
  int w;
  int nb;
  if(strcmp(argv[1],"yes") == 0){
    state = true;
  }
  else if(strcmp(argv[1],"no") == 0){
    state = false;
  }
  else{
    printf("Argument wrapping invalide\n");
  }
  if(atoi(argv[2]) == 0){
    printf("Argument hauteur invalide\n");
  }
  else{
    h = atoi(argv[2]);
  }
  if(atoi(argv[3]) == 0){
    printf("Argument largeur invalide\n");
  }
  else{
    w = atoi(argv[3]);
  }
  if(atoi(argv[4]) == 0 || atoi(argv[4]) > 16){
    printf("Argument nombre de couleurs invalide\n");
  }
  else{
    nb = atoi(argv[4]);
  }
  /* color cells[144] = {
      0, 0, 0, 2, 0, 2, 1, 0, 1, 0, 3, 0, 0, 3, 3, 1, 1, 1, 1, 3, 2, 0, 1, 0,
      1, 0, 1, 2, 3, 2, 3, 2, 0, 3, 3, 2, 2, 3, 1, 0, 3, 2, 1, 1, 1, 2, 2, 0,
      2, 1, 2, 3, 3, 3, 3, 2, 0, 1, 0, 0, 0, 3, 3, 0, 1, 1, 2, 3, 3, 2, 1, 3,
      1, 1, 2, 2, 2, 0, 0, 1, 3, 1, 1, 2, 1, 3, 1, 3, 1, 0, 1, 0, 1, 3, 3, 3,
      0, 3, 0, 1, 0, 0, 2, 1, 1, 1, 3, 0, 1, 3, 1, 0, 0, 0, 3, 2, 3, 1, 0, 0,
      1, 3, 3, 1, 1, 2, 2, 3, 2, 0, 0, 2, 2, 0, 2, 3, 0, 1, 1, 1, 2, 3, 0, 1}; */
  color * cells = malloc((w*h)*sizeof(color));
  if(cells == NULL){
    fprintf(stderr,"Problem allocation memory\n");
    exit(EXIT_FAILURE);
  }
  for(uint i=0 ; i<w*h ; i++){
    cells[i] = rand()%nb;
  }
  game g = game_new_ext(w,h,cells,12,state);
  printf("nb coups joués : %d ; nb coups max : %d\n", game_nb_moves_cur(g),
         game_nb_moves_max(g));
  affichage_grille(g);
  printf(
      "Jouer un coup: (0,1,2,3,4,5,6,7,8,9,a,b,c,d,e,f ou r ou q ;  r pour redémarrer ou q pour "
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
          "Jouer un coup: (0,1,2,3,4,5,6,7,8,9,a,b,c,d,e,f ou r ou q ;  r pour redémarrer ou q pour "
          "quitter)\n");
    }
    if (c >= '0' && c <= '9'){
      game_play_one_move(g, c - 48);
      printf("nb coups joués : %d ; nb coups max : %d\n", game_nb_moves_cur(g),
             game_nb_moves_max(g));
      affichage_grille(g);
      printf(
          "Jouer un coup: (num couleur ou r pour redemarrer ou q pour "
          "quitter)\n");
    }
    if(c >= 'A' && c <= 'F'){
      game_play_one_move(g, c - 65+16);
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
