#include <stdlib.h>
#include <stdio.h>

typedef struct Monstro *Apmonstro;

typedef struct Monstro{
    char nomemonstro;
    int forca, recompensa,posx,posy;
}monstro;

void inicializaMonstro(Apmonstro* monster);
void preencheMonstro(Apmonstro* monster,char nome, int forca, int recompensa,int posx,int posy);