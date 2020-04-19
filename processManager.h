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
typedef struct Processo
{
    char nome_processo[10];
    int tempo_chegada;
    int tempo_burst;
    int pid;
    int prioridade;
    int PC;
    int estado;
} Processo;

//Definição das listas
/*typedef struct Processo* Pronto;
typedef struct Processo* Bloqueado;
typedef struct Processo* Terminado;*/

//LerFicheiros
Processo *carregarDados(int *);

//Escalonadores
int ultimoProcesso(Processo *);
void FCFS(Processo *);
void swap(Processo *, Processo *);
void bubbleSort(Processo *, int);
void SJF(Processo *);

//linhaDeExecussao
char *obterCor(char *);
void barraProgressoAdicionarElemento(char *, char *);