#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "item.h"
#include "mapa.h"
#include "monstros.h"

// cria o mapa
void inicializaMapaVazio(mapa *terreno, int x, int y) {
    int i, j;

    terreno->mat = malloc(x * sizeof(char *));
    for (i = 0; i < x; i++) {
        terreno->mat[i] = malloc(y * sizeof(char));
    }
    // preenchendo a matriz com '.'
    for (i = 0; i < x; i++) {
        for (j = 0; j < y; j++) {
            terreno->mat[i][j] = '.';
        }
    }

    // alocando matriz inicializada com 0
    terreno->matrizaux = malloc(x * sizeof(item *));
    for (i = 0; i < x; i++) {
        terreno->matrizaux[i] = malloc(y * sizeof(item));
    }
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            inicializaItem(&terreno->matrizaux[i][j]);
        }
    }

    terreno->tamanhox = x;
    terreno->tamanhoy = y;
}

// imprime o mapa recebido pelo arquivo
void imprimeMapa(mapa terreno) {
    int i, j;
    for (i = 0; i < terreno.tamanhox; i++) {
        for (j = 0; j < terreno.tamanhoy; j++) {
            printf("%c", terreno.mat[i][j]);
        }
        printf("\n");
    }
}

// busca localização do herói no mapa e atribui suas caracteristicas na estrutura dele
static void procuraPosHeroi(mapa terreno, heroi *hero, int power, int pk) {
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

// busca localização do Guiygas no mapa e atribui suas caracteristicas na estrutura dele
static void procuraPosBoss(mapa terreno, guiygas *boss, int power, int recompensa) {
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

// imprime resultado final percorrendo a matriz auxiliar
static void caminhoFinal(mapa terreno, heroi hero, int x, int y, int *vertical, int *horizontal,
                         int iter) {
    int m, auxx, auxy;
    m = 0;

    do {
        auxx = x;
        auxy = y;
        x += vertical[m];
        y += horizontal[m];
        if (x < terreno.tamanhox && x >= 0 && y < terreno.tamanhoy && y >= 0 &&
            terreno.mat[x][y] != 'G') {

            if (terreno.matrizaux[x][y].id == (iter + 1)) {

                printf("Linha: %d, Coluna: %d; ", x + 1, y + 1);
                switch (terreno.mat[x][y]) {
                case 'U':
                    printf("P: %d, K: %d\n", terreno.matrizaux[x][y].poder,
                           terreno.matrizaux[x][y].qtpk);
                    break;
                case 'T':
                    printf("P: %d, K: %d\n", terreno.matrizaux[x][y].poder,
                           terreno.matrizaux[x][y].qtpk);
                    break;
                case 'S':
                    printf("P: %d, K: %d\n", terreno.matrizaux[x][y].poder,
                           terreno.matrizaux[x][y].qtpk);
                    break;
                case 'B':
                    printf("P: %d, K: %d\n", terreno.matrizaux[x][y].poder,
                           terreno.matrizaux[x][y].qtpk);
                    break;
                default:
                    printf("\n");
                    break;
                }
                caminhoFinal(terreno, hero, x, y, vertical, horizontal, iter + 1);
                return;
            }
        }
        x = auxx;
        y = auxy;
        m++;
    } while (m < 4);
}

// verifica se o heroi consegue derrotar o monstro
static bool heroiGanha(heroi *hero, monstro Monster) {
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

// bloqueia a direção do movimento que está sendo realizado para que não se repita
static void bloqueiaAresta(mapa *terreno, heroi hero, bool *tentarMover, int xn, int yn, int m) {
    if (m == 0 && terreno->matrizaux[xn][yn].B == false) {
        terreno->matrizaux[hero.atualx][hero.atualy].C = true;
        terreno->matrizaux[xn][yn].B = true;
        *tentarMover = true;
    } else if (m == 1 && terreno->matrizaux[xn][yn].E == false) {
        terreno->matrizaux[hero.atualx][hero.atualy].D = true;
        terreno->matrizaux[xn][yn].E = true;
        *tentarMover = true;
    } else if (m == 2 && terreno->matrizaux[xn][yn].C == false) {
        terreno->matrizaux[hero.atualx][hero.atualy].B = true;
        terreno->matrizaux[xn][yn].C = true;
        *tentarMover = true;
    } else if (m == 3 && terreno->matrizaux[xn][yn].D == false) {
        terreno->matrizaux[hero.atualx][hero.atualy].E = true;
        terreno->matrizaux[xn][yn].D = true;
        *tentarMover = true;
    }
}

// desbloqueia a direção do movimento em caso de backtracking
static void desbloqueiaAresta(mapa *terreno, heroi hero, int xn, int yn, int m) {
    if (m == 0) {
        terreno->matrizaux[hero.atualx][hero.atualy].B = false;
        terreno->matrizaux[xn][yn].C = false;
    } else if (m == 1) {
        terreno->matrizaux[hero.atualx][hero.atualy].E = false;
        terreno->matrizaux[xn][yn].D = false;
    } else if (m == 2) {
        terreno->matrizaux[hero.atualx][hero.atualy].C = false;
        terreno->matrizaux[xn][yn].B = false;
    } else if (m == 3) {
        terreno->matrizaux[hero.atualx][hero.atualy].D = false;
        terreno->matrizaux[xn][yn].E = false;
    }
}
// função para contabilizar os contadores do modo de análise
static void modoAnalise(int *profundidadeMaxima, int *numChamadas, int i) {
    (*numChamadas)++;
    if (i > (*profundidadeMaxima))
        *profundidadeMaxima = i;
}

// função recursiva responsável por tentar realizar as movimentações do heroi no mapa exercendo as
// verificações necessárias

static bool tentaMoverHeroi(heroi *hero, mapa terreno, int *vertical, int *horizontal, int i,
                            int *profundidadeMaxima, int *numChamadas) {
    int xn, yn, m, xant, yant, poderant, pkant;
    bool q1;
    bool tentarMover;
    m = 0;
    do {
        q1 = false;
        tentarMover = false;
        xn = hero->atualx + vertical[m];
        yn = hero->atualy + horizontal[m];
        xant = hero->atualx;
        yant = hero->atualy;
        poderant = hero->poder;
        pkant = hero->qtPk;
        if (xn < terreno.tamanhox && xn >= 0 && yn < terreno.tamanhoy && yn >= 0) {
            if (terreno.mat[xn][yn] == 'G') {
                if (hero->poder >= terreno.boss.forca) {
                    return true;
                }
            }
            if ((terreno.mat[xn][yn] == '-' && vertical[m] == 0 &&
                 (terreno.matrizaux[xn][yn].D == false || terreno.matrizaux[xn][yn].E == false)) &&
                terreno.matrizaux[xn][yn].id == 0) {
                bloqueiaAresta(&terreno, *hero, &tentarMover, xn, yn, m);
            }
            if ((terreno.mat[xn][yn] == '|' && horizontal[m] == 0 &&
                 (terreno.matrizaux[xn][yn].C == false || terreno.matrizaux[xn][yn].B == false))) {
                bloqueiaAresta(&terreno, *hero, &tentarMover, xn, yn, m);
            }
            if (terreno.mat[xn][yn] == '+') {

                bloqueiaAresta(&terreno, *hero, &tentarMover, xn, yn, m);
            } else if (terreno.matrizaux[xn][yn].id == 0) {
                monstro monster;
                switch (terreno.mat[xn][yn]) {
                case 'U':
                    monster = terreno.U;
                    if (heroiGanha(hero, monster))
                        bloqueiaAresta(&terreno, *hero, &tentarMover, xn, yn, m);
                    break;
                case 'T':
                    monster = terreno.T;
                    if (heroiGanha(hero, monster))
                        bloqueiaAresta(&terreno, *hero, &tentarMover, xn, yn, m);
                    break;
                case 'S':
                    monster = terreno.S;
                    if (heroiGanha(hero, monster))
                        bloqueiaAresta(&terreno, *hero, &tentarMover, xn, yn, m);
                    break;
                case 'B':
                    monster = terreno.B;
                    if (heroiGanha(hero, monster))
                        bloqueiaAresta(&terreno, *hero, &tentarMover, xn, yn, m);
                    break;
                default:
                    break;
                }
            }
            if (tentarMover) {
                hero->atualx = xn;
                hero->atualy = yn;
                int id_ant = terreno.matrizaux[xn][yn].id;
                if (terreno.matrizaux[xn][yn].id == 0) {
                    terreno.matrizaux[xn][yn].id = i;
                    terreno.matrizaux[xn][yn].poder = hero->poder;
                    terreno.matrizaux[xn][yn].qtpk = hero->qtPk;
                }
                if (i < (terreno.tamanhox * terreno.tamanhoy)) {
                    modoAnalise(profundidadeMaxima, numChamadas, i);
                    q1 = tentaMoverHeroi(hero, terreno, vertical, horizontal, i + 1,
                                         profundidadeMaxima, numChamadas);
                    if (q1 == false) {
                        desbloqueiaAresta(&terreno, *hero, xant, yant, m);
                        hero->atualx = xant;
                        hero->atualy = yant;
                        hero->poder = poderant;
                        hero->qtPk = pkant;
                        if (terreno.matrizaux[xn][yn].id != id_ant) {
                            terreno.matrizaux[xn][yn].id = 0;
                        }
                    }
                }
            }
        }
        m++;
    } while (q1 == false && (m < 4));
    return q1;
}

// função que chama a tentaMoverHeroi e responsável por identificar o resultado do caminho
static void movimentaHeroi(heroi *hero, mapa terreno, char opcao) {
    int i, j, posicaoinicialx, posicaoinicialy, poderinicial, pkinicial, profundidadeMaxima,
        numChamadas;
    bool resultado;
    // cima, direita, baixo, esquerda
    int vertical[] = {-1, 0, 1, 0};
    int horizontal[] = {0, 1, 0, -1};
    // preenche a matriz aux com 0
    for (i = 0; i < terreno.tamanhox; i++) {
        for (j = 0; j < terreno.tamanhoy; j++) {
            terreno.matrizaux[i][j].id = 0;
        }
    }
    posicaoinicialx = hero->atualx;
    posicaoinicialy = hero->atualy;
    poderinicial = hero->poder;
    pkinicial = hero->qtPk;
    terreno.matrizaux[hero->atualx][hero->atualy].id = 1;
    profundidadeMaxima = 1;
    numChamadas = 1;
    resultado =
        tentaMoverHeroi(hero, terreno, vertical, horizontal, 2, &profundidadeMaxima, &numChamadas);
    if (resultado == true) {
        printf("Linha: %d, Coluna: %d; P: %d, K: %d\n", posicaoinicialx + 1, posicaoinicialy + 1,
               poderinicial, pkinicial);
        caminhoFinal(terreno, *hero, posicaoinicialx, posicaoinicialy, vertical, horizontal, 1);
        printf("Guiygas foi derrotado.\n");
    } else {
        printf("Apesar de todas as tentativas, Ness falha em derrotar Guiygas!\n");
    }
    if (opcao == 'S')
        printf("A profundidade maxima alcancada foi %d e o numero de chamadas recursivas feitas "
               "foram %d.\n",
               profundidadeMaxima, numChamadas);
}

// realiza a leitura do arquivo e faz os solicita os preenchimentos necessários
void leArqv(char *path) {
    FILE *arq;
    char opcao;
    char buffer[10];
    char Linha[100];
    char *result;
    // A ordem dos monstros segundo a entrada U, T, S, B e G.
    mapa terreno;
    heroi hero;
    monstro U, T, S, B;
    guiygas G;
    int poderhero, qtpk, poderU, recompensaU, poderT, recompensaT, poderS, recompensaS, poderB,
        recompensaB, poderG, recompensaG, mapax, mapay;
    int i, j;
    arq = fopen(path, "rt");
    if (!arq) {
        printf("Problemas na abertura do arquivo\n");
        return;
    }
    if (!feof(arq)) {
        printf("Deseja utilizar o modo de analise? (S/N)\n");
        fgets(buffer, 10, stdin);
        sscanf(buffer, "%c", &opcao);
        while (opcao != 'S' && opcao != 'N') {
            printf("Opcao invalida!\n");
            fgets(buffer, 10, stdin);
            sscanf(buffer, "%c", &opcao);
        }
        fscanf(arq, "%d %d", &poderhero, &qtpk);
        printf(" -> O heroi inicia sua jornada com %d de poder e com %d pk's.\n", poderhero, qtpk);
        fscanf(arq, "%d %d", &poderU, &recompensaU);
        printf(" -> O monstro U tem %d de pontos de vida e oferece recompensa de %d xp!\n", poderU,
               recompensaU);
        fscanf(arq, "%d %d", &poderT, &recompensaT);
        printf(" -> O monstro T tem %d de pontos de vida e oferece recompensa de %d xp!\n", poderT,
               recompensaT);
        fscanf(arq, "%d %d", &poderS, &recompensaS);
        printf(" -> O monstro S tem %d de pontos de vida e oferece recompensa de %d xp!\n", poderS,
               recompensaS);
        fscanf(arq, "%d %d", &poderB, &recompensaB);
        printf(" -> O monstro B tem %d de pontos de vida e oferece recompensa de %d xp!\n", poderB,
               recompensaB);
        fscanf(arq, "%d %d", &poderG, &recompensaG);
        printf(" -> O chefe final, Guiygas, eh conhecido por possuir %d de poder.\n", poderG);
        inicializaHeroi(&hero);
        inicializaMonstro(&U);
        inicializaMonstro(&T);
        inicializaMonstro(&S);
        inicializaMonstro(&B);
        inicializaBoss(&G);
        fscanf(arq, "%d %d", &mapax, &mapay);
        inicializaMapaVazio(&terreno, mapax, mapay);
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

    terreno.boss = G;
    terreno.U = U;
    terreno.T = T;
    terreno.S = S;
    terreno.B = B;
    printf(" -> Mapa de entrada:\n");
    imprimeMapa(terreno);
    printf("------------------------------------\n");
    movimentaHeroi(&hero, terreno, opcao);

    desalocaMapa(terreno);
}

// função para desalocar
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
