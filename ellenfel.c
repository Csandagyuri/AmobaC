#include "ellenfel.h"
#include "allas.h"
#include "debugmalloc.h"



bool ellenfel( int nehezseg,int n_szama,int n_meret,int **jatek_matrix, int *aktualis, SDL_Renderer * renderer){
    int ahossz = 2;
    int i=0;
    int kozepso = n_szama/2;
    bool rakott = false;
    ListaElem *potencialis = NULL;
    if (nehezseg == 1 && !rakott && leghosszabb(ahossz, &potencialis, jatek_matrix,n_szama)){
        ListaElem *l = potencialis;
        while ( l != NULL && !rakott){
            int x = l->eleje.x;
            int y = l->eleje.y;
            int i = l->vege.x;
            int j = l->vege.y;
            int hossz = l->hossz;
                if (x-i < n_szama && x-i >= 0 && y-j < n_szama && y-j >= 0 && jatek_matrix[x-i][y-j] == 8){
                    alak_rajzol((x-i)*n_meret, (y-j)*n_meret,n_meret,*aktualis,renderer);
                    jatek_matrix[x-i][y-j] = *aktualis;
                    rakott = true;
                }
                else if(x+i*hossz+i < n_szama && x+i*hossz+i >= 0 && y+j*hossz+j < n_szama && y+j*hossz+j >= 0 && jatek_matrix[x+i*hossz+i][y+j*hossz+j] == 8){
                    alak_rajzol((x+i*hossz+i)*n_meret,(y+j*hossz+j)*n_meret, n_meret, *aktualis, renderer);
                    jatek_matrix[x+i*hossz+i][y+j*hossz+j] = *aktualis;
                    rakott = true;
                }
            l = l->kov;
        }
    }
    lista_torol(&potencialis);

    while(!rakott && i+kozepso < n_szama){
        if (!rakott && jatek_matrix[kozepso+i][kozepso+i] == 8){
            alak_rajzol((kozepso+i)*n_meret,(kozepso+i)*n_meret,n_meret,*aktualis,renderer);
            jatek_matrix[kozepso+i][kozepso+i] = *aktualis;
            rakott = true;
        }
        i++;
    }

    while(!rakott){
        int x = rand()%n_szama;
        int y = rand()%n_szama;
        if (jatek_matrix[x][y] == 8){
            alak_rajzol(x*n_meret,y*n_meret, n_meret, *aktualis, renderer);
            jatek_matrix[x][y] = *aktualis;
            rakott = true;
        }
    }


    *aktualis = (*aktualis+1)%2;
    SDL_RenderPresent(renderer);
    return true;
}



