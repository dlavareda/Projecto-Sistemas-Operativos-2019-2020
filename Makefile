#A Simple Example Makefile for soshell
#
# Syntax:
# Alvo: Dependencias
# tab Action 1
# tab Action 2
#
# Variaveis: Compiler, compiler flags, libraries to link, name of of object files
#
CC=cc
FLAGS=-c -Wall
LIBS=-lm
OBS=main.o LerFicheiros.o

#Alvo por defeito é o primeiro
all :  processManager

main.o : processManager.h main.c
	$(CC) $(FLAGS) main.c
LerFicheiros.o : processManager.h LerFicheiros.c
	$(CC) $(FLAGS) LerFicheiros.c
processManager : $(OBS)
	$(CC)  -o processManager  $(OBS) $(LIBS)
clean limpar:
	rm -f current_dir *.o
	rm -f *~
	echo "Limpeza dos ficheiros exectuaveis, objectos e gedit tralha"