#include <stdlib.h>
#include <stdio.h>

typedef struct Mapa *Apmapa; 

typedef struct Mapa{
    char *mat;
    int tamanhox, tamanhoy;
}mapa;

void inicializaMapa(Apmapa* terreno);
void fazMapaVazio(Apmapa* terreno);
void leArqv();