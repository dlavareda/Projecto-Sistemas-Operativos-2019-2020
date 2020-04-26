#include "processManager.h"
//Antigas dependencias para descomentar para o debuger do VSCODE

//#include "linhaDeExecussao.c"

//manippulação de listas

PCB *inserirLista(PCB *lista, PCB *elemento, int tamanho)
{
    lista = realloc(lista, tamanho * sizeof(PCB));
    lista[(tamanho)-1].estado = elemento->estado;
    strcpy(lista[(tamanho)-1].nome_processo, elemento->nome_processo);
    lista[(tamanho)-1].PC = elemento->PC;
    lista[(tamanho)-1].pid = elemento->pid;
    lista[(tamanho)-1].ppid = elemento->ppid;
    lista[(tamanho)-1].prioridade = elemento->prioridade;
    lista[(tamanho)-1].tempo_burst = elemento->tempo_burst;
    lista[(tamanho)-1].tempo_chegada = elemento->tempo_chegada;
    lista[(tamanho)-1].tempo_cpu = elemento->tempo_cpu;
    return lista;
}
PCB *removerLista(PCB *lista, PCB *elemento, int *tamanho)
{
}
PCB *limparLista(PCB *lista)
{
    free(lista);
    return NULL;
}

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

PCB *FCFS(PCB *arr_processos, int numProcessoLidos) //First Come First Served
{
    PCB *processos_ordenados = malloc(0 * sizeof(PCB));
    int processos_ordenados_index = 0;
    printf("Linha de execussão dos processos usando o algoritmo de escalonamento FCFS\n");
    int actual = 0;
    for (int z = 0; z <= ultimoProcesso(arr_processos); z++)
    {
        for (int i = 0; i < numProcessoLidos; i++) //percorre o array todo
        {
            if (arr_processos[i].tempo_chegada == actual)
            {
                for (int j = 0; j < arr_processos[i].tempo_burst; j++)
                {
                    //arr_processos[i].tempo_cpu++;
                    //copia para o novo array a devolver
                    processos_ordenados = realloc(processos_ordenados, (processos_ordenados_index + 1) * sizeof(PCB));
                    processos_ordenados[processos_ordenados_index].estado = arr_processos[i].estado;
                    strcpy(processos_ordenados[processos_ordenados_index].nome_processo, arr_processos[i].nome_processo);
                    processos_ordenados[processos_ordenados_index].PC = arr_processos[i].PC;
                    processos_ordenados[processos_ordenados_index].pid = arr_processos[i].pid;
                    processos_ordenados[processos_ordenados_index].ppid = arr_processos[i].ppid;
                    processos_ordenados[processos_ordenados_index].prioridade = arr_processos[i].prioridade;
                    processos_ordenados[processos_ordenados_index].tempo_burst = arr_processos[i].tempo_burst;
                    processos_ordenados[processos_ordenados_index].tempo_chegada = arr_processos[i].tempo_chegada;
                    processos_ordenados[processos_ordenados_index].tempo_cpu++;
                    processos_ordenados_index++;
                }
            }
        }
        actual++;
    }

    return processos_ordenados;
}

void swap(PCB *xp, PCB *yp)
{
    PCB *aux;
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

//Ordenação por tempo de burst

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
//Ordenação por tempo de chegada
void bubbleSortTempoChegada(PCB *temp, int n)
{
    PCB t;
    int i, j;
    for (i = 1; i < n; i++)
        for (j = 0; j < n - i; j++)
        {
            if (temp[j].tempo_chegada > temp[j + 1].tempo_chegada)
            {
                t = temp[j];
                temp[j] = temp[j + 1];
                temp[j + 1] = t;
            }
        }
}
void SJF(PCB *arr_processos, int numProcessoLidos) //Shortest-Job-First Não Preemptivo
{
    int actual = 0;
    printf("Linha de execussão dos processos usando o algoritmo de escalonamento Shortest-Job-First (Não Preemptivo)\n");
    for (int z = 0; z <= ultimoProcesso(arr_processos); z++) //Percorrer todos os segundos até ao segundo do ultimo processo a chegar
    {
        PCB *arr_tmp = malloc(0);
        int tamanho_arr_tmp = 0;
        for (int i = 0; i < numProcessoLidos; i++) //percorrer toda a lista de processos
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
        bubbleSortTempoChegada(arr_tmp, tamanho_arr_tmp);
        //percorrer o arr_tmp e chamar os prints
        for (int w = 0; w < tamanho_arr_tmp; w++)
        {
            for (int i = 0; i < arr_tmp[w].tempo_burst; i++)
            {
                arr_processos[i].tempo_cpu++;
                barraProgressoAdicionarElemento(arr_tmp[w].nome_processo, obterCor(arr_tmp[w].nome_processo));
            }
            printf("%s->", Normal);
        }

        free(arr_tmp);
    }
    printf("%s[Fim da Execussão]", Normal);
}






//Não é meu

//Priority Non Pre-emptive
void PRT_NP(PCB P[], int n)
{
    PCB temp[10];
    PCB t;
    int sumw = 0, sumt = 0;
    float avgwt = 0.0, avgta = 0.0;
    int i, j;
    int x = 0;

    for (i = 0; i < n; i++)
        temp[i] = P[i];

    bubbleSort(temp, n);

    for (i = 2; i < n; i++)
        for (j = 1; j < n - i + 1; j++)
        {
            if (temp[j].prioridade > temp[j + 1].prioridade)
            {
                t = temp[j];
                temp[j] = temp[j + 1];
                temp[j + 1] = t;
            }
        }

    printf("\n\n PROC.\tB.T.\tA.T.");
    for (i = 0; i < n; i++)
        printf("\n %s\t%d\t%d", temp[i].nome_processo, temp[i].tempo_burst, temp[i].tempo_chegada);

    sumw = temp[0].tempo_espera = 0;
    sumt = temp[0].tempo_chegada = temp[0].tempo_burst - temp[0].tempo_chegada;

    for (i = 1; i < n; i++)
    {
        temp[i].tempo_espera = (temp[i - 1].tempo_burst + temp[i - 1].tempo_chegada + temp[i - 1].tempo_espera) - temp[i].tempo_chegada;
        ;
        temp[i].tempo_chegada = (temp[i].tempo_espera + temp[i].tempo_burst);
        sumw += temp[i].tempo_espera;
        sumt += temp[i].tempo_chegada;
    }
    avgwt = (float)sumw / n;
    avgta = (float)sumt / n;
    printf("\n\n PROC.\tB.T.\tA.T.\tW.T\tT.A.T");
    for (i = 0; i < n; i++)
        printf("\n %s\t%d\t%d\t%d\t%d", temp[i].nome_processo, temp[i].tempo_burst, temp[i].tempo_chegada, temp[i].tempo_espera, temp[i].tempo_turnaround);

    printf("\n\n GANTT CHART\n ");
    for (i = 0; i < n; i++)
        printf("   %s   ", temp[i].nome_processo);
    printf("\n ");

    printf("0\t");
    for (i = 1; i <= n; i++)
    {
        x += temp[i - 1].tempo_burst;
        printf("%d      ", x);
    }
    printf("\n\n Average waiting time = %0.2f\n Average turn-around = %0.2f.", avgwt, avgta);
}

//Shortest Job First - Pre-emptive
void SJF_P(PCB P[],int n){
	int i,t_total=0,tcurr,b[10],min_at,j,x,min_bt;
	int sumw=0,sumt=0;
	float avgwt=0.0,avgta=0.0;
	PCB temp[10],t;

	for(i=0;i<n;i++){
		temp[i]=P[i];
		t_total+=P[i].tempo_burst;
	}

	bubbleSortTempoChegada(temp,n);

	for(i=0;i<n;i++)
		b[i] = temp[i].tempo_burst;

	i=j=0;
	printf("\n GANTT CHART\n\n %d %s",i,temp[i].nome_processo);
	for(tcurr=0;tcurr<t_total;tcurr++){

		if(b[i] > 0 && temp[i].tempo_chegada <= tcurr)
			b[i]--;

		if(i!=j)
			printf(" %d %s",tcurr,temp[i].nome_processo);

		if(b[i]<=0 && temp[i].flag != 1){
		
			temp[i].flag = 1;
			temp[i].tempo_espera = (tcurr+1) - temp[i].tempo_burst - temp[i].tempo_chegada;
			temp[i].tempo_chegada = (tcurr+1) - temp[i].tempo_chegada;
			sumw+=temp[i].tempo_espera;
			sumt+=temp[i].tempo_chegada;
		}
		j=i;	min_bt = 999;
		for(x=0;x<n;x++){
		
			if(temp[x].tempo_chegada <= (tcurr+1) && temp[x].flag != 1){
			
				if(min_bt != b[x] && min_bt > b[x]){
					min_bt = b[x];
					i=x;
				}
			}
		}
		
	}
	printf(" %d",tcurr);
	avgwt = (float)sumw/n;	avgta = (float)sumt/n;
	printf("\n\n Average waiting time = %0.2f\n Average turn-around = %0.2f.",avgwt,avgta);
}

