#include <stdio.h>
#include <string.h>

#include "guiygas.h"
#include "heroi.h"
#include "mapa.h"
#include "monstros.h"

int main() {
    int opc;
    char nomeArquivo[100];
    char data[100];
    char buffer[100];
    opc = 1;
    while (opc != 0) {
        strcpy(data, "data/");
        printf("Digite o nome do arquivo desejado: Ex: mapa\n");
        fgets(buffer, 100, stdin);
        sscanf(buffer,"%s", nomeArquivo);
        strcat(nomeArquivo,".txt");
        strcat(data,nomeArquivo);
        leArqv(data);
        printf("Deseja sair: \n0 - Sim \n1 - Nao\n");
        fgets(buffer, 100, stdin);
        sscanf(buffer,"%d", &opc);
    }

    return 0;
}
