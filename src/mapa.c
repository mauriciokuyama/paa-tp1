#include "mapa.h"

void inicializaMapaVazio(mapa *terreno, int x, int y) {
    int i, j;
    terreno->mat = malloc(x * sizeof(char *));
    for (i = 0; i < x; i++) {
        terreno->mat[i] = malloc(y * sizeof(char));
    }
    terreno->tamanhox = x;
    terreno->tamanhoy = y;
    for (i = 0; i < x; i++) {
        for (j = 0; j < y; j++) {
            terreno->mat[i][j] = '.';
        }
    }
}

void imprimeMapa(mapa terreno) {
    int i, j;
    for (i = 0; i < terreno.tamanhox; i++) {
        for (j = 0; j < terreno.tamanhoy; j++) {
            printf("%c", terreno.mat[i][j]);
        }
        printf("\n");
    }
}

void leArqv() {
    FILE *arq;
    char Linha[100];
    char *result;
    //  U, T, S, B e G.
    mapa terreno;
    heroi hero;
    monstro U, T, S, B;
    guiygas G;
    int poderhero, qtpk, poderU, recompensaU, poderT, recompensaT, poderS, recompensaS, poderB,
        recompensaB, poderG, recompensaG, mapax, mapay;
    int i, j;
    arq = fopen("data/mapa1.txt", "rt");
    if (arq == NULL) {
        printf("Problemas na abertura do arquivo\n");
        return;
    }
    fscanf(arq, "%d %d", &poderhero, &qtpk);
    fscanf(arq, "%d %d", &poderU, &recompensaU);
    fscanf(arq, "%d %d", &poderT, &recompensaT);
    fscanf(arq, "%d %d", &poderS, &recompensaS);
    fscanf(arq, "%d %d", &poderB, &recompensaB);
    fscanf(arq, "%d %d", &poderG, &recompensaG);
    inicializaHeroi(&hero);
    inicializaMonstro(&U);
    inicializaMonstro(&T);
    inicializaMonstro(&S);
    inicializaMonstro(&B);
    inicializaBoss(&G);
    fscanf(arq, "%d %d", &mapax, &mapay);
    inicializaMapaVazio(&terreno, mapax, mapay);
    i = 0;
    fgets(Linha, 100, arq);
    while (!feof(arq)) {
        result = fgets(Linha, 100, arq);
        if (result) {
            for (j = 0; j < mapay; j++)
                terreno.mat[i][j] = Linha[j];
        }
        i++;
    }

    fclose(arq);
    procuraPosHeroi(terreno, &hero, poderhero, qtpk);
    procuraPosBoss(terreno, &G, poderG, recompensaG);
    preencheMonstro(&U, poderU, recompensaU);
    preencheMonstro(&T, poderT, recompensaT);
    preencheMonstro(&S, poderS, recompensaS);
    preencheMonstro(&B, poderB, recompensaB);
    printf("Força: %d | Recompensa: %d\n", U.forca, U.recompensa);

    desalocaMapa(terreno);
}

void procuraPosHeroi(mapa terreno, heroi *hero, int power, int pk) {
    int i, j;
    for (i = 0; i < terreno.tamanhox; i++) {
        for (j = 0; j < terreno.tamanhoy; j++) {
            if (terreno.mat[i][j] == '@') {
                preencheHeroi(hero, power, pk, i, j);
                return;
            }
        }
    }
}

void movimentaHeroi(heroi *hero, mapa terreno) {

    int x, y;
    x = hero->atualx;
    y = hero->atualy;
    // cima, direita, baixo, esquerda
    int vertical[] = {-1, 0, 1, 0};
    int horizontal[] = {0, 1, 0, -1};
    if (x < 0 || x >= terreno.tamanhox || y < 0 || y >= terreno.tamanhoy ||
        terreno.mat[x][y] == '.') {
        return;
    }
    hero->atualx = x;
    hero->atualy = y;
}

void procuraPosBoss(mapa terreno, guiygas *boss, int power, int recompensa) {
    int i, j;
    for (i = 0; i < terreno.tamanhox; i++) {
        for (j = 0; j < terreno.tamanhoy; j++) {
            if (terreno.mat[i][j] == 'G') {
                preencheBoss(boss, power, recompensa, i, j);
                return;
            }
        }
    }
}

void desalocaMapa(mapa terreno) {
    for (int i = 0; i < terreno.tamanhox; i++) {
        free(terreno.mat[i]);
    }

    free(terreno.mat);
}
