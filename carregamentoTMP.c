void carregarDados(Memory *m, int *RAM_size)
{
    strcpy(m[0].instrucao, "M");
    m[0].valor = 100;
    strcpy(m[0].nome, "NULL");
    strcpy(m[1].instrucao, "A");
    m[1].valor = 19;
    strcpy(m[1].nome, "NULL");
    strcpy(m[2].instrucao, "A");
    m[2].valor = 20;
    strcpy(m[2].nome, "NULL");
    strcpy(m[3].instrucao, "S");
    m[3].valor = 12;
    strcpy(m[3].nome, "NULL");
    strcpy(m[4].instrucao, "A");
    m[4].valor = 1;
    strcpy(m[4].nome, "NULL");
    strcpy(m[5].instrucao, "A");
    m[5].valor = 4;
    strcpy(m[5].nome, "NULL");
    strcpy(m[6].instrucao, "C");
    m[6].valor = 2;
    strcpy(m[6].nome, "NULL");
    strcpy(m[7].instrucao, "L");
    strcpy(m[7].nome, "filho1");
    strcpy(m[8].instrucao, "C");
    m[8].valor = 2;
    strcpy(m[8].nome, "NULL");
    strcpy(m[9].instrucao, "L");
    strcpy(m[9].nome, "filho2");
    strcpy(m[10].instrucao, "T");
    strcpy(m[10].nome, "NULL");

    strcpy(m[11].instrucao, "M");
    m[11].valor = 200;
    strcpy(m[11].nome, "NULL");
    strcpy(m[12].instrucao, "A");
    m[12].valor = 19;
    strcpy(m[12].nome, "NULL");
    strcpy(m[13].instrucao, "T");
    strcpy(m[13].nome, "NULL");

    strcpy(m[14].instrucao, "M");
    m[14].valor = 300;
    strcpy(m[14].nome, "NULL");
    strcpy(m[15].instrucao, "S");
    m[15].valor = 12;
    strcpy(m[15].nome, "NULL");
    strcpy(m[16].instrucao, "A");
    m[15].valor = 5;
    strcpy(m[16].nome, "NULL");
    strcpy(m[17].instrucao, "T");
    strcpy(m[17].nome, "NULL");
    *RAM_size = 18;
}