#ifndef MAPA_H
#define MAPA_H

#include <stdio.h>
#include <stdlib.h>

#include "guiygas.h"
#include "heroi.h"
#include "monstros.h"

typedef struct Mapa {
    char **mat;
    int tamanhox, tamanhoy;
} mapa;

void leArqv();
void inicializaMapaVazio(mapa *terreno, int x, int y);
void imprimeMapa(mapa terreno);
void procuraPosHeroi(mapa terreno, heroi *hero, int power, int pk);
void movimentaHeroi(heroi *hero, mapa terreno);
void procuraPosBoss(mapa terreno, guiygas *boss, int power, int recompensa);
void desalocaMapa(mapa terreno);

#endif
