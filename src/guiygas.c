#include "guiygas.h"

void inicializaBoss(Apguiygas *boss)
{
    (*boss) = (Apguiygas)malloc(sizeof(guiygas));
    (*boss)->forca = 0;
    (*boss)->recompensa = 0;
    (*boss)->posx = 0;
    (*boss)->posy = 0;
}
void preencheBoss(Apguiygas *boss, int forca, int recompensa, int posx, int posy)
{
    (*boss)->forca = forca;
    (*boss)->recompensa = recompensa;
    (*boss)->posx = posx;
    (*boss)->posy = posy;
}
void desalocaBoss(Apguiygas *boss)
{
    free(*boss);
}