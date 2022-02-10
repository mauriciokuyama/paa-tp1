#include "guiygas.h"

void inicializaMonstro(Apmonstro *monster)
{
    (*monster) = (Apmonstro)malloc(sizeof(monstro));
    (*monster)->nomemonstro = ' ';
    (*monster)->forca = 0;
    (*monster)->recompensa = 0;
    (*monster)->posx = 0;
    (*monster)->posy = 0;
}
void preencheMonstro(Apmonstro *monster,char nome, int forca, int recompensa, int posx, int posy)
{
    (*monster)->nomemonstro = nome;
    (*monster)->forca = forca;
    (*monster)->recompensa = recompensa;
    (*monster)->posx = posx;
    (*monster)->posy = posy;    
}