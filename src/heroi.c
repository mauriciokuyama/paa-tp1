#include "heroi.h"

void inicializaHeroi(heroi *hero) {
    hero->atualx = -1;
    hero->atualy = -1;
    hero->poder = 0;
    hero->qtPk = 0;
}

void preencheHeroi(heroi *hero, int power, int pk, int posx, int posy) {
    hero->poder = power;
    hero->qtPk = pk;
    hero->atualx = posx;
    hero->atualy = posy;
}
