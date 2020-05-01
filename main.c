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
#include "ficheiros.c"
#include "operacoes.c"
#include "execute.c"
//Função para ler novo processo
Memory *lerProcesso(char *, int *);
//Função para carregar o novo programa aos proximos lugares na memoria
void adicionarProgramaRAM(Memory *RAM, int *RAM_size, Memory *novoPrograma, int novoPrograma_size)
{

    for (int i = 0; i < novoPrograma_size; i++)
    {

        strcpy(RAM[*RAM_size].instrucao, novoPrograma[i].instrucao);
        RAM[*RAM_size].valor = novoPrograma[i].valor;
        strcpy(RAM[*RAM_size].nome, novoPrograma[i].nome);
        (*RAM_size)++;
    }
}

//Função que lista os processos existentes no PCB
void mostrarPCB(PCB *ProcessCB, int PCB_size)
{
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
        printf("Estado %d\n", ProcessCB[i].estado);
    }
}

void mostrarRAM(Memory *RAM, int RAM_size)
{
    for (int i = 0; i < RAM_size; i++)
    {
        printf("Instrução %c - Valor %d - Nome %s\n", RAM[i].instrucao[0], RAM[i].valor, RAM[i].nome);
    }
}

//cria o processo do escalonador
void inicializarPCB(PCB *ProcessCB, int *PCB_size)
{
    strcpy(ProcessCB[0].nome_processo, "escalonador");
    ProcessCB[0].start = 0;
    ProcessCB[0].variavel = 0;
    ProcessCB[0].PC = 0;
    ProcessCB[0].PID = 0;
    ProcessCB[0].PPID = 0;
    ProcessCB[0].prioridade = 0;
    ProcessCB[0].estado = 1;
    *PCB_size = 1;
}
int adicionarProcessoPCB(PCB *ProcessCB, int *PCB_size, char *nome[15], int primeiroElementoMemoria)
{
    int i = (*PCB_size);
    strcpy(ProcessCB[i].nome_processo, nome);
    ProcessCB[i].start = primeiroElementoMemoria;
    ProcessCB[i].variavel = 0;
    ProcessCB[i].PC = 0;
    ProcessCB[i].PID = (ProcessCB[i - 1].PID) + 1;
    ProcessCB[i].PPID = 0;
    ProcessCB[i].prioridade = 0;
    ProcessCB[i].estado = 1;
    (*PCB_size)++;
    return i;
}
int main()
{
    //Definição da memoria até 1000 instruções
    int RAM_size = 0; //variavel com o numero de slots de memoria ocupados
    Memory *RAM = malloc((1000 * sizeof(Memory)));
    //Definição da estrutura Plano
    plan *plano = malloc(20 * sizeof(plan));
    int plano_size = 0; //variavel com o numero de programas recebidos no plan.txt
    //Definição da estrutura PCB
    PCB *ProcessCB = malloc(100 * sizeof(PCB));
    int PCB_size = 0;

    ///////////////////////////////////////////////     Leitura do Plano    ///////////////////////////////////////////////
    //Faz a leitura do ficheiro plan.txt e adiciona a estrutura
    plano_size = lerPlan(plano);

    ////////////////////////////////////////     Inicialização do PCB    //////////////////////////////////////////////////

    //inicializar PCB
    inicializarPCB(ProcessCB, &PCB_size);

    ////////////////////////     Carregamento dos Programas do plano para RAM do Plano    //////////////////////////////////

    int novoProgramaSize = 0;
    int startPrograma = 0;
    Memory *novoPrograma;
    int novoPCB = 0;
    for (int i = 0; i < plano_size; i++)
    {
        startPrograma = (RAM_size);
        novoPrograma = lerProcesso(plano[i].programa, &novoProgramaSize);
        adicionarProgramaRAM(RAM, &RAM_size, novoPrograma, novoProgramaSize);
        //Adiciona o programa recem carregado ao PCB
        novoPCB = adicionarProcessoPCB(ProcessCB, &PCB_size, plano[i].programa, startPrograma);
        free(novoPrograma);
        novoProgramaSize = 0;
    }
    mostrarRAM(RAM, RAM_size);

    //mostrar PCB
    mostrarPCB(ProcessCB, PCB_size);
    ////////////////////////     Executar o programa.txt   //////////////////////////////////

    int PID = 1; //executar programa PID 1
    executarPrograma(RAM, RAM_size, PID, ProcessCB, &PCB_size);
    mostrarPCB(ProcessCB, PCB_size);

    return;
}
