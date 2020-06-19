#A Simple Example Makefile for projecto SO 2020
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
OBS=main.o Report.o operacoes.o linhaDeExecussao.o ficheiros.o execute.o escalonadores.o

#Alvo por defeito é o primeiro
all :  processManager

main.o : processManager.h main.c
	$(CC) $(FLAGS) main.c
ficheiros.o : processManager.h ficheiros.c
	$(CC) $(FLAGS) ficheiros.c
Report.o : processManager.h Report.c
	$(CC) $(FLAGS) Report.c
operacoes.o : processManager.h operacoes.c
	$(CC) $(FLAGS) operacoes.c
linhaDeExecussao.o : processManager.h linhaDeExecussao.c
	$(CC) $(FLAGS) linhaDeExecussao.c
execute.o : processManager.h execute.c
	$(CC) $(FLAGS) execute.c
escalonadores.o : processManager.h escalonadores.c
	$(CC) $(FLAGS) escalonadores.c
processManager : $(OBS)
	$(CC)  -o processManager  $(OBS) $(LIBS)
clean limpar:
	rm -f current_dir *.o
	rm -f *~
	echo "Limpeza dos ficheiros exectuaveis, objectos e gedit tralha"


	