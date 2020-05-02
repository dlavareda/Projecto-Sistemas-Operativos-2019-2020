//criação da estrutura do Gestor de processos
typedef struct Gestor
{
    int tempo;
    int RunningState; //indice do PCB do processo em execussao
    int PC;           //PC do processo em execução
    PCB *PCBtabela;   //apontador para o PCB
    int *Prontos;     //array de inteiros com os PID dos processos em execussao
    int prontos_size;
    int *Bloqueados; //array de inteiros com os PID dos processos bloqueados
    int bloqueados_size;

} Gestor;

//função irá incorporar o PCBtabela e inicializar os restantes campos
Gestor *inicializarGestor(PCB *PCBtabela, int PCB_size)
{
    Gestor *gest = malloc(sizeof(Gestor));
    gest->prontos_size = 0;
    gest->tempo = 0;
    gest->PC = 0;
    gest->PCBtabela = PCBtabela;
    gest->Prontos = malloc(PCB_size * sizeof(int));
    for (int i = 0; i < PCB_size; i++)
    {
        gest->Prontos[i] = PCBtabela[i].PID;
        gest->prontos_size++;
    }

    return gest;
}
//Função para executar o programa
void executarPrograma(Memory *RAM, int RAM_size, int PID, PCB *ProcessCB, int *PCB_size)
{
    int indicePCB = -1;
    int start = -1, end = -1;
    for (int i = 0; i < (*PCB_size); i++)
    {
        if (ProcessCB[i].PID == PID)
        {
            start = ProcessCB[i].start;
            indicePCB = i;
        }
        if (ProcessCB[i].PID != PID && ProcessCB[i - 1].PID == PID) //vai ao proximo programa, obtem o endereço de inicio dele e subtrai 1
        {
            end = (ProcessCB[i].start - 1);
        }
    }
    //para o caso de ser o ultimo processo em memoria
    if (end == -1)
    {
        end = RAM_size;
    }

    for (int i = start; i <= end; i++)
    {
        if (RAM[i].instrucao[0] == 77) //EXECUTAR O M
        {
            M(ProcessCB, (*PCB_size), PID, RAM[i].valor);
        }
        if (RAM[i].instrucao[0] == 65) //EXECUTAR O A
        {
            A(ProcessCB, (*PCB_size), PID, RAM[i].valor);
        }
        if (RAM[i].instrucao[0] == 83) //EXECUTAR O S
        {
            S(ProcessCB, (*PCB_size), PID, RAM[i].valor);
        }
        if (RAM[i].instrucao[0] == 67) //EXECUTAR O S
        {
            C(ProcessCB, PCB_size, PID, RAM[i].valor);
        }
        if (RAM[i].instrucao[0] == 84) //EXECUTAR O T
        {
            T(ProcessCB, PCB_size, PID);
        }
    }
}
