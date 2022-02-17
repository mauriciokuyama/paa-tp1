#ifndef MAPA_H
#define MAPA_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "guiygas.h"
#include "heroi.h"
#include "item.h"
#include "monstros.h"

typedef struct Mapa {
    char **mat;
    item **matrizaux;
    int tamanhox, tamanhoy;
    monstro U, T, S, B;
    guiygas boss;
} mapa;

void leArqv(char *path);
void inicializaMapaVazio(mapa *terreno, int x, int y);
void imprimeMapa(mapa terreno);
void procuraPosHeroi(mapa terreno, heroi *hero, int power, int pk);
void movimentaHeroi(heroi *hero, mapa terreno);
bool tentaMoverHeroi(heroi *hero, mapa terreno, int *vertical, int *horizontal, int i);
bool heroiGanha(heroi *hero, monstro Monster);
void procuraPosBoss(mapa terreno, guiygas *boss, int power, int recompensa);
void desalocaMapa(mapa terreno);

#endif
