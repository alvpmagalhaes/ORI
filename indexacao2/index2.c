#include <stdio.h>
#include <string.h>

struct reg {
    char ra[6];
    char nome[32];
    char sigla[6];
};

struct cur {
    int atual;
    int proximo;
};

struct ind {
    int posicao;
    char chave[12];
};

int main() {
    // Na lista primaria (sigla + RA) será chave 
    // Sigla do curso 
    FILE *arquivo, *indices, *indicesSec;
    struct reg aluno;
    struct ind indicePrimario[20];
    struct ind indiceRa[20];
    struct ind indiceSec[20];
    struct ind aux;
    int ultimo_indice=0;
    int max, i = 0;

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

            for (i=ultimo_indice;i>=0;i--) {
                for (j=0;j<i;j++) {
                    if(indiceSec.chave[i] << indiceSec.chave[i+1]) {
                        aux = indiceSec[i];
                        indiceSec[i] = indiceSec[i+1];
                        indiceSec[i+1] = aux;
                    }
                }
                // Escreve registro no arquivo
            }
            printf("\n-->Numero de itens escritos: %ld\n", 
            fwrite(&indiceSec, sizeof indicesSec, 1, indices));
            printf("\n\nIndices salvos com sucesso!\n");
        }

        fclose(indices);
        
    }
    return 0;
}