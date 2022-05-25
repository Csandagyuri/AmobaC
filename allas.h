#ifndef ALLAS_H_INCLUDED
#define ALLAS_H_INCLUDED
#include <stdbool.h>
#include "struct.h"
#include "Jelenito.h"

int ** matrix (int db, int *hosszu_tombpointer);
bool nyert(int **jatek_allas, int p_meret, SDL_Renderer * renderer);
bool leghosszabb( int nyero , ListaElem **vonal , int **jatek_allas, int p_meret);
bool dontetlen (int **jatek_allas, int p_meret);
void Lista_beszuras(ListaElem **elso, int x, int y, int a, int b, int hossz);
void fajlba_mentes(int n_szama,int n_meret,int nyeresi,int nehezseg,int aktualis,int tovabbi_utasit,int **jatek_matrix);
int **fajlbol_beolv(int *negyzetek_szama, int *negyzet_meret, int *nyeres_feltetel, int *nehezseg, int *aktualis, int *tovabbi_utasit);
void lista_torol (ListaElem **elso);


#endif // ALLAS_H_INCLUDED
