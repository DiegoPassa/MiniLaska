all: main.c supp.c supp.h
	gcc main.c supp.h supp.c -o laska.exe -ansi -pedantic -Wall
