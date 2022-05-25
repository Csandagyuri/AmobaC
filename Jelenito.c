#include "jelenito.h"
#include "menu.h"
#include "debugmalloc.h"
#include "bemenet.h"
/* létrehozza az ablakot */
void sdl_init(char const *felirat, int szeles, int magas, SDL_Window **pwindow, SDL_Renderer **prenderer) {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        SDL_Log("Nem indithato az SDL: %s", SDL_GetError());
        exit(1);
    }
    SDL_Window *window = SDL_CreateWindow(felirat, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, szeles, magas, 0);
    if (window == NULL) {
        SDL_Log("Nem hozhato letre az ablak: %s", SDL_GetError());
        exit(1);
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (renderer == NULL) {
        SDL_Log("Nem hozhato letre a megjelenito: %s", SDL_GetError());
        exit(1);
    }
    SDL_RenderClear(renderer);

    *pwindow = window;
    *prenderer = renderer;
}


void sdl_close(SDL_Window **pwindow, SDL_Renderer **prenderer, TTF_Font **pfont) {
    SDL_DestroyRenderer(*prenderer);
    *prenderer = NULL;

    SDL_DestroyWindow(*pwindow);
    *pwindow = NULL;

    TTF_CloseFont(*pfont);
    *pfont = NULL;

    SDL_Quit();
}


/* négyzet hálókká alakítja a játékteret */
void palya_kirajzolasa (int n_szam, int a_meret, int aktualis, SDL_Renderer * renderer ){
    int n_meret = a_meret / n_szam;
    boxRGBA(renderer, 0, 0, a_meret, a_meret, 255, 255, 255, 255 );
    for (int i = 0; i < n_szam; i++){
        lineRGBA(renderer, i*n_meret , 0, i*n_meret, a_meret, 170, 170, 170, 170);
    }
    for (int i = 0; i < n_szam; i++){
        lineRGBA(renderer, 0, i*n_meret, a_meret, i*n_meret, 170, 170, 170, 170);
    }
    boxRGBA(renderer,0, a_meret, a_meret, a_meret+80, 150,0,100,155);
    thickLineRGBA(renderer, 0, a_meret+5, a_meret, a_meret+5,10, 0,0, 0, 255);
    boxRGBA(renderer, 0, a_meret, n_meret/2, a_meret+n_meret/2, 255, 255, 255, 255);
    alak_rajzol(0, a_meret+35 , n_meret/2, aktualis, renderer);
    boxRGBA(renderer, a_meret*0.2, a_meret+20, a_meret*0.8, a_meret+60, 55, 175, 115, 255);
    szoveg_RGBA(renderer,a_meret*0.5, a_meret+40 ,"Kilépés és mentés", 255,255,255, 25);
}


void alak_rajzol (int x, int y, int n_meret,  int alak,SDL_Renderer * renderer){
    int kerekitett_x = x / n_meret * n_meret;
    int kerekitett_y = y / n_meret * n_meret;
    if (alak == 1){
    thickLineRGBA(renderer, kerekitett_x+n_meret*0.1, kerekitett_y+n_meret*0.1, kerekitett_x+n_meret*0.9, kerekitett_y+n_meret*0.9, n_meret/10, 200, 000, 200, 255);
    thickLineRGBA(renderer, kerekitett_x+n_meret*0.1, kerekitett_y+n_meret*0.9, kerekitett_x+n_meret*0.9, kerekitett_y+n_meret*0.1, n_meret/10, 000, 200, 200, 255);
    }
    if (alak == 0){
    filledCircleRGBA(renderer, kerekitett_x+n_meret/2, kerekitett_y+n_meret/2, n_meret/2*0.88, 195, 207, 235, 255);
    filledCircleRGBA(renderer, kerekitett_x+n_meret/2, kerekitett_y+n_meret/2, n_meret/2*0.72, 255, 255, 255, 255);
    }
    SDL_RenderPresent(renderer);
}

/* Az egérrõl kapott koordináta szerint rajzol */



void athuzas (ListaElem *vonal, int n_meret, SDL_Renderer * renderer){
    while (vonal != NULL){
        thickLineRGBA(renderer, (vonal->eleje.x+0.5)*n_meret, (vonal->eleje.y+0.5)*n_meret, (vonal->vege.x*vonal->hossz+vonal->eleje.x+0.5)*n_meret, (vonal->vege.y*vonal->hossz+vonal->eleje.y+0.5)*n_meret, 5, 55, 55, 55, 255);
        vonal = vonal->kov;
    }
    SDL_RenderPresent(renderer);
}


void szoveg_RGBA(SDL_Renderer * renderer ,int hova_x ,int hova_y , char * mit, int r, int b, int g, int meret){
    TTF_Init();
    TTF_Font *font = TTF_OpenFont("LiberationSerif-Regular.ttf", meret);
    if (!font) {
        SDL_Log("Nem sikerult megnyitni a fontot! %s\n", TTF_GetError());
        exit(1);
    }
    /* felirat megrajzolasa, kulonfele verziokban */
    SDL_Surface *felirat;
    SDL_Texture *felirat_t;
    SDL_Rect hova = { 0, 0, 0, 0 };
    SDL_Color szin = {r, b, g};

    felirat = TTF_RenderUTF8_Blended(font, mit, szin);
    felirat_t = SDL_CreateTextureFromSurface(renderer, felirat);
    hova.x = (hova_x-(felirat->w)/2);
    hova.y = (hova_y-(felirat->h)/2);
    hova.w = felirat->w;
    hova.h = felirat->h;
    SDL_RenderCopy(renderer, felirat_t, NULL, &hova);
    SDL_FreeSurface(felirat);
    SDL_DestroyTexture(felirat_t);
    TTF_CloseFont(font);
}


void felugroablak(SDL_Renderer *felugro, int eredmeny, int *tovabbi_utasitas){
    boxRGBA(felugro, 0, 0, 600, 400, 54, 154, 200, 255);
    if (eredmeny == 1)  szoveg_RGBA(felugro,600/2, 70 ,"Nyertél!!!", 255,255,255, 60);
    if (eredmeny == -1) szoveg_RGBA(felugro,600/2, 70 ,"Nem nyertél", 255,255,255, 60);
    if (eredmeny == 0)  szoveg_RGBA(felugro,600/2, 70 ,"Döntetlen", 255,255,255, 60);
    boxRGBA(felugro, 30, 150, 570, 210, 255, 154, 200, 255);
    szoveg_RGBA(felugro,600/2,(150+210)/2,"Újra ugyanígy", 255,255,255, 40);
    boxRGBA(felugro, 30, 300, 570, 360, 255, 154, 200, 255);
    szoveg_RGBA(felugro,600/2,(300+360)/2,"Menübe", 255,255,255, 40);
    SDL_RenderPresent(felugro);
    bool quit = false;
    while (!quit) {
        int x;
        int y;
        eger_koordinata( &x, &y, &quit);
        if (x >= 30 && x <= 570){                                           ///////////////////////////////////
            if (y > 150 && y < 210){
                *tovabbi_utasitas = 0;
                quit = true;
                SDL_Quit();                                               //
                break;
            }
            if (y > 300 && y < 360){
                *tovabbi_utasitas = 1;
                SDL_Quit();
                quit=true;

                break;

            }
        }
    }
}



