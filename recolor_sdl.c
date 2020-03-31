#include <SDL.h>
#include <SDL_image.h>  // required to load transparent texture from PNG
#include <SDL_ttf.h>    // required to use TTF fonts     

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "recolor_sdl.h"
#include "time.h"
#include "game.h"
#include "game_io.h"

/* **************************************************************** */
#define FONT "Calibri.ttf"
#define FONTSIZE 12
#define BANDEAU 20
//typedef uint color;

/* **************************************************************** */

     
struct Env_t {  

  /* PUT YOUR VARIABLES HERE */
  game g ;
  SDL_Color *colors;
  SDL_Texture *text;
  




}; 
     
/* **************************************************************** */
     
Env * init(SDL_Window* win, SDL_Renderer* ren, int argc, char* argv[]){

  Env * env = malloc(sizeof(struct Env_t));
  PRINT("Move a cell with  mouse.\n");
  PRINT("Press 'q' if you want to stop the game and to save or press 'r' to restart the game !\n");
  PRINT("Good luck.\n");


    /* Init colors */
  env->colors=malloc(16*sizeof(SDL_Color));
  env->colors[0]= (SDL_Color){255,0,0,0};//red
  env->colors[1]= (SDL_Color){0,255,0,0};//green
  env->colors[2]= (SDL_Color){0,0,255,0};//blue
  env->colors[3]= (SDL_Color){255,255,0,0};//yellow
  env->colors[4]= (SDL_Color){255,165,0,0};//orange
  env->colors[5]= (SDL_Color){238,130,238,0};//violet
  env->colors[6]= (SDL_Color){255,192,203,0};//pink
  env->colors[7]= (SDL_Color){128,128,128,0};//grey
  env->colors[8]= (SDL_Color){0,255,255,0};//cyan
  env->colors[9]= (SDL_Color){139,69,19,0};//brown
  env->colors[10]= (SDL_Color){128,0,0,0};//bordeaux red
  env->colors[11]= (SDL_Color){0,0,0,0};//black
  env->colors[12]= (SDL_Color){255,255,255,0};//white or 
  env->colors[13]= (SDL_Color){245,245,220,0};//beige
  env->colors[14]= (SDL_Color){0,100,0,0};//dark green
  env->colors[15]= (SDL_Color){210,105,30,0};//chocolate
  
  
  /* init text using arial font */
 // SDL_Color color = {0,0,255,255};
  /*TTF_Font *font = TTF_OpenFont(FONT,FONTSIZE);
  if(!font){
    ERROR("TTF_OpenFont: %s\n",FONT);
  }
  TTF_SetFontStyle(font,TTF_STYLE_NORMAL);
  //SDL_Surface * surf = TTF_RenderText_Blended(font,"Recolor",color);
  //env->text = SDL_CreateTextureFromSurface(ren, surf);
  //SDL_FreeSurface(surf);
  TTF_CloseFont(font);
   
  //init game  que l'on mettra en argument */
    // with argument
  
  
  if(argc !=2 && argc != 5){
   color cells[144] = {
      0, 0, 0, 2, 0, 2, 1, 0, 1, 0, 3, 0, 0, 3, 3, 1, 1, 1, 1, 3, 2, 0, 1, 0,
      1, 0, 1, 2, 3, 2, 3, 2, 0, 3, 3, 2, 2, 3, 1, 0, 3, 2, 1, 1, 1, 2, 2, 0,
      2, 1, 2, 3, 3, 3, 3, 2, 0, 1, 0, 0, 0, 3, 3, 0, 1, 1, 2, 3, 3, 2, 1, 3,
      1, 1, 2, 2, 2, 0, 0, 1, 3, 1, 1, 2, 1, 3, 1, 3, 1, 0, 1, 0, 1, 3, 3, 3,
      0, 3, 0, 1, 0, 0, 2, 1, 1, 1, 3, 0, 1, 3, 1, 0, 0, 0, 3, 2, 3, 1, 0, 0,
      1, 3, 3, 1, 1, 2, 2, 3, 2, 0, 0, 2, 2, 0, 2, 3, 0, 1, 1, 1, 2, 3, 0, 1};
    env->g = game_new(cells, 12);


 }else if (argc == 2){
    env->g = game_load(argv[1]);
  }else{
    bool state=atoi(argv[1]);  // wrapping
    int h= atoi(argv[2]);       // height
    int w= atoi(argv[3]);       // width
    int nb= atoi(argv[4]);      // nb_colors

    color * cells = malloc((w * h) * sizeof(color));
    if (cells == NULL) {
      fprintf(stderr, "Problem allocation memory\n");
      exit(EXIT_FAILURE);
    }
    
    srand(time(NULL));  // initialisation de rand
    //color cells[w*h];
    for (uint i = 0; i < w * h; i++) {
    cells[i] = rand() % nb;  // On remplit un tableau de couleur de taille
                               // largeur * hauteur avec des couleurs aléatoires
    env->g = game_new_ext(w, h, cells, 12, state);
    }
 }

  /* init text texture using Arial font */
  SDL_Color color = { 0, 0, 0, 0 }; /* blue color in RGBA */
  TTF_Font * font = TTF_OpenFont(FONT, FONTSIZE);
  if(!font) ERROR("TTF_OpenFont: %s\n", FONT);
  TTF_SetFontStyle(font, TTF_STYLE_BOLD); // TTF_STYLE_ITALIC | TTF_STYLE_NORMAL
  SDL_Surface * surf = TTF_RenderText_Blended(font, "Hello World", color); // blended rendering for ultra nice text
  env->text = SDL_CreateTextureFromSurface(ren, surf);
  SDL_FreeSurface(surf);
  TTF_CloseFont(font);
    

  return env;
}
     
/* **************************************************************** */
     
void render(SDL_Window* win, SDL_Renderer* ren, Env * env)
{ 
  SDL_Rect rect;
  int w,h;
  uint c;
  SDL_GetWindowSize(win, &w, &h);
  uint h_windows = h;
  uint w_windows = w;
  w = w/game_width(env->g);
  h = (h-(h/BANDEAU))/game_height(env->g); //delimitation of the blindfold and the height of the game
  rect.w = w; //Case width
  rect.h = h; //Case height
  rect.x = 0;
  rect.y = h_windows/BANDEAU;
  /** Course of the game and graphic formatting **/
  for (uint b=0; b<game_height(env->g); b++){
    for (uint a=0; a<game_width(env->g); a++){
      c=game_cell_current_color(env->g, a, b);
      //SDL_Color color =  env->colors[c];
      SDL_SetRenderDrawColor(ren, env->colors[c].r, env->colors[c].g, env->colors[c].b, env->colors[c].a);
      //SDL_SetRenderDrawColor(ren,255,0,0,255);
      SDL_RenderFillRect(ren, &rect);
      rect.x = rect.x + w;
      rect.w = rect.w + w;
    }
    rect.x = 0;
    rect.y = rect.y + h;
    rect.h = rect.h + h;
  }
  /*rect.x=0;
  rect.y = h*game_height(env->g);
  rect.w= w*game_width(env->g);
  rect.h= h;
  SDL_SetRenderDrawColor(ren, 128, 128, 128, 0);
  SDL_RenderFillRect(ren, &rect);*/
  
  /** Delimitation of Boxes **/
  //Vertical
  uint x = 0;
  for (uint a=0; a<game_width(env->g); a++){
    SDL_SetRenderDrawColor(ren,0,0,0,255);
    SDL_RenderDrawLine(ren,x,h_windows/BANDEAU,x,h_windows);
    x = x + w; 
  }
  //Horizontal
  uint y = h_windows/BANDEAU;
  for (uint b=0; b<game_height(env->g); b++){
    SDL_SetRenderDrawColor(ren,0,0,0,255);
    SDL_RenderDrawLine(ren,0,y,w_windows,y);
    y = y + h; 
  }

  /*char move[60];
  //char * move = malloc(60*sizeof(char));
  SDL_Color col ={0,0,0,0};
  fprintf(move,"%u / %u",game_nb_moves_cur(env->g),game_nb_moves_max(env->g));
  if (game_nb_moves_cur(env->g) > game_nb_moves_max(env->g)){
    fprintf(move,"DOMAGE => %u / %u",game_nb_moves_cur(env->g),game_nb_moves_max(env->g));
  }else if (game_is_over(env->g)){
    fprintf(move,"BRAVO");
  }
  SDL_Surface *surf = TTF_RenderText_Blended(env->g,move,col);
  env->text= SDL_CreateTextureFromSurface(ren,surf);
  SDL_FreeSurface(surf);
  SDL_Rect pos;
  pos.x=2*w;
  pos.y=BANDEAU/2; //+h *game_height(env->g);
  free(move);*/

  /* render text texture */
  rect.w=4*rect.w;
  rect.h=4*rect.h;
  SDL_QueryTexture(env->text, NULL, NULL, &rect.w, &rect.h);
  rect.x = 3*w;
  rect.y = BANDEAU/2; 
  SDL_RenderCopy(ren, env->text, NULL, &rect);


  /* PUT YOUR CODE HERE TO RENDER TEXTURES, ... */
}
     
/* **************************************************************** */
     
     
bool process(SDL_Window* win, SDL_Renderer* ren, Env * env, SDL_Event * e)
{

  int w,h;
  SDL_GetWindowSize(win, &w, &h);

  if (e->type == SDL_QUIT) {
    return true;
  }
  else if (e->type == SDL_MOUSEBUTTONDOWN){
     SDL_Point mouse;
     SDL_GetMouseState(&mouse.x, &mouse.y);
      w = w/game_width(env->g);
      h = (h-BANDEAU)/game_height(env->g);
      uint x = (mouse.x- BANDEAU )/w;
      uint y = (mouse.y - 3*BANDEAU)/h;
      color c = game_cell_current_color(env->g,x,y);
      if (x< game_width(env->g) && y < game_height(env->g)){ // sinon affiche "probleme size"
        game_play_one_move(env->g,c);
      }
      

  }else if (e->type == SDL_KEYDOWN){
    switch (e->key.keysym.sym){
      case SDLK_r: game_restart(env->g); break;
      case SDLK_q:
      case SDLK_ESCAPE: return true; break;
    }
  }
  /* PUT YOUR CODE HERE TO PROCESS EVENTS */
  
  return false; 
}

/* **************************************************************** */

void clean(SDL_Window* win, SDL_Renderer* ren, Env * env)
{
  /* PUT YOUR CODE HERE TO CLEAN MEMORY */
  free(env->colors);
  game_delete(env->g);
  SDL_DestroyTexture(env->text);
  free(env);
}
     
/* **************************************************************** */
