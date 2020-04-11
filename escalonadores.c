#include "teste_loadbar.c"
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
}

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
}

/*int main()
{
    barraProgressoAdicionarElemento("P1", Vermelho);
    barraProgressoAdicionarElemento("P1", Vermelho);
    barraProgressoAdicionarElemento("P2", Verde);
    printf("%s\n", Normal);//Faz reset a cor
    return 0;
}*/