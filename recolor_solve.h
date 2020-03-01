#ifndef RECOLOR_SOLVE_H
#define RECOLOR_SOLVE_H
#include <stdio.h>
#include "game.h"
#include <stdbool.h>


/**
 * @file recolor_solve.h
 *
 * @brief This file provides functions to test and give solution or the number of solution in a game.
 *
 **/

/**
 * @brief give number max color in the game
 * @return number max color
 * g is the game.
 **/
uint max(game g);

/**
 * @brief give number max color in the game
 * @return number max color
 * g is the game.
 **/
uint nb_colors(game g);

/**
 * @brief give tab present color in the game
 * @return number tab present color
 * g is the game.
 **/
uint colors_present(game g);

/**
 *@brief save and print the result
 * g is the game
 * file is the file in order to convert to 'file'.nbsol
 * cpt is number of solution
 **/
void save_nbsol(game g, char* file, uint cpt);

/**
 * @brief this function counts the number of possible solutions in a game by
 *browsing the grid if the game is winner.
 * @return the number of solution if you win else 0 solution .
 * g is the game
 * this fonction was called by NB_SOL
 **/
uint nb_sol_aux(game g, uint nbcolors);


/**
 * @brief this fonction call NB_SOL_AUX and save_nbsol
 * @return number of possible solution when you win in a file .nbsol.
 * g is the game.
 * file is the name of game load.
 * nbcolors is the maximum number of colors in the game.
 **/
void nb_sol(game g, char* file, uint nbcolors);

/**
 * @brief this function find and give a solution to win the game.
 * @return a solution in a file .sol.
 * game_curr is the file of the game
 * sol is the solution file.
 * nb_color is the max number color in the game.  
**/
void find_one(char* game_curr, char* sol, uint nb_color);

void find_min_aux(game g, uint nbcolors,  color color_possible[], uint *nb_max , uint *tab, uint *tabn, uint cpt);
void find_min(game g, char* fichier_sol, color color_possible[]);

#endif  // RECOLOR_SOLVE_H__