#include "heroi.h"

void inicializaHeroi(Apheroi* hero){
    (hero) = (Apheroi)malloc(sizeof(heroi));
    (*hero)-> atualx = NULL;
    (*hero)-> atualy = NULL;
    (*hero)-> poder = 0;
    (*hero)-> qtPk = 0;
}

void preencheHeroi(Apheroi* hero, int power, int pk,int posx, int posy) {
    (*hero)->poder = power;
    (*hero)->qtPk = pk;
    (*hero)->atualx = posx;
    (*hero)->atualy = posy;

}
