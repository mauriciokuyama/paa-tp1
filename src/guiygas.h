#include <stdlib.h>
#include <stdio.h>

typedef struct Guiygas *Apguiygas;

typedef struct Guiygas
{
    int forca, recompensa, posx, posy;
} guiygas;

void inicializaBoss(Apguiygas *boss);
void preencheBoss(Apguiygas *boss, int forca, int recompensa, int posx, int posy);
void desalocaBoss(Apguiygas *boss);