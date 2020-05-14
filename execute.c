//função irá incorporar o PCBtabela e inicializar os restantes campos
Gestor *inicializarGestor(PCB *PCBtabela, int PCB_size)
{
    Gestor *gest = malloc(sizeof(Gestor));
    gest->bloqueados_size = 0;
    gest->prontos_size = 0;
    gest->Bloqueados = malloc(0);
    gest->tempo = 0;
    gest->PC = 0;
    gest->PCBtabela = PCBtabela;
    gest->Prontos = malloc(PCB_size * sizeof(int));
    gest->terminados_size = 0;
    gest->terminados = malloc(0);
    for (int i = 0; i < PCB_size; i++)
    {
        gest->Prontos[i] = PCBtabela[i].PID;
        gest->prontos_size++;
    }

    return gest;
}
//Função para executar o programa
void executarPrograma(Memory *RAM, int *RAM_size, int PID, PCB *ProcessCB, int *PCB_size, int *TIME, Gestor *gest, int N_instrucoes)
{

    int indicePCB = -1;
    int start = -1, end = -1;
    for (int i = 0; i < (*PCB_size); i++)
    {

        if (ProcessCB[i].PID == PID)
        {
            start = ProcessCB[i].start + ProcessCB[i].PC; //retomar execussão anteriormente parada
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
        end = *RAM_size;
    }
    //start += ProcessCB[indicePCB].PC;
    for (int i = start; i <= end; i++)
    {
        if (i < (start + N_instrucoes))
        {
            //Nao executar um processo bloqueado
            if (ProcessCB[indicePCB].estado == 2)
            {
                //printf("Nao pode executar um processo bloqueado\n");
                return;
            }
            if (RAM[i].instrucao[0] == 77) //EXECUTAR O M
            {
                (*TIME)++;
                ProcessCB[indicePCB].PC++;
                ProcessCB[indicePCB].tempo_cpu++;
                M(ProcessCB, (*PCB_size), PID, RAM[i].valor);
            }
            if (RAM[i].instrucao[0] == 65) //EXECUTAR O A
            {
                (*TIME)++;
                ProcessCB[indicePCB].PC++;
                ProcessCB[indicePCB].tempo_cpu++;
                A(ProcessCB, (*PCB_size), PID, RAM[i].valor);
            }
            if (RAM[i].instrucao[0] == 83) //EXECUTAR O S
            {
                (*TIME)++;
                ProcessCB[indicePCB].PC++;
                ProcessCB[indicePCB].tempo_cpu++;
                S(ProcessCB, (*PCB_size), PID, RAM[i].valor);
            }
            if (RAM[i].instrucao[0] == 67) //EXECUTAR O C
            {
                (*TIME)++;
                ProcessCB[indicePCB].PC++;
                ProcessCB[indicePCB].tempo_cpu++;
                C(ProcessCB, PCB_size, PID, (RAM[i].valor - 1), gest); //valor -1 pois um ja foi incrementado acima
            }
            if (RAM[i].instrucao[0] == 84) //EXECUTAR O T
            {
                (*TIME)++;
                ProcessCB[indicePCB].PC++;
                ProcessCB[indicePCB].tempo_cpu++;
                T(ProcessCB, PCB_size, PID, gest);
             /*   int i = 0;
                while (gest->Prontos[i] != PID)
                { //encontra a posição no array prontos do PID
                    i++;
                }
                //remove do array Prontos
                gest->Prontos = RemoverProntos(gest->Prontos, i, &gest->prontos_size);*/
            }
            if (RAM[i].instrucao[0] == 76) //EXECUTAR O L
            {
                (*TIME)++;
                ProcessCB[indicePCB].PC++;
                ProcessCB[indicePCB].tempo_cpu++;
                L(ProcessCB, PCB_size, PID, RAM[i].nome, RAM, RAM_size, *TIME, gest);
            }
            if (RAM[i].instrucao[0] == 66) //EXECUTAR O B
            {
                (*TIME)++;
                ProcessCB[indicePCB].PC++;
                ProcessCB[indicePCB].tempo_cpu++;
                B(ProcessCB, PCB_size, PID, gest);
                return;
            }
        }
        else
        {
            //  printf("Executadas 5 instruções, valor actual = %d\n", ProcessCB[indicePCB].variavel);
            return; //Ja executou o numero de instruções indicada
        }
    }
}
