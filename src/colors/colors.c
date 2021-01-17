
#include <stdio.h>
#include "colors.h"

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

void setWhite (){
    printf("\033[7m");
}