#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Ficheiros.c"
#include "escalonadores.c"

Processo *carregarDados();
int main(int argc, char const *argv[])
{
    Processo *arr_processos;     //array de estruturas
    arr_processos = carregarDados();
    mostrarArray(arr_processos);
    return 0;
}