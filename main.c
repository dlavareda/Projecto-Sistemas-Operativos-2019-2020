#include "processManager.h"

//Antigas dependencias para descomentar para o debuger do VSCODE
/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LerFicheiros.c"
#include "escalonadores.c"*/

Processo *carregarDados();
int main(int argc, char const *argv[])
{
    int numProcessoLidos = 0, resposta = 0;
    Processo *Pronto = carregarDados(&numProcessoLidos); //array de estruturas

    while (resposta != 9)
    {
        printf("Escolha o algoritmo de escalonamento?\n");
        printf("0 - Mostrar Ready Queue\n");
        printf("1 - FCFS\n");
        printf("2 - Shortest-Job-First (Não Preemptivo)\n");
        printf("9 - Sair\n");
        scanf("%d", &resposta);
        if (resposta == 0)
        {
            for (int i = 0; i < numProcessoLidos; i++)
            {
                printf("nome_processo %s - tempo_chegada %d - tempo_burst %d - pid %d - prioridade %d - PC %d - estado %d\n", Pronto[i].nome_processo, 
                Pronto[i].tempo_chegada, Pronto[i].tempo_burst, Pronto[i].pid, Pronto[i].prioridade, Pronto[i].PC,Pronto[i].estado);
            }

            printf("\n");
        }
        else if (resposta == 1)
        {
            FCFS(Pronto);
            printf("\nForam escalonados %d processos", numProcessoLidos);
            printf("\n");
        }
        else if (resposta == 2)
        {
            SJF(Pronto);
            printf("\nForam escalonados %d processos", numProcessoLidos);
            printf("\n");
        }
    }
}