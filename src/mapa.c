#include "mapa.h"

void inicializaMapa(Apmapa *terreno)
{
    (*terreno) = (Apmapa)malloc(sizeof(mapa));
}
void fazMapaVazio(Apmapa *terreno)
{

}

void leArqv(){
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
            printf("Linha %d : %s", i, Linha);
        i++;
    }
    printf("\n");
    fclose(arq);
}

int main(){
    leArqv();
}
