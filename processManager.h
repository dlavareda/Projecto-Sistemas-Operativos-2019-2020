#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N_ELEMENTOS_FICHEIRO 10
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

//Definição de estruturas
typedef struct PCB
{
    char nome_processo[10];
    int tempo_chegada;
    int tempo_burst;
    int pid;
    int ppid;
    int prioridade;
    int PC;
    int estado;
    int tempo_cpu;
} PCB;

//Definição das listas
/*typedef struct Processo* Pronto;
typedef struct Processo* Bloqueado;
typedef struct Processo* Terminado;*/

//LerFicheiros
PCB *carregarDados(int *);

//Escalonadores
int ultimoProcesso(PCB *);
void FCFS(PCB *);
void swap(PCB *, PCB *);
void bubbleSort(PCB *, int);
void SJF(PCB *);

//linhaDeExecussao
char *obterCor(char *);
void barraProgressoAdicionarElemento(char *, char *);

//Manipulação de listas
/*
Parece-me que basta uma função inserir, remover e limpar dado que as listas têm a mesma estrutura.
Mas caso nao dê ja tens aqui os 9 prototipos.
*/

/*
Basicamente inserir o elemento na lista e retornar a cabeça da lista
*/
PCB *inserirProntos(PCB *lista, PCB *elemento);
PCB *inserirTerminados(PCB *lista, PCB *elemento);
PCB *inserirBloqueados(PCB *lista, PCB *elemento);

/*
Basicamente remover o elemento na lista e retornar a cabeça da lista
*/
PCB *removerProntos(PCB *lista, PCB *elemento);
PCB *removerTerminados(PCB *lista, PCB *elemento);
PCB *removerBloqueados(PCB *lista, PCB *elemento);
/*
limpar todos os elementos da lista
*/
PCB *limparProntos(PCB *lista, PCB *elemento);
PCB *limparTerminados(PCB *lista, PCB *elemento);
PCB *limparBloqueados(PCB *lista, PCB *elemento);