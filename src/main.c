#include "guiygas.h"
#include "heroi.h"
#include "mapa.h"
#include "monstros.h"

int main() {
    // Apmapa teste;
    // int tamanhox, tamanhoy;
    // tamanhox = 10;
    // tamanhoy = 10;
    // inicializaMapa(&teste);
    // fazMapaVazio(&teste, tamanhox, tamanhoy);
    // imprimeMapa(teste);
    // Apheroi heroteste;
    // int poder,pk,posx,posy;
    // poder = 1;
    // pk=1;
    // posx=1;
    // posy=1;
    // inicializaHeroi(&heroteste);
    // preencheHeroi(&heroteste,poder,pk,posx,posy);
    // printf("%d,%d,%d,%d\n",(*heroteste).poder,(*heroteste).qtPk,(*heroteste).atualx,(*heroteste).atualy);

    leArqv("data/mapa2.txt");
    return 0;
}
