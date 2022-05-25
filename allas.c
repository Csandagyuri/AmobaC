#include "allas.h"
#include <stdio.h>
#include "debugmalloc.h"
#include "Jelenito.h"


/* A játékmenet mátrixának létrehozása */
int **matrix (int db, int *hosszu_tombpointer){
    int **uj;
    uj = (int**) malloc (db * sizeof(int*));
    uj[0] = (int*) malloc (db * db * sizeof(int));
    for (int y = 0; y < db; y++){
        uj[y] = uj [0] + y*db;
    }
    for (int i = 0; i < db; i++)
        for (int j = 0; j < db; j++){
            uj[i][j] = 8;
        }
    *hosszu_tombpointer = &uj;
    return uj;
}



bool leghosszabb( int nyero , ListaElem **vonal ,int **jatek_allas, int p_meret){
    int max = 0;
    for (int i = 0; i < p_meret; i++)
        for (int j = 0; j < p_meret; j++)
            for (int a = 0; a <= 1; a++)    //a függőleges irány vizsgálata
                for (int b = -1; b <= 1; b++)  // vízszintes irány vizsgálat
                    if ( a != 0 || b != 0)
                        if ( a != 0 || b != 8){
                    int hossz = 1;
                    //Addig, ameddig a pályán belül van, és az odébbi elem megegyezik a jelenleg vizsgált mező elemével
                    while (jatek_allas[j][i] != 8 && i+a*hossz >= 0 && i+a*hossz < p_meret && j+b*hossz < p_meret && j+b*hossz >= 0 && (jatek_allas[j+b*hossz][i+a*hossz] == jatek_allas[j][i])){
                        hossz++;
                        if (hossz >= max){
                            max = hossz;
                        if (max >= nyero)
                        Lista_beszuras(&*vonal, j, i, b,a, hossz-1);
                        }
                    }
                }
    if (max >= nyero){
        return true;

    }

    else{
            return false;
    }
}

bool dontetlen (int **jatek_allas, int p_meret){
    for (int i = 0; i < p_meret; i++)
        for (int j = 0; j < p_meret; j++){
            if (jatek_allas[j][i] == 8) return false;
        }
    return true;
}


void Lista_beszuras(ListaElem **elso, int x, int y, int a, int b, int hossz){
    ListaElem *uj = (ListaElem*) malloc(sizeof(ListaElem));
    uj->eleje.x = x;
    uj->eleje.y = y;
    uj->vege.x = a;
    uj->vege.y = b;
    uj->hossz = hossz;
    uj->kov = NULL;
    if (*elso == NULL){
        *elso = uj;
    }
    else {
        uj->kov = *elso;
        *elso = uj;
    }
}

void lista_torol (ListaElem **elso){
    ListaElem *mozgo = *elso;
    while( mozgo != NULL){
        ListaElem *torlendo;
        torlendo = mozgo;
        mozgo = mozgo->kov;
        free(torlendo);
    }
    *elso = NULL;
}


void fajlba_mentes(int n_szama,int n_meret,int nyeresi,int nehezseg,int aktualis,int tovabbi_utasit,int **jatek_matrix){
    /* Az fp változóval hivatkozunk majd a nyitott fájlra. */
    FILE* fp;

    /* Létrehozzuk a fájlt, w = write = írni fogunk bele. */
    fp = fopen("allas.txt", "wt");
    if (fp == NULL) printf("valami gaz?");

    /* Beleírjuk a "Helló, világ!" szöveget. */
    fprintf(fp, "%d %d %d %d %d %d\n", n_szama, n_meret, nyeresi, nehezseg, aktualis, tovabbi_utasit);
    for (int i = 0; i < n_szama; i++){
        for (int j = 0; j < n_szama; j++)
        fprintf(fp,"%d ", jatek_matrix[j][i]);
        fprintf(fp,"\n");
    }

    /* Végeztünk, bezárjuk a fájlt. */
    fclose(fp);
}



int **fajlbol_beolv(int *negyzetek_szama, int *negyzet_meret, int *nyeres_feltetel, int *nehezseg, int *aktualis, int *tovabbi_utasit){
    FILE* fp;
    fp = fopen("allas.txt", "rt");
    fscanf(fp,"%d %d %d %d %d %d\n", &*negyzetek_szama, &*negyzet_meret, &*nyeres_feltetel, &*nehezseg, &*aktualis, &*tovabbi_utasit);
        int matrix_hosszu[*negyzetek_szama];
        int **regi_matrix = matrix(*negyzetek_szama, matrix_hosszu);
        for (int i = 0; i < *negyzetek_szama; i++){
        for (int j = 0; j < *negyzetek_szama; j++)
            fscanf(fp, "%d ",&regi_matrix[j][i]);
            fscanf(fp, "\n");
        }
    fclose(fp);
    return regi_matrix;

}
