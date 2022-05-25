#ifndef JELENITO_H_INCLUDED
#define JELENITO_H_INCLUDED
#include <SDL2/SDL_ttf.h>
#include <windows.h>
#include "struct.h"

#include "allas.h"


void sdl_init(char const *felirat, int szeles, int magas, SDL_Window **pwindow, SDL_Renderer **prenderer);
void sdl_close(SDL_Window **pwindow, SDL_Renderer **prenderer, TTF_Font **pfont);
void palya_kirajzolasa (int n_szam, int a_meret, int aktualis, SDL_Renderer * renderer);
void alak_rajzol (int x, int y, int n_meret, int alak, SDL_Renderer * renderer);
void rajzolo (int n_szama, int n_meret, int ** jatek_matrix, int *aktualis, SDL_Renderer * renderer);
void athuzas (ListaElem *vonal, int n_meret, SDL_Renderer * renderer);
void szoveg_RGBA(SDL_Renderer * renderer ,int hova_x ,int hova_y , char * mit, int r, int b, int g, int meret);
void felugroablak(SDL_Renderer *felugro, int eredmeny, int *tovabbi_utasitas);

#endif // JELENITO_H_INCLUDED
