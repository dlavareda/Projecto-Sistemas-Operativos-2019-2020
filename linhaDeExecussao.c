//definição da palete de cores
#define Normal "\x1B[0m"
#define Vermelho "\x1B[31m"
#define Verde "\x1B[32m"
#define Amarelo "\x1B[33m"
#define Azul "\x1B[34m"
#define Magenta "\x1B[35m"
#define Ciano "\x1B[36m"
#define CinzaClaro "\x1b[90m"
#define VermelhoClaro "\x1b[91m"
#define VerdeClaro "\x1b[92m"
#define AmareloClaro "\x1b[93m"
#define AzulClaro "\x1b[94m"
#define MagentaClaro "\x1b[95m"
#define CianoClaro "\x1b[96m"

char *obterCor(char *Processo)
{
    if (strcmp(Processo, "P1") == 0)
    {
        return Vermelho;
    }
    else if (strcmp(Processo, "P2") == 0)
    {
        return Verde;
    }
    else if (strcmp(Processo, "P3") == 0)
    {
        return Amarelo;
    }
    else if (strcmp(Processo, "P4") == 0)
    {
        return Azul;
    }
    else if (strcmp(Processo, "P5") == 0)
    {
        return Magenta;
    }
    else if (strcmp(Processo, "P6") == 0)
    {
        return Ciano;
    }
    else if (strcmp(Processo, "P7") == 0)
    {
        return CinzaClaro;
    }
    else if (strcmp(Processo, "P8") == 0)
    {
        return VermelhoClaro;
    }
    else if (strcmp(Processo, "P9") == 0)
    {
        return VerdeClaro;
    }
    else if (strcmp(Processo, "P10") == 0)
    {
        return AmareloClaro;
    }
    else if (strcmp(Processo, "P11") == 0)
    {
        return AzulClaro;
    }
    else if (strcmp(Processo, "P12") == 0)
    {
        return MagentaClaro;
    }
    else if (strcmp(Processo, "P13") == 0)
    {
        return CianoClaro;
    }
    else
    {
        return Normal;
    }
}
void barraProgressoAdicionarElemento(char *Processo, char *cor)
{
    printf("%s%s", cor, Processo);
}