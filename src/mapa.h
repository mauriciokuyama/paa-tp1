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
void desalocaMapa(mapa terreno);

#endif
