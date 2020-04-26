#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Definição da estrutura PCB
typedef struct PCB
{
    char nome_processo[10];
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

typedef struct plano
{
    char programa[15];
    int tempo_chegada;
} plano;


int main()
{

}