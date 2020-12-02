all: main.c supporto.c supporto.h
	gcc main.c supporto.h supporto.c -o laska.exe -ansi -pedantic -Wall -lm
