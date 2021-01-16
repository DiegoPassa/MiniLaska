/*
    ID gruppo : 51

    886711 Passarella-Diego | 882082 Pasqual-Davide | 881493 Ravagnan-Michelle

 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "../colors/colors.h"
#include "../game_engine/game_engine.h"
#include "ia.h"
#include "../memory_management/memory_management.h"
#include "../movement/movement.h"
#include "../user_interaction/user_interaction.h"

struct valueMinimax{
    int value;
    char* directions;
};

unsigned int round_ia_random(player_t *players, board_t *board, unsigned int nPl){
    int num_pawn = -1, dim_canMove = 2, flag;
    int newMove;
    char* move;
    srand(time(NULL));
    num_pawn = rand()%(players[nPl].dim_pawns);

    while (!check_while(players, nPl, num_pawn)){

        if(last_move(players, nPl) == -1){
            num_pawn = rand()%(players[nPl].dim_pawns);
        }else{
            num_pawn = last_move(players,nPl);
        }

    }

    if (players[nPl].pawns[num_pawn].isPromoted){
        dim_canMove = 4;
    }

    newMove = rand()%(dim_canMove);

    while(players[nPl].pawns[num_pawn].canMove[newMove] == 0){
        newMove = rand()%(dim_canMove);    
    }

    if (newMove == 0){
        move = "sx";
    }else if (newMove == 1){
        move = "dx";
    }else if (newMove == 2){
        move = "bassodx";
    }else if (newMove == 3){
        move = "bassosx";
    }

    if(nPl == 1){
        flag = move_p2(players, num_pawn, move, board);
    }else{
        flag = move_p1(players, num_pawn, move, board, nPl);
    }

    if (flag > -2){
        return 4;
    }else{
        return 2;
    }

    printf("Num ped : %u\n",num_pawn);

    return 0;
}

int last_move(player_t *players,unsigned int nPl){
    unsigned int flag = 0 ,pos = 0,i;
    for(i = 0 ; i < players[nPl].dim_pawns ; ++i){
        if(check_canMove(players,i,nPl)){
            ++flag ;
            pos = i;
        }
    }
    if(flag < 2){
        return pos;
    }else{
        return -1;
    }
}

int round_ia_minimax(player_t *players, board_t *board,unsigned int nPl, unsigned int depth){
    valueMinimax_t *value_arr;
    unsigned int pos;
    int *alpha,*beta;
    value_arr = (valueMinimax_t*)calloc(players[nPl].dim_pawns,sizeof(valueMinimax_t));
    for(pos = 0 ; pos < players[nPl].dim_pawns ; ++pos){
        value_arr[pos].directions = calloc(8,sizeof(char));
    }
    alpha = (int*)calloc(1,sizeof( int)) ;
    beta = (int*)calloc(1,sizeof( int)) ;
    if(value_arr && alpha && beta){
        *alpha = -9999;
        *beta = +9999;
        for(pos = 0; pos < players[nPl].dim_pawns ; ++pos){
            if(!check_while(players,nPl,pos)){
                value_arr[pos].value = -9017;
            }else{        
                minimax(*board,players,depth,pos,nPl,&(value_arr[pos]),1,alpha,beta);
            }
        }
        pos = max(value_arr,players[nPl].dim_pawns);
        printf("Numero di pedina e direzione : %u e %s\n",pos,value_arr[pos].directions);
        if(nPl == 0){
            move_p1(players,pos,value_arr[pos].directions,board,nPl);
        }else{
            move_p2(players,pos,value_arr[pos].directions,board);
        }
        update_board(board,players);
        destroy_value_minimax(value_arr,players[nPl].dim_pawns);
        free(alpha);
        free(beta);
        return 4;
    }else{
        printf("Errore calloc round_ia_minimax\n");
        return 3;
    }
}

int minimax(board_t board, player_t *players, int depth,unsigned  int nPed,unsigned int nPl,valueMinimax_t *v, int cheat,int *alpha,int *beta){
    board_t *board_copy = NULL;
    player_t *players_copy = NULL;

    if (depth == 0 || (!check_while(players,nPl,nPed)) ){
        v->value = evaluate_score(board, players);
        return v->value;
    }

    board_copy = copy_board(board, board_copy,players[nPl].pawns[0].dim_label+3+1,1);
    players_copy = player_copy(players, players_copy, players[nPl].pawns[0].dim_label+3+1,1);

    if (cheat == 1){

        int maxEval;

        maxEval = -9999;

        if (players_copy[nPl].pawns[nPed].canMove[0] == 1) {
            if((!interrupt_minimax(alpha,beta) ) ){
                int x;
                x = call_minimax(board_copy,players_copy,depth,nPed,nPl,v,"sx",maxEval, cheat,alpha,beta);
                maxEval < x  ?  maxEval = x : maxEval ;
            }else{
                strcpy(v->directions, "sx");
            }
        }
        restore_copy(board,players,board_copy,players_copy);

        if (players_copy[nPl].pawns[nPed].canMove[1]) {
            if((!interrupt_minimax(alpha,beta) ) ){
                int x;
                x = call_minimax(board_copy,players_copy,depth,nPed,nPl,v,"dx",maxEval, cheat,alpha,beta);
                maxEval < x  ?  maxEval = x : maxEval ;
            }else{
                strcpy(v->directions, "dx");
            }
        }
        restore_copy(board,players,board_copy,players_copy);

        if (players_copy[nPl].pawns[nPed].isPromoted  ) {
            if (players_copy[nPl].pawns[nPed].canMove[2] ) {
                if((!interrupt_minimax(alpha,beta) ) ){
                    int x;
                    x = call_minimax(board_copy,players_copy,depth,nPed,nPl,v,"bassodx",maxEval, cheat,alpha,beta);
                    maxEval < x  ?  maxEval = x : maxEval ;
                }else{
                    strcpy(v->directions, "bassodx");
                }
            }
            restore_copy(board,players,board_copy,players_copy);

            if (players_copy[nPl].pawns[nPed].canMove[3]&& (!interrupt_minimax(alpha,beta) )) {
                if((!interrupt_minimax(alpha,beta) ) ){
                    int x;
                    x = call_minimax(board_copy,players_copy,depth,nPed,nPl,v,"bassosx",maxEval, cheat,alpha,beta);
                    maxEval < x  ?  maxEval = x : maxEval ;
                }else{
                    strcpy(v->directions, "bassosx");
                }
            }
            restore_copy(board,players,board_copy,players_copy);
        }
        destroy_player(players_copy);
        destroy_board(board_copy);
        return maxEval;

    }else{
        int maxEval,i;

        maxEval = +9999;

        restore_copy(board,players,board_copy,players_copy);

        for (i = 0; i < players_copy[nPl].dim_pawns; i++){
            
            if (is_selected(players_copy,i,nPl) ){
                if (players_copy[nPl].pawns[i].canMove[0] == 1) {
                    if((!interrupt_minimax(alpha,beta) ) ){
                        int x;
                        x = call_minimax(board_copy,players_copy,depth,i,nPl,v,"sx",maxEval, cheat,alpha,beta);
                        maxEval > x  ?  maxEval = x : maxEval ;
                    }else{
                        strcpy(v->directions, "sx");
                    }
                }
                restore_copy(board,players,board_copy,players_copy);

                if (players_copy[nPl].pawns[i].canMove[1] == 1 && (!interrupt_minimax(alpha,beta) )){
                    if((!interrupt_minimax(alpha,beta) ) ){
                        int x;
                        x = call_minimax(board_copy,players_copy,depth,i,nPl,v,"dx",maxEval, cheat,alpha,beta);
                        maxEval > x  ?  maxEval = x : maxEval ;
                    }else{
                        strcpy(v->directions, "dx");
                    }
                }
                restore_copy(board,players,board_copy,players_copy);

                if (players_copy[nPl].pawns[i].isPromoted){
                    if (players_copy[nPl].pawns[i].canMove[2] == 1 && (!interrupt_minimax(alpha,beta) )){
                        if((!interrupt_minimax(alpha,beta) ) ){
                            int x;
                            x = call_minimax(board_copy,players_copy,depth,i,nPl,v,"bassodx",maxEval, cheat,alpha,beta);
                            maxEval > x  ?  maxEval = x : maxEval ;
                        }else{
                            strcpy(v->directions, "bassodx");
                        }
                    }
                    restore_copy(board,players,board_copy,players_copy);

                    if (players_copy[nPl].pawns[i].canMove[3] == 1 && (!interrupt_minimax(alpha,beta) )) {
                        if((!interrupt_minimax(alpha,beta) ) ){
                            int x;
                            x = call_minimax(board_copy,players_copy,depth,i,nPl,v,"bassosx",maxEval, cheat,alpha,beta);
                            maxEval > x  ?  maxEval = x : maxEval ;
                        }else{
                            strcpy(v->directions, "bassosx");
                        }
                    }
                    restore_copy(board,players,board_copy,players_copy);
                }
            }
        }
        destroy_player(players_copy);
        destroy_board(board_copy);
       
        return maxEval;

    }
}

int call_minimax(board_t *board_copy, player_t *players_copy,unsigned int depth, unsigned int nPed,unsigned int nPl,valueMinimax_t *v,char *str,int maxEval, int cheat,int *alpha,int *beta){
    int x,eval;
    if(nPl == 0){
        x = move_p1(players_copy, nPed, str, board_copy,0);
    }else{
        x = move_p2(players_copy, nPed, str, board_copy);
    }

    update_board(board_copy,players_copy);

    if(cheat == 1){
        set_moves_pawn(players_copy, board_copy, 0, -1);
        if ( is_selected(players_copy,x,1) ) {
            set_moves_pawn(players_copy, board_copy, 1,-1);
        }
        eval = minimax(*board_copy, players_copy, depth - 1, nPed, 1, v, 0,alpha,beta);
        if ( maxEval < eval ) {
            *beta = eval;
            maxEval = eval;
            v->value = eval;
            strcpy(v->directions, str);
            return eval;
        }else{
            return maxEval;
        }
    }else{
        set_moves_pawn(players_copy, board_copy, 1, -1);
        if(is_selected(players_copy,x,0) ){
            set_moves_pawn(players_copy, board_copy, 0, -1);
        }
        eval = minimax(*board_copy, players_copy, depth-1, nPed, 0,v, 1,alpha,beta);
        if ( maxEval > eval ) {
            *alpha = eval;
            maxEval = eval;
            v->value = eval;
            strcpy(v->directions, str);
            return eval;
        }else{
            return maxEval;
        }
    }
    return -1;
}

unsigned int interrupt_minimax(int *alpha ,int *beta){
    if(*alpha != -9999 && *beta != 9999){
        return (*beta <= *alpha) ;
    }
    return 0;
}

int evaluate_score(board_t board, player_t *players){
    int i, val = 0,j;
    for(j = 0 ; j < 2 ; ++j){
        for(i = 0 ; i < players[j].dim_pawns ; ++i){
            if(is_selected(players,i,j)){
                if (j == 0){
                    val+=players[j].pawns[i].grade;
                    if (players[j].pawns[i].isPromoted){
                        val++;
                    }                
                }else{
                    val-=players[j].pawns[i].grade;
                    if (players[j].pawns[i].isPromoted){
                        val--;
                    }                
                }
            }
        }
    }
    return val;
}

void print_minimax(valueMinimax_t *value_arr,unsigned int dim_arr){
    unsigned int i;
    for(i = 0 ; i < dim_arr ; ++i){
        if(value_arr[i].value == -9017){
            printf("\n\n*** MINIMAX ped. %u: non esiste ***\n\n",i);
        }else{
            printf("\n\n*** MINIMAX ped. %u: %d e %s***\n\n",i,value_arr[i].value,value_arr[i].directions );
        }
    }
}

unsigned int max(valueMinimax_t *arr,unsigned int dim){
    unsigned int i,pos = 0;
    int max;
    max = arr[0].value;
    for(i = 1 ; i < dim ; ++i){
        if(arr[i].value != -9017){
            if((check_string(arr[i].directions))&&(max < arr[i].value)){
                max = arr[i].value;
                pos = i;
            }
        }
    }
    return pos;
}

void destroy_value_minimax(valueMinimax_t *arr,unsigned int dim){
    unsigned int i;
    for(i = 0 ; i < dim ; ++i){
        free(arr[i].directions);
    }
    free(arr);
}