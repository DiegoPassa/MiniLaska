#include <stdio.h>
#include "colors.h"
#include <ncurses.h>
/*
    **********************
    *    1 = Testo       *
    *    2 = Sfondo      *
    **********************
*/

void setRed (int n) {
    if (n == 1){
        printf("\033[0;31m");
    }
    if (n == 2){
        printf(REDB);
    }
}

void setYellow (int n){
    if (n == 1){
        printf("\033[0;33m");
    }
    if (n == 2){
        printf("\033[43m");
    }
}

void printTextColor(char color){
    if (color == 'R'){
        printf(RED);
    }
    if (color == 'Y'){
        printf(YEL);
    }
    if (color == 'G'){
        printf(GRN);
    }
    if (color == 'C'){
        printf(CYN);
    }
    if (color == 'M'){
        printf(MAG);
    }
    if (color == 'B'){
        printf(BLU);
    }
}

void printColor(char color){
    if (color == 'R'){
        printf(REDB);
    }
    if (color == 'Y'){
        printf(YELB);
    }
    if (color == 'G'){
        printf(GRNB);
    }
    if (color == 'C'){
        printf(CYNB);
    }
    if (color == 'M'){
        printf(MAGB);
    }
    if (color == 'B'){
        printf(BLUB);
    }
}

void printPlayerTurn(char nPl){
    if (nPl == 'B'){
        setYellow(1);
    }
    if (nPl == 'N'){
        setRed(1);
    }
}

void setBlack (){
    printf("\033[0;30m");
}

void setWhite (){
    printf("\033[7m");
}

void resetColor () {
    printf("\033[0m");
}