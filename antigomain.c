else if (resp == 5)
        {
            resp = 0;
            while (resp != 9)
            {
                printf("1 - Carregar Dados\n");
                printf("2 - Mostrar RAM\n");
                printf("3 - Mostrar PCB\n");
                printf("4 - Executar programa\n");
                printf("5 - Executar escalonador de curto prazo FCFS\n");
                printf("6 - Executar escalonador de curto prazo SJF (Ainda nao operacional)\n");
                printf("7 - Mostrar Processos Ready\n");
                printf("8 - Mostrar Processos Bloqueados\n");
                printf("9 - Sair\n");
                scanf("%d", &resp);
                if (resp == 1)
                {
                    ///////////////////////////////////////////////     Leitura do Plano    ///////////////////////////////////////////////

                    //Faz a leitura do ficheiro plan.txt e adiciona a estrutura
                    plano_size = lerPlan(plano);

                    ////////////////////////////////////////     Inicialização do PCB    //////////////////////////////////////////////////

                    //inicializar PCB
                    inicializarPCB(ProcessCB, &PCB_size);

                    ////////////////////////     Carregamento dos Programas do plano para RAM do Plano    //////////////////////////////////

                    int novoProgramaSize = 0;
                    int startPrograma = 0;
                    Memory *novoPrograma;
                    int novoPCB = 0;
                    for (int i = 0; i < plano_size; i++)
                    {
                        startPrograma = (RAM_size);
                        novoPrograma = lerProcesso(plano[i].programa, &novoProgramaSize);
                        adicionarProgramaRAM(RAM, &RAM_size, novoPrograma, novoProgramaSize);
                        //Adiciona o programa recem carregado ao PCB
                        novoPCB = adicionarProcessoPCB(ProcessCB, &PCB_size, plano[i].programa, startPrograma, plano[i].tempo_chegada, novoProgramaSize);
                        free(novoPrograma);
                        novoProgramaSize = 0;
                    }

                    ////////////////////////////////////////     Inicialização do Gestor    //////////////////////////////////////////////////
                    gest = inicializarGestor(ProcessCB, PCB_size);
                }
                else if (resp == 2)
                {
                    mostrarRAM(RAM, RAM_size);
                }
                else if (resp == 3)
                {
                    mostrarPCB(ProcessCB, PCB_size);
                }
                else if (resp == 4)
                {
                    int N_instrucoes = 0;
                    printf("Insira o PID do programa a executar\n");
                    scanf("%d", &PID);
                    printf("Insira o numero de instruções a executar\n");
                    scanf("%d", &N_instrucoes);
                    executarPrograma(RAM, &RAM_size, PID, ProcessCB, &PCB_size, &TIME, gest, N_instrucoes);
                    printf("\n");
                }
                else if (resp == 5)
                {
                    ProcessCB = FCFS(ProcessCB, PCB_size);
                    mostrarPCB(ProcessCB, PCB_size);
                }
                else if (resp == 6)
                {
                    ProcessCB = SJF(ProcessCB, PCB_size);
                    mostrarPCB(ProcessCB, PCB_size);
                }
                else if (resp == 7)
                {
                    mostrarProcessosReady(gest);
                }
                else if (resp == 8)
                {
                    mostrarProcessosBlocked(gest);
                }
            }