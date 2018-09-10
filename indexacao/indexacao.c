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
<<<<<<< HEAD
    int i=0,max, qt_registros, option, tam, busca_chave;
=======
    int i=0,max, qt_registros, limite, option;
>>>>>>> parent of e052790... Up 10/09

    //Funcao de verificacao de existencia e quantidade de registros

    indices = fopen("indices.bin", "rb");
    if(indices == NULL)
        perror("Erro ao abrir indices.bin");
    else {
        i = 0;
        while (fread(&indice[i], sizeof indice[i], 1, indices) > 0 ){
            i++;
        }

        qt_registros = i;
        
        fclose(indices);
    }

    printf("\nBem vindo!\nQuantidade de registros recuperados: %d\n\n", qt_registros);
<<<<<<< HEAD
    printf("--> MENU <--\n0) Sair\n1) Insere\n2) Listar todos\n3) Busca\nSelecione uma opcao: ");
    scanf("%d", &i);

    while(i != 0){
=======

    printf("--> MENU <--\n1) Insere\n2) Listar todos\n3) Busca\nSelecione uma opcao: ");
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
                
                registro.chave = i;

                // Salva indices dos registros
                indice[i].chave = i;
                indice[i].posicao = ftell(arquivo);
                strcpy (indice[i].cidade, registro.cidade);
>>>>>>> parent of e052790... Up 10/09

        if (i == 1) {

            arquivo = fopen("registros.bin", "ab");
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

                   registro.chave = i;

                    // Salva indices dos registros
                    indice[i].chave = i;
                    indice[i].posicao = ftell(arquivo);
                    strcpy (indice[i].cidade, registro.cidade);

                    // Escreve registro no arquivo
                    printf("\n-->Numero de itens escritos: %ld\n", 
                    fwrite(&registro, sizeof registro, 1, arquivo));
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
                        fwrite(&indice[i], sizeof indice[i], 1, indices));
                        
                    }
                    printf("\n\nIndices salvos com sucesso!\n");
                }

                fclose(indices);
                
            }
        } else if(i == 2){
            arquivo = fopen("registros.bin", "rb"); // acesso de leitura
            if(arquivo == NULL)
                perror("Erro ao abrir registros.bin\n");
            else{
                // Varredura do arquivo
                printf("\n");
                while(fread(&registro, sizeof registro, 1, arquivo) > 0)
                    printf("\nChave: %d\nPrimeiro nome: %s\nUltimo nome: %s\nEndereco: %s\nCidade: %s\nEstado: %s\nCEP: %s\nTelefone: %s\n\n", 
                    registro.chave, registro.primeironome, registro.ultimonome, registro.endereco, registro.cidade, registro.estado, registro.cep, registro.telefone);
            }
            fclose(registros);
        } else if(i == 3) {
            
            printf("\nDigite o tipo de busca desejada:\n1) Chave\n2) Cidade\n");
            scanf("%d", &option);

            if(option == 1){
                do {
                    printf("\nInsira uma chave valida para o registro desejado: ");
                    scanf("%d", &i);

                        if (i >= qt_registros){
                            printf("\nCHAVE INVALIDA!!!\n");
                        }

<<<<<<< HEAD
                } while (i >= qt_registros);

                arquivo = fopen("registros.bin", "rb"); // acesso de leitura
                if(arquivo == NULL)
                    perror("Erro ao abrir registros.bin");
                else{
                    // Varredura do arquivo
                    fseek(arquivo, indice[i].posicao, SEEK_SET);
                    fread(&registro, sizeof registro, 1, arquivo);
                    printf("\n%s %s\n%s\n%s\n%s\n%s\n%s\n\n", registro.primeironome, registro.ultimonome, registro.endereco, registro.cidade, registro.estado, registro.cep, registro.telefone);
                }
                fclose(registros);

            } else if (option == 2){
                    char cidade_desejada[40];
                    printf("\nInsira a cidade desejada: ");
                    scanf("%s", cidade_desejada);

                    arquivo = fopen("registros.bin", "rb");
                    if(arquivo == NULL)
                    perror("Erro ao abrir registros.bin");
                else{
                    // Varredura do arquivo
                    fseek(arquivo, SEEK_SET, 0);
                    fread(&registro, sizeof registro, 1, arquivo);
                    //comparacao de strings;
                    printf("\n%s %s\n%s\n%s\n%s\n%s\n%s\n\n", registro.primeironome, registro.ultimonome, registro.endereco, registro.cidade, registro.estado, registro.cep, registro.telefone);
                }
                fclose(registros);
                    
=======
        } else if (option == 2){
                printf("\nInsira a cidade desejada: ");
               // scanf("%s", cidade_desejada);
>>>>>>> parent of e052790... Up 10/09


            }
        }

        if(i != 0)
            printf("\nDeseja voltar ao menu?\n1) Sim\n2)Não\n");
            scanf("%d", &i);
            if(i == 2){
                i = 0;
            }else{
                printf("--> MENU <--\n0) Sair\n1) Insere\n2) Listar todos\n3) Busca\nSelecione uma opcao: ");
                scanf("%d", &i);
            }
    }
    return 0;
}