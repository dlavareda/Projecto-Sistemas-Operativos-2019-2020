#include "linhaDeExecussao.c"
int ultimoProcesso(Processo *arr_processos) //Encontra a hora do ultimo processo a chegar
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

void FCFS(Processo *arr_processos) //First Come First Served
{
    printf("Linha de execussão dos processos usando o algoritmo de escalonamento FCFS\n");
    int actual = 0;
    for (int z = 0; z < ultimoProcesso(arr_processos); z++)
    {
        for (int i = 0; i < 10; i++) //percorre o array todo
        {
            if (arr_processos[i].tempo_chegada == actual)
            {
                for (int j = 0; j < arr_processos[i].tempo_burst; j++)
                {
                    barraProgressoAdicionarElemento(arr_processos[i].nome_processo, obterCor(arr_processos[i].nome_processo));
                }
                printf("%s->", Normal);
            }
        }
        actual++;
    }
    printf("%s[Fim da Execussão]", Normal);
}

void swap(Processo *xp, Processo *yp)
{
    Processo *aux;
    strcpy(aux->nome_processo, xp->nome_processo);
    aux->tempo_burst = xp->tempo_burst;
    aux->tempo_chegada = xp->tempo_chegada;
    strcpy(xp->nome_processo, yp->nome_processo);
    xp->tempo_burst = yp->tempo_burst;
    xp->tempo_chegada = yp->tempo_chegada;
    strcpy(yp->nome_processo, aux->nome_processo);
    yp->tempo_burst = aux->tempo_burst;
    yp->tempo_chegada = aux->tempo_chegada;
}

void bubbleSort(Processo *arr, int n)
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

void SJF(Processo *arr_processos) //Shortest-Job-First Não Preemptivo
{

    printf("Linha de execussão dos processos usando o algoritmo de escalonamento Shortest-Job-First (Não Preemptivo)\n");
    int actual = 0;
    for (int z = 0; z <= ultimoProcesso(arr_processos); z++) //Percorrer todos os segundos até ao segundo do ultimo processo a chegar
    {
        Processo *arr_tmp = malloc(0);
        int tamanho_arr_tmp = 0;
        for (int i = 0; i < 10; i++) //percorrer toda a lista de processos
        {
            if (arr_processos[i].tempo_chegada == z) //Verificar se o elemento actual chegou no momento z
            {
                //Caso sim, adicionar o elemento a um array temporario de processos que chegaram no momento z
                tamanho_arr_tmp++;
                arr_tmp = realloc(arr_tmp, tamanho_arr_tmp * sizeof(arr_tmp));
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
            for (int i = 0; i < arr_tmp[w].tempo_burst; i++)
            {
                barraProgressoAdicionarElemento(arr_tmp[w].nome_processo, obterCor(arr_tmp[w].nome_processo));
            }
            printf("%s->", Normal);
        }

        free(arr_tmp);
    }
    printf("%s[Fim da Execussão]", Normal);
}