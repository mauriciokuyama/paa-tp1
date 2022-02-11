#ifndef GUIYGAS_H
#define GUIYGAS_H

#include <stdio.h>

typedef struct Guiygas {
    int forca, recompensa, posx, posy;
} guiygas;

void inicializaBoss(guiygas *boss);
void preencheBoss(guiygas *boss, int forca, int recompensa, int posx, int posy);

#endif
