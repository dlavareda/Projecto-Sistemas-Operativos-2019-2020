
void R(int TIME, PCB *ProcessCB, int PCB_size, Gestor *gest)
{ //onde vou buscar os processos em execução

    printf("TEMPO ATUAL: %d\\n\n", TIME);

    for (int i = 0; i < PCB_size; i++)
    {
        if (gest->RunningState == ProcessCB[i].PID)
        { //verificar o processo em execução
            printf("PROCESSO EM EXECUÇÃO: \n");
            printf("Nome do processo: %s\n", ProcessCB[i].nome_processo);
            printf("PID: %d\n", ProcessCB[i].PID);
            printf("PPID: %d\n", ProcessCB[i].PPID);
            printf("Valor da variável: %d\n", ProcessCB[i].variavel);
            printf("Prioridade: %d\n", ProcessCB[i].prioridade);
            printf("Tempo de inicio: %d\n", ProcessCB[i].tempo_chegada);
            printf("Número de instruções: %d\n", ProcessCB[i].tempo_burst);
            printf("Tempo do CPU: %d\n", ProcessCB[i].tempo_cpu);
        }
    }

    for (int i = 0; i < gest->bloqueados_size; i++)
    {
        for (int e = 0; e < PCB_size; e++)
        {
            if (gest[i].Bloqueados == ProcessCB[e].PID)
            { //verificar quais os processos que já terminaram a execução

                printf("PROCESSO TERMINADOS: \n");
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

    for (int i = 0; i < gest->prontos_size; i++)
    {
        for (int e = 0; e < PCB_size; e++)
        {
            if (gest[i].Prontos == ProcessCB[e].PID)
            { //verificar quais os processos que já terminaram a execução

                printf("PROCESSO TERMINADOS: \n");
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

    for (int i = 0; i < gest->terminados_size; i++)
    {
        for (int e = 0; e < PCB_size; e++)
        {
            if (gest[i].terminados == ProcessCB[e].PID)
            { //verificar quais os processos que já terminaram a execução

                printf("PROCESSO TERMINADOS: \n");
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