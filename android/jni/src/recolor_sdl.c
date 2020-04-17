#include "recolor_sdl.h"
#include <SDL.h>
#include <SDL_image.h>  // required to load transparent texture from PNG
#include <SDL_ttf.h>    // required to use TTF fonts
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "game_io.h"
#include "game_rand.h"
#include "time.h"

/* **************************************************************** */
#define FONT "Arial.ttf"
#define FONTSIZE 12
#define BANDEAU 30

/* **************************************************************** */

struct Env_t {
  /* PUT YOUR VARIABLES HERE */
  game g;
  SDL_Color *colors;
  SDL_Texture *text;
  int argc;
  char **argv;
  SDL_Texture *Button_Quit;
  SDL_Texture *Button_new ;
	SDL_Texture *Button_Restart;
  SDL_Texture *level;
  int width;
  int height;
  int nb_col;
  int nb_mov_max;
  bool wrapping;
};

/* **************************************************************** */

Env *init(SDL_Window *win, SDL_Renderer *ren, int argc, char *argv[]) {
  Env *env = malloc(sizeof(struct Env_t));
  env->argc = argc;
  env->argv = argv;  // argv[env->argc];
  PRINT("Move a cell with  mouse.\n");
  PRINT(
      "Press 'q' if you want to stop the game and to save or press 'r' to "
      "restart the game !\n");
  PRINT("Good luck.\n");

  /* Init colors  */
  // in rgba
  env->colors = malloc(16 * sizeof(SDL_Color));
  env->colors[0] = (SDL_Color){255, 0, 0, 0};       // red
  env->colors[1] = (SDL_Color){0, 255, 0, 0};       // green
  env->colors[2] = (SDL_Color){0, 0, 255, 0};       // blue
  env->colors[3] = (SDL_Color){255, 255, 0, 0};     // yellow
  env->colors[4] = (SDL_Color){255, 165, 0, 0};     // orange
  env->colors[5] = (SDL_Color){238, 130, 238, 0};   // violet
  env->colors[6] = (SDL_Color){255, 192, 203, 0};   // pink
  env->colors[7] = (SDL_Color){128, 128, 128, 0};   // grey
  env->colors[8] = (SDL_Color){0, 255, 255, 0};     // cyan
  env->colors[9] = (SDL_Color){139, 69, 19, 0};     // brown
  env->colors[10] = (SDL_Color){128, 0, 0, 0};      // bordeaux red
  env->colors[11] = (SDL_Color){0, 0, 0, 0};        // black
  env->colors[12] = (SDL_Color){255, 255, 255, 0};  // white or
  env->colors[13] = (SDL_Color){245, 245, 220, 0};  // beige
  env->colors[14] = (SDL_Color){0, 100, 0, 0};      // dark green
  env->colors[15] = (SDL_Color){210, 105, 30, 0};   // chocolate

 

  
  // init game  */
  // with argument

  if (argc != 2 && argc != 6 && argc != 5 && argc != 4) {
    color cells[144] = {
        0, 0, 0, 2, 0, 2, 1, 0, 1, 0, 3, 0, 0, 3, 3, 1, 1, 1, 1, 3, 2, 0, 1, 0,
        1, 0, 1, 2, 3, 2, 3, 2, 0, 3, 3, 2, 2, 3, 1, 0, 3, 2, 1, 1, 1, 2, 2, 0,
        2, 1, 2, 3, 3, 3, 3, 2, 0, 1, 0, 0, 0, 3, 3, 0, 1, 1, 2, 3, 3, 2, 1, 3,
        1, 1, 2, 2, 2, 0, 0, 1, 3, 1, 1, 2, 1, 3, 1, 3, 1, 0, 1, 0, 1, 3, 3, 3,
        0, 3, 0, 1, 0, 0, 2, 1, 1, 1, 3, 0, 1, 3, 1, 0, 0, 0, 3, 2, 3, 1, 0, 0,
        1, 3, 3, 1, 1, 2, 2, 3, 2, 0, 0, 2, 2, 0, 2, 3, 0, 1, 1, 1, 2, 3, 0, 1};
    env->g = game_new(cells, 12);

  } else if (argc == 2) {
    env->g = game_load(argv[1]);
  } else {
    int w = atoi(argv[1]);       // width
    int h = atoi(argv[2]);       // height
    bool state=false;                  // wrapping
    int nb_max = atoi(argv[3]);  // nb_max_move
    int nb;                      // nb_colors

    // choice with nb_colors
    if (argc == 5 || argc == 6) {
      if (atoi(argv[4]) == 0 || atoi(argv[4]) > 16) {
        nb = 4;
      } else {
        nb = atoi(argv[4]);
      }
    } else {
      nb = 3;
    }
    // choice wrapping
    if (argc == 6) {
      if (strcmp(argv[5], "S") == 0) {
        state = true;
      } else if (strcmp(argv[5], "N") == 0) {
        state = false;
      }

    } else {
      state = false;
    }

    env->width =w;
    env->height =h;
    env->nb_col =nb;
    env->nb_mov_max = nb_max;
    env->wrapping = state;
    // initialization of rand

    srand(time(NULL));

    env->g = game_random_ext(w, h, state, nb, nb_max);
  }

  TTF_Font *button = TTF_OpenFont(FONT, 2*FONTSIZE);

env->Button_Quit    = SDL_CreateTextureFromSurface(ren, TTF_RenderUTF8_Blended(button, "QUIT", (SDL_Color){255, 255, 255, 0}));
env->Button_Restart = SDL_CreateTextureFromSurface(ren, TTF_RenderUTF8_Blended(button, "RESTART", (SDL_Color){255, 255, 255, 0}));
env->Button_new = SDL_CreateTextureFromSurface(ren, TTF_RenderUTF8_Blended(button, "NEW", (SDL_Color){255, 255, 255, 0}));
env->level = SDL_CreateTextureFromSurface(ren, TTF_RenderUTF8_Blended(button, "LEVEL", (SDL_Color){255, 255, 255, 0}));
TTF_CloseFont(button);

  return env;
}

/* **************************************************************** */

void render(SDL_Window *win, SDL_Renderer *ren, Env *env) { /* HERE CODE  TO RENDER TEXTURES, ... */
  SDL_Rect rect;
  int w, h;
  uint c;
  // get current windows size
  SDL_GetWindowSize(win, &w, &h);
  uint h_windows = h;
  uint w_windows = w;
  w = w / game_width(env->g);
  h = (h - BANDEAU) / game_height(env->g);  // delimitation of the blindfold
                                            // and the height of the game
  rect.w = w;                               // Case width
  rect.h = h;                               // Case height
  rect.x = 0;
  rect.y = BANDEAU;
  /** Init course of the game and graphic formatting **/

  for (uint b = 0; b < game_height(env->g); b++) {
    for (uint a = 0; a < game_width(env->g); a++) {
      c = game_cell_current_color(env->g, a, b);

      SDL_SetRenderDrawColor(ren, env->colors[c].r, env->colors[c].g,
                             env->colors[c].b, env->colors[c].a);

      SDL_RenderFillRect(ren, &rect);
      rect.x = rect.x + w;
      rect.w = rect.w + w;
    }
    rect.x = 0;
    rect.y = rect.y + h;
    rect.h = rect.h + h;
  }

  /** Delimitation of Boxes **/
  // Vertical
  uint x = 0;
  for (uint a = 0; a < game_width(env->g); a++) {
    SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
    SDL_RenderDrawLine(ren, x, BANDEAU, x, h_windows);
    x = x + w;
  }
  // Horizontal
  uint y = BANDEAU;
  for (uint b = 0; b < game_height(env->g); b++) {
    SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
    SDL_RenderDrawLine(ren, 0, y, w_windows, y);
    y = y + h;
  }

  // init texture using Arial and change mvmt

  char move[50];
  SDL_Color col = {0, 0, 0, 0};  // black color in RGBA
  TTF_Font *font = TTF_OpenFont(FONT, FONTSIZE);
  if (!font) {
    ERROR("TTF_OpenFont: %s\n", FONT);
  }
  TTF_SetFontStyle(font,
                   TTF_STYLE_NORMAL);  // or TTF_STYLE_BOLD | TTF_STYLE_ITALIC

  // print nb_move with diferent conditions
  if (game_nb_moves_cur(env->g) > game_nb_moves_max(env->g)) {
    sprintf(move, "DOMAGE => Nb moves curr : %u / Nb moves max : %u",
            game_nb_moves_cur(env->g), game_nb_moves_max(env->g));
    TTF_SetFontStyle(font, TTF_STYLE_ITALIC | TTF_STYLE_UNDERLINE);
    col = env->colors[4];

  } else if (game_is_over(env->g)) {
    sprintf(move, "BRAVO => Win in : %u", game_nb_moves_cur(env->g));
    font = TTF_OpenFont(FONT, rand() % (20 - 10) + 10);
    TTF_SetFontStyle(font, TTF_STYLE_BOLD | TTF_STYLE_UNDERLINE);
    col = env->colors[rand() % 16];
  } else {
    sprintf(move, "Nb moves curr : %u / Nb moves max : %u",
            game_nb_moves_cur(env->g), game_nb_moves_max(env->g));
  }
  SDL_Surface *surf = TTF_RenderText_Blended(font, move, col);
  env->text = SDL_CreateTextureFromSurface(ren, surf);
  SDL_FreeSurface(surf);

  SDL_QueryTexture(env->text, NULL, NULL, &rect.w, &rect.h);
  // position  of score
  rect.x = w_windows / 3;
  rect.y = BANDEAU / 2;

  SDL_RenderCopy(ren, env->text, NULL, &rect);
  TTF_CloseFont(font);


  //render the Buttons
 //init Button

SDL_Rect rect_2;
rect_2.x =5; 
rect_2.y=5;
rect_2.w=30;
rect_2.h=16;
SDL_SetRenderDrawColor(ren, rand()%255,rand()%255 ,rand()%255 , 0);
SDL_RenderFillRect(ren, &rect_2);
SDL_QueryTexture(env->Button_Quit, NULL, NULL, &rect.w, &rect.h);
rect.x = (rect_2.x / 2 - rect_2.w / 2+18) ;
rect.y = (rect_2.y / 2 - rect_2.h / 2 +13);
SDL_RenderCopy(ren, env->Button_Quit, NULL, &rect);




rect_2.x =38; 
rect_2.y=5;
rect_2.w=58;
rect_2.h=16;
SDL_SetRenderDrawColor(ren, rand()%255,rand()%255 ,rand()%255 ,0);
SDL_RenderFillRect(ren, &rect_2);
SDL_QueryTexture(env->Button_Restart, NULL, NULL, &rect.w, &rect.h);
rect.x = (rect_2.x / 2 - rect_2.w / 2+50) ;
rect.y = (rect_2.y / 2 - rect_2.h / 2 +13);
SDL_RenderCopy(ren, env->Button_Restart, NULL, &rect);



rect_2.x =100; 
rect_2.y=5;
rect_2.w=30;
rect_2.h=16;
SDL_SetRenderDrawColor(ren,rand()%255,rand()%255 ,rand()%255 , 0);
SDL_RenderFillRect(ren, &rect_2);
SDL_QueryTexture(env->Button_new, NULL, NULL, &rect.w, &rect.h);
rect.x = (rect_2.x / 2 - rect_2.w / 2+65) ;
rect.y = (rect_2.y / 2 - rect_2.h / 2 +13);
SDL_RenderCopy(ren, env->Button_new, NULL, &rect);

rect_2.x =140; 
rect_2.y=5;
rect_2.w=45;
rect_2.h=16;
SDL_SetRenderDrawColor(ren,rand()%255,rand()%255 ,rand()%255 , 0);
SDL_RenderFillRect(ren, &rect_2);
SDL_QueryTexture(env->level, NULL, NULL, &rect.w, &rect.h);
rect.x = (rect_2.x / 2 - rect_2.w / 2+95) ;
rect.y = (rect_2.y / 2 - rect_2.h / 2 +13);
SDL_RenderCopy(ren, env->level, NULL, &rect);

}



/* **************************************************************** */

bool process(SDL_Window *win, SDL_Renderer *ren, Env *env, SDL_Event *e) {
  int w, h;
  // get current windows size
  SDL_GetWindowSize(win, &w, &h);
  // generic events

  if (e->type == SDL_QUIT) {
    return true;
  }


  // events with mouse
  else if (e->type == SDL_MOUSEBUTTONDOWN) {
    SDL_Point mouse;
    SDL_GetMouseState(&mouse.x, &mouse.y);
    if (game_is_over(env->g) == false) {

     
      w = w / game_width(env->g);
      h = (h - BANDEAU) / game_height(env->g);
      uint x = (mouse.x) / w;  // case width
      if (mouse.y > BANDEAU + 18) {
        uint y = (mouse.y - BANDEAU) / h;  // case height
        if (x < game_width(env->g) && y < game_height(env->g)) {
          color c = game_cell_current_color(env->g, x, y);
          game_play_one_move(env->g, c);
        }
      }
    }// click to restart or quit
      if ((mouse.x <= 100)&&(mouse.x >38) &&(mouse.y <BANDEAU) ){
        game_restart(env->g);
      } if ((mouse.x <=35)&&(mouse.x>=5) &&(mouse.y <BANDEAU)){
        if (env->argc == 2) {
          game_save(env->g, env->argv[1]);  // save the game
        }
        if (env->argc == 6 || env->argc == 5 || env->argc == 4) {
          game_save(env->g, "recolor_v2.rec");  // save game with v2
        }
        if (env->argc != 2 && env->argc != 6 && env->argc != 5 &&
            env->argc != 4) {
          game_save(env->g, "recolor_v1.rec");  // save game with v1
        }
        return true;
      }
      if ((mouse.y<BANDEAU)&&(mouse.x<=130)&&(mouse.x>=103)){
        uint c =rand()%15+ 2;
        env->g =game_random_ext(game_width(env->g),game_height(env->g),game_is_wrapping(env->g),c,game_nb_moves_max(env->g));
        
        
      }
      if((mouse.y<BANDEAU)&&(mouse.x<=185)&&(mouse.x>=140)){
        uint c =rand()%15+ 2;
        uint w=rand()% 20+2;
        uint h=rand()% 20+2;
        uint nb_max=rand()% 120+2;
        env->g =game_random_ext(w,h,game_is_wrapping(env->g),c,nb_max);

      }

    

    // event with key
  } else if (e->type == SDL_KEYDOWN) {
    switch (e->key.keysym.sym) {
      case SDLK_r:
        game_restart(env->g);
        break;
      case SDLK_q:
        // save the game
        if (env->argc == 2) {
          game_save(env->g, env->argv[1]);  // save the game
        }
        if (env->argc == 6 || env->argc == 5 || env->argc == 4) {
          game_save(env->g, "recolor_v2.rec");  // save game with v2
        }
        if (env->argc != 2 && env->argc != 6 && env->argc != 5 &&
            env->argc != 4) {
          game_save(env->g, "recolor_v1.rec");  // save game with v1
        }
      case SDLK_ESCAPE:
        return true;
        break;
    }
  }

  return false;
}

/* **************************************************************** */
void clean(SDL_Window *win, SDL_Renderer *ren, Env *env) {
  /* CODE TO CLEAN MEMORY */
  free(env->colors);
  game_delete(env->g);
  SDL_DestroyTexture(env->text);
  SDL_DestroyTexture(env->Button_Quit);
  SDL_DestroyTexture(env->Button_Restart);
  SDL_DestroyTexture(env->Button_new);
  free(env);
}
/* **************************************************************** */