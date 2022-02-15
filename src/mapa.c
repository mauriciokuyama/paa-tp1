#include "mapa.h"
#include <stdlib.h>

void inicializaMapaVazio(mapa *terreno, int x, int y) {
    int i, j;

    terreno->mat = malloc(x * sizeof(char *));
    for (i = 0; i < x; i++) {
        terreno->mat[i] = malloc(y * sizeof(char));
    }
    // preenchendo a matriz com .
    for (i = 0; i < x; i++) {
        for (j = 0; j < y; j++) {
            terreno->mat[i][j] = '.';
        }
    }

    // alocando matriz inicializada com 0
    terreno->matrizaux = calloc(x, sizeof(int *));
    for (i = 0; i < x; i++) {
        terreno->matrizaux[i] = calloc(y, sizeof(int));
    }

    terreno->tamanhox = x;
    terreno->tamanhoy = y;
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

    if (!feof(arq)) {
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
    } else {
        printf("Problemas na abertura do arquivo\n");
        return;
    }

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

    movimentaHeroi(&hero, terreno, U, T, S, B, G);

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

void movimentaHeroi(heroi *hero, mapa terreno, monstro U, monstro T, monstro S, monstro B,
                    guiygas boss) {

    int i, j;
    bool resultado;
    // cima, direita, baixo, esquerda
    int vertical[] = {-1, 0, 1, 0};
    int horizontal[] = {0, 1, 0, -1};
    // preenche a matriz aux com 0
    for (i = 0; i < terreno.tamanhox; i++) {
        for (j = 0; j < terreno.tamanhoy; j++) {
            terreno.matrizaux[i][j] = 0;
        }
    }
    terreno.matrizaux[hero->atualx][hero->atualy] = 1;
    resultado = tentaMoverHeroi(hero, terreno, vertical, horizontal, 2, U, T, S, B, boss);
    // if (resultado == true)
    // {
    for (i = 0; i < terreno.tamanhox; i++) {
        for (j = 0; j < terreno.tamanhoy; j++) {
            printf("%d ", terreno.matrizaux[i][j]);
        }
        printf("\n");
    }
    //}
    // else
    // {
    //     printf("Nao tem solucao\n");
    // }
}

// VERIFICAR MATRIZAUX[][]
bool tentaMoverHeroi(heroi *hero, mapa terreno, int *vertical, int *horizontal, int i, monstro U,
                     monstro T, monstro S, monstro B, guiygas boss) {
    int xn, yn, m;
    bool q1;
    m = 0;
    do {
        q1 = false;
        xn = hero->atualx + horizontal[m];
        yn = hero->atualy + vertical[m];
        if (xn <= terreno.tamanhox && xn >= 0 && yn <= terreno.tamanhoy && yn >= 0) {
            if (terreno.mat[xn][yn] == 'G' && hero->poder >= boss.forca) {
                return true;
            }
            if (terreno.mat[xn][yn] != '.' && terreno.matrizaux[xn][yn] != 0) {
                if (terreno.mat[xn][yn] == '+' ||
                    (terreno.mat[xn][yn] == '-' && vertical[yn] == 0) ||
                    (terreno.mat[xn][yn] == '|' && horizontal[xn] == 0)) {
                    hero->atualx = xn;
                    hero->atualy = yn;
                    terreno.matrizaux[xn][yn] = i;
                    if (i < (terreno.tamanhox * terreno.tamanhoy)) {
                        q1 = tentaMoverHeroi(hero, terreno, vertical, horizontal, i + 1, U, T, S, B,
                                             boss);
                        if (q1 == false) {
                            terreno.matrizaux[xn][yn] = 0;
                        } else {
                            q1 = true;
                        }
                    }
                }
                if (terreno.mat[xn][yn] == 'U') {
                    if (heroiGanha(hero, U)) {
                        hero->atualx = xn;
                        hero->atualy = yn;
                        terreno.matrizaux[xn][yn] = i;
                        if (i < (terreno.tamanhox * terreno.tamanhoy)) {
                            q1 = tentaMoverHeroi(hero, terreno, vertical, horizontal, i + 1, U, T,
                                                 S, B, boss);
                            if (q1 == false) {
                                terreno.matrizaux[xn][yn] = 0;
                            } else {
                                q1 = true;
                            }
                        }
                    }
                }
                if (terreno.mat[xn][yn] == 'T') {
                    if (heroiGanha(hero, T)) {
                        hero->atualx = xn;
                        hero->atualy = yn;
                        terreno.matrizaux[xn][yn] = i;
                        if (i < (terreno.tamanhox * terreno.tamanhoy)) {
                            q1 = tentaMoverHeroi(hero, terreno, vertical, horizontal, i + 1, U, T,
                                                 S, B, boss);
                            if (q1 == false) {
                                terreno.matrizaux[xn][yn] = 0;
                            } else {
                                q1 = true;
                            }
                        }
                    }
                }
                if (terreno.mat[xn][yn] == 'S') {
                    if (heroiGanha(hero, S)) {
                        hero->atualx = xn;
                        hero->atualy = yn;
                        terreno.matrizaux[xn][yn] = i;
                        if (i < (terreno.tamanhox * terreno.tamanhoy)) {
                            q1 = tentaMoverHeroi(hero, terreno, vertical, horizontal, i + 1, U, T,
                                                 S, B, boss);
                            if (q1 == false) {
                                terreno.matrizaux[xn][yn] = 0;
                            } else {
                                q1 = true;
                            }
                        }
                    }
                }
                if (terreno.mat[xn][yn] == 'B') {
                    if (heroiGanha(hero, B)) {
                        hero->atualx = xn;
                        hero->atualy = yn;
                        terreno.matrizaux[xn][yn] = i;
                        if (i < (terreno.tamanhox * terreno.tamanhoy)) {
                            q1 = tentaMoverHeroi(hero, terreno, vertical, horizontal, i + 1, U, T,
                                                 S, B, boss);
                            if (q1 == false) {
                                terreno.matrizaux[xn][yn] = 0;
                            } else {
                                q1 = true;
                            }
                        }
                    }
                }
            }
        }
        m++;
    } while (q1 || (m == 3));
    return q1;
}

bool heroiGanha(heroi *hero, monstro Monster) {
    if (hero->poder >= Monster.forca) {
        hero->poder += Monster.recompensa;
        return true;
    } else if (hero->qtPk > 0) {
        hero->poder += Monster.recompensa;
        hero->qtPk--;
        return true;
    } else {
        return false;
    }
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

    for (int i = 0; i < terreno.tamanhox; i++) {
        free(terreno.matrizaux[i]);
    }
    free(terreno.matrizaux);
}
