#include "mapa.h"

void inicializaMapa(Apmapa *terreno)
{
    (*terreno) = (Apmapa)malloc(sizeof(mapa));
}
void fazMapaVazio(Apmapa *terreno, int x, int y)
{
    int i, j;
    (*terreno)->mat = malloc(x * sizeof(char *));
    for (i = 0; i < x; i++)
    {
        (*terreno)->mat[i] = malloc(y * sizeof(char));
    }
    (*terreno)->tamanhox = x;
    (*terreno)->tamanhoy = y;
    for (i = 0; i < x; i++)
    {
        for (j = 0; j < y; j++)
        {
            (*terreno)->mat[i][j] = '.';
        }
    }
}
void imprimeMapa(Apmapa terreno)
{
    int i, j;
    for (i = 0; i < terreno->tamanhox; i++)
    {
        for (j = 0; j < terreno->tamanhoy; j++)
        {
            printf("%c", terreno->mat[i][j]);
        }
        printf("\n");
    }
}

void leArqv()
{
    FILE *arq;
    char Linha[100];
    char *result;
    //  U, T, S, B e G.
    Apmapa terreno;
    Apheroi hero;
    ApMonstro U, T, S, B;
    Apguiygas G;
    int poderhero, qtpk, poderU, recompensaU, poderT, recompensaT, poderS, recompensaS, poderB,
        recompensaB, poderG, recompensaG, mapax, mapay;
    int i, j;
    arq = fopen("../data/mapa1.txt", "rt");
    if (arq == NULL)
    {
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
    inicializaMapa(&terreno);
    fazMapaVazio(&terreno, mapax, mapay);
    i = 0;
    fgets(Linha, 100, arq);
    while (!feof(arq))
    {

        result = fgets(Linha, 100, arq);
        if (result)
        {
            for (j = 0; j < mapay; j++)
                (*terreno).mat[i][j] = Linha[j];
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
    printf("Força: %d | Recompensa: %d\n", U->forca, U->recompensa);

    desalocaHeroi(&hero);
    desalocaMonstro(&U);
    desalocaMonstro(&T);
    desalocaMonstro(&S);
    desalocaMonstro(&B);
    desalocaBoss(&G);
    desalocaMapa(&terreno);

    close(arq);
}

void procuraPosHeroi(Apmapa terreno, Apheroi *hero, int power, int pk)
{
    int i, j;
    for (i = 0; i < terreno->tamanhox; i++)
    {
        for (j = 0; j < terreno->tamanhoy; j++)
        {
            if (terreno->mat[i][j] == '@')
            {
                preencheHeroi(hero, power, pk, i, j);
                return;
            }
        }
    }
}

void procuraPosBoss(Apmapa terreno, Apguiygas *boss, int power, int recompensa)
{
    int i, j;
    for (i = 0; i < terreno->tamanhox; i++)
    {
        for (j = 0; j < terreno->tamanhoy; j++)
        {
            if (terreno->mat[i][j] == 'G')
            {
                preencheBoss(boss, power, recompensa, i, j);
                return;
            }
        }
    }
}

void desalocaMapa(Apmapa *terreno)
{
    free((*terreno)->mat);
    free(*terreno);
}