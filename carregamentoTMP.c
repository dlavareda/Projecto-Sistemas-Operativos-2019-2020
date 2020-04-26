//carregamento de dados manual até a função ler dos ficheiros estar pronta
    //Processos
    Processo *p = malloc(11 * sizeof(Processo));
    strcpy(p[0].instrucao, "M");
    p[0].valor = 100;
    strcpy(p[1].instrucao, "A");
    p[1].valor = 19;
    strcpy(p[2].instrucao, "A");
    p[2].valor = 20;
    strcpy(p[3].instrucao, "S");
    p[3].valor = 12;
    strcpy(p[4].instrucao, "A");
    p[4].valor = 1;
    strcpy(p[5].instrucao, "A");
    p[5].valor = 4;
    strcpy(p[6].instrucao, "C");
    p[6].valor = 2;
    strcpy(p[7].instrucao, "L");
    strcpy(p[7].filho, "filho1");
    strcpy(p[8].instrucao, "C");
    p[8].valor = 2;
    strcpy(p[9].instrucao, "L");
    strcpy(p[9].filho, "filho2");
    strcpy(p[10].instrucao, "T");

    Processo *p2 = malloc(3 * sizeof(Processo));
    strcpy(p2[0].instrucao, "M");
    p2[0].valor = 200;
    strcpy(p2[1].instrucao, "A");
    p2[1].valor = 19;
    strcpy(p2[2].instrucao, "T");

    Processo *p3 = malloc(4 * sizeof(Processo));
    strcpy(p3[0].instrucao, "M");
    p3[0].valor = 300;
    strcpy(p3[1].instrucao, "S");
    p3[1].valor = 12;
    strcpy(p3[2].instrucao, "A");
    p3[2].valor = 5;
    strcpy(p3[3].instrucao, "T");

    //plan

    