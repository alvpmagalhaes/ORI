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
    char estado[3];
    char cep[10];
    char telefone[20];
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
    int i=0,max, regs_indice, option;
    char chave[40];
    char cidade[40];

    //Funcao de verificacao de existencia e quantidade de registros no indice

    indices = fopen("indices.bin", "rb");
    if(indices == NULL)
        perror("Erro ao abrir indices.bin");
    else {   // Varredura do arquivo
            while(fread(&indice, sizeof indice, 1, indices) > 0)
                regs_indice++;
        }
        fclose(indices);

        printf("\nBem-vindo!\nNúmero de registros recuperados: %d\n", regs_indice);

    fclose(indices);

    printf("\n*********MENU*********\n\n0)Sair\n1) Escrever\n2) Ler todos\n3)Ler um registro\nSelecione uma opcao: ");
    scanf("%d", &i);

        while(i != 0){

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
        } else if(i == 2) {
            //Ler todos os registros
            arquivo = fopen("registros.bin", "rb"); // acesso de leitura
            if(arquivo == NULL)
                perror("Erro ao abrir registros.bin");
            else{
                // Varredura do arquivo
                while(fread(&registro, sizeof registro, 1, arquivo) > 0)
                    printf("\n%d\n%s %s\n%s\n%s\n%s\n%s\n%s\n", 
                    registro.chave,
                    registro.primeironome, 
                    registro.ultimonome,
                    registro.endereco,
                    registro.cidade,
                    registro.estado,
                    registro.cep,
                    registro.telefone);
            }
            fclose(registros);
        }else if(i ==3){
                //Buscar um arquivo
                printf("\nBusca de Arquivos. Selecione uma opção:\n1)Chave\n2)Cidade\n");
                scanf("%d", &i);

                if(i == 1){
                     arquivo = fopen("registros.bin", "rb"); // acesso de leitura
                    if(arquivo == NULL)
                    perror("Erro ao abrir registros.bin");
                    else{
                        printf("\nDigite a chave desejada: \n");
                        scanf("%s", chave);
                        fseek(arquivo, sizeof(registro)*(strlen(chave)), SEEK_SET);

                        if(strlen(chave) >= regs_indice){
                                printf("\nChave inválida\n");
                        }else {
                        fread(&registro, sizeof registro, 1, arquivo);
                            printf("\n%d\n%s %s\n%s\n%s\n%s\n%s\n%s\n", 
                            registro.chave,
                            registro.primeironome, 
                            registro.ultimonome,
                            registro.endereco,
                            registro.cidade,
                            registro.estado,
                            registro.cep,
                            registro.telefone);
                        }

                    }
                }else if(i == 2){
                    printf("\nDigite a cidade desejada: \n");
                        scanf("%s", cidade);
                        fseek(arquivo, sizeof(registro)*(strlen(cidade)), SEEK_SET);
                                fread(&registro, sizeof registro, 1, arquivo);
                                printf("\n%d\n%s %s\n%s\n%s\n%s\n%s\n%s\n", 
                                registro.chave,
                                registro.primeironome, 
                                registro.ultimonome,
                                registro.endereco,
                                registro.cidade,
                                registro.estado,
                                registro.cep,
                                registro.telefone);
 
                }

        }

        printf("\nDeseja retornar ao Menu Principal?\n1)Sim\n2)Nao\n");
        scanf("%d", &i);
        if(i == 2){
            i = 0;
        } else {
            printf("\n*********MENU*********\n\n0)Sair\n1) Escrever\n2) Ler todos\n3)Ler um registro\nSelecione uma opcao: ");
    scanf("%d", &i);
        }
    }
    return 0;
}