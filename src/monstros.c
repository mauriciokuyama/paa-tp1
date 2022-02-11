#include "monstros.h"

void inicializaMonstro(ApMonstro *Monster){
    (*Monster) = (ApMonstro)malloc(sizeof(monstro));
    (*Monster)->forca = 0;
    (*Monster)->recompensa = 0;
}
void preencheMonstro(ApMonstro *Monster, int forca, int recompensa){
    (*Monster)->forca = forca;
    (*Monster)->recompensa = recompensa;
}
void desalocaMonstro(ApMonstro *Monster) {
    free(*Monster);
}