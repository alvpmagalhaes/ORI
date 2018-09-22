#include <stdio.h>
#include <string.h>

struct reg {
    char ra[7];
    char nome[33];
    char sigla[7];
};

struct ind {
    int posicao;
    char chave[13];
};

int main() {
    FILE *arquivo, *indices, *indicesSec;
    struct reg aluno;
    struct ind indicePrimario[20];
    struct ind indiceRa[20];
    struct ind indiceSec[20];
    struct ind aux;
    int ultimo_indice=0;
    int max,j, i = 0;

    // Coleta a quantidade de alunos cadastrados
    indices = fopen("indices.bin", "rb");
    if(indices == NULL)
        perror("Erro ao abrir indices.bin");
    else {   
        // Varredura do arquivo
        while(fread(&indicePrimario[i], sizeof (struct ind), 1, indices) > 0)
            ultimo_indice++;
        }
        fclose(indices);

        printf("\nBem-vindo!\nNúmero total de alunos: %d\n", ultimo_indice);

    fclose(indices);

    printf("\n*********MENU*********\n\n1) Escrever\n2) Ler todos\n3) Ler um registro\n5) Sair\n\nSelecione uma opcao: ");
    scanf("%d", &i);

    while(i != 5){
        if (i == 1){
            arquivo = fopen("alunos.bin", "wb");
            if(arquivo == NULL)
                perror("Erro ao abrir alunos.bin");
            else {
                printf("\nInsira o numero de registro que deseja escrever: ");
                scanf("%d", &max);
                getchar();
                for (i=0;i<max;i++) {
                    // Coleta valores dos alunos
                    printf("RA: ");
                    scanf("%[^\n]s", aluno.ra);
                    getchar();
                    printf("Nome: ");
                    scanf("%[^\n]s", aluno.nome);
                    getchar();
                    printf("Sigla do curso: ");
                    scanf("%[^\n]s", aluno.sigla);
                    getchar();

                    // Escreve registro no arquivo
                    printf("\n-->Numero de itens escritos: %ld\n", 
                    fwrite(&aluno, sizeof aluno, 1, arquivo));
                    
                    // Salva indices dos alunos
                    indicePrimario[i].posicao = ultimo_indice + i;
                    strcat(indicePrimario[i].chave, aluno.sigla);
                    strcat(indicePrimario[i].chave, aluno.ra);
                }
                printf("\n\nAlunos salvos com sucesso!\n");

                fclose(arquivo);
                
                indices = fopen("indices.bin", "wb");
                if(indices == NULL)
                    perror("Erro ao abrir indices.bin");
                else {
                    fseek(indices, 1, SEEK_END);
                    for (i=0;i<max;i++) {
                        // Escreve registro no arquivo
                        printf("\n-->Numero de itens escritos: %ld\n", 
                        fwrite(&indicePrimario[i+ultimo_indice], sizeof (struct ind), 1, indices));
                        
                    }
                    printf("\n\nIndices salvos com sucesso!\n");
                }

                fclose(indices);

                indices = fopen("indicesSec.bin", "wb");
                if(indices == NULL)
                    perror("Erro ao abrir indicesSec.bin");
                else {
                    for (i=0; i<ultimo_indice; i++) {
                        indiceSec[i] = indicePrimario[i];
                    }

                    for (i=ultimo_indice;i>0;i--) {
                        for (j=0;j<i;j++) {
                            if(indiceSec[j].chave > indiceSec[j+1].chave) {
                                aux = indiceSec[i];
                                indiceSec[j] = indiceSec[j+1];
                                indiceSec[j+1] = aux;
                            }
                        }
                    }
                    printf("\n-->Numero de itens escritos: %ld\n", 
                    fwrite(&indiceSec, sizeof indicesSec, 1, indices));
                    printf("\n\nIndices salvos com sucesso!\n");
                }

                fclose(indices);
                
            }
        } else if(i == 2) {
            //Ler todos os registros
            arquivo = fopen("alunos.bin", "rb"); // acesso de leitura
            if(arquivo == NULL)
                perror("Erro ao abrir alunos.bin");
            else{
                // Varredura do arquivo
                while(fread(&aluno, sizeof aluno, 1, arquivo) > 0)
                    printf("\nRA: %s \nNome: %s \nSigla: %s\n", 
                    aluno.ra,
                    aluno.nome, 
                    aluno.sigla);
            }
            fclose(arquivo);
        }
        printf("\n*********MENU*********\n\n1) Escrever\n2) Ler todos\n3) Ler um registro\n5) Sair\n\nSelecione uma opcao: ");
        scanf("%d", &i);
    }    
    return 0;
}