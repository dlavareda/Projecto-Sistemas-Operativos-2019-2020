Memory *lerProcesso(char *nomePrograma, int *programaSize)
{
    //criação da estrutura auxiliar
    typedef struct ProcessoAux
    {
        char campo1[1];
        char campo2[15];
    } ProcessoAux;

    FILE *f;
    f = fopen(nomePrograma, "r");
    int i = 0;
    char campo1[1];
    char campo2[15];
    ProcessoAux *aux = calloc(aux, 0);
    while (fscanf(f, "%s %s", campo1, campo2) >= 1)
    {
        aux = realloc(aux, (i + 1) * sizeof(ProcessoAux));
        strcpy(aux[i].campo1, campo1);
        strcpy(aux[i].campo2, campo2);
        i++;
    }
    int tamanho_array_aux = i;
    Memory *Processo = malloc((tamanho_array_aux * sizeof(Memory)));
    for (int i = 0; i < tamanho_array_aux; i++)
    {
        if ((aux[i].campo1[0] == 77) || (aux[i].campo1[0] == 65) || (aux[i].campo1[0] == 83) || (aux[i].campo1[0] == 67))
        {
            strcpy(Processo[i].instrucao, aux[i].campo1);
            Processo[i].valor = atoi(aux[i].campo2);
            strcpy(Processo[i].nome, "NULL");
        }
        else if ((aux[i].campo1[0] == 76))
        {
            strcpy(Processo[i].instrucao, aux[i].campo1);
            Processo[i].valor = 0;
            strcpy(Processo[i].nome, aux[i].campo2);
        }
        else if ((aux[i].campo1[0] == 84))
        {
            strcpy(Processo[i].instrucao, aux[i].campo1);
            Processo[i].valor = 0;
            strcpy(Processo[i].nome, "NULL");
        }
        else if ((aux[i].campo1[0] == 66)) //B
        {
            strcpy(Processo[i].instrucao, aux[i].campo1);
            Processo[i].valor = 0;
            strcpy(Processo[i].nome, "NULL");
        }
    }
    free(aux);
    *programaSize = i;
    fclose(f);
    return Processo;
}
int lerPlan(plan *Plano)
{
    FILE *f;
    f = fopen("plan.txt", "r");
    int i = 0;
    char programa[15];
    int tempo_chegada;
    while (fscanf(f, "%s %d", &programa, &tempo_chegada) == 2)
    {
        strcpy(Plano[i].programa, programa);
        Plano[i].tempo_chegada = tempo_chegada;
        i++;
    }
    fclose(f);
    return i;
}