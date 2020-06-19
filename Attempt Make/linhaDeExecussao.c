#include "processManager.h"
char *obterCor(int Processo)
{
    if (Processo == 1)
    {
        return Vermelho;
    }
    else if (Processo == 2)
    {
        return Verde;
    }
    else if (Processo == 3)
    {
        return Amarelo;
    }
    else if (Processo == 4)
    {
        return Azul;
    }
    else if (Processo == 5)
    {
        return Magenta;
    }
    else if (Processo == 6)
    {
        return Ciano;
    }
    else if (Processo == 7)
    {
        return CinzaClaro;
    }
    else if (Processo == 8)
    {
        return VermelhoClaro;
    }
    else if (Processo == 9)
    {
        return VerdeClaro;
    }
    else if (Processo == 10)
    {
        return AmareloClaro;
    }
    else if (Processo == 11)
    {
        return AzulClaro;
    }
    else if (Processo == 12)
    {
        return MagentaClaro;
    }
    else if (Processo == 13)
    {
        return CianoClaro;
    }
    else
    {
        return Normal;
    }
}
void barraProgressoAdicionarElemento(int Processo, char *cor)
{
    printf("%s%d", cor, Processo);
}