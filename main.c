#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Ficheiros.c"
#include "escalonadores.c"

Processo *carregarDados();
int main(int argc, char const *argv[])
{
    Processo *arr_processos; //array de estruturas
    arr_processos = carregarDados();
    //mostrarArray(arr_processos);
    //test_print();
    //return 0;

    int resposta = 0;
    while (resposta != 9)
    {
        printf("Escolha o algoritmo de escalonamento?\n");
        printf("1 - FCFS\n");
        printf("2 - Shortest-Job-First (Não Preemptivo)\n");
        printf("9 - Sair\n");
        scanf("%d", &resposta);
        if(resposta == 1){
            FCFS(arr_processos);
            printf("\n");
        }else if(resposta == 2){
            SJF(arr_processos);
            printf("\n");
        }
        
    }
}