#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "game_engine.h"

struct board{
    char **mat; /*!< Detailed description after the member */
    dim_board n_rows;
    dim_board n_cols;
};

struct point{
    coord x; /* cols */
    coord y; /* rows */
};

struct pawn{
    char *label; /* etichetta della pedina Es.|  BN07 | */
    unsigned int dim_label;
    point_t coordinate;
    unsigned int cima;
    unsigned int grade;
    flag isPromoted; /* Es: |  BN07^ | */
    unsigned int *canMove; /* 0010 -> bassodx */
};

struct player{
    char color;
    pawn_t *pawns;
    unsigned int dim_pawns;
};


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
        printf("Move %u : %u\n",i,arr[i]);
    }
    if(flag != 0){
        if(flag == 1){
            printf("La pedina %u puo' muoversi solo in questa direzione : \n",np);
        }else{
            printf("La pedina %u puo' muoversi in queste direzioni : \n",np);
        }
        for(i = 0 ; i < dim ; ++i){
            if(i == 0 && arr[0] == 1){
                printf("-> sx\n");
            }
            if(i == 1 && arr[1] == 1){
                printf("-> dx\n");
            }
            if(i == 2 && arr[2] == 1){
                printf("-> bassodx\n");
            }
            if(i == 3 && arr[3] == 1){
                printf("-> bassosx\n");
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
    if(!strcmp(str, "sx")){
        index = 0;
    }
    if(!strcmp(str, "dx")){
        index = 1;
    }
    if(!strcmp(str, "bassodx")){
        index = 2;
    }
    if(!strcmp(str, "bassosx")){
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
    if( ((nPl == 0)&&(can_eat(players,n_pawn,"sx",board, 0) >= 0)) || ((nPl == 1)&&(can_eat(players, n_pawn, "bassosx", board,1)>=0))  ){
        if(is_selected(players,n_pawn,nPl) && flag == 1){
            reset_moves_pawns(players, n_pawn, nPl);
            flag = 0;
        }
        players[nPl].pawns[n_pawn].canMove[0] = 1;
    }

    if( ((nPl == 0)&&(can_eat(players,n_pawn,"dx",board, 0) >= 0)) || ((nPl == 1)&&(can_eat(players, n_pawn, "bassodx", board,1)>=0))  ){
        if(is_selected(players,n_pawn,nPl) && flag == 1){
            reset_moves_pawns(players, n_pawn, nPl);
            flag = 0;
        }
        players[nPl].pawns[n_pawn].canMove[1] = 1;
    }

    if ((players[nPl].pawns[n_pawn].isPromoted)){

        if( ((nPl == 0)&&(can_eat(players,n_pawn,"bassodx",board, 0) >= 0)) || ((nPl == 1)&&(can_eat(players, n_pawn, "dx", board,1)>=0))  ){
            if(is_selected(players,n_pawn,nPl) && flag == 1){
                reset_moves_pawns(players, n_pawn, nPl);
                flag = 0;
            }
            players[nPl].pawns[n_pawn].canMove[2] = 1;
        }

        if( ((nPl == 0)&&(can_eat(players,n_pawn,"bassosx",board, 0) >= 0)) || ((nPl == 1)&&(can_eat(players, n_pawn, "sx", board,1)>=0))){
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
        if ((!strcmp(str, "sx"))) {
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
        if ((!strcmp(str, "dx"))) {
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
        if ((!strcmp(str, "bassosx")) ) {
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
        if ((!strcmp(str, "bassodx")) ) {
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

unsigned int all_blocked(player_t *players, board_t board, unsigned int nPl){
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

unsigned int round_choice(){
    char str[2];

    printf("Inizia il turno come da predefinito (quindi primo giocatore)? ");
    scanf("%s",str);
    if((!strcmp(str,"si"))||(!strcmp(str,"Si"))||(!strcmp(str,"SI"))){
        return 0;
    }else{
        printf("Lancio monetina ? ");
        scanf("%s",str);
        if((!strcmp(str,"no"))||(!strcmp(str,"NO"))||(!strcmp(str,"No")) ){
            unsigned int npl = 0;
            printf("Giocatore 1 o 2 inizia per primo? : ");
            scanf("%u",&npl);
            while(npl != 1 && npl != 2){
                printf("Quale giocatore inizia per primo(1/2) ? ");
                scanf("%u",&npl);
            }

            return npl-1;
        }
        if((!strcmp(str,"si"))||(!strcmp(str,"Si"))||(!strcmp(str,"SI"))){
            int x = 0 ;
            srand(time(NULL));
            while(x == 0){
                x = rand()%10;
            }
            if(x%2 == 0){
                x = 0;
            }else{
                x = 1;
            }
            return x;
        }
    }
    return 0;
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
        if( ( (nPl == 0)&&(move_p1(newPlayers, nPawn, "sx", newBoard, 0) > -2)) || ((nPl == 1)&&(move_p2(newPlayers, nPawn, "sx",  newBoard) > -2)) ){
            players[nPl].pawns[nPawn].canMove[0] = 1;
            flag = 1;
            newBoard = copy_board(board, newBoard,dim_label,0);
            newPlayers = player_copy(players,newPlayers, dim_label,0);
        }

        if( ((nPl == 0)&&(move_p1(newPlayers, nPawn, "dx", newBoard, 0) > -2)) || ((nPl == 1)&&(move_p2(newPlayers, nPawn, "dx", newBoard) > -2))){
             players[nPl].pawns[nPawn].canMove[1] = 1;
            flag = 1;
            newBoard = copy_board(board, newBoard,dim_label,0);
            newPlayers = player_copy(players,newPlayers, dim_label,0);
        }

        if (newPlayers[nPl].pawns[nPawn].isPromoted){
            if( ((nPl == 0)&&(move_p1(newPlayers, nPawn, "bassodx", newBoard, 0) > -2)) || ((nPl == 1)&&(move_p2(newPlayers, nPawn, "bassodx", newBoard) > -2))){
                players[nPl].pawns[nPawn].canMove[2] = 1;
                flag = 1;
                newBoard = copy_board(board, newBoard,dim_label,0);
                newPlayers = player_copy(players,newPlayers, dim_label,0);
            }
            if( ((nPl == 0)&&(move_p1(newPlayers, nPawn, "bassosx", newBoard, 0) > -2)) || ((nPl == 1)&&(move_p2(newPlayers, nPawn, "bassosx", newBoard) > -2))){
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
        printf("Errore nella is_notstuck\n");
        if(newBoard != NULL){
            destroy_board(newBoard);
        }
        if(newPlayers != NULL){
            destroy_player(newPlayers);
        }
        return 0;
    }
}

unsigned int add_pawn(player_t *players, unsigned int enemy_pawn, unsigned int nPl,char c ){
    int nPl2 = 1;

    if (nPl == 1){
        nPl2 = 0;
    }
    
    players[nPl].pawns = (pawn_t*)realloc(players[nPl].pawns,(players[nPl].dim_pawns+1)*sizeof(pawn_t));
    players[nPl].pawns[players[nPl].dim_pawns].label = (char*)calloc((players[nPl2].pawns[enemy_pawn].dim_label+3+1),sizeof(char));
    players[nPl].pawns[players[nPl].dim_pawns].canMove = (unsigned int*)calloc(2,sizeof(unsigned int));

    if((players[nPl].pawns) &&(players[nPl].pawns[players[nPl].dim_pawns].label)) {
        unsigned int i,index;
        char temp[3];
        temp[0] = ' ';
        temp[1] = c;
        temp[2] = players[nPl2].pawns[enemy_pawn].label[players[nPl2].pawns[enemy_pawn].cima]; /* 012 */

        players[nPl2].pawns[enemy_pawn].label[players[nPl2].pawns[enemy_pawn].cima] = ' ';
        players[nPl2].pawns[enemy_pawn].cima+=1;
        players[nPl2].pawns[enemy_pawn].grade-=1;

        players[nPl].pawns[players[nPl].dim_pawns].grade = players[nPl2].pawns[enemy_pawn].grade;
        players[nPl2].pawns[enemy_pawn].grade = 0;
        players[nPl].pawns[players[nPl].dim_pawns].cima = players[nPl2].pawns[enemy_pawn].cima;

        players[nPl].pawns[players[nPl].dim_pawns].coordinate.x = players[nPl2].pawns[enemy_pawn].coordinate.x;
        players[nPl].pawns[players[nPl].dim_pawns].coordinate.y = players[nPl2].pawns[enemy_pawn].coordinate.y;

        players[nPl].pawns[players[nPl].dim_pawns].dim_label = players[nPl2].pawns[enemy_pawn].dim_label;

        players[nPl].pawns[players[nPl].dim_pawns].isPromoted = 0;
        players[nPl2].pawns[enemy_pawn].isPromoted = 0;
        players[nPl2].pawns[players[nPl].dim_pawns].label[players[nPl].pawns[players[nPl].dim_pawns].dim_label+3] = ' ';
        players[nPl].pawns[players[nPl].dim_pawns].label[players[nPl].pawns[players[nPl].dim_pawns].dim_label+3] = ' ';

        /* in caso if per cifre e riadattare cifre*/
        for(i = 0 ; i < 3 ; ++i){
            players[nPl].pawns[players[nPl].dim_pawns].label[i] = temp[i];
        }
        index = players[nPl2].pawns[enemy_pawn].dim_label;
        for(i = 3 ; i < players[nPl2].pawns[enemy_pawn].dim_label+3 ; ++i){
            players[nPl].pawns[players[nPl].dim_pawns].label[i] = players[nPl2].pawns[enemy_pawn].label[i];
            --index;
        }

        ++players[nPl].dim_pawns;
        return 1;
    }else{
        printf("Errore nella realloc\n");
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
    if(!strcmp(str,"sx")){
        flag = 1;
    }
    if(!strcmp(str,"dx")){
        flag = 1;
    }
    if(!strcmp(str,"bassosx")){
        flag = 1;
    }
    if(!strcmp(str,"bassodx")){
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