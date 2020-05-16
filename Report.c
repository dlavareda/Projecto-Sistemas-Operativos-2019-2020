
void R(int TIME, PCB *ProcessCB, int PCB_size, Gestor *gest)
{ //onde vou buscar os processos em execução

    printf("TEMPO ATUAL: %d\n", TIME);

    for (int i = 0; i < PCB_size; i++)
    {
        if (gest->RunningState == ProcessCB[i].PID && ProcessCB[i].estado == 1)
        { //verificar o processo em execução
            printf("%s- PROCESSO EM EXECUÇÃO:%s\n", Azul, Normal);
            printf("Nome do processo: %s\n", ProcessCB[i].nome_processo);
            printf("PID: %d\n", ProcessCB[i].PID);
            printf("PPID: %d\n", ProcessCB[i].PPID);
            printf("Valor da variável: %d\n", ProcessCB[i].variavel);
            printf("PC: %d\n", ProcessCB[i].PC);
            printf("ESTADO: %d\n", ProcessCB[i].estado);
            printf("Prioridade: %d\n", ProcessCB[i].prioridade);
            printf("Tempo de inicio: %d\n", ProcessCB[i].tempo_chegada);
            printf("Número de instruções: %d\n", ProcessCB[i].tempo_burst);
            printf("Tempo do CPU: %d\n", ProcessCB[i].tempo_cpu);
        }
    }
    printf("%s- PROCESSOS BLOQUEADOS:%s \n", Amarelo, Normal);

    for (int i = 0; i < gest->bloqueados_size; i++)
    {
        for (int e = 1; e < PCB_size; e++)
        {
            if ((gest->Bloqueados[i]) == ProcessCB[e].PID && ProcessCB[e].estado == 2)
            { //verificar quais os processos que já terminaram a execução

                printf("Nome do processo: %s\n", ProcessCB[e].nome_processo);
                printf("PID: %d\n", ProcessCB[e].PID);
                printf("PPID: %d\n", ProcessCB[e].PPID);
                printf("Valor da variável: %d\n", ProcessCB[e].variavel);
                printf("Prioridade: %d\n", ProcessCB[e].prioridade);
                printf("Tempo de inicio: %d\n", ProcessCB[e].tempo_chegada);
                printf("Número de instruções: %d\n", ProcessCB[e].tempo_burst);
                printf("Tempo do CPU: %d\n", ProcessCB[e].tempo_cpu);
            }
        }
    }

    printf("%s- PROCESSOS PRONTOS:%s \n", Verde, Normal);

    for (int i = 0; i < gest->prontos_size; i++)
    {
        for (int e = 1; e < PCB_size; e++)
        {
            if ((gest->Prontos[i]) == ProcessCB[e].PID && ProcessCB[e].estado == 1 /*&& ProcessCB[e].PID != gest->RunningState*/)
            { //verificar quais os processos que já terminaram a execução

                printf("Nome do processo: %s\n", ProcessCB[e].nome_processo);
                printf("PID: %d\n", ProcessCB[e].PID);
                printf("PPID: %d\n", ProcessCB[e].PPID);
                printf("Valor da variável: %d\n", ProcessCB[e].variavel);
                printf("Prioridade: %d\n", ProcessCB[e].prioridade);
                printf("Tempo de inicio: %d\n", ProcessCB[e].tempo_chegada);
                printf("Número de instruções: %d\n", ProcessCB[e].tempo_burst);
                printf("Tempo do CPU: %d\n", ProcessCB[e].tempo_cpu);
            }
        }
    }
    printf("%s- PROCESSOS TERMINADOS:%s \n", Vermelho, Normal);

    for (int i = 0; i < gest->terminados_size; i++)
    {
        for (int e = 1; e < PCB_size; e++)
        {
            if ((gest->terminados[i]) == ProcessCB[e].PID && ProcessCB[e].estado == -1)
            { //verificar quais os processos que já terminaram a execução

                printf("Nome do processo: %s\n", ProcessCB[e].nome_processo);
                printf("PID: %d\n", ProcessCB[e].PID);
                printf("PPID: %d\n", ProcessCB[e].PPID);
                printf("Valor da variável: %d\n", ProcessCB[e].variavel);
                printf("Prioridade: %d\n", ProcessCB[e].prioridade);
                printf("Tempo de inicio: %d\n", ProcessCB[e].tempo_chegada);
                printf("Número de instruções: %d\n", ProcessCB[e].tempo_burst);
                printf("Tempo do CPU: %d\n", ProcessCB[e].tempo_cpu);
            }
        }
    }
}