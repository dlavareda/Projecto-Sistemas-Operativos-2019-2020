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