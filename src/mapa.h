#include <stdlib.h>
#include <stdio.h>

#include "heroi.c"

typedef struct Mapa *Apmapa;

typedef struct Mapa
{
    char **mat;
    int tamanhox, tamanhoy;
} mapa;

void leArqv();
void inicializaMapa(Apmapa *terreno);
void fazMapaVazio(Apmapa *terreno, int x, int y);
void imprimeMapa(Apmapa terreno);

void addHeroinoMapa(Apmapa *terreno, Apheroi *hero);