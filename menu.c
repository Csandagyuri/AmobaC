#include "menu.h"
#include "Jelenito.h"
#include "debugmalloc.h"


void menu_app (SDL_Renderer *menu,int *menu_pont){
    bool quit = false;
    while (!quit) {
        boxRGBA(menu, 0, 0, 600, 800, 253, 244, 248, 255 );
        boxRGBA(menu, 125, 100, 475, 200, 153, 144, 248, 255 );         // új játék
        szoveg_RGBA(menu,(125+475)/2,(100+200)/2,"Új játék",255,255,255,50);
        boxRGBA(menu, 125, 250, 475, 350, 253, 244, 100, 255 );         // játék folytatás
        szoveg_RGBA(menu,(125+475)/2,(250+350)/2,"Folytatás",255,255,255,50);
        boxRGBA(menu, 125, 400, 475, 500, 253, 144, 248, 255 );         // sugó
        szoveg_RGBA(menu,(125+475)/2,(400+500)/2,"Segítség",255,255,255,50);
        boxRGBA(menu, 125, 550, 475, 650, 253, 100, 248, 255 );         // kilépés
        szoveg_RGBA(menu,(125+475)/2,(550+650)/2,"Kilépés",255,255,255,50);
        SDL_RenderPresent(menu);
        SDL_Event event;
        SDL_WaitEvent(&event);
        switch (event.type){
                           /* eger kattintas */
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    if (event.button.x >= 125 && event.button.x <= 475){
                        if (event.button.y > 100 && event.button.y < 200){
                            *menu_pont = 1;
                            quit = true;
                            SDL_Quit();
                            Sleep(200);
                            break;
                        }
                        if (event.button.y > 250 && event.button.y < 350){
                            *menu_pont = 2;
                            quit = true;
                            SDL_Quit();
                            Sleep(200);
                            break;
                        }
                        if (event.button.y > 400 && event.button.y < 500){
                            *menu_pont = 3;
                            quit = true;
                            Sleep(200);
                            break;

                        }
                        if (event.button.y > 550 && event.button.y < 650){
                            quit = true;
                            *menu_pont = 4;
                            SDL_Quit();
                            break;
                        }
                    }
                }
                break;
            /* ablak bezarasa */
            case SDL_QUIT:
                quit = true;
                break;
        }
    }
}


void tulajdonsagok_app_nyeres(SDL_Renderer * tulajdonsagok, int *nyereshez){
    boxRGBA(tulajdonsagok, 0, 0, 300, 200, 154, 154, 200, 255);
    szoveg_RGBA(tulajdonsagok,300/2,30,"Mennyivel lehessen nyerni?", 255,255,255, 20);
    boxRGBA(tulajdonsagok, 10, 80, 290, 110, 255, 154, 200, 255);
    szoveg_RGBA(tulajdonsagok,300/2,(80+110)/2,"3 hosszúságúval", 255,255,255, 20);
    boxRGBA(tulajdonsagok, 10, 140, 290, 170, 255, 154, 200, 255);
    szoveg_RGBA(tulajdonsagok,300/2,(140+170)/2,"5 hosszúságúval", 255,255,255, 20);
    SDL_RenderPresent(tulajdonsagok);
    bool quit = false;
    while (!quit) {

        SDL_Event event;
        SDL_WaitEvent(&event);
        switch (event.type){
                           /* eger kattintas */
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    if (event.button.x >= 10 && event.button.x <= 190){
                        if (event.button.y > 80 && event.button.y < 110){                                                                                                             ////       Ez az új játék gombra kattintás esete
                            quit = true;

                            *nyereshez = 3;                                                                                                                            //
                            break;
                        }
                        if (event.button.y > 140 && event.button.y < 170){
                            quit=true;
                            *nyereshez = 5;
                            break;
                        }
                    }
                }
                break;
            /* ablak bezarasa */
            case SDL_QUIT:
                quit = true;
                break;
        }
    }
}


void sugo_ablak(SDL_Renderer *menu){
    boxRGBA(menu, 0, 0, 600, 800, 200, 200, 200, 255);
    szoveg_RGBA(menu,600/2,40,"Az amőba pályájája eleinte üres négyzetrácsokból áll. Egy játékos ",      255,255,255, 20);
    szoveg_RGBA(menu,600/2,80," mindig csak X-et vagy csak O-t tud lerakni az üresnégyzetekbe.",      255,255,255, 20);
    szoveg_RGBA(menu,600/2,120,"Mindig az X kezd, ilyenkor ő lerak egy X-et valamelyik négyzetbe.",      255,255,255, 20);
    szoveg_RGBA(menu,600/2,160,"Ezután az O következik, aki ugyanígy lerak egy O-t ",     255,255,255, 20);
    szoveg_RGBA(menu,600/2,200,"valamelyiknégyzetbe, majd az X jön ismét és ígymegy ez tovább,",      255,255,255, 20);
    szoveg_RGBA(menu,600/2,240,"ameddig az előre meghatározott mennyiségű X-et vagy O-t egy sorba, ",255,255,255, 20);
    szoveg_RGBA(menu,600/2,280,"oszlopba vagy átlóba le nem rakott az egyik játékos, ",       255,255,255, 20);
    szoveg_RGBA(menu,600/2,320,"ilyenkor ez a játékos nyer. Illetve ha a meghatározott ",     255,255,255, 20);
    szoveg_RGBA(menu,600/2,360,"méretű pályán nincsen hely, és egyik játékos sem érte el",    255,255,255, 20);
    szoveg_RGBA(menu,600/2,400," a meghatározott hosszúságot a játék döntetlennel zárul.",    255,255,255, 20);
    boxRGBA(menu, (600-80)/2, 440, (600+80)/2, 480, 255, 154, 200, 255);
    szoveg_RGBA(menu,300,(440+480)/2,"OK",    255,255,255, 30);
    SDL_RenderPresent(menu);
    bool quit = false;
    while (!quit) {
        SDL_Event event;
        SDL_WaitEvent(&event);
        switch (event.type){
                           /* eger kattintas */
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    if (event.button.x >= (600-80)/2 && event.button.x <= (600+80)/2){                                           ///////////////////////////////////
                        if (event.button.y > 440 && event.button.y < 480){                                       //                                                                      ////       Ez az új játék gombra kattintás esete
                            SDL_Quit();
                            quit = true;
                            break;
                        }
                    }
                }
                break;
            /* ablak bezarasa */
            case SDL_QUIT:
                quit = true;
                break;
        }
    }
}


void tulajdonsagok_app_diff(SDL_Renderer * tulajdonsagok, int *nehezseg){
    boxRGBA(tulajdonsagok, 0, 0, 300, 200, 104, 104, 0, 255);
    szoveg_RGBA(tulajdonsagok,300/2,30,"Milyen nehézségen szeretnél játszani", 255,255,255, 20);
    boxRGBA(tulajdonsagok, 10, 50, 290, 80, 255, 154, 200, 255);
    szoveg_RGBA(tulajdonsagok,300/2,(50+80)/2,"Könnyű", 255,255,255, 20);
    boxRGBA(tulajdonsagok, 10, 100, 290, 130, 255, 154, 200, 255);
    szoveg_RGBA(tulajdonsagok,300/2,(100+130)/2,"Közepes", 255,255,255, 20);

    boxRGBA(tulajdonsagok, 10, 150, 290, 180, 255, 154, 200, 255);
    szoveg_RGBA(tulajdonsagok,300/2,(150+180)/2,"Többjátékos", 255,255,255, 20);
    SDL_RenderPresent(tulajdonsagok);
    bool quit = false;
    while (!quit) {
        int x;
        int y;
        eger_koordinata(&x, &y, &quit);
        if (x >= 10 && x <= 290){                                           ///////////////////////////////////
            if (y > 50 && y < 80){
                *nehezseg = 0;                                                                                                       ////       Ez az új játék gombra kattintás esete
                quit = true;                                                                         //        Létrehoz egy új ablakot, és bezárja az előzőt.                                  //                                               //
                break;
            }
            if (y > 100 && y < 130){
                *nehezseg = 1;
                quit=true;
                break;
            }





            if (y > 150 && y < 180){
                *nehezseg = 8;
                quit=true;
                break;
            }
        }
    }
}

void tulajdonsagok_app_meret(SDL_Renderer * tulajdonsagok, int *n_szama){
    while (*n_szama < 5 || *n_szama > 20){

        SDL_Window *window;
        TTF_Font *font;
        sdl_init_szov(300, 200, "LiberationSerif-Regular.ttf", &window, &tulajdonsagok, &font);

        SDL_Color feher = {255, 255, 255}, fekete = { 0, 0, 0 };
        SDL_Rect hely;

        char szoveg[100];

        SDL_Event event;
        SDL_Surface *screen = SDL_GetWindowSurface(window);
        SDL_Surface *background = SDL_CreateRGBSurface(0, 300, 200, 32, 0, 0, 0, 0);

        boxRGBA(tulajdonsagok, 0, 0, 300, 200, 104, 104,140,255);
        boxRGBA(tulajdonsagok, 0, 0, 300, 200, 104, 104, 140, 255);
        szoveg_RGBA(tulajdonsagok,300/2,30,"Mekkora legyem a pálya?", 255,255,255, 20);
        szoveg_RGBA(tulajdonsagok,300/2,60,"(4-nél nagyobb, 21-nél kisebb!)", 255,255,255, 17);
        SDL_BlitSurface(screen, NULL, background, NULL);
        SDL_RenderPresent(tulajdonsagok);

        /*szoveg bekerese */
        SDL_Rect r = { 10, 150, 280, 30 };
        input_text(szoveg, 100, r, fekete, feher, font, tulajdonsagok);

        /* szoveg kirajzolasa */
        if (szoveg[0] != 0x0000) {
            *n_szama= atoi(szoveg);
        }
        SDL_FreeSurface(background);
        sdl_close_szov(&window, &tulajdonsagok, &font);
    }
}

void tulajdonsagok_app_kezd(SDL_Renderer * tulajdonsagok, int *alakom){
    boxRGBA(tulajdonsagok, 0, 0, 300, 200, 104, 104, 0, 255);
    szoveg_RGBA(tulajdonsagok,300/2,30,"Milyen alakzattal lennél?", 255,255,255, 20);
    boxRGBA(tulajdonsagok, 10, 50, 290, 80, 255, 154, 200, 255);
    szoveg_RGBA(tulajdonsagok,300/2,(50+80)/2,"O", 255,255,255, 20);
    boxRGBA(tulajdonsagok, 10, 100, 290, 130, 255, 154, 200, 255);
    szoveg_RGBA(tulajdonsagok,300/2,(100+130)/2,"X", 255,255,255, 20);
    SDL_RenderPresent(tulajdonsagok);
    bool quit = false;
    while (!quit) {
        int x;
        int y;
        eger_koordinata( &x, &y, &quit);
        if (x >= 10 && x <= 290){                                           ///////////////////////////////////
            if (y > 50 && y < 80){
                *alakom = 0;                                                                                                       ////       Ez az új játék gombra kattintás esete
                quit = true;
                SDL_Quit();                                                                         //        Létrehoz egy új ablakot, és bezárja az előzőt.                                  //                                               //
                break;
            }
            if (y > 100 && y < 130){
                *alakom = 1;
                quit=true;
                SDL_Quit();
                break;
            }
        }
    }
}
