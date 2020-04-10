#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//criação da estrutura
typedef struct Processo
{
    char nome_processo[10];
    int tempo_chegada;
    int tempo_burst;
} Processo;
Processo *carregarDados()
{
    FILE *file;

    Processo *arr_processos = malloc(sizeof(Processo) * 10);

    for (int i = 0; i < 10; i++) //inicialização a default
    {
        strcpy(arr_processos[i].nome_processo, "NULL");
        arr_processos[i].tempo_chegada = 0;
        arr_processos[i].tempo_burst = 0;
    }

    file = fopen("tabela.txt", "r"); //operações do ficheiro

    if (file == NULL)
    {
        printf("ERRO AO ABRIR O FICHEIRO!\n");
        exit(1);
    }
    else
    {
        printf("FICHEIRO ABERTO COM SUCESSO!\n\n");
    }

    char linha[10], *token;
    int i = 0;

    while (fgets(linha, 10, file) != NULL)
    { //vai ler o que está no file até ser diferente de NULL

        token = strtok(linha, " "); //vai dividir a string linha acima por espaços até ao espaço

        while (token != NULL) //executar até o token ser diferente do \n
        {
            int indice = 0;

            if (indice == 0)
            { //copia para nome do processo o primeiro corte
                strcpy(arr_processos[i].nome_processo, strdup(token));
                token = strtok(NULL, " ");
                indice++;
            }

            if (indice == 1)
            { //copia para tempo chegada a segunda parte do corte
                arr_processos[i].tempo_chegada = atoi(strdup(token));
                token = strtok(NULL, " ");
                indice++;
            }

            if (indice == 2)
            { //copia para tempo burst a terceira parte do corte
                arr_processos[i].tempo_burst = atoi(strdup(token));
                token = strtok(NULL, " ");
                indice = 0;
            }
        }
        i++;
    }

    /*for (int e = 0; e < 10; e++) // impressão do array de estruturas
    {
        printf("%s %d %d\n", arr_processos[e].nome_processo,
               arr_processos[e].tempo_chegada,
               arr_processos[e].tempo_burst);
    }*/

    fclose(file);
    return arr_processos;
}
void mostrarArray(Processo* arr_processos)
{
    for (int e = 0; e < 10; e++) // impressão do array de estruturas
    {
        printf("%s %d %d\n", arr_processos[e].nome_processo,
               arr_processos[e].tempo_chegada,
               arr_processos[e].tempo_burst);
    }
}