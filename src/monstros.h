#include <stdlib.h>
#include <stdio.h>


typedef struct Monstro *ApMonstro;

typedef struct Monstro
{
    int forca, recompensa;
} monstro;

void inicializaMonstro(ApMonstro *Monster);
void preencheMonstro(ApMonstro *Monster, int forca, int recompensa);
void desalocaMonstro(ApMonstro *Monster);