#include<stdio.h>
#include <unistd.h>
#include<stdlib.h>
#include"supporto.h"
#include<string.h>
#include<time.h>
#include <math.h>
#include "src/colors/colors.h"

/* void pawn_remove_promotion(player_t *players ,int num_pawn,unsigned int nPl){
    if (num_pawn > -1 && num_pawn < players[nPl].dim_pawns && (nPl == 0 || nPl == 1)){
        if(players[nPl].pawns[num_pawn].isPromoted == 1){
            players[nPl].pawns[num_pawn].isPromoted = 0;
            players[nPl].pawns[num_pawn].label[players[nPl].pawns[num_pawn].dim_label+3] = ' ';
             free(players[nPl].pawns[num_pawn].canMove);
            players[nPl].pawns[num_pawn].canMove = (unsigned int*)calloc(2 ,sizeof(unsigned int));
        }
    }
}
*/