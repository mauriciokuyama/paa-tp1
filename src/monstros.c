#include "monstros.h"

void inicializaMonstro(monstro *Monster) {
    Monster->forca = 0;
    Monster->recompensa = 0;
}
void preencheMonstro(monstro *Monster, int forca, int recompensa) {
    Monster->forca = forca;
    Monster->recompensa = recompensa;
}
