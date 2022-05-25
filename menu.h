#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include "struct.h"
#include <stdbool.h>
#include <stdio.h>

void menu_app (SDL_Renderer *menu,int *menu_pont);
void tulajdonsagok_app_nyeres(SDL_Renderer * tulajdonsagok, int *nyereshez);
void sugo_ablak(SDL_Renderer *menu);
void tulajdonsagok_app_diff(SDL_Renderer * tulajdonsagok, int *nehezseg);
void tulajdonsagok_app_meret(SDL_Renderer * tulajdonsagok, int *n_szama);
void tulajdonsagok_app_kezd(SDL_Renderer * tulajdonsagok, int *alakom);
#endif // MENU_H_INCLUDED
