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
typedef struct PCB //process control block
{
    char nome_processo[15];
    int start;    // posição na ram onde começa este programa
    int variavel; //o que o programa vai alterar na variável
    int PC;       // ultima instrução que foi executada deste programa
    int PID;      // é geraddo quando se carrega
    int PPID;     // do pai caso tenha filhos
    int prioridade;
    int estado;        // 1 - pronto 2 - bloqueado
    int tempo_chegada; //quando chega
    int tempo_burst;   //tamanho do programa, um programa que tem 10 introções ou 5 instruções etc
    int tempo_cpu;     // quando estou a excetutar o programa, a cada instrução que ele executa ele acrescenta aqui o valor (tempo que o processo já gastou de cpu)
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

#define TIME_QUANTUN 5

//Função para ler novo processo
Memory *lerProcesso(char *, int *);

//criação da estrutura auxiliar
    typedef struct ProcessoAux
    {
        char campo1[1];
        char campo2[15];
    } ProcessoAux;


//Função para carregar o novo programa aos proximos lugares na memoria
void adicionarProgramaRAM(Memory *, int *, Memory *, int);

//Função que lista os processos existentes no PCB
void mostrarPCB(PCB *, int );

//mostra o conteudo da RAM
void mostrarRAM(Memory *, int );

//cria o processo do escalonador
void inicializarPCB(PCB *, int *);


int adicionarProcessoPCB(PCB *ProcessCB, int *PCB_size, char *nome[15], int primeiroElementoMemoria, int tempo_chegada, int tempo_burst);

//Função para listar processos prontos no gestor
void mostrarProcessosReady(Gestor *);

//Função para listar processos bloqueados no gestor
void mostrarProcessosBlocked(Gestor *);

//Move os processos blocked para a lista ready
void EscalonadorLPrazo(PCB *, int *, Gestor *);


//////////////////////////////////////////     escalonadores.c            //////////////////////////////////////////

//Encontra a hora do ultimo processo a chegar
int ultimoProcesso(PCB *);

//First Come First Served
PCB *FCFS(PCB *, int ); 

//troca 2 elementos PCB*
void swap(PCB *, PCB *);

//Ordena pelo tempo de burst para uso no SVF
void bubbleSort(PCB *, int );

//Shortest-Job-First Não Preemptivo
PCB *SJF(PCB *, int );

//////////////////////////////////////////     execute.c            //////////////////////////////////////////


//função irá incorporar o PCBtabela e inicializar os restantes campos
Gestor *inicializarGestor(PCB *, int );

//Função para executar o programa
void executarPrograma(Memory *, int *, int , PCB *, int *, int *, Gestor *, int );

//////////////////////////////////////////     ficheiros.c            //////////////////////////////////////////

Memory *lerProcesso(char *, int *);

int lerPlan(plan *);

int lerControl(control *);

//////////////////////////////////////////     operacoes.c            //////////////////////////////////////////


void M(PCB *, int , int , int );

void A(PCB *, int , int , int );

void S(PCB *, int , int , int );

void C(PCB *, int *, int , int , Gestor *);

void T(PCB *, int *, int , Gestor *);

void L(PCB *, int *, int , char *, Memory *, int *, int , Gestor *);

void B(PCB *, int *, int , Gestor *);

int PesquisaExaustiva(PCB , PCB *, int );

PCB *Remover(PCB , PCB *, int *);

int *RemoverProntos(int *, int , int *);

int *RemoverBloqueados(int *, int , int *);





