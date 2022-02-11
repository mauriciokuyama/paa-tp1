#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "heroi.c"
#include "guiygas.c"
#include "monstros.c"

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
void procuraPosHeroi(Apmapa terreno, Apheroi *hero, int power, int pk);
void procuraPosBoss(Apmapa terreno, Apguiygas *boss, int power, int recompensa);
void desalocaMapa(Apmapa *terreno);