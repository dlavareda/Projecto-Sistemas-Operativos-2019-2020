#include "linhaDeExecussao.c"
int ultimoProcesso(Processo *arr_processos) //Encontra a hora do ultimo processo a chegar
{
    int ultimo = 0;
    for (int i = 0; i < 10; i++)
    {
        if (arr_processos[i].tempo_chegada > ultimo)
        {
            ultimo = arr_processos[i].tempo_chegada;
        }
    }
    return ultimo;
}

void FCFS(Processo *arr_processos) //First Come First Served
{
    printf("Linha de execussão dos processos usando o algoritmo de escalonamento FCFS\n");
    int actual = 0;
    for (int z = 0; z < ultimoProcesso(arr_processos); z++)
    {
        for (int i = 0; i < 10; i++) //percorre o array todo
        {
            if (arr_processos[i].tempo_chegada == actual)
            {
                for (int j = 0; j < arr_processos[i].tempo_burst; j++)
                {
                    barraProgressoAdicionarElemento(arr_processos[i].nome_processo, obterCor(arr_processos[i].nome_processo));
                }
                printf("%s->", Normal);
            }
        }
        actual++;
    }
    printf("%s[Fim da Execussão]", Normal);
}
void SJF(Processo *arr_processos) //Shortest-Job-First Não Preemptivo
{
    printf("Linha de execussão dos processos usando o algoritmo de escalonamento Shortest-Job-First (Não Preemptivo)\n");
    int actual = 0;
    for (int z = 0; z < ultimoProcesso(arr_processos); z++)
    {
        for (int i = 0; i < 10; i++) //percorre o array todo
        {
            if (arr_processos[i].tempo_chegada == actual)
            {
                
            }
        }
    }
}
    /*
void test_print()
{
    barraProgressoAdicionarElemento("P1", Vermelho);
    printf("%s->", Normal);
    barraProgressoAdicionarElemento("P1", Vermelho);
    printf("%s->", Normal);
    barraProgressoAdicionarElemento("P2", Verde);
    printf("%s->", Normal);
    barraProgressoAdicionarElemento("P1", Vermelho);
    printf("%s->", Normal);
    barraProgressoAdicionarElemento("P1", Vermelho);
    printf("%s->", Normal);
    barraProgressoAdicionarElemento("P3", Amarelo);
    printf("%s->", Normal);
    barraProgressoAdicionarElemento("P3", Amarelo);
    printf("%s\n", Normal); //Faz reset a cor
}*/

    /*int main()
{
    barraProgressoAdicionarElemento("P1", Vermelho);
    barraProgressoAdicionarElemento("P1", Vermelho);
    barraProgressoAdicionarElemento("P2", Verde);
    printf("%s\n", Normal);//Faz reset a cor
    return 0;
}*/