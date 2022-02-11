#include "heroi.h"

void inicializaHeroi(Apheroi *hero)
{
    (*hero) = (Apheroi)malloc(sizeof(heroi));
    (*hero)->atualx = -1;
    (*hero)->atualy = -1;
    (*hero)->poder = 0;
    (*hero)->qtPk = 0;
}

void preencheHeroi(Apheroi *hero, int power, int pk, int posx, int posy)
{
    (*hero)->poder = power;
    (*hero)->qtPk = pk;
    (*hero)->atualx = posx;
    (*hero)->atualy = posy;
}

void movimentaHeroi(Apheroi *hero, Apmapa terreno)
{

    int x, y;
    x = (*hero)->atualx;
    y = (*hero)->atualy;
    // cima, direita, baixo, esquerda
    int vertical[] = {-1, 0, 1, 0};
    int horizontal[] = {0, 1, 0, -1};
    if (x < 0 || x >= (*terreno).tamanhox || y < 0 || y >= (*terreno).tamanhoy || (*terreno).mat[x][y] == '.')
    {
        return;
    }
    (*hero)->atualx = x;
    (*hero)->atualy = y;
}

void desalocaHeroi(Apheroi *hero)
{
    free(*hero);
}