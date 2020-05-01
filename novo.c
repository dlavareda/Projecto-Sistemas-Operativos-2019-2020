#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    FILE *file;
    char linha[10], *token;
    int i = 0, numero_processos = 0;

    //criação da 1º estrutura
    typedef struct Processo
    {
        char nome_processo[10];
        char tempo_chegada[10];
    }Processo;
    
    file = fopen("tabela.txt", "r");//operações do ficheiro

    if (file == NULL)
    {
        printf("ERRO AO ABRIR O FICHEIRO!\n");
        exit(1);
    }else
    {
        printf("FICHEIRO ABERTO COM SUCESSO!\n\n");
    }

    //contar linhas de processos 
    while(fgets(linha, 10, file) != NULL){
        numero_processos++;
    }

    rewind (file);//ponteiro volta para o início do ficheiro
    
    Processo arr_processos[numero_processos];//array de estruturas
    
    for (int i = 0; i < numero_processos; i++)//inicialização a default
    {
        strcpy(arr_processos[i].nome_processo, "NULL");
        strcpy(arr_processos[i].tempo_chegada, "NULL");
    }

    while(fgets(linha, 10, file) != NULL){//vai ler o que está no file até ser diferente de NULL
                        
        token = strtok(linha, " ");//vai dividir a string linha acima por espaços até ao espaço
        
        while (token != NULL)//executar até o token ser diferente do \n
        {
            int indice = 0;

            if(indice == 0){ //copia para nome do processo o primeiro corte
                strcpy(arr_processos[i].nome_processo, strdup(token));
                token = strtok(NULL, " ");
                indice++;
            }

            if(indice == 1){//copia para tempo chegada a segunda parte do corte
                strcpy(arr_processos[i].tempo_chegada, strdup(token));o
                token = strtok(NULL, " ");
                indice = 0;
            }
        }
        i++;
    }
    
    //Gravar na outra estrutura e fazer os ifs
    for (int e = 0; e < i; e++)    // impressão do array de estruturas
    {
        printf("%s %s", arr_processos[e].nome_processo, 
        arr_processos[e].tempo_chegada); 
    }
    
    printf("\nLeu %d processos.\n", numero_processos);
    fclose(file);
    return 0;
}
