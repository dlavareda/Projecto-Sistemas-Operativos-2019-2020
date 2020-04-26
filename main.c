#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Definição da estrutura PCB
typedef struct PCB
{
    char nome_processo[15];
    int start;
    int variavel;
    int PC;
    int PID;
    int PPID;
    int prioridade;
    int estado;
} PCB;

//Definição da estrutura memoria
typedef struct Memory
{
    char instrucao[1];
    int valor;
    char nome[15];
} Memory;

typedef struct plan
{
    char programa[15];
    int tempo_chegada;
} plan;
#include "carregamentoTMP.c"
#include "ficheiros.c"

//Função temporaria para preencher com dados dummy
void carregarDados(Memory *, int *);

//Função que lista os processos existentes no PCB
void mostrarPCB(PCB *ProcessCB, int PCB_size){
    for (int i = 0; i < PCB_size; i++)
    {
        printf("\n\nProcesso %d\n", i);
        printf("Nome %s\n", ProcessCB[i].nome_processo);
        printf("Inicio memoria %d\n", ProcessCB[i].start);
        printf("Variavel %d\n", ProcessCB[i].variavel);
        printf("Program Couter %d\n", ProcessCB[i].PC);
        printf("PID %d\n", ProcessCB[i].PID);
        printf("PPID %d\n", ProcessCB[i].PPID);
        printf("Prioridade %d\n", ProcessCB[i].prioridade);
        printf("Estado %d\n",ProcessCB[i].estado);
    }
}

int main()
{
    //Definição da memoria até 1000 instruções
    int RAM_size = 0; //variavel com o numero de slots de memoria ocupados
    Memory *RAM = malloc(1000 * sizeof(Memory));
    carregarDados(RAM, &RAM_size);

    //teste para ver se a array RAM esta a ser bem construido

    for (int i = 0; i < RAM_size; i++)
    {
        printf("%s - %d - %s\n", RAM[i].instrucao, RAM[i].valor, RAM[i].nome);
    }

    // Carregamento do plan.txt
    plan *plano = malloc(20 * sizeof(plan));
    int plano_size = 0; //variavel com o numero de programas recebidos no plan.txt
    plano_size = lerPlan(plano);

    //teste para ver se a array PLAN esta a ser bem construido
    for (int i = 0; i < plano_size; i++)
    {
        printf("%s - %d\n", plano[i].programa, plano[i].tempo_chegada);
    }
    PCB *ProcessCB = malloc(0);
    int PCB_size = 0;
    //inicialização do PCB
    for (int i = 0; i < plano_size; i++)
    {
        ProcessCB = realloc(ProcessCB, (i + 1) * sizeof(PCB));
        strcpy(ProcessCB[i].nome_processo, plano[i].programa);
        ProcessCB[i].start = 0;
        ProcessCB[i].variavel = 0;
        ProcessCB[i].PC = 0;
        ProcessCB[i].PID = i + 1;
        ProcessCB[i].PPID = 0;
        ProcessCB[i].prioridade = 0;
        ProcessCB[i].estado = 1;
    }
    PCB_size = plano_size;
    mostrarPCB(ProcessCB, PCB_size);

    return;
}
