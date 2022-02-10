#include "mapa.h"

void inicializaMapa(Apmapa* terreno){
    terreno = (Apmapa) malloc(sizeof(mapa));
}
void fazMapaVazio(Apmapa* terreno, int x, int y){
    int i,j;
    (*terreno)->mat= malloc (x * y * sizeof(char));
    (*terreno)->tamanhox = x;
    (*terreno)->tamanhoy = y;
    for (i=0;i<x;i++){
        for (j=0;j<y;j++){
            (*terreno)->mat[i][j] = '.';
        }
    }
}
void imprimeMapa(Apmapa terreno){
    int i,j;
    for (i=0;i<terreno->tamanhox;i++){
        for (j=0;j<terreno->tamanhoy;j++){
            printf("%c",terreno->mat[i][j]);
        }
    }
}


int main(){
    
}