#include<stdio.h>

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
        printf("\033[41m");
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

void setBlack (){
    printf("\033[0;30m");
}

void setWhite (){
    printf("\033[7m");
}

void resetColor () {
    printf("\033[0m");
}