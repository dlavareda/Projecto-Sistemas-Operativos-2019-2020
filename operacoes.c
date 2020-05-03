//Operação M
void M(PCB *ProcessCB, int PCB_size, int PID, int valor)
{
    for (int i = 0; i < PCB_size; i++)
    {
        if (ProcessCB[i].PID == PID)
        {
            ProcessCB[i].variavel = valor;
        }
    }
}
//Operação A
void A(PCB *ProcessCB, int PCB_size, int PID, int valor)
{
    for (int i = 0; i < PCB_size; i++)
    {
        if (ProcessCB[i].PID == PID)
        {
            ProcessCB[i].variavel += valor;
        }
    }
}
//Operação S
void S(PCB *ProcessCB, int PCB_size, int PID, int valor)
{
    for (int i = 0; i < PCB_size; i++)
    {
        if (ProcessCB[i].PID == PID)
        {
            ProcessCB[i].variavel -= valor;
        }
    }
}

void C(PCB *ProcessCB, int *PCB_size, int PID, int valor)
{

    int novoPCB = -1;
    for (int i = 0; i < (*PCB_size); i++)
    {
        if (ProcessCB[i].PID == PID) //encontra o elemento
        {
            //fazer copia desde PID no PCB
            novoPCB = adicionarProcessoPCB(ProcessCB, (PCB_size), ProcessCB[i].nome_processo, ProcessCB[i].start, ProcessCB[i].tempo_chegada, ProcessCB[i].tempo_burst);
            strcpy(ProcessCB[novoPCB].nome_processo, ProcessCB[i].nome_processo);
            ProcessCB[novoPCB].estado = ProcessCB[i].estado;         //Filho mantem o estado ou seja Pronto
            ProcessCB[novoPCB].PC = ProcessCB[i].PC;                 //Filho executa a partir daqui
            ProcessCB[novoPCB].PPID = ProcessCB[i].PID;              //Adiciona o PID do Parent
            ProcessCB[novoPCB].prioridade = ProcessCB[i].prioridade; //mantém prioridade
            ProcessCB[novoPCB].variavel = ProcessCB[i].variavel;     //mantém variavel
            ProcessCB[novoPCB].tempo_cpu = 0;
            ProcessCB[novoPCB].tempo_burst = ProcessCB[i].tempo_burst - ProcessCB[i].PC; //Total do tamanho - as linhas que ja foram executadas
            ProcessCB[novoPCB].start = ProcessCB[i].start;
            //ProcessCB[novoPCB].tempo_chegada //terá de ser o momento atual
            //aumentar valor no PCB do pai
            ProcessCB[i].PC += valor;
            char nome_processo[15];
        }
    }
}

//função adaptada da UC Programação II
int PesquisaExaustiva(PCB X, PCB *L, int N)
{
    int i;
    for (i = 0; i < N; i++)
    {
        if (X.PID == L[i].PID)
        {
            return i; //Existe no indice i
        }
    }
    return -1; //não existe
}

//função adaptada da UC Programação II
PCB *Remover(PCB X, PCB *L, int *N)
{
    int i, pos;
    pos = PesquisaExaustiva(X, L, *N);
    if (pos >= 0)
    { // X existe em L
        for (i = pos; i < *N - 1; i++)
        {
            L[i] = L[i + 1];
        }
        *N = *N - 1;
        printf("\nANTES(remove.c)Tamanho PCB %d\n", (*N));
        // L = (PCB *)realloc(L, (*N) * sizeof(PCB));
    }
    return L;
}
void T(PCB *ProcessCB, int *PCB_size, int PID)
{
    printf("\n(T.c)Tamanho PCB %d\n", (*PCB_size));

    //remover do PCB
    for (int i = 0; i < (*PCB_size); i++)
    {
        if (ProcessCB[i].PID == PID) //encontra o elemento
        {
            printf("PID %d terminou a execussão valor = %d", PID, ProcessCB[i].variavel);
            ProcessCB = Remover(ProcessCB[i], ProcessCB, PCB_size);
        }
    }
}
void L(PCB *ProcessCB, int *PCB_size, int PID, char *filho, Memory *RAM, int *RAM_size)
{
    for (int i = 0; i < (*PCB_size); i++)
    {
        if (ProcessCB[i].PID == PID) //encontra o elemento
        {
            int tempoactual = 10; // futuramente variavel global sobre qual o tempo atual
            int novoProgramaSize = 0;
            Memory *novoPrograma;
            int startPrograma = (*RAM_size);
            novoPrograma = lerProcesso(filho, &novoProgramaSize);
            adicionarProgramaRAM(RAM, RAM_size, novoPrograma, novoProgramaSize);
            //Adiciona o programa recem carregado ao PCB
            int novoPCB = adicionarProcessoPCB(ProcessCB, PCB_size, filho, startPrograma, tempoactual, novoProgramaSize);
            ProcessCB[novoPCB].PPID = ProcessCB[i].PID;
            ProcessCB[novoPCB].PC = 0;
            free(novoPrograma);
        }
    }
}
//função adaptada da UC Programação II
int *RemoverProntos(int *L, int pos, int *N)
{
    int i;
    for (i = pos; i < *N - 1; i++)
    {
        L[i] = L[i + 1];
    }
    *N = *N - 1;
    L = (PCB *)realloc(L, (*N) * sizeof(int));
    return L;
}

void B(PCB *ProcessCB, int *PCB_size, int PID, Gestor *gest)
{
    //tem de alterar o estado no PCB
    for (int i = 0; i < (*PCB_size); i++)
    {
        if (ProcessCB[i].PID == PID) //encontra o elemento
        {
            ProcessCB[i].estado = 2; //1 pronto, 2 bloqueado
        }
    }
    int i = 0;
    while (gest->Prontos[i] != PID)
    { //encontra a posição no array prontos do PID
        i++;
    }
    //remove do array Prontos
    gest->Prontos = RemoverProntos(gest->Prontos, i, &gest->prontos_size);
    //adiciona ao array Bloqueados
    gest->bloqueados_size++;
    gest->Bloqueados = (int *)realloc(gest->Bloqueados, gest->bloqueados_size * sizeof(int));
    gest->Bloqueados[gest->bloqueados_size - 1] = PID;

}