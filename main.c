#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N_ELEMENTOS_FICHEIRO 10
#include "LerFicheiros.c"
#include "escalonadores.c"

Processo *carregarDados();
int main(int argc, char const *argv[])
{
    int numProcessoLidos = 0, resposta = 0;;
    Processo *arr_processos = carregarDados(&numProcessoLidos); //array de estruturas
 
    while (resposta != 9)
    {
        printf("Escolha o algoritmo de escalonamento?\n");
        printf("1 - FCFS\n");
        printf("2 - Shortest-Job-First (Não Preemptivo)\n");
        printf("9 - Sair\n");
        scanf("%d", &resposta);
        if (resposta == 1)
        {
            FCFS(arr_processos);
            printf("\nForam escalonados %d processos", numProcessoLidos);
            printf("\n");
        }
        else if (resposta == 2)
        {
            SJF(arr_processos);
            printf("\nForam escalonados %d processos", numProcessoLidos);
            printf("\n");
        }
    }
}