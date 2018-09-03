/*
1-Crie um programa em C para, considerando as informações acima, construa um
arquivo de dados e insira nesse arquivo pelo menos 10 registros. Considere 
campos de tamanho fixo em  bytes e registros  de  tamanho  fixo  em  bytes. 
As informações devem ser obtidas da entrada padrão
*/

#include <stdio.h>

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
}

struct ind {
    int chave;
    int posicao;
}

int main () {
    FILE *arquivo, *indices;
    struct reg registro;
    struct cur cursor;
    struct ind indice[20];
    int i,max;
    

    printf("1) Escrever\n2) Ler todos\nSelecione uma opcao: ");
    scanf("%d", &i);
    if (i == 1) {
        arquivo = fopen("registros.bin", "wb");
        if(arquivo == NULL)
            perror("Erro ao abrir registros.bin");
        else {
                printf("\nInsira o numero de registro que deseja escrever: ");
                scanf("%d", &max);
                getchar();
                for (i=0;i<max;i++) {
                    // Coleta valores dos registros
                    printf("Ultimo nome: ");
                    scanf("%[^\n]s", registro.ultimonome);
                    getchar();
                    printf("Primeiro nome: ");
                    scanf("%[^\n]s", registro.primeironome);
                    getchar();
                    printf("Endereco: ");
                    scanf("%[^\n]s", registro.endereco);
                    getchar();
                    printf("Cidade: ");
                    scanf("%[^\n]s", registro.cidade);
                    getchar();
                    printf("Estado: ");
                    scanf("%[^\n]s", registro.estado);
                    getchar();
                    printf("CEP: ");
                    scanf("%[^\n]s", registro.cep);
                    getchar();
                    printf("Telefone: ");
                    scanf("%[^\n]s", registro.telefone);
                    getchar();

                    // Escreve registro no arquivo
                    printf("\n-->Numero de itens escritos: %ld\n", 
                    fwrite(&registro, sizeof registro, 1, arquivo));
                    
                    // Salva indices dos registros
                    indice[i].chave = i;
                    indice[i].cursor = ftell(arquivo);
                }
                printf("\n\nRegistros salvos com sucesso!\n");

                indices = fopen("indices.bin", "wb");
                if(indices == NULL)
                    perror("Erro ao abrir indices.bin");
                else {
                    for (i=0;i<max;i++) {
                        // Escreve registro no arquivo
                        printf("\n-->Numero de itens escritos: %ld\n", 
                        fwrite(&indice[i], sizeof indice, 1, indices));
                    }
                    printf("\n\nIndices salvos com sucesso!\n");
                }

                fclose(indices);
            }
        }
    } else {
        arquivo = fopen("registros.bin", "rb"); // acesso de leitura
        if(arquivo == NULL)
            perror("Erro ao abrir registros.bin");
        else{
            // Varredura do arquivo
            while(fread(&registro, sizeof registro, 1, arquivo) > 0)
                printf("%s %s\n", registro.primeironome, registro.ultimonome);
        }
    }

	fclose(arquivo);
	
    return 0;
}