#include<stdio.h>

/* Regular background */
#define BLKB "\033[40m" /*  black   */
#define REDB "\033[41m" /*  red     */
#define GRNB "\033[42m" /*  green   */
#define YELB "\033[43m" /*  yellow  */
#define BLUB "\033[44m" /*  blue    */
#define MAGB "\033[45m" /*  magenta */
#define CYNB "\033[46m" /*  cyano   */
#define WHTB "\033[47m" /*  white   */

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