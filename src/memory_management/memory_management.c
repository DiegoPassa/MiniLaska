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
#include "../ia/ia.h"
#include "memory_management.h"
#include "../movement/movement.h"
#include "../user_interaction/user_interaction.h"


board_t* create_board(unsigned int n_rows,unsigned int n_cols,unsigned int cifre){
    board_t *t = NULL;

    t = (board_t*)malloc(sizeof(board_t));
    if(t != NULL){
        unsigned int i;
        t->n_rows = n_rows;
        t->n_cols = (n_cols*cifre);
        t->mat = (char**)calloc((t->n_rows),sizeof(char*));
        for(i = 0 ; i < t->n_rows ; ++i){
            t->mat[i] = calloc((t->n_cols),sizeof(char));
        }

        return t;
    }else{
        printf("Errore nella malloc nella funzione crea_campo\n");
        return NULL;
    }
}

player_t *create_pawns(unsigned int totPawns,char player1, char player2, unsigned int cifre, board_t board){
    player_t *players = NULL;
    int nPl;
    unsigned int h;

    players = (player_t*)calloc(2, sizeof(player_t));

    for (nPl = 0; nPl < 2; nPl++){
        players[nPl].pawns = (pawn_t*)calloc(totPawns,sizeof(pawn_t));
        for(h = 0 ; h < totPawns ; ++h){
            players[nPl].pawns[h].label = (char*)calloc((cifre+3+1),sizeof(char));
        }
        if( (players != NULL) && (players[nPl].pawns != NULL)){
            unsigned int i,nr,nc = 0;
            int c = -1;

            if(nPl == 0){
                nr = board.n_rows-1;
            }else{
                nr = 0;
            }
            while(c == -1){
                if(board.mat[nr][nc] == '#'){
                    c = nc;
                }
                ++nc;
            }
            nc = c ;

            for(i = 0 ; i < totPawns ; ++i){
                players[nPl].pawns[i].canMove = (unsigned int*) calloc(2, sizeof(unsigned int));
                players[nPl].pawns[i].label[0] = ' ';
                players[nPl].pawns[i].label[1] = ' ';
                if (nPl == 0){
                    players[nPl].pawns[i].label[2] = player1;
                }else{
                    players[nPl].pawns[i].label[2] = player2;                 
                }
                  
                if(i < 10){
                    unsigned int z;
                    for(z = 3 ; z < (3+cifre)-1 ; ++z){
                        players[nPl].pawns[i].label[z] = '0';
                    }
                    players[nPl].pawns[i].label[(3+cifre)-1] = '0'+i;
                }else {
                    unsigned int dest,index,num;
                    index = cifre-1;
                    if ((pow(10, index-1) == i) && (i != 1)) {
                        --index;
                    }
                    num = i;
                    for(dest = 3 ; dest < cifre+3 ; ++dest){
                        players[nPl].pawns[i].label[dest] = int_converter(num,index);
                        num -= pow(10,index)*(players[nPl].pawns[i].label[dest]-'0');
                        --index;
                    }
                }
                players[nPl].pawns[i].label[3+cifre] = ' ';
                players[nPl].pawns[i].dim_label = cifre;
                players[nPl].pawns[i].cima = 2 ;
                players[nPl].pawns[i].grade = 1 ;
                players[nPl].pawns[i].coordinate.y = nr;
                players[nPl].pawns[i].coordinate.x = nc;
                if (nPl == 0){
                    players[nPl].color = player1;
                }else{
                    players[nPl].color = player2;
                }
                
                if(nPl == 0){
                    if((nc+((3+cifre+1)*2) < board.n_cols) && (nc+((3+cifre+1)*2) > 0)){
                        nc +=((3+cifre+1)*2);
                    }else{
                        --nr;
                        if( c == 0){
                            c = (3+cifre+1) ;
                            nc = (3+cifre+1);
                        }else{
                            c = 0;
                            nc = 0;
                        }
                    }
                }else{
                    if((nc+((3+cifre+1)*2) < board.n_cols) && (nc+((3+cifre+1)*2) > 0)){
                        nc +=((3+cifre+1)*2);
                    }else{
                        ++nr;
                        if( c == 0){
                            c = (3+cifre+1) ;
                            nc = (3+cifre+1);
                        }else{
                            c = 0;
                            nc = 0;
                        }

                    }
                }

            }
            players[nPl].dim_pawns = totPawns;
        }else{
            printf("Errore malloc funzione crea_pedine\totPawns");
            return NULL;
        }
    }
    return players;  
}

board_t *copy_board(board_t board ,board_t *newBoard,unsigned int cifre,unsigned int set){
    if(set){
        newBoard = (board_t*)malloc(sizeof(board_t));
    }
    if(newBoard != NULL){
        unsigned int j,k;
        newBoard->n_rows = board.n_rows;
        newBoard->n_cols = board.n_cols;
        if(set){
            unsigned int i;
            newBoard->mat = (char**)calloc(board.n_rows,sizeof(char*));
            for(i = 0 ; i < board.n_rows ; ++i){
                newBoard->mat[i] = (char*)calloc(board.n_cols,sizeof(char));
            }
            if(!(newBoard->mat)){
                printf("Errore nella campo_copy(malloc della matrice di char)");
                return NULL;
            }
        }
        for(k = 0 ; k < board.n_rows ; ++k){
            for(j = 0 ; j < board.n_cols ; ++j){
                newBoard->mat[k][j] = board.mat[k][j];
            }
        }
        return newBoard;
    }else{
        printf("Errore nella campo_copy (malloc di newBoard)");
        return NULL;
    }
}

player_t *player_copy(player_t *players, player_t *newPlayers, unsigned int dim_label,unsigned int set){
    if(set == 1){
        unsigned int l,nPl;
        newPlayers = (player_t*)calloc(2, sizeof(player_t));
        for(nPl = 0 ; nPl < 2 ; ++nPl){
            newPlayers[nPl].pawns = (pawn_t*)calloc(players[nPl].dim_pawns,sizeof(pawn_t));
            for(l = 0 ; l < players[nPl].dim_pawns ; ++l){
                newPlayers[nPl].pawns[l].label = (char*)malloc(dim_label*sizeof(char));
            }
            for(l = 0 ; l < players[nPl].dim_pawns ; ++l){
                unsigned int dim = 2;
                if( players[nPl].pawns[l].isPromoted){
                    dim = 4;
                }
                newPlayers[nPl].pawns[l].canMove = (unsigned int*)calloc(dim,sizeof(unsigned int));
            }
        }

    }
    if(newPlayers != NULL  ){
        unsigned int  nPl;
        for (nPl = 0; nPl < 2; nPl++) {
            unsigned int i, j;

            newPlayers[nPl].dim_pawns = players[nPl].dim_pawns;
            newPlayers[nPl].color = players[nPl].color;

            for (i = 0; i < players[nPl].dim_pawns; ++i) {

                newPlayers[nPl].pawns[i].isPromoted = players[nPl].pawns[i].isPromoted;
                if (players[nPl].pawns[i].isPromoted == 0) {
                    newPlayers[nPl].pawns[i].canMove[0] = players[nPl].pawns[i].canMove[0];
                    newPlayers[nPl].pawns[i].canMove[1] = players[nPl].pawns[i].canMove[1];
                }else{
                    int k;
                    for(k = 0 ; k < 4 ; ++k){
                        newPlayers[nPl].pawns[i].canMove[k] = players[nPl].pawns[i].canMove[k];
                    }
                }
                newPlayers[nPl].pawns[i].dim_label = players[nPl].pawns[i].dim_label;
                newPlayers[nPl].pawns[i].cima = players[nPl].pawns[i].cima;
                newPlayers[nPl].pawns[i].grade = players[nPl].pawns[i].grade;
                newPlayers[nPl].pawns[i].coordinate.y = players[nPl].pawns[i].coordinate.y;
                newPlayers[nPl].pawns[i].coordinate.x = players[nPl].pawns[i].coordinate.x;



                for (j = 0; j < dim_label; ++j) {
                    newPlayers[nPl].pawns[i].label[j] = players[nPl].pawns[i].label[j];
                }
            }
        }

        return newPlayers;
    }else{
        printf("Errore player_copy");
        return NULL;
    }
}

void destroy_player (player_t *players){
    unsigned int i, nPl;

    for (nPl = 0; nPl < 2; nPl++){
        for(i = 0 ; i < players[nPl].dim_pawns ;++i){
            if (players[nPl].pawns[i].canMove){
                free(players[nPl].pawns[i].canMove);
            }
            
            free(players[nPl].pawns[i].label);
        }
        free(players[nPl].pawns);
    }
    
    free(players);
}

void destroy_board(board_t *board) {
    unsigned int i;

    for (i = 0; i < board->n_rows ;++i) {
        free(board->mat[i]);
    }
    free(board->mat);
    free(board);
}

void restore_copy(board_t board, player_t *players, board_t *board_copy, player_t *players_copy){
    board_copy = copy_board(board, board_copy,players[0].pawns[0].dim_label+3+1,0);
    players_copy = player_copy(players, players_copy, players[0].pawns[0].dim_label+3+1,0);
}