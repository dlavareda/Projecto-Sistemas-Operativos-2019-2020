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

void C(PCB *ProcessCB, int *PCB_size, int PID, int valor, Gestor *gest)
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
            //adiciona ao ready
            gest->prontos_size++;
            gest->Prontos = realloc(gest->Prontos, (gest->prontos_size * sizeof(int)));
            gest->Prontos[gest->prontos_size - 1] = ProcessCB[novoPCB].PID;
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
    }
    return L;
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
    L = (int *)realloc(L, (*N) * sizeof(int));
    return L;
}
void T(PCB *ProcessCB, int *PCB_size, int PID, Gestor *gest)
{
    //remover do PCB
    for (int i = 0; i < (*PCB_size); i++)
    {
        if (ProcessCB[i].PID == PID) //encontra o elemento
        {
            printf("PID %d - %s terminou a execussão valor = %d", PID,ProcessCB[i].nome_processo, ProcessCB[i].variavel);
            ProcessCB = Remover(ProcessCB[i], ProcessCB, PCB_size);
        }
    }
    //remover do ready
    int i = 0;
    while (gest->Prontos[i] != PID)
    { //encontra a posição no array prontos do PID
        i++;
    }
    gest->Prontos = RemoverProntos(gest->Prontos, i, &gest->prontos_size);
    //adicionar ao gest->teminados
    gest->terminados_size++;
    gest->terminados = realloc(gest->terminados, (gest->terminados_size * sizeof(int)));
    gest->terminados[gest->terminados_size - 1] = PID;
}
void L(PCB *ProcessCB, int *PCB_size, int PID, char *filho, Memory *RAM, int *RAM_size, int tempoactual, Gestor *gest)
{
    for (int i = 0; i < (*PCB_size); i++)
    {
        if (ProcessCB[i].PID == PID) //encontra o elemento
        {
            int novoProgramaSize = 0;
            Memory *novoPrograma;
            int startPrograma = (*RAM_size);
            novoPrograma = lerProcesso(filho, &novoProgramaSize);
            adicionarProgramaRAM(RAM, RAM_size, novoPrograma, novoProgramaSize);
            //Adiciona o programa recem carregado ao PCB
            int novoPCB = adicionarProcessoPCB(ProcessCB, PCB_size, filho, startPrograma, tempoactual, novoProgramaSize);
            ProcessCB[novoPCB].PPID = ProcessCB[i].PID;
            ProcessCB[novoPCB].PC = 0;
            //adiciona ao ready
            gest->prontos_size++;
            gest->Prontos = realloc(gest->Prontos, (gest->prontos_size * sizeof(int)));
            gest->Prontos[gest->prontos_size - 1] = ProcessCB[novoPCB].PID;
            free(novoPrograma);
            T(ProcessCB, PCB_size, PID, gest);
            (*PCB_size)++;
        }
    }
}

//função adaptada da UC Programação II
int *RemoverBloqueados(int *L, int pos, int *N)
{
    int i;
    for (i = pos; i < *N - 1; i++)
    {
        L[i] = L[i + 1];
    }
    *N = *N - 1;
    L = (int *)realloc(L, (*N) * sizeof(int));
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