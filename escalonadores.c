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

PCB *FCFS(PCB *arr_processos, int arr_processos_size) //First Come First Served
{
    PCB *ordenado = malloc(arr_processos_size * sizeof(PCB)); //criação do array ordenado
    int w = 1;
    printf("Linha de execussão dos processos usando o algoritmo de escalonamento FCFS\n");
    int actual = 0;
    //para nao mexer no PID 0 Escalonador
    strcpy(ordenado[0].nome_processo, arr_processos[0].nome_processo);
    ordenado[0].start = arr_processos[0].start;
    ordenado[0].variavel = arr_processos[0].variavel;
    ordenado[0].PC = arr_processos[0].PC;
    ordenado[0].PID = arr_processos[0].PID;
    ordenado[0].PPID = arr_processos[0].PPID;
    ordenado[0].prioridade = arr_processos[0].prioridade;
    ordenado[0].estado = arr_processos[0].estado;
    ordenado[0].tempo_chegada = arr_processos[0].tempo_chegada;
    ordenado[0].tempo_burst = arr_processos[0].tempo_burst;
    ordenado[0].tempo_cpu = arr_processos[0].tempo_cpu;
    for (int z = 0; z <= ultimoProcesso(arr_processos); z++) //tempo
    {
        for (int i = 1; i < arr_processos_size; i++) //percorre o array todo execto o 0 - escalonador
        {
            if (arr_processos[i].tempo_chegada == actual)
            {
                strcpy(ordenado[w].nome_processo, arr_processos[i].nome_processo);
                ordenado[w].start = arr_processos[i].start;
                ordenado[w].variavel = arr_processos[i].variavel;
                ordenado[w].PC = arr_processos[i].PC;
                ordenado[w].PID = arr_processos[i].PID;
                ordenado[w].PPID = arr_processos[i].PPID;
                ordenado[w].prioridade = arr_processos[i].prioridade;
                ordenado[w].estado = arr_processos[i].estado;
                ordenado[w].tempo_chegada = arr_processos[i].tempo_chegada;
                ordenado[w].tempo_burst = arr_processos[i].tempo_burst;
                ordenado[w].tempo_cpu = arr_processos[i].tempo_cpu;
                //barraProgressoAdicionarElemento(arr_processos[i].PID, obterCor(arr_processos[i].PID));
                // printf("%s->", Normal);
                w++;
            }
        }
        actual++;
    }
    //printf("%s[Fim da Execussão]\n", Normal);
    return ordenado;
}

void swap(PCB *xp, PCB *yp)
{
    PCB *aux = malloc(sizeof(PCB));
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
    free(aux);
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

PCB *SJF(PCB *arr_processos, int arr_processos_size) //Shortest-Job-First Não Preemptivo
{

    //printf("Linha de execussão dos processos usando o algoritmo de escalonamento Shortest-Job-First (Não Preemptivo)\n");
    PCB *ordenado = malloc(arr_processos_size * sizeof(PCB));
    //para nao mexer no PID 0 Escalonador
    strcpy(ordenado[0].nome_processo, arr_processos[0].nome_processo);
    ordenado[0].start = arr_processos[0].start;
    ordenado[0].variavel = arr_processos[0].variavel;
    ordenado[0].PC = arr_processos[0].PC;
    ordenado[0].PID = arr_processos[0].PID;
    ordenado[0].PPID = arr_processos[0].PPID;
    ordenado[0].prioridade = arr_processos[0].prioridade;
    ordenado[0].estado = arr_processos[0].estado;
    ordenado[0].tempo_chegada = arr_processos[0].tempo_chegada;
    ordenado[0].tempo_burst = arr_processos[0].tempo_burst;
    ordenado[0].tempo_cpu = arr_processos[0].tempo_cpu;
    int w = 1;
    for (int z = 0; z <= ultimoProcesso(arr_processos); z++) //Percorrer todos os segundos até ao segundo do ultimo processo a chegar
    {

        for (int i = 1; i < arr_processos_size; i++) //percorrer toda a lista de processos ignorar o 0 - escalonador
        {
            if (arr_processos[i].tempo_chegada == z) //Verificar se o elemento actual chegou no momento z
            {
                //Caso sim, adicionar o elemento a um array temporario de processos que chegaram no momento z
                strcpy(ordenado[w].nome_processo, arr_processos[i].nome_processo);
                ordenado[w].start = arr_processos[i].start;
                ordenado[w].variavel = arr_processos[i].variavel;
                ordenado[w].PC = arr_processos[i].PC;
                ordenado[w].PID = arr_processos[i].PID;
                ordenado[w].PPID = arr_processos[i].PPID;
                ordenado[w].prioridade = arr_processos[i].prioridade;
                ordenado[w].estado = arr_processos[i].estado;
                ordenado[w].tempo_chegada = arr_processos[i].tempo_chegada;
                ordenado[w].tempo_burst = arr_processos[i].tempo_burst;
                ordenado[w].tempo_cpu = arr_processos[i].tempo_cpu;
                w++;
            }
        }
        //ordenar o arr_tmp
        bubbleSort(ordenado, w);
    }
    //percorrer o arr_tmp e chamar os prints
    for (int p = 0; p < w; p++)
    {
        barraProgressoAdicionarElemento(ordenado[p].PID, obterCor(ordenado[p].PID));
        printf("%s->", Normal);
    }
    // printf("%s[Fim da Execussão]\n", Normal);
    return ordenado;
}