#ifndef MONSTROS_H
#define MONSTROS_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Monstro {
    int forca, recompensa;
} monstro;

void inicializaMonstro(monstro *Monster);
void preencheMonstro(monstro *Monster, int forca, int recompensa);

#endif
