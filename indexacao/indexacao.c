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
    int chave_aux;
    int posicao_aux;
    char cidade_aux[40];
    int i=0,max;

    //Funcao de verificacao de existencia e quantidade de registros

    indices = fopen("indices.bin", "wb");
    if(indices == NULL)
        perror("Erro ao abrir indices.bin");
    else {
        printf("entrooou\n");
        while (fread(&chave_aux, sizeof chave_aux, 1, indices) > 0 &&
        fread(&posicao_aux, sizeof posicao_aux, 1, indices) > 0 &&
        fread(cidade_aux, sizeof cidade_aux, 1, indices) > 0){
            indice[i].chave = chave_aux;
            indice[i].posicao = posicao_aux;
            strcpy (indice[i].cidade, cidade_aux);
            printf("chave: %d\ncidade: %s\nposicao: %d\n\n", indice[i].chave, indice[i].cidade, indice[i].posicao);
            i++;
        }
        
    }

    fclose(indices);
    

    printf("1) Escrever\n2) Ler todos\n3)Ler um registro\nSelecione uma opcao: ");
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
                indice[i].posicao = ftell(arquivo);
                strcpy (indice[i].cidade, registro.cidade);
            }
            printf("\n\nRegistros salvos com sucesso!\n");

            fclose(arquivo);
            
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
    } else {
        arquivo = fopen("registros.bin", "rb"); // acesso de leitura
        if(arquivo == NULL)
            perror("Erro ao abrir registros.bin");
        else{
            // Varredura do arquivo
            while(fread(&registro, sizeof registro, 1, arquivo) > 0)
                printf("%s %s\n", registro.primeironome, registro.ultimonome);
        }
        fclose(registros);
    }
	
	
	
    return 0;
}