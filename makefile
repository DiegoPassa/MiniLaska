all: main.c supporto.c supporto.h src/colors/colors.h src/colors/colors.c
	gcc main.c supporto.h supporto.c src/colors/colors.h src/colors/colors.c -o laska.exe -ansi -pedantic -Wall -lm