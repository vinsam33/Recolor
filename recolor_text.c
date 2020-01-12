#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "game_io.h"
#include "string.h"

void affichage_grille(game g) { //affiche la grille
  color c; //couleur.
  for (unsigned int y = 0; y < game_height(g); y++) {
    for (unsigned int x = 0; x < game_width(g); x++) {
      c = game_cell_current_color(g, x, y);
      if (c >= 10){ // si c = A,B,C,D,E ou F.
        c = 'A' + (c-10);
        printf("%c",c); // affiche la lettre.
      }
      else{
        printf("%u",c); // sinon affiche chiffre.
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
  int h; //height.
  int w; //weight.
  int nb; // nb_color.
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
    cells[i] = rand()%nb; //selectionne couleur au hasard.
  }
  game g = game_new_ext(w,h,cells,12,state); //jeux initialisé.
  printf("nb coups joués : %d ; nb coups max : %d\n", game_nb_moves_cur(g), //affiche le score.
         game_nb_moves_max(g));
  affichage_grille(g);
  
  printf("Jouer un coup: ("); // affiche le message en fonction du nombre de couleurs choisies.
  uint k; 
  if (nb>9){
    for(uint i=0; i<10; i++){
      printf("%d,",i);
    }
    for (uint j =10; j<nb; j++){
      k = 'A' + (j-10);
      printf("%c,", k); 
    }
  }
  else{
    for(uint i=0; i<nb; i++){
      printf("%d,",i);
    }
  }
  printf(" ou r ou q ; r pour redémarrer ou q pour quitter)\n");
  
  while (game_is_over(g) == false) {
    int c = getchar();
    if (c == EOF) {
      exit(EXIT_SUCCESS);
    }
    if (c == 'q') { // quitte le jeu.
      break;
    }
    if (c == 'r') { //redemarre le jeu.
      game_restart(g);
      printf("nb coups joués : %d ; nb coups max : %d\n", game_nb_moves_cur(g), //affiche le score quand on redemarre.
             game_nb_moves_max(g));
      affichage_grille(g);
      
      printf("Jouer un coup: ("); //affiche le message de depart quand on redemarre le jeu.
      uint k; 
      if (nb>9){
        for(uint i=0; i<10; i++){
          printf("%d,",i);
        }
        for (uint j =10; j<nb; j++){
          k = 'A' + (j-10);
          printf("%c,", k); 
        }
      }
      else{
        for(uint i=0; i<nb; i++){
          printf("%d,",i);
        }
      }
      printf(" ou r ou q ; r pour redémarrer ou q pour quitter)\n");
    }
    
    if (c >= '0' && c <= '9'){ // deplacement avec les chiffres.
      game_play_one_move(g, c - 48);
      printf("nb coups joués : %d ; nb coups max : %d\n", game_nb_moves_cur(g),
             game_nb_moves_max(g));
      affichage_grille(g);
      printf(
          "Jouer un coup: (num couleur ou r pour redemarrer ou q pour "
          "quitter)\n");
    }
    
    if(c >= 'A' && c <= 'F'){ // deplacement avec les lettres.
      game_play_one_move(g, c - 71+16);
      printf("nb coups joués : %d ; nb coups max : %d\n", game_nb_moves_cur(g),
             game_nb_moves_max(g));
      affichage_grille(g);
      printf(
          "Jouer un coup: (num couleur ou r pour redemarrer ou q pour "
          "quitter)\n");
    }
  }

  if (game_is_over(g) && game_nb_moves_cur(g) <= game_nb_moves_max(g)) {
    printf("BRAVO\n"); //affiche si on a gagné.
  } else {
    printf("DOMMAGE\n");//affiche si on a perdu/on quitte le jeu.
  }
  game_delete(g);
  return EXIT_SUCCESS;
}
