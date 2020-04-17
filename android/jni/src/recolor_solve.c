#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "game_io.h"
#include "string.h"
#include "time.h"
#include "solve.h"

int main(int argc, char* argv[]) {
  if (argc != 4) {
    fprintf(stderr, "error argument\n");
    return EXIT_FAILURE;
  }
  game g = game_load(argv[2]);
  if (g == NULL) {
    fprintf(stderr, "ERROR : load %s", argv[2]);
    exit(EXIT_FAILURE);
  }
  if (strcmp(argv[1], "FIND_ONE") == 0) {
    find_one(g,strcat(argv[3],".sol"),nb_colors(g));
    //find_one(argv[2], argv[3], max(g));
  } else if (strcmp(argv[1], "NB_SOL") == 0) {
    nb_sol(g, argv[3], nb_colors(g));

  } else if (strcmp(argv[1], "FIND_MIN") == 0) {
    find_min(g,strcat(argv[3],".sol")); 
  }else{ 
    fprintf(stderr,"ERROR: FILE OR  FUNCTION NAME INCORRECT\n");
    exit(EXIT_FAILURE);
  }
  game_delete(g);

  return EXIT_SUCCESS;
}
