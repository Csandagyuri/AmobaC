#ifndef STRUCT_H_INCLUDED
#define STRUCT_H_INCLUDED


typedef struct Pont{
    int x,y;
}Pont;

typedef struct ListaElem{
    Pont eleje,vege;
    int hossz;
    struct ListaElem *kov;
}ListaElem;

    typedef enum Alakzat{
        ures = 8,
        kor = 0,
        iksz = 1
    } Alakzat;

#endif // STRUCT_H_INCLUDED
