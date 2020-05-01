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
void B(PCB *ProcessCB, int PCB_size, int PID)
{
    for (int i = 0; i < PCB_size; i++)
    {
        if (ProcessCB[i].PID == PID)
        {
            ProcessCB[i].estado = 2; //1 - Pronto 2-Blocked
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
            novoPCB = adicionarProcessoPCB(ProcessCB, (PCB_size), ProcessCB[i].nome_processo, ProcessCB[i].start);
            ProcessCB[novoPCB].estado = ProcessCB[i].estado;         //Filho mantem o estado ou seja Pronto
            ProcessCB[novoPCB].PC = ProcessCB[i].PC;                 //Filho executa a partir daqui
            ProcessCB[novoPCB].PPID = ProcessCB[i].PID;              //Adiciona o PID do Parent
            ProcessCB[novoPCB].prioridade = ProcessCB[i].prioridade; //mantém prioridade
            ProcessCB[novoPCB].variavel = ProcessCB[i].variavel;     //mantém variavel
            //aumentar valor no PCB do pai
            ProcessCB[i].PC += valor;
        }
    }
}
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
        L = (PCB *)realloc(L, (*N) * sizeof(PCB));
    }
    return L;
}
void T(PCB *ProcessCB, int *PCB_size, int PID)
{
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