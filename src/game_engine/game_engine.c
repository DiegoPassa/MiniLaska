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
#include "game_engine.h"
#include "../ia/ia.h"
#include "../memory_management/memory_management.h"
#include "../movement/movement.h"
#include "../user_interaction/user_interaction.h"

void initialize_board(board_t *board,unsigned int cifre){
    unsigned int i,j;

    for(i = 0 ; i < board->n_rows ; ++i) {
        for (j = 0; j < board->n_cols; j += cifre) {

            if (((j / cifre) + i) % 2 == 0) {
                int z;
                for (z = 0; z < cifre; ++z) {
                    board->mat[i][j+z] = '#';
                }

            } else {
                int z;
                for (z = 0; z < cifre; ++z) {
                    board->mat[i][j+z] = ' ';
                }

            }
        }
    }
}

void print_directions(unsigned int *arr,unsigned int dim,unsigned int np){
    unsigned int i,flag = 0;
    for(i = 0 ; i < dim ;++i){
        if(arr[i]){
            ++flag;
        }
    }
    if(flag != 0){
        if(flag == 1){
            printf(" Pawn no. %u can move only in this direction: \n",np);
        }else{
            printf(" Pawn no. %u can move in these directions : \n",np);
        }
        for(i = 0 ; i < dim ; ++i){
            if(i == 0 && arr[0] == 1){
                printf(" -> left [l]\n");
            }
            if(i == 1 && arr[1] == 1){
                printf(" -> right [r]\n");
            }
            if(i == 2 && arr[2] == 1){
                printf(" -> bottom right [botr]\n");
            }
            if(i == 3 && arr[3] == 1){
                printf(" -> bottom left [botl]\n");
            }
        }
    }
}

void update_board(board_t *t,player_t *player){
    unsigned int i;
    unsigned int pl;

    for (pl = 0; pl < 2; ++pl){
        for(i = 0 ; i < player[pl].dim_pawns ; ++i){
            if(is_selected(player,i,pl)){
                unsigned int j;
                for(j = 0 ; j < player[pl].pawns[i].dim_label+3+1 ; ++j){
                    if(player[pl].pawns[i].coordinate.y < t->n_rows && player[pl].pawns[i].coordinate.x < t->n_cols ){
                        t->mat[player[pl].pawns[i].coordinate.y][player[pl].pawns[i].coordinate.x+j] = player[pl].pawns[i].label[j];
                    }
                }
            }
        }
    }
}

unsigned int check_spot(board_t board,unsigned int row,unsigned int col,unsigned int dim_label){
    unsigned int i;
    if(row < board.n_rows && col < board.n_cols){
        for(i = 0 ; i < dim_label; ++i){
            if( (board.mat[row][col+i] != '#' ) ){
                return 1;
            }
        }
    }
    return 0;
}

unsigned int is_selected(player_t *player, int num_pawn, unsigned int nPl){
    if(((num_pawn > -1)&&(num_pawn < player[nPl].dim_pawns))&&(player[nPl].pawns[num_pawn].grade > 0)){
        return 1;
    }else{
        return 0;
    }
}

void remove_pawn(board_t *board, unsigned int row, unsigned int col, unsigned int dim_label){
    unsigned int i;
    if(row < board->n_rows && col < board->n_cols){
        for(i = 0 ; i < dim_label ; ++i){
            board->mat[row][col+i] = '#';
        }
    }

}

void pawn_promotion(player_t *players, unsigned int num_pawn, unsigned int nPl, unsigned int last_row){
    if(((nPl == 0)&&(players[nPl].pawns[num_pawn].coordinate.y == 0)) || ((nPl == 1)&&(players[nPl].pawns[num_pawn].coordinate.y == last_row))){
        players[nPl].pawns[num_pawn].isPromoted = 1;
        players[nPl].pawns[num_pawn].label[players[nPl].pawns[num_pawn].dim_label+3] = '^';
        free(players[nPl].pawns[num_pawn].canMove);
        players[nPl].pawns[num_pawn].canMove = (unsigned int*)calloc(4 ,sizeof(unsigned int));
    }
}

int check_player(player_t *players, unsigned int x, unsigned int y,unsigned int nPl){
    unsigned int  i,j = 1;
    int flag = -1;
    if(nPl == 1){
        j = 0;
    }
    for(i = 0 ; i < players[j].dim_pawns ; ++i){
        if((players[j].pawns[i].coordinate.y == x)&&(players[j].pawns[i].coordinate.x == y) && j != nPl && is_selected(players,i,j)){
            flag = j;
        }
    }

    return flag;
}

unsigned int is_in(int r, int c, board_t board){
    if( (r < board.n_rows)&&(c<board.n_cols)){
        return 1;
    }else {
        return 0;
    }
}

unsigned int check_directions(unsigned int *canMove_arr, unsigned int dim_canMove, char *str){
    unsigned int flag = 0, index = 5;
    for(index = 0 ; index < dim_canMove ; ++index){
        if(canMove_arr[index]){
            flag = 1;
        }
    }
    if(!flag){
        return 1;
    }
    if(!strcmp(str, "l")){
        index = 0;
    }
    if(!strcmp(str, "r")){
        index = 1;
    }
    if(!strcmp(str, "botr")){
        index = 2;
    }
    if(!strcmp(str, "botl")){
        index = 3;
    }
    if( index < dim_canMove && canMove_arr[index] == 1 ){
        return 1;
    }else{
        return 0;
    }
}

void must_eat(player_t *players, board_t *board, unsigned int n_pawn, unsigned int nPl){

    unsigned int flag = 1; 
    if( ((nPl == 0)&&(can_eat(players,n_pawn,"l",board, 0) >= 0)) || ((nPl == 1)&&(can_eat(players, n_pawn, "botl", board,1)>=0))  ){
        if(is_selected(players,n_pawn,nPl) && flag == 1){
            reset_moves_pawns(players, n_pawn, nPl);
            flag = 0;
        }
        players[nPl].pawns[n_pawn].canMove[0] = 1;
    }

    if( ((nPl == 0)&&(can_eat(players,n_pawn,"r",board, 0) >= 0)) || ((nPl == 1)&&(can_eat(players, n_pawn, "botr", board,1)>=0))  ){
        if(is_selected(players,n_pawn,nPl) && flag == 1){
            reset_moves_pawns(players, n_pawn, nPl);
            flag = 0;
        }
        players[nPl].pawns[n_pawn].canMove[1] = 1;
    }

    if ((players[nPl].pawns[n_pawn].isPromoted)){

        if( ((nPl == 0)&&(can_eat(players,n_pawn,"botr",board, 0) >= 0)) || ((nPl == 1)&&(can_eat(players, n_pawn, "r", board,1)>=0))  ){
            if(is_selected(players,n_pawn,nPl) && flag == 1){
                reset_moves_pawns(players, n_pawn, nPl);
                flag = 0;
            }
            players[nPl].pawns[n_pawn].canMove[2] = 1;
        }

        if( ((nPl == 0)&&(can_eat(players,n_pawn,"botl",board, 0) >= 0)) || ((nPl == 1)&&(can_eat(players, n_pawn, "l", board,1)>=0))){
            if(is_selected(players,n_pawn,nPl) && flag == 1){
                reset_moves_pawns(players, n_pawn, nPl);
                flag = 0;
            }
            players[nPl].pawns[n_pawn].canMove[3] = 1;
        }
    }
}

int can_eat(player_t *players, unsigned int num_pawn, char *str, board_t *board, unsigned int nPl) {
    unsigned int nPl2 = 1;
    if(nPl == 1){
        nPl2 = 0;
    }
    if(!is_selected(players,num_pawn,nPl)){
        return -1;
    }
    if((nPl == 0)||(players[nPl].pawns[num_pawn].isPromoted)) {
        if ((!strcmp(str, "l"))) {
            if ((is_in(players[nPl].pawns[num_pawn].coordinate.y-2, players[nPl].pawns[num_pawn].coordinate.x - ((players[nPl].pawns[num_pawn].dim_label + 3 + 1) * 2), *board)) &&
                ((is_in(players[nPl].pawns[num_pawn].coordinate.y - 1, players[nPl].pawns[num_pawn].coordinate.x - (players[nPl].pawns[num_pawn].dim_label + 3 + 1), *board)))) {
                 int x, y, z;
                x = players[nPl].pawns[num_pawn].coordinate.y - 1;
                y = players[nPl].pawns[num_pawn].coordinate.x - (players[nPl].pawns[num_pawn].dim_label + 3 + 1);
                z = check_player(players, x, y,nPl);
                if ((z == nPl2  ) &&
                    (check_spot(*board, players[nPl].pawns[num_pawn].coordinate.y - 1, players[nPl].pawns[num_pawn].coordinate.x - (players[nPl].pawns[num_pawn].dim_label + 3 + 1),
                                (players[nPl].pawns[num_pawn].dim_label + 3 + 1))) &&
                    (!check_spot(*board, players[nPl].pawns[num_pawn].coordinate.y - 2, players[nPl].pawns[num_pawn].coordinate.x - ((players[nPl].pawns[num_pawn].dim_label + 3 + 1) * 2),
                                 (players[nPl].pawns[num_pawn].dim_label + 3 + 1)))) {
                    int num = -1;
                    num = char_converter(*board, players[nPl].pawns[num_pawn].coordinate.y - 1, players[nPl].pawns[num_pawn].coordinate.x - (players[nPl].pawns[num_pawn].dim_label + 3 + 1),
                                         2 + players[nPl].pawns[num_pawn].dim_label);
                    if ((num > -1) && (num < players[nPl].dim_pawns)) {
                        return num;
                    } else {
                        return -1;
                    }
                } else {
                    return -2;
                }
            } else {
                return -3;
            }
        }
        if ((!strcmp(str, "r"))) {
            if ((is_in(players[nPl].pawns[num_pawn].coordinate.y - 2, players[nPl].pawns[num_pawn].coordinate.x + ((players[nPl].pawns[num_pawn].dim_label + 3 + 1) * 2), *board)) &&
                ((is_in(players[nPl].pawns[num_pawn].coordinate.y - 1, players[nPl].pawns[num_pawn].coordinate.x + (players[nPl].pawns[num_pawn].dim_label + 3 + 1), *board)))) {
                 int x, y, z;
                x = players[nPl].pawns[num_pawn].coordinate.y - 1;
                y = players[nPl].pawns[num_pawn].coordinate.x + (players[nPl].pawns[num_pawn].dim_label + 3 + 1);
                z = check_player(players, x, y,nPl);
                if ((z ==  nPl2 ) &&
                    (check_spot(*board, players[nPl].pawns[num_pawn].coordinate.y - 1, players[nPl].pawns[num_pawn].coordinate.x + (players[nPl].pawns[num_pawn].dim_label + 3 + 1),
                                players[nPl].pawns[num_pawn].dim_label + 3 + 1)) &&
                    (!check_spot(*board, (players[nPl].pawns[num_pawn].coordinate.y - 2), (players[nPl].pawns[num_pawn].coordinate.x + ((players[nPl].pawns[num_pawn].dim_label + 3 + 1) * 2)),
                                 (players[nPl].pawns[num_pawn].dim_label + 3 + 1)))) {
                    int num = -1;
                    num = char_converter(*board, players[nPl].pawns[num_pawn].coordinate.y - 1, players[nPl].pawns[num_pawn].coordinate.x + (players[nPl].pawns[num_pawn].dim_label + 3 + 1),
                                         2 + players[nPl].pawns[num_pawn].dim_label);
                    if ((num > -1) && (num < players[nPl].dim_pawns)) {
                        return num;
                    } else {
                        return -1;
                    }

                } else {
                    return -2;
                }
            } else {
                return -3;
            }
        }
    }
    if (((nPl == 1) || (players[nPl].pawns[num_pawn].isPromoted))) {
        if ((!strcmp(str, "botl")) ) {
            if ((is_in(players[nPl].pawns[num_pawn].coordinate.y + 2, players[nPl].pawns[num_pawn].coordinate.x - ((players[nPl].pawns[num_pawn].dim_label + 3 + 1) * 2), *board)) &&
                ((is_in(players[nPl].pawns[num_pawn].coordinate.y + 1, players[nPl].pawns[num_pawn].coordinate.x - (players[nPl].pawns[num_pawn].dim_label + 3 + 1), *board)))) {
                 int x, y, z;
                x = players[nPl].pawns[num_pawn].coordinate.y + 1;
                y = players[nPl].pawns[num_pawn].coordinate.x - (players[nPl].pawns[num_pawn].dim_label + 3 + 1);
                z = check_player(players, x, y,nPl);
                if ((z ==  nPl2 ) && (check_spot(*board, players[nPl].pawns[num_pawn].coordinate.y + 1, players[nPl].pawns[num_pawn].coordinate.x - (players[nPl].pawns[num_pawn].dim_label + 3 + 1),
                                           (players[nPl].pawns[num_pawn].dim_label + 3 + 1))) &&
                    (!check_spot(*board, (players[nPl].pawns[num_pawn].coordinate.y + 2), (players[nPl].pawns[num_pawn].coordinate.x - ((players[nPl].pawns[num_pawn].dim_label + 3 + 1) * 2)),
                                (players[nPl].pawns[num_pawn].dim_label + 3 + 1)))) {
                    int num = -1;
                    num =  char_converter(*board, players[nPl].pawns[num_pawn].coordinate.y + 1, players[nPl].pawns[num_pawn].coordinate.x - (players[nPl].pawns[num_pawn].dim_label + 3 + 1), 2 + players[nPl].pawns[num_pawn].dim_label);
                    if ((num > -1) && (num < players[nPl].dim_pawns)) {
                        return num;
                    } else {
                        return -1;
                    }
                } else {
                    return -2;
                }
            } else {
                return -3;
            }
        }
        if ((!strcmp(str, "botr")) ) {
            if ((is_in(players[nPl].pawns[num_pawn].coordinate.y + 2, players[nPl].pawns[num_pawn].coordinate.x + ((players[nPl].pawns[num_pawn].dim_label + 3 + 1) * 2), *board)) &&
                ((is_in(players[nPl].pawns[num_pawn].coordinate.y + 1, players[nPl].pawns[num_pawn].coordinate.x + (players[nPl].pawns[num_pawn].dim_label + 3 + 1), *board)))) {
                 int x, y, z;
                x = players[nPl].pawns[num_pawn].coordinate.y + 1;
                y = players[nPl].pawns[num_pawn].coordinate.x + (players[nPl].pawns[num_pawn].dim_label + 3 + 1);
                z = check_player(players, x, y,nPl);
                if ((z ==  nPl2 ) && (check_spot(*board, players[nPl].pawns[num_pawn].coordinate.y + 1, players[nPl].pawns[num_pawn].coordinate.x + (players[nPl].pawns[num_pawn].dim_label + 3 + 1),
                                           (players[nPl].pawns[num_pawn].dim_label + 3 + 1)) &&
                                 (!check_spot(*board, (players[nPl].pawns[num_pawn].coordinate.y + 2), (players[nPl].pawns[num_pawn].coordinate.x + ((players[nPl].pawns[num_pawn].dim_label + 3 + 1) * 2)),
                                             (players[nPl].pawns[num_pawn].dim_label + 3 + 1))))) {
                    int num = -1;
                    num =  char_converter(*board, players[nPl].pawns[num_pawn].coordinate.y + 1, players[nPl].pawns[num_pawn].coordinate.x + (players[nPl].pawns[num_pawn].dim_label + 3 + 1), 2 + players[nPl].pawns[num_pawn].dim_label);
                    if ((num > -1) && (num < players[nPl].dim_pawns)) {
                        return num;
                    } else {
                        return -1;
                    }
                } else {
                    return -2;
                }
            } else {
                return -3;
            }
        } else {
            return -4;
        }
    }
    return -3;
}

unsigned int all_blocked(player_t *players, unsigned int nPl){
    unsigned int i, flag = 1;
    for(i = 0 ; i < players[nPl].dim_pawns ; ++i){
        if(players[nPl].pawns[i].grade > 0 && check_canMove(players, i,nPl)){
            flag = 0;
        }
    }
    return flag;
}

unsigned int is_victory(player_t *players){
    int i, nPl, winner_p1 = 0, winner_p2 = 0, flag = 0 ;

    for (nPl = 0; nPl < 2; nPl++){
        for(i = 0 ; i < players[nPl].dim_pawns ; ++i){
            players[nPl].pawns[i].grade == 0 && nPl == 1 ? ++winner_p1 : winner_p1;
            players[nPl].pawns[i].grade == 0 && nPl == 0 ? ++winner_p2 : winner_p2;
        }
    }
    if(winner_p1 == players[1].dim_pawns){
        winner_p1 = 0;
        i = 1;
    }else if (winner_p2 == players[0].dim_pawns ){
        winner_p2 = 1;
        i = 2;
    }
    if(winner_p1 == 0 && winner_p2 == 1){
        flag = 17;
    }else{
        flag = 17;
        if(winner_p2 == 1 && i == 2){
            flag = i;
        }
        if(winner_p1 == 0 && i == 1){
            flag = i;
        }
    }
    return flag;
}

int is_empty(player_t p){
    int i;
    for(i = 0 ; i < p.dim_pawns ; ++i){
        if(p.pawns[i].grade == 0){
            return i;
        }
    }
    return -1;
}

unsigned int max_pawns(unsigned int r,unsigned int c){
    unsigned int k,l,t = 0,numped = 0;

    l = ((r+1)/2)-1;
    k = (c+1)/2;
    if(r%2 == 0){
        --r;
    }
    while(r-1 > l){
        if(!t){
            numped += k;
            t = 1;
        }else{
            if(c%2 != 0){
                numped += k-1;
            }else{
                numped += k;
            }
            t = 0;
        }
        --r;
    }

    return numped;
}

unsigned int is_notstuck(player_t *players, board_t board, unsigned int nPawn, unsigned int nPl){
    board_t *newBoard = NULL;
    player_t *newPlayers = NULL;
    unsigned int dim_label = 0;

    dim_label = (players[0].pawns[0].dim_label+3+1);
  
    newBoard = copy_board(board, newBoard,dim_label,1);

    newPlayers = player_copy(players, newPlayers, dim_label,1);

    if(newBoard != NULL && newPlayers != NULL){
        unsigned int flag = 0;
        update_board(newBoard, newPlayers);
        if( ( (nPl == 0)&&(move_p1(newPlayers, nPawn, "l", newBoard, 0) > -2)) || ((nPl == 1)&&(move_p2(newPlayers, nPawn, "l",  newBoard) > -2)) ){
            players[nPl].pawns[nPawn].canMove[0] = 1;
            flag = 1;
            newBoard = copy_board(board, newBoard,dim_label,0);
            newPlayers = player_copy(players,newPlayers, dim_label,0);
        }

        if( ((nPl == 0)&&(move_p1(newPlayers, nPawn, "r", newBoard, 0) > -2)) || ((nPl == 1)&&(move_p2(newPlayers, nPawn, "r", newBoard) > -2))){
             players[nPl].pawns[nPawn].canMove[1] = 1;
            flag = 1;
            newBoard = copy_board(board, newBoard,dim_label,0);
            newPlayers = player_copy(players,newPlayers, dim_label,0);
        }

        if (newPlayers[nPl].pawns[nPawn].isPromoted){
            if( ((nPl == 0)&&(move_p1(newPlayers, nPawn, "botr", newBoard, 0) > -2)) || ((nPl == 1)&&(move_p2(newPlayers, nPawn, "botr", newBoard) > -2))){
                players[nPl].pawns[nPawn].canMove[2] = 1;
                flag = 1;
                newBoard = copy_board(board, newBoard,dim_label,0);
                newPlayers = player_copy(players,newPlayers, dim_label,0);
            }
            if( ((nPl == 0)&&(move_p1(newPlayers, nPawn, "botl", newBoard, 0) > -2)) || ((nPl == 1)&&(move_p2(newPlayers, nPawn, "botl", newBoard) > -2))){
                players[nPl].pawns[nPawn].canMove[3] = 1;
                flag = 1;
                newBoard = copy_board(board, newBoard,dim_label,0);
                newPlayers = player_copy(players,newPlayers, dim_label,0);
            }
        }
        destroy_board(newBoard);
        destroy_player(newPlayers);
        return flag;
    }else{
        printf(" Error in the is_notstuck function\n");
        if(newBoard != NULL){
            destroy_board(newBoard);
        }
        if(newPlayers != NULL){
            destroy_player(newPlayers);
        }
        return 0;
    }
}

void set_moves_pawn(player_t *players, board_t *board, unsigned int nPl, int nPawn){

    if(nPawn == -1){
        int i;
        reset_moves_pawns(players, -1, nPl);
        for(i = 0; i < players[nPl].dim_pawns; ++i){
            if(is_selected(players,i,nPl)){
                is_notstuck(players, *board, i, nPl);
                must_eat(players, board, i, nPl);

            }
        }

    }else{
        if(nPawn > 0 && nPawn < players[nPl].dim_pawns){
            reset_moves_pawns(players, nPawn, nPl);
            if(is_selected(players,nPawn,nPl)){
                is_notstuck(players, *board, nPawn, nPl);
                must_eat(players, board, nPawn, nPl);
            }
        }
    }
}

void reset_moves_pawns(player_t *players, int nPawn, unsigned int nPl){
    unsigned int i;
    if (nPawn == -1){
        for(i = 0 ; i < players[nPl].dim_pawns ; ++i){
            unsigned int j,z;
            if(players[nPl].pawns[i].isPromoted == 1){
                z = 4;
            }else{
                z = 2;
            }
            for(j = 0; j < z ; ++j){
                players[nPl].pawns[i].canMove[j] = 0;
            }
        }
    }else{
        unsigned int j,z;
        if(players[nPl].pawns[nPawn].isPromoted == 1){
            z = 4;
        }else{
            z = 2;
        }
        for(j = 0; j < z ; ++j){
            players[nPl].pawns[nPawn].canMove[j] = 0;
        }   
    } 
}

unsigned int check_canMove(player_t *players, unsigned int nPed,unsigned int nPl){
    unsigned int i = 0, dim = 2, flag = 0;
    if (players[nPl].pawns[nPed].isPromoted == 1){
        dim = 4;
    }
    while (i < dim){
        if (players[nPl].pawns[nPed].canMove[i] == 1){
            flag = 1;
        }

        i++;
    }
    return flag;
}

unsigned int check_while(player_t *players, unsigned int nPl, unsigned int nPawn){
    unsigned int flag = 0;
    if ( ( (nPawn >= 0) && (nPawn < players[nPl].dim_pawns)) && (is_selected(players,nPawn,nPl)) ){
        flag  = check_canMove(players, nPawn,nPl);
    }
    return flag;
}

unsigned int check_string(char *str){
    unsigned int flag = 0;
    if(!strcmp(str,"l")){
        flag = 1;
    }
    if(!strcmp(str,"r")){
        flag = 1;
    }
    if(!strcmp(str,"botl")){
        flag = 1;
    }
    if(!strcmp(str,"botr")){
        flag = 1;
    }
    return flag;
}

unsigned int char_converter(board_t board, unsigned int r, unsigned int c, unsigned int dim_label){
    unsigned int i,num = 0,z = 0;
    for(i = dim_label ; i > 2 ; --i){
        num += ((board.mat[r][c+i]-'0')*pow(10,z));
        z++;
    }
    return num;
}

char int_converter(int num,unsigned int index){

    char let;
    let = '0';
    if((num/pow(10,index)) > 0){
        return (let+(num/pow(10,index)));
    }else{
        return '0';
    }
}
char uppercase(char c){
    return ((c-'a')+'A');
}

unsigned int check_char_color(char c){
    char new_c = c;
    unsigned int flag = 1;
    if(c >= 'a' && c <= 'z'){
        new_c = uppercase(c);
        flag = 2 ;
    }
    if( new_c == 'R'|| new_c == 'G' || new_c == 'M' || new_c == 'B' || new_c == 'C' || new_c == 'Y' ){
        return flag;
    }else{
        return 0;
    }
}