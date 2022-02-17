#ifndef HEROI_H
#define HEROI_H

#include <stdio.h>
#include <stdbool.h>

typedef struct Heroi {
    int poder;
    int qtPk;
    int atualx, atualy;
    bool avanca;
} heroi;

void inicializaHeroi(heroi *hero);
void preencheHeroi(heroi *hero, int power, int pk, int posx, int posy);

#endif
