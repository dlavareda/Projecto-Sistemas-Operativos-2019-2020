#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>

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
Memoria *firstFree(Memoria *RAM, int *count)
{
    while (RAM->nseg != NULL)
    {
        if (RAM->PID != NULL)
        {
            RAM = RAM->nseg;
        }
        else
        {
            return RAM;
        }
        (*count)++;
    }
    return RAM;
}
int alocate_mem(Memoria *RAM, int process_id, int num_units)
{
    int count = 0;
    int alocado = 0;
    RAM = firstFree(RAM, &count);
    if (RAM == NULL)
    {
        return -1;
    }

    for (int i = 0; i < num_units; i++)
    {
        if (RAM == NULL)
        {
            return -1;
        }
        else if (RAM->PID != NULL)
        {
            return -1;
        }
        RAM->PID = process_id;
        RAM = RAM->nseg;
        count++;
        alocado++;
    }
    if (alocado == num_units)
    {
        return count;
    }
    else
    {
        return -1;
    }
}
Memoria *deallocate_mem(Memoria *RAM, int process_id, int *status)
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
int main()
{
    int qntsimulacao = 0;
    Memoria *RAM = NULL;
    int status = 0;
    RAM = initialize_mem(RAM, &status);
    if (status == 1)
    {
        printf("Inicializados 256KB de memoria com sucesso!\n");
    }
    printf("Qual a quantidade de pedidos de memoria deseja simular?\n");
    scanf("%d", &qntsimulacao);
    printf("Inicio da simulação de %d pedidos de memoria usando o first-fit\n", qntsimulacao);
    int lowerQNT = 3, upperQNT = 10, qnt = 0, resp = 0, pid = 0, lowerPID = 1, upperPID = 20000;
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
        do
        {
            srand(time(0));
            pid = (rand() % (upperPID - lowerPID + 1)) + lowerPID;
        } while (findPID(PID, qntsimulacao, pid) == 1);

        pidcount++;
        PID[pidcount - 1] = pid;
        resp = alocate_mem(RAM, pid, qnt);
        if (resp > 0)
        {
            printf("Inicialização com sucesso %d elementos ao PID %d percorridos %d elementos!\n", qnt, pid, resp);
        }
        else if (resp == -1)
        {
            printf("Falha ao adicionar %d elementos ao PID %d percorridos sem memoria disponivel!\n", qnt, pid);
        }
        //random dealocation
        srand(time(0));
        if ((rand() % (1 - 0 + 1)) == 1)
        {
            //dealocate random existing pid
            int elemento;
            do
            {
                srand(time(0));
                elemento = (rand() % (qntsimulacao + 1));
                pid = PID[elemento];
            } while (PID[elemento] == -1);
            RAM = deallocate_mem(RAM, pid, &status);
            if (status == 1)
            {
                printf("Dealocação com sucesso do PID %d !\n", pid);
                PID[elemento] = -1;
            }
        }
    }
    printf("Existem %d furos", fragment_count(RAM));
}