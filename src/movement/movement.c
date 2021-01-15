#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "../colors/colors.h"
#include "../game_engine/game_engine.h"
#include "../ia/ia.h"
#include "../memory_management/memory_management.h"
#include "movement.h"
#include "../user_interaction/user_interaction.h"

unsigned int move_noeat(player_t *players, unsigned int num_pawn, char *str, board_t *board, unsigned int nPl){
    if(!strcmp(str,"sx")){
        if((is_in(players[nPl].pawns[num_pawn].coordinate.y-1,players[nPl].pawns[num_pawn].coordinate.x-(players[nPl].pawns[num_pawn].dim_label+3+1),*board))&&(!check_spot(*board,players[nPl].pawns[num_pawn].coordinate.y-1,players[nPl].pawns[num_pawn].coordinate.x-(players[nPl].pawns[num_pawn].dim_label+3+1),(players[nPl].pawns[num_pawn].dim_label+3+1)))){
            remove_pawn(board,players[nPl].pawns[num_pawn].coordinate.y,players[nPl].pawns[num_pawn].coordinate.x,(players[nPl].pawns[num_pawn].dim_label+3+1));
            --players[nPl].pawns[num_pawn].coordinate.y;
            players[nPl].pawns[num_pawn].coordinate.x -= (players[nPl].pawns[num_pawn].dim_label+3+1);
            pawn_promotion(players,num_pawn,nPl,board->n_rows-1);
            return 1;
        }else{
            return 0;
        }
    }else{
        if (!strcmp(str, "dx")) {
            if((is_in(players[nPl].pawns[num_pawn].coordinate.y-1, players[nPl].pawns[num_pawn].coordinate.x + (players[nPl].pawns[num_pawn].dim_label + 3+1), *board))&&(!check_spot(*board, players[nPl].pawns[num_pawn].coordinate.y - 1, players[nPl].pawns[num_pawn].coordinate.x + (players[nPl].pawns[num_pawn].dim_label + 3+1),players[nPl].pawns[num_pawn].dim_label+3+1))){
                remove_pawn(board,players[nPl].pawns[num_pawn].coordinate.y,players[nPl].pawns[num_pawn].coordinate.x,(players[nPl].pawns[num_pawn].dim_label+3+1));
                --players[nPl].pawns[num_pawn].coordinate.y;
                players[nPl].pawns[num_pawn].coordinate.x += (players[nPl].pawns[num_pawn].dim_label+3+1);
                pawn_promotion(players,num_pawn,nPl,board->n_rows-1);
                return 1;
            }else{
                return 0;
            }
        }
        if (!strcmp(str, "bassosx") && ((nPl == 1) || (players[nPl].pawns[num_pawn].isPromoted))) {
            if((is_in(players[nPl].pawns[num_pawn].coordinate.y+1,players[nPl].pawns[num_pawn].coordinate.x-(players[nPl].pawns[num_pawn].dim_label+3+1),*board))&&(!check_spot(*board,players[nPl].pawns[num_pawn].coordinate.y+1,players[nPl].pawns[num_pawn].coordinate.x-(players[nPl].pawns[num_pawn].dim_label+3+1),(players[nPl].pawns[num_pawn].dim_label+3+1)))){
                remove_pawn(board,players[nPl].pawns[num_pawn].coordinate.y,players[nPl].pawns[num_pawn].coordinate.x,(players[nPl].pawns[num_pawn].dim_label+3+1));
                players[nPl].pawns[num_pawn].coordinate.y++;
                players[nPl].pawns[num_pawn].coordinate.x -= (players[nPl].pawns[num_pawn].dim_label+3+1);
                if(nPl == 1){
                    pawn_promotion(players,num_pawn,nPl,board->n_rows-1);
                }
                return 1;
            }else{
                return 0;
            }
        }
        if (!strcmp(str, "bassodx") && ((nPl == 1) || (players[nPl].pawns[num_pawn].isPromoted))) {
            if((is_in(players[nPl].pawns[num_pawn].coordinate.y+1, players[nPl].pawns[num_pawn].coordinate.x + (players[nPl].pawns[num_pawn].dim_label + 3+1), *board))&&(!check_spot(*board, players[nPl].pawns[num_pawn].coordinate.y+1, players[nPl].pawns[num_pawn].coordinate.x + (players[nPl].pawns[num_pawn].dim_label + 3+1),players[nPl].pawns[num_pawn].dim_label + 3+1))){
                remove_pawn(board,players[nPl].pawns[num_pawn].coordinate.y,players[nPl].pawns[num_pawn].coordinate.x,(players[nPl].pawns[num_pawn].dim_label+3+1));
                players[nPl].pawns[num_pawn].coordinate.y++;
                players[nPl].pawns[num_pawn].coordinate.x += (players[nPl].pawns[num_pawn].dim_label+3+1);
                if(nPl == 1){
                    pawn_promotion(players,num_pawn,nPl,board->n_rows-1);
                }
                return 1;
            }else{
                return 0;
            }
        }

    }

    return 0;
}

unsigned int eat(player_t *players, char *str, unsigned int num_pawn, board_t board, unsigned int enemy_pawn, unsigned int nPl){

    unsigned int nPl2 = 1, i;
    char temp[3];

    if (nPl == 1){
        nPl2 = 0;
    }

    temp[0] = players[nPl].pawns[num_pawn].label[1];
    temp[1] = players[nPl].pawns[num_pawn].label[2];
    temp[2] = players[nPl2].pawns[enemy_pawn].label[players[nPl2].pawns[enemy_pawn].cima]; /* 012 */

    if (players[nPl2].pawns[enemy_pawn].grade == 1){
        players[nPl2].pawns[enemy_pawn].grade = 0;
    }else if((players[nPl2].pawns[enemy_pawn].grade > 1) && players[nPl2].pawns[enemy_pawn].label[players[nPl2].pawns[enemy_pawn].cima] == players[nPl2].pawns[enemy_pawn].label[players[nPl2].pawns[enemy_pawn].cima+1]){
        players[nPl2].pawns[enemy_pawn].label[players[nPl2].pawns[enemy_pawn].cima] = ' ';
        players[nPl2].pawns[enemy_pawn].cima+=1;
        players[nPl2].pawns[enemy_pawn].grade-=1;
    }else{
        int newPos = is_empty(players[nPl]);
        if (newPos == -1){
            add_pawn(players, enemy_pawn, nPl,players[nPl].pawns[num_pawn].label[players[nPl].pawns[num_pawn].cima]);
        }else if(newPos >= 0 && players[nPl2].pawns[enemy_pawn].grade > 1){
            int newPos_copy;
            unsigned int index;
            players[nPl2].pawns[enemy_pawn].label[players[nPl2].pawns[enemy_pawn].cima] = ' ';
            players[nPl2].pawns[enemy_pawn].cima+=1;
            players[nPl2].pawns[enemy_pawn].grade-=1;
            players[nPl].pawns[newPos].grade = players[nPl2].pawns[enemy_pawn].grade;
            players[nPl2].pawns[enemy_pawn].grade = 0;
            players[nPl].pawns[newPos].cima = players[nPl2].pawns[enemy_pawn].cima;

            players[nPl].pawns[newPos].coordinate.x = players[nPl2].pawns[enemy_pawn].coordinate.x;
            players[nPl].pawns[newPos].coordinate.y = players[nPl2].pawns[enemy_pawn].coordinate.y;

            players[nPl].pawns[newPos].dim_label = players[nPl2].pawns[enemy_pawn].dim_label;

            players[nPl].pawns[newPos].isPromoted = 0;
            players[nPl2].pawns[enemy_pawn].isPromoted = 0;
            players[nPl2].pawns[newPos].label[players[nPl].pawns[newPos].dim_label+3] = ' ';
            players[nPl].pawns[newPos].label[players[nPl].pawns[newPos].dim_label+3] = ' ';

            for (i = 0; i < 3; i++){
                players[nPl].pawns[newPos].label[i] = players[nPl2].pawns[enemy_pawn].label[i];
            }
            index = players[nPl].pawns[newPos].dim_label-1;
            newPos_copy = newPos;
            for (i = 3; i < players[nPl].pawns[newPos].dim_label+3; i++){
                players[nPl].pawns[newPos].label[i] = int_converter(newPos_copy, index);
                newPos_copy -= (pow(10, index)*(players[nPl].pawns[newPos].label[i] - '0'));

                index--;
            }

        }
        
    }
    if (players[nPl].pawns[num_pawn].grade < 3){
        for (i = 0; i < 3; i++){
            players[nPl].pawns[num_pawn].label[i] = temp[i];
        }
        players[nPl].pawns[num_pawn].cima-=1;
        players[nPl].pawns[num_pawn].grade+=1;
    }
    remove_pawn(&board,players[nPl2].pawns[enemy_pawn].coordinate.y,players[nPl2].pawns[enemy_pawn].coordinate.x,players[nPl2].pawns[enemy_pawn].dim_label+3+1);
    if(!strcmp(str,"sx")){
        players[nPl].pawns[num_pawn].coordinate.y -= 2;
        players[nPl].pawns[num_pawn].coordinate.x -= (players[nPl].pawns[num_pawn].dim_label+3+1)*2;
    }
    if(!strcmp(str,"dx")){
        players[nPl].pawns[num_pawn].coordinate.y -= 2;
        players[nPl].pawns[num_pawn].coordinate.x += (players[nPl].pawns[num_pawn].dim_label+3+1)*2;
    }
    if(!strcmp(str,"bassosx")){
        players[nPl].pawns[num_pawn].coordinate.y += 2;
        players[nPl].pawns[num_pawn].coordinate.x -= (players[nPl].pawns[num_pawn].dim_label+3+1)*2;
    }
    if(!strcmp(str,"bassodx")){
        players[nPl].pawns[num_pawn].coordinate.y += 2;
        players[nPl].pawns[num_pawn].coordinate.x += (players[nPl].pawns[num_pawn].dim_label+3+1)*2;
    }

    if(!strcmp(str,"sx")){
        remove_pawn(&board,players[nPl].pawns[num_pawn].coordinate.y+2,players[nPl].pawns[num_pawn].coordinate.x+((players[nPl].pawns[num_pawn].dim_label+3+1)*2),players[nPl].pawns[num_pawn].dim_label+3+1);
    }
    if(!strcmp(str,"dx")){
        remove_pawn(&board,players[nPl].pawns[num_pawn].coordinate.y+2,players[nPl].pawns[num_pawn].coordinate.x-((players[nPl].pawns[num_pawn].dim_label+3+1)*2),(players[nPl].pawns[num_pawn].dim_label+3+1));
    }
    if(!strcmp(str,"bassosx")){
        remove_pawn(&board,players[nPl].pawns[num_pawn].coordinate.y-2,players[nPl].pawns[num_pawn].coordinate.x+((players[nPl].pawns[num_pawn].dim_label+3+1)*2),players[nPl].pawns[num_pawn].dim_label+3+1);
    }
    if(!strcmp(str,"bassodx")){
        remove_pawn(&board,players[nPl].pawns[num_pawn].coordinate.y-2,players[nPl].pawns[num_pawn].coordinate.x-((players[nPl].pawns[num_pawn].dim_label+3+1)*2),(players[nPl].pawns[num_pawn].dim_label+3+1));
    }
    pawn_promotion(players,num_pawn,nPl,board.n_rows-1);
    return 1;
}

int move_p1 (player_t *players, unsigned int num_pawn, char *str, board_t *board, unsigned int nPl){
    int enemy_pawn;
    enemy_pawn = can_eat(players,num_pawn,str,board, nPl);
    if(enemy_pawn > -1){
        eat(players, str, num_pawn, *board, enemy_pawn, nPl);
        return enemy_pawn;
    }else if(enemy_pawn == -4){
        printf("Errore nella can_eat\n");
    }else if(move_noeat(players, num_pawn, str, board, nPl)){
        return -1;
    }else{
        return -2;
    }

    return 0;
}

int move_p2(player_t *players,unsigned int num_pawn,char *str,board_t *board){
    if(!strcmp(str,"sx")) {
        return move_p1(players,num_pawn,"bassosx",board,1);
    }else{
        if(!strcmp(str,"dx")){
            return move_p1(players,num_pawn,"bassodx",board,1);
        }
        if(!strcmp(str,"bassodx")&&(players[1].pawns[num_pawn].isPromoted)) {
            return move_p1(players,num_pawn,"dx",board,1);
        }
        if(!strcmp(str,"bassosx")&&(players[1].pawns[num_pawn].isPromoted)) {
            return move_p1(players,num_pawn,"sx",board,1);
        }
    }

    return 0;
}