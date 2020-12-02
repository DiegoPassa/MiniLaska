all: main.c supporto.c supporto.h colori.c colori.h 
	gcc main.c supporto.h supporto.c colori.h colori.c -o laska.exe -ansi -pedantic -Wall -lm
