#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>

#define Normal "\x1B[0m"
#define Vermelho "\x1B[31m"
#define Verde "\x1B[32m"
#define Amarelo "\x1B[33m"

typedef struct MEMORIA
{
    int PID;
    char valor;  //dado
    char valor2; //dado2
    struct MEMORIA *nseg;
} Memoria;

Memoria *makenode()
{
    Memoria *nv;
    nv = (Memoria *)malloc(sizeof(Memoria));
    nv->PID = NULL;
    nv->valor = NULL;
    nv->valor2 = NULL;
    nv->nseg = NULL;
    return (nv);
}
Memoria *insertlast(Memoria *T, Memoria *nv)
{

    Memoria *aux = T;
    if (T == NULL)
    {
        return nv;
    }
    while (aux->nseg != NULL)
    {
        aux = aux->nseg;
    }
    aux->nseg = nv;
    return T;
}

//Contagem de elementos
int totalElementos(Memoria *L)
{
    int count = 0;
    while (L->nseg != NULL)
    {
        count++;
        L = L->nseg;
    }
    return count;
}

Memoria *initialize_mem(Memoria *RAM, int *sinal)
{
    Memoria *aux = RAM;
    int i;
    for (i = 0; i < 128; i++)
    {
        Memoria *nv = NULL;
        nv = makenode();
        RAM = insertlast(RAM, nv);
    }
    (*sinal) = totalElementos(RAM) + 1;
    if ((*sinal) == 128)
    {
        return RAM;
    }
}
Memoria *firstFit(Memoria *RAM, int process_id, int num_units, int *count)
{
    Memoria *start = RAM;
    Memoria *aux = NULL;
    int size_available = 0;
    while (RAM->nseg != NULL)
    {
        if (RAM->PID != NULL)
        {
            size_available = 0;
            (*count)++;
            RAM = RAM->nseg;
        }
        else
        {
            if (size_available == 0) //primeiro elemento da sequencia actual
            {
                aux = RAM;
            }
            size_available++;
            (*count)++;
            RAM = RAM->nseg;
            if (size_available == num_units)
            {
                for (int i = 0; i < num_units; i++)
                {
                    aux->PID = process_id;
                    aux = aux->nseg;
                }
                return start;
            }
        }
    }
    //Se chegar aqui retorna NULL
    return NULL;
}

//worstFit
Memoria *worstFit(Memoria *RAM, int process_id, int alocsize, int *count1)
{
    int maior = 0;
    int count = 0;
    Memoria *aux = RAM;
    Memoria *espacoMaior = NULL;
    while (RAM->nseg != NULL)
    {
        if (RAM->PID == NULL)
        {
            //guarda o primeiro elemento do intervalo
            if (aux == NULL)
            {
                aux = RAM;
            }
            count++;
        }
        else
        {
            if (count > maior)
            {
                maior = count;
                espacoMaior = aux;
                aux = NULL;
            }
        }
        (*count1)++;
        RAM = RAM->nseg;
    }
    (alocsize) = maior;

    return espacoMaior;
}

//bestFit
Memoria bestFit(Memoria *RAM, int alocsize)
{

    int anterior = 0;
    int count = 0;
    int menor = 0;
    Memoria *aux = RAM;
    Memoria *espacoMenor = NULL;
    while (RAM->nseg != NULL)
    {
        if (RAM->PID == NULL)
        {
            //guarda o primeiro elemento do intervalo
            if (aux == NULL)
            {
                aux = RAM;
            }
            count++;
        }
        else
        {
            if (count >= alocsize)
            {
                if (count < anterior)
                {
                    menor = count;
                    espacoMenor = aux;
                    aux = NULL;
                }
            }
        }
        RAM = RAM->nseg;
        anterior = count;
    }
    (alocsize) = menor;
    return *espacoMenor;
}

int alocate_mem(Memoria *RAM, int process_id, int num_units, int algoritmo) //1 = first fit, 2 = Worst fit, 3 = Best fit
{
    int count = 0;
    if (algoritmo == 1)
    {
        RAM = firstFit(RAM, process_id, num_units, &count);
    }else if(algoritmo == 2){
        RAM = worstFit(RAM, process_id, num_units, &count);
    }

    if (RAM == NULL)
    {
        return -1;
    }
    else
    {
        return count;
    }
}

Memoria *deallocate_mem(Memoria *RAM, int process_id, int *status, int *size)
{
    (*status) = -1;
    Memoria *AUX = RAM;
    while (RAM->nseg != NULL)
    {
        if (RAM->PID == process_id)
        {
            RAM->PID = NULL;
            RAM->valor = NULL;
            RAM->valor2 = NULL;
            (*status) = 1;
            (*size)++;
        }
        RAM = RAM->nseg;
    }
    if ((*status) != 1)
    {
        (*status) = -1;
    }

    return (AUX);
}

int fragment_count(Memoria *RAM)
{
    int count = 0;
    while (RAM->nseg != NULL)
    {
        if (RAM->PID == NULL)
        {
            count++;
        }
        RAM = RAM->nseg;
    }
    return count;
}

//Função para esperar x milisegundos, sleep do c apenas permite x segundos
//foi necessário adicionar o sleep devido ao rand dentro do loop dar numeros iguais devido ao time ser igual
//https://qnaplus.com/c-program-to-sleep-in-milliseconds/
int msleep(long tms)
{
    struct timespec ts;
    int ret;

    if (tms < 0)
    {
        errno = EINVAL;
        return -1;
    }

    ts.tv_sec = tms / 1000;
    ts.tv_nsec = (tms % 1000) * 1000000;

    do
    {
        ret = nanosleep(&ts, &ts);
    } while (ret && errno == EINTR);

    return ret;
}
int findPID(int PID[], int qntsimulacao, int valor)
{
    for (int i = 0; i < qntsimulacao; i++)
    {
        if (PID[i] == valor)
        {
            return 1;
        }
        return 0;
    }
}
void showMemory(Memoria *RAM)
{
    while (RAM->nseg != NULL)
    {
        if (RAM->PID != NULL)
        {
            printf("[%d]", RAM->PID);
        }
        else
        {
            printf("[ ]");
        }
        RAM = RAM->nseg;
    }
}
int main()
{
    float percent = 0;
    int RAMOcupada = 0;
    int qntsimulacao = 0;
    int size = 0;
    Memoria *RAM = NULL;
    int status = 0;
    RAM = initialize_mem(RAM, &status);
    if (status == 1)
    {
        printf("Inicializados 256KB de memoria com sucesso!\n");
    }
    printf("Qual a quantidade de pedidos de memoria deseja simular?\n");
    scanf("%d", &qntsimulacao);
    int algoritmo = 0;
    do
    {
        printf("Qual o algorimo de gestão de memoria?\n1 - First Fit\n2 - Worst Fit\n3 - Best Fit\n");
        scanf("%d", &algoritmo);
    } while (algoritmo < 1 || algoritmo > 3);
    int lowerQNT = 3, upperQNT = 10, qnt = 0, resp = 0, pid = 0, lowerPID = 1, upperPID = qntsimulacao;
    int *PID = malloc(qntsimulacao * sizeof(int));
    int pidcount = 0;
    for (int i = 0; i < qntsimulacao; i++)
    {
        PID[i] = -1;
    }

    for (int i = 0; i < qntsimulacao; i++)
    {
        msleep(800);
        srand(time(0));
        qnt = (rand() % (upperQNT - lowerQNT + 1)) + lowerQNT;
        //adicionado para evitar numeros iguais devido ao rand correr no mesmo segundo
        srand(time(0));
        do
        {
            pid = (rand() % (upperPID - lowerPID + 1)) + lowerPID;
        } while (findPID(PID, qntsimulacao, pid) == 1);

        pidcount++;
        PID[pidcount - 1] = pid;
        resp = alocate_mem(RAM, pid, qnt, algoritmo);
        if (algoritmo == 3)
        {
            return;
        }

        if (resp > 0)
        {
            RAMOcupada += qnt;
            printf("%sInicialização com sucesso %d elementos ao PID %d percorridos %d elementos!%s\n", Verde, qnt, pid, resp, Normal);
            percent = 100 * ((float)RAMOcupada / 128);
            printf("Ocupação RAM = %.2f%\n", percent);
            showMemory(RAM);
            printf("\n");
        }
        else if (resp == -1)
        {
            printf("%sFalha ao adicionar %d elementos ao PID %d percorridos sem memoria disponivel!%s\n", Vermelho, qnt, pid, Normal);
            percent = 100 * ((float)RAMOcupada / 128);
            printf("Ocupação RAM = %.2f%\n", percent);
        }
        //random dealocation
        srand(time(0));
        if ((rand() % (1 - 0 + 1)) == 1)
        {
            //dealocate random existing pid
            int elemento;
            srand(time(0));
            do
            {
                elemento = (rand() % (qntsimulacao));
                pid = PID[elemento];
            } while (pid == -1 && pid != 0);
            size = 0;
            RAM = deallocate_mem(RAM, pid, &status, &size);
            if (status == 1)
            {
                RAMOcupada -= size;
                printf("%sDealocação com sucesso de %d elementos do PID %d !%s\n", Amarelo, size, pid, Normal);
                percent = 100 * ((float)RAMOcupada / 128);
                printf("Ocupação RAM = %.2f%\n", percent);
                showMemory(RAM);
                printf("\n");
                PID[elemento] = -1;
            }
        }
    }
    printf("Existem %d furos", fragment_count(RAM));
}
