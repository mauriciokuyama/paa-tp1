#include <stdlib.h>
#include <stdio.h>

typedef struct Heroi *Apheroi;

typedef struct Heroi
{
    int poder;
    int qtPk;
    int atualx, atualy;
} heroi;

void inicializaHeroi(Apheroi *hero);
void preencheHeroi(Apheroi *hero, int power, int pk, int posx, int posy);
void movimentaHeroi(Apheroi *hero, Apmapa terreno);
void desalocaHeroi(Apheroi *hero);