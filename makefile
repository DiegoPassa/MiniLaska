all: main.c supporto.c src/colors/colors.c
	gcc main.c supporto.c src/colors/colors.c -o laska.exe -ansi -pedantic -Wall -lm -lncurses