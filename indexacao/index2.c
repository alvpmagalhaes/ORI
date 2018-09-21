/*
1-Crie um programa em C para, considerando as informações acima, construa um
arquivo de dados e insira nesse arquivo pelo menos 10 registros. Considere 
campos de tamanho fixo em  bytes e registros  de  tamanho  fixo  em  bytes. 
As informações devem ser obtidas da entrada padrão
*/

#include <stdio.h>
#include <string.h>

struct reg {
    int chave;
    char ultimonome[40];
    char primeironome[40];
    char endereco[200];
    char cidade[40];
    char estado[2];
    char cep[9];
    char telefone[15];
};

struct cur {
    int atual;
    int proximo;
};

struct ind {
    int chave;
    int posicao;
    char cidade[40];
};

int main () {
    FILE *arquivo, *indices, *registros;
    struct reg registro;
    struct cur cursor;
    struct ind indice[20];
    int i=0, max, qt_registros;

    //Funcao de verificacao de existencia e quantidade de registros

        indices = fopen("indices.bin", "rb");
        if(indices == NULL)
            perror("Erro ao abrir indices.bin");
        else {
            while (fread(&indice[i].chave, sizeof indice[i].chave, 1, indices) > 0 &&
                fread(&indice[i].posicao, sizeof indice[i].posicao, 1, indices) > 0 &&
                fread(indice[i].cidade, sizeof indice[i].cidade, 1, indices) > 0){
                    printf("chave: %d\ncidade: %s\nposicao: %d\n\n", indice[i].chave, indice[i].cidade, indice[i].posicao);
                    i++;
                }
            fclose(indices);
        }
    return 0;
}