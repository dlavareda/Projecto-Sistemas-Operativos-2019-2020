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
typedef struct PCB  //process control block
{
    char nome_processo[15];
    int start; // posição na ram onde começa este programa
    int variavel; //o que o programa vai alterar na variável
    int PC; // ultima instrução que foi executada deste programa 
    int PID; // é geraddo quando se carrega
    int PPID; // do pai caso tenha filhos
    int prioridade;
    int estado; // 1 - pronto 2 - bloqueado 
    int tempo_chegada; //quando chega 
    int tempo_burst; //tamanho do programa, um programa que tem 10 introções ou 5 instruções etc
    int tempo_cpu; // quando estou a excetutar o programa, a cada instrução que ele executa ele acrescenta aqui o valor (tempo que o processo já gastou de cpu)
    //numero de intruções que ele já gastou ao cpu
} PCB;

//Definição da estrutura memoria
typedef struct Memory
{
    char instrucao[1];
    int valor;
    char nome[15];
} Memory;

typedef struct plan //ler o ficheiro.plan
{
    char programa[15];
    int tempo_chegada;
} plan;

//definição da estrutura control    //ler o controlo
typedef struct control 
{
    char programa[1];
} control;
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
    int *terminados; //array de inteiros com os PID dos processos terminados
    int terminados_size;
} Gestor;

#include "ficheiros.c"
#include "operacoes.c"
#include "execute.c"
#include "escalonadores.c"
#include "Report.c"
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
//Função para listar processos terminados no gestor
void mostrarProcessosTerminados(Gestor *gest)
{

    //Começa em 1 para ignorar o processo 0 escalonador
    for (int i = 1; i < gest->terminados_size; i++)
    {
        printf("Processo %d Terminado\n", gest->terminados[i]);
    }
}
void EscalonadorLPrazo(PCB *ProcessCB, int *PCB_size, Gestor *gest)
{
    //tem de alterar o estado no PCB
    for (int i = 0; i < PCB_size; i++)
    {
        ProcessCB[i].estado = 1; //1 pronto, 2 bloqueado
    }

    for (int i = 0; i < gest->bloqueados_size; i++)
    {
        //adiciona ao array Bloqueados
        gest->prontos_size++;
        gest->Prontos = (int *)realloc(gest->Prontos, gest->prontos_size * sizeof(int));
        gest->Prontos[gest->prontos_size - 1] = gest->Bloqueados[i];
        //remove do array Bloqueados
        gest->Bloqueados = RemoverBloqueados(gest->Bloqueados, i, &gest->bloqueados_size);
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
    //Criação da estrutura que recebe o control.txt
    control *controlo = malloc(0);
    int size_control = 0;
    //Definição da estrutura PCB
    PCB *ProcessCB = malloc(100 * sizeof(PCB));
    int PCB_size = 0;
    Gestor *gest;
    int resp = 0;
    int PID;
    while (resp != 6)
    {
        printf("1 - Executar CONTROL.TXT\n");
        printf("2 - Debugging\n");
        printf("3 - Mostrar readys\n");
        printf("4 - Mostrar bloqueados\n");
        printf("5 - Mostrar terminados\n");
        printf("6 - Sair\n");
        scanf("%d", &resp);
        if (resp == 1)
        {
            printf("Executando com o FCFS\n");
            /////////////////////////////////////////////// leitura do control.txt  ///////////////////////////////////////////////
            size_control = lerControl(controlo);
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

            ////////////////////////////////////////  Executa o FCFS ////////////////////////////////////////
            ProcessCB = FCFS(ProcessCB, PCB_size);
            //     mostrarPCB(ProcessCB, PCB_size);
            /////////////////////////////////////// Inicio da execussao ///////////////////////////////////////
            for (int i = 0; i < size_control; i++)
            {
                if (controlo[i].programa[0] == 69) //Caso seja E
                {
                    printf("\nExecução E\n");
                    executarPrograma(RAM, &RAM_size, ProcessCB[1].PID, ProcessCB, &PCB_size, &TIME, gest, TIME_QUANTUN);
                    //mostrarPCB(ProcessCB, PCB_size);
                    //mostrarProcessosBlocked(gest);
                }
                else if (controlo[i].programa[0] == 73) //Caso seja I
                {
                    printf("\nExecução I\n");
                    //reutilização da operação B para bloquear o processo em execussao
                    B(ProcessCB, &PCB_size, ProcessCB[1].PID, gest);
                    //mostrarProcessosBlocked(gest);
                }
                else if (controlo[i].programa[0] == 82) //Caso seja R
                {
                    R(TIME, ProcessCB, PCB_size, gest);
                }
                else if (controlo[i].programa[0] == 84) //Caso seja T
                {
                }
                else if (controlo[i].programa[0] == 68) //Caso seja D
                {
                    printf("\nExecução D\n");
                    EscalonadorLPrazo(ProcessCB, PCB_size, gest);
                }
            }
        }
        else if (resp == 2)
        {

            printf("Executando com o FCFS\n");
            /////////////////////////////////////////////// leitura do control.txt  ///////////////////////////////////////////////
            size_control = lerControl(controlo);
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

            ////////////////////////////////////////  Executa o FCFS ////////////////////////////////////////
            ProcessCB = FCFS(ProcessCB, PCB_size);
            //     mostrarPCB(ProcessCB, PCB_size);
            /////////////////////////////////////// Inicio da execussao ///////////////////////////////////////
            int len;
            char linha[1];
            char prompt[100];
            while (linha[0] != 84)
            {
                printf("SGP: Introduza um comando>");
                scanf("%s", linha);
                if (linha[0] == 69) //Caso seja E
                {
                    printf("\nExecução E\n");
                    executarPrograma(RAM, &RAM_size, ProcessCB[1].PID, ProcessCB, &PCB_size, &TIME, gest, TIME_QUANTUN);
                    //mostrarPCB(ProcessCB, PCB_size);
                    mostrarProcessosBlocked(gest);
                }
                else if (linha[0] == 73) //Caso seja I
                {
                    printf("\nExecução I\n");
                    //reutilização da operação B para bloquear o processo em execussao
                    B(ProcessCB, &PCB_size, ProcessCB[1].PID, gest);
                    mostrarProcessosBlocked(gest);
                }
                else if (linha[0] == 82) //Caso seja R
                {                 
                   R(TIME, ProcessCB, PCB_size, gest);
                }
                else if (linha[0] == 84) //Caso seja T
                {
                }
                else if (linha[0] == 68) //Caso seja D
                {
                    printf("\nExecução D\n");
                    EscalonadorLPrazo(ProcessCB, PCB_size, gest);
                }
            }
        }
        else if (resp == 3)
        {
            mostrarProcessosReady(gest);
        }
        else if (resp == 4)
        {
            mostrarProcessosBlocked(gest);
        }
        else if (resp == 5)
        {
            mostrarProcessosTerminados(gest);
        }
    }
    printf("Foram executadas %d operações\n", TIME);
    return 0;
}
