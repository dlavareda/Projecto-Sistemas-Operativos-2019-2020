#include "linhaDeExecussao.c"

int ultimoProcesso(PCB *arr_processos) //Encontra a hora do ultimo processo a chegar
{
    int ultimo = 0;
    for (int i = 0; i < 10; i++)
    {
        if (arr_processos[i].tempo_chegada > ultimo)
        {
            ultimo = arr_processos[i].tempo_chegada;
        }
    }
    return ultimo;
}

void FCFS(PCB *arr_processos, int arr_processos_size) //First Come First Served
{
    printf("Linha de execussão dos processos usando o algoritmo de escalonamento FCFS\n");
    int actual = 0;
    for (int z = 0; z <= ultimoProcesso(arr_processos); z++) //tempo
    {
        for (int i = 1; i < arr_processos_size; i++) //percorre o array todo execto o 0 - escalonador
        {
            if (arr_processos[i].tempo_chegada == actual)
            {
                barraProgressoAdicionarElemento(arr_processos[i].PID, obterCor(arr_processos[i].PID));
                printf("%s->", Normal);
            }
        }
        actual++;
    }
    printf("%s[Fim da Execussão]\n", Normal);
}

void swap(PCB *xp, PCB *yp)
{
    PCB *aux;
    strcpy(aux->nome_processo, xp->nome_processo);
    aux->PID = xp->PID;
    aux->tempo_burst = xp->tempo_burst;
    aux->tempo_chegada = xp->tempo_chegada;
    strcpy(xp->nome_processo, yp->nome_processo);
    xp->PID = yp->PID;
    xp->tempo_burst = yp->tempo_burst;
    xp->tempo_chegada = yp->tempo_chegada;
    strcpy(yp->nome_processo, aux->nome_processo);
    yp->PID = aux->PID;
    yp->tempo_burst = aux->tempo_burst;
    yp->tempo_chegada = aux->tempo_chegada;
}

void bubbleSort(PCB *arr, int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++)
    {
        // Last i elements are already in place
        for (j = 0; j < n - i - 1; j++)
        {
            if (arr[j].tempo_burst > arr[j + 1].tempo_burst)
            {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
    return;
}

void SJF(PCB *arr_processos, int arr_processos_size) //Shortest-Job-First Não Preemptivo
{

    printf("Linha de execussão dos processos usando o algoritmo de escalonamento Shortest-Job-First (Não Preemptivo)\n");
    int actual = 0;
    for (int z = 0; z <= ultimoProcesso(arr_processos); z++) //Percorrer todos os segundos até ao segundo do ultimo processo a chegar
    {
        PCB *arr_tmp = malloc(0);
        int tamanho_arr_tmp = 0;
        for (int i = 1; i < arr_processos_size; i++) //percorrer toda a lista de processos ignorar o 0 - escalonador
        {
            if (arr_processos[i].tempo_chegada == z) //Verificar se o elemento actual chegou no momento z
            {
                //Caso sim, adicionar o elemento a um array temporario de processos que chegaram no momento z
                tamanho_arr_tmp++;
                arr_tmp = realloc(arr_tmp, tamanho_arr_tmp * sizeof(PCB));
                arr_tmp[tamanho_arr_tmp - 1].PID = arr_processos[i].PID;
                strcpy(arr_tmp[tamanho_arr_tmp - 1].nome_processo, arr_processos[i].nome_processo);
                arr_tmp[tamanho_arr_tmp - 1].tempo_burst = arr_processos[i].tempo_burst;
                arr_tmp[tamanho_arr_tmp - 1].tempo_chegada = arr_processos[i].tempo_chegada;
            }
        }
        //ordenar o arr_tmp
        bubbleSort(arr_tmp, tamanho_arr_tmp);
        //percorrer o arr_tmp e chamar os prints
        for (int w = 0; w < tamanho_arr_tmp; w++)
        {
            barraProgressoAdicionarElemento(arr_tmp[w].PID, obterCor(arr_tmp[w].PID));
            printf("%s->", Normal);
        }

        free(arr_tmp);
    }
    printf("%s[Fim da Execussão]\n", Normal);
}