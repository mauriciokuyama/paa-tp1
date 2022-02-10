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
    int i;
    arq = fopen("../data/mapa1.txt", "rt");
    if (arq == NULL)
    {
        printf("Problemas na abertura do arquivo\n");
        return;
    }
    i = 1;
    while (!feof(arq))
    {

        result = fgets(Linha, 100, arq);
        if (result)
            // printf("Linha %d : %s", i, Linha);
        i++;
    }
    printf("\n");
    fclose(arq);
}

int main()
{
    // Apmapa teste;
    // int tamanhox, tamanhoy;
    // tamanhox = 10;
    // tamanhoy = 10;
    // inicializaMapa(&teste);
    // fazMapaVazio(&teste, tamanhox, tamanhoy);
    // imprimeMapa(teste);
    leArqv();
    return 0;
}