#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//definição da palete de cores
#define Normal "\x1B[0m"
#define Vermelho "\x1B[31m"
#define Verde "\x1B[32m"
#define Amarelo "\x1B[33m"
#define Azul "\x1B[34m"
#define Magenta "\x1B[35m"
#define Ciano "\x1B[36m"
#define CinzaClaro "\x1b[90m"
#define VermelhoClaro "\x1b[91m"
#define VerdeClaro "\x1b[92m"
#define AmareloClaro "\x1b[93m"
#define AzulClaro "\x1b[94m"
#define MagentaClaro "\x1b[95m"
#define CianoClaro "\x1b[96m"
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
    int tempo_chegada;
    int tempo_burst;
    int tempo_cpu;
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
//criação da estrutura do Gestor de processos
typedef struct Gestor
{
    int tempo;
    int RunningState; //indice do PCB do processo em execussao
    int PC;           //PC do processo em execução
    PCB *PCBtabela;   //apontador para o PCB
    int *Prontos;     //array de inteiros com os PID dos processos em execussao
    int prontos_size;
    int *Bloqueados; //array de inteiros com os PID dos processos bloqueados
    int bloqueados_size;

} Gestor;

#include "ficheiros.c"
#include "operacoes.c"
#include "execute.c"
#include "escalonadores.c"
#define TIME_QUANTUN 5

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
        printf("Tempo chegada %d\n", ProcessCB[i].tempo_chegada);
        printf("Tempo burst %d\n", ProcessCB[i].tempo_burst);
        printf("Tempo CPU %d\n", ProcessCB[i].tempo_cpu);
    }
}

//mostra o conteudo da RAM
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
    ProcessCB[0].tempo_chegada = 0;
    ProcessCB[0].tempo_burst = 0;
    ProcessCB[0].tempo_cpu = 0;
}
int adicionarProcessoPCB(PCB *ProcessCB, int *PCB_size, char *nome[15], int primeiroElementoMemoria, int tempo_chegada, int tempo_burst)
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
    ProcessCB[i].tempo_chegada = tempo_chegada;
    ProcessCB[i].tempo_burst = tempo_burst;
    ProcessCB[i].tempo_cpu = 0;
    (*PCB_size)++;
    return i;
}
//Função para listar processos prontos no gestor
void mostrarProcessosReady(Gestor *gest)
{
    //Começa em 1 para ignorar o processo 0 escalonador
    for (int i = 1; i < gest->prontos_size; i++)
    {
        printf("Processo %d Ready\n", gest->Prontos[i]);
    }
}
//Função para listar processos bloqueados no gestor

void mostrarProcessosBlocked(Gestor *gest)
{
    //Começa em 1 para ignorar o processo 0 escalonador
    for (int i = 0; i < gest->bloqueados_size; i++)
    {
        printf("Processo %d Blocked\n", gest->Bloqueados[i]);
    }
}
int main()
{
    int TIME = 0;
    //Definição da memoria até 1000 instruções
    int RAM_size = 0; //variavel com o numero de slots de memoria ocupados
    Memory *RAM = malloc((1000 * sizeof(Memory)));
    //Definição da estrutura Plano
    plan *plano = malloc(20 * sizeof(plan));
    int plano_size = 0; //variavel com o numero de programas recebidos no plan.txt
    //Definição da estrutura PCB
    PCB *ProcessCB = malloc(100 * sizeof(PCB));
    int PCB_size = 0;
    Gestor *gest;
    int resp = 0;
    int PID;
    while (resp != 3)
    {
        printf("1 - Executar PLAN\n");
        printf("2 - Debugging\n");
        printf("3 - Sair\n");
        scanf("%d", &resp);
        if (resp == 1)
        {
        }
        else if (resp == 2)
        {
            resp = 0;
            while (resp != 9)
            {
                printf("1 - Carregar Dados\n");
                printf("2 - Mostrar RAM\n");
                printf("3 - Mostrar PCB\n");
                printf("4 - Executar programa\n");
                printf("5 - Executar escalonador de curto prazo FCFS\n");
                printf("6 - Executar escalonador de curto prazo SJF (Ainda nao operacional)\n");
                printf("7 - Mostrar Processos Ready\n");
                printf("8 - Mostrar Processos Bloqueados\n");
                printf("9 - Sair\n");
                scanf("%d", &resp);
                if (resp == 1)
                {
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
                        novoPCB = adicionarProcessoPCB(ProcessCB, &PCB_size, plano[i].programa, startPrograma, plano[i].tempo_chegada, novoProgramaSize);
                        free(novoPrograma);
                        novoProgramaSize = 0;
                    }

                    ////////////////////////////////////////     Inicialização do Gestor    //////////////////////////////////////////////////
                    gest = inicializarGestor(ProcessCB, PCB_size);
                }
                else if (resp == 2)
                {
                    mostrarRAM(RAM, RAM_size);
                }
                else if (resp == 3)
                {
                    mostrarPCB(ProcessCB, PCB_size);
                }
                else if (resp == 4)
                {
                    int N_instrucoes = 0;
                    printf("Insira o PID do programa a executar\n");
                    scanf("%d", &PID);
                    printf("Insira o numero de instruções a executar\n");
                    scanf("%d", &N_instrucoes);
                    executarPrograma(RAM, &RAM_size, PID, ProcessCB, &PCB_size, &TIME, gest, N_instrucoes);
                    printf("\n");
                }
                else if (resp == 5)
                {
                    ProcessCB = FCFS(ProcessCB, PCB_size);
                    mostrarPCB(ProcessCB, PCB_size);
                }
                else if (resp == 6)
                {
                    ProcessCB = SJF(ProcessCB, PCB_size);
                    mostrarPCB(ProcessCB, PCB_size);
                }
                else if (resp == 7)
                {
                    mostrarProcessosReady(gest);
                }
                else if (resp == 8)
                {
                    mostrarProcessosBlocked(gest);
                }
            }
        }
    }

    printf("Foram executadas %d operações\n", TIME);
    return;
}
