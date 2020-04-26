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