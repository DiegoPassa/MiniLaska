all: main.c supporto.c supporto.h lib/colori.c lib/colori.h 
	gcc main.c supporto.h supporto.c lib/colori.h lib/colori.c -o laska.exe -ansi -pedantic -Wall -lm