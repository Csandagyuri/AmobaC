#include "jelenito.h"
#include "allas.h"
#include <stdio.h>
#include "struct.h"
#include "debugmalloc.h"

void jatekmenet (int n_szama, int n_meret, int nyeresi, int nehezseg, int ** jatek_matrix, int aktualis, SDL_Renderer * renderer, int *tovabbi_utasit){
    SDL_RenderPresent(renderer);
    ListaElem *nyero = NULL;
    bool quit = false;
    while (!quit) {
        int x;
        int y;
        eger_koordinata(&x, &y, &quit);
        if (x > (n_szama*n_meret*0.2) && x <(n_szama*n_meret*0.8) && y > n_szama*n_meret+20 && y< n_szama*n_meret+60){
            fajlba_mentes(n_szama, n_meret, nyeresi, nehezseg, aktualis, *tovabbi_utasit, jatek_matrix);
            quit = true;
            *tovabbi_utasit = 1;
            SDL_Quit();
        }
        bool rajzolt = true;
        if (jatek_matrix[x/n_meret][y/n_meret] == 8 && y <= n_meret*n_szama)
            rajzolt = false;
        while ( rajzolt == false){
                //mátrixba
                jatek_matrix[x / n_meret][y / n_meret] = aktualis;
                //képernyőre
                alak_rajzol (x, y, n_meret, aktualis, renderer);


                if (leghosszabb( nyeresi, &nyero, jatek_matrix, n_szama)){
                    athuzas(nyero, n_meret, renderer);
                    SDL_RenderPresent(renderer);
                    Sleep(1000);
                    quit = true;                                                                        //
                    SDL_Window *ablak;                                                                     //
                    SDL_Renderer *felugro;                                                           //
                    sdl_init("Eredmény jelző", 600, 400, &ablak, &felugro);                                   //
                    felugroablak(felugro, 1, &*tovabbi_utasit);                                                      //
                    SDL_RenderPresent(felugro);
                    SDL_Quit();
                }
                aktualis = (aktualis+1)%2;

                rajzolt = true;


                SDL_RenderPresent(renderer);
                if (!quit && dontetlen(jatek_matrix, n_szama)){
                    quit = true;
                    SDL_Event sajt;                                                                        //
                    SDL_Window *ablak;                                                                     //
                    SDL_Renderer *felugro;                                                           //
                    sdl_init("Eredmény jelző", 600, 400, &ablak, &felugro);                                   //
                    felugroablak(felugro,0, &*tovabbi_utasit);                                                      //
                    SDL_RenderPresent(felugro);
                    SDL_Quit();
                }
            Sleep(800);
                if (!quit && nehezseg != 8)
                    ellenfel(nehezseg,n_szama, n_meret, jatek_matrix, &aktualis, renderer);
                if (!quit && leghosszabb( nyeresi, &nyero, jatek_matrix, n_szama)){
                    athuzas(nyero, n_meret, renderer);
                    quit = true;                                                                        //
                    SDL_Window *ablak;                                                                     //
                    SDL_Renderer *felugro;                                                           //
                    sdl_init("Eredmény jelző", 600, 400, &ablak, &felugro);                                   //
                    felugroablak (felugro, -1, &*tovabbi_utasit);                                                      //
                    SDL_RenderPresent(felugro);
                    SDL_Quit();
                }
            lista_torol(&nyero);
        }
    }
}




int main(int argc, char *argv[]) {

    bool kilepes = false;
    while (kilepes == false){
    /* ablak létrehozása */
    int ablak_meret = 0;
    int negyzetek_szama = 1;
    int negyzet_meret = ablak_meret/ negyzetek_szama;
    int nyeres_feltetel = 0;
    int nehezseg;
    int kezdoalak=8;
    int tovabbi_utasit = 0;
    int matrix_hosszu[negyzetek_szama];
    int **jatek_matrix;

    Alakzat aktualis = iksz;
    SDL_Window *ablak;
    SDL_Renderer *renderer;
    SDL_Renderer *menu;
    sdl_init("Menu", 600, 800, &ablak, &renderer);
    int menu_pont = 0;
    menu_app(renderer, &menu_pont);
    if (menu_pont == 1){
        sdl_init("Beállítások", 300, 200, &ablak, &renderer);                                   //
        tulajdonsagok_app_nyeres (renderer, &nyeres_feltetel);
        if (nyeres_feltetel == 3) {
           negyzet_meret = 100;
           negyzetek_szama = 3;
        }
        if (nyeres_feltetel == 5){
            SDL_Window *window;
            SDL_Renderer *tulajdonsagok;
            tulajdonsagok_app_meret(tulajdonsagok, &negyzetek_szama);
            if (negyzetek_szama < 10) negyzet_meret = 100;
            if (negyzetek_szama >= 10) negyzet_meret = 900/negyzetek_szama;

        }
        tulajdonsagok_app_diff(renderer, &nehezseg);
        tulajdonsagok_app_kezd( renderer, &aktualis);
        ablak_meret = negyzetek_szama*negyzet_meret;
        SDL_Quit();

            if (menu_pont == 1){

        while (tovabbi_utasit == 0){
            jatek_matrix = matrix(negyzetek_szama, matrix_hosszu);
            sdl_init("Amőba játék", negyzetek_szama*negyzet_meret, negyzetek_szama*negyzet_meret+80, &ablak, &renderer);
            palya_kirajzolasa(negyzetek_szama,negyzetek_szama*negyzet_meret, aktualis, renderer);


            SDL_Event ev;

            jatekmenet( negyzetek_szama, negyzet_meret, nyeres_feltetel, nehezseg, jatek_matrix, aktualis, renderer, &tovabbi_utasit);


            while (SDL_WaitEvent(&ev) && ev.type != SDL_QUIT) {                                //
                /* SDL_RenderPresent(renderer); - MacOS Mojave esetén */                               /////////////////////////////////
            }

            SDL_Quit();
            free(jatek_matrix[0]);
            free(jatek_matrix);
        }
    }
    }
    if (menu_pont == 2){
        jatek_matrix = fajlbol_beolv(&negyzetek_szama, &negyzet_meret, &nyeres_feltetel, &nehezseg, &aktualis, &tovabbi_utasit);
        //printf("%d %d %d %d %d %d", negyzetek_szama, negyzet_meret, nyeres_feltetel, nehezseg, aktualis, tovabbi_utasit);

        sdl_init("Amőba játék", negyzetek_szama*negyzet_meret, negyzetek_szama*negyzet_meret+80, &ablak, &renderer);
        palya_kirajzolasa(negyzetek_szama,negyzetek_szama*negyzet_meret, aktualis, renderer);
        for (int i = 0; i < negyzetek_szama; i++){
            for (int j = 0; j < negyzetek_szama; j++){
                if (jatek_matrix[i][j] != 8){
                    alak_rajzol(i*negyzet_meret,j*negyzet_meret, negyzet_meret, jatek_matrix[i][j], renderer);
                }
            }
        }

        SDL_Event ev;
        jatekmenet( negyzetek_szama, negyzet_meret, nyeres_feltetel, nehezseg, jatek_matrix, aktualis, renderer, &tovabbi_utasit);
        if (tovabbi_utasit == 0) menu_pont = 1;


        while (SDL_WaitEvent(&ev) && ev.type != SDL_QUIT) {                                //
            /* SDL_RenderPresent(renderer); - MacOS Mojave esetén */                               /////////////////////////////////
        }

        SDL_Quit();
        free(jatek_matrix[0]);
        free(jatek_matrix);
    }

    if (menu_pont == 3){
        sugo_ablak(renderer);
    }


    if (menu_pont == 4)
        kilepes = true;
}

    return 0;
}
