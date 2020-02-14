#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "game_io.h"
#include "string.h"
#include "time.h"

#define FILE_SIZE 300
typedef enum { FIND_ONE, NB_SOL, FIND_MIN }e_fonctions;
FILE* my_file = NULL;
//fonction qui permet de trouver une solution

color* FIND_ONE(cgame g){
    const uint nb_moves_max = nb_move_max(g);
    color cell_cur = game_cell_current_color(g, 0, 0);
    uint genere_solution;
    color* solutions= malloc(nb_moves_max* sizeof(color));
    if( solutions == NULL){
        fprintf(stderr, "Problem allocation memory \n");
        exit(EXIT_FAILURE);
    }
  uint max_col = ... // si on a une fonction qui genere le max de couleur.pour l'instant je vois pas trop.
    time_t temps;
    srand((unsigned) time(&temps));

    NEW_GENERATE:
    game_restart(g);

    for(uint i=0; i < nb_moves_max; i++){
        // j'utilise do while parce que je pense qu'il faut jouer au moins une fois
        do {
            genere_solution= rand () % (max_col+1);
        } while (genere_solution == cell_cur);
        game_play_one_move(g, genere_solution);
        cell_cur = genere_solution;
        solutions[i] = genere_solution;

        if( game_is_over(g) ){
            break;
        }
    }
    if(!game_is_over(g) ){
        goto NEW_GENERATE;
    
        return solutions;
    }
}
void NB_SOL(){

    return NULL;
}
void FIND_MIN(){

    return NULL;
}
int main(int argc, char* argv[]){
     if(argc!=4){
        fprintf(stderr,"recolor_solve FIND_ONE|NB_SOL|FIND_MIN <nom_fichier_pb> <prefix_fichier_sol>\n");
        exit(EXIT_FAILURE);
    }
    cgame g = load_game(argv[2]);

    if(strcmp(argv[1],"FIND_ONE")==0){          
        char file_name[FILE_SIZE];
        cgame solutions = FIND_ONE(g,0);
        sprintf(my_file, "%s.sol", argv[3]);// si une solution a été trouvé, on enregistre la solution dans le fichier
        if(NB_SOL()>0){ // à revoir pour le type de retour de la fonction
            game_save(solutions, file_name);
        }
        else {
            my_file = NULL;

        }
}