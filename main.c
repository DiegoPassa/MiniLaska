#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "src/user_interaction/user_interaction.h"


int main(){


    /*menu();*/
    player_vs_player(0);

    /*player_vs_ia();*/

    /*board_t *board;
    player_t *players;

    board = create_board(7,7,6);
    initialize_board(board, 6);

    players = create_pawns(11, 'B', 'N', 2, *board);

    update_board(board, players);

    print_player(players[0]);
    print_player(players[1]);

    print_board(*board, 6, 0);*/
/*  tcampo *board;

    tplayer *p1;
    tplayer *p2;
    board = create_board(7, 7, 6);
    initialize_board(board, 6);
    p1 = create_pawns(11, 'B', 1, 2, *board);
    p2 = create_pawns(11, 'N', 2, 2, *board);

    update_board(board, *p1, *p2);

    set_moves_pawn(p1, p2, *board, 1);
    set_moves_pawn(p1, p2, *board, 2);

    print_board(*board, 6, 1);

    print_player(*p1);
    printf("\n");
    print_player(*p2);

    destroy_board(board);
    destroy_player(p1);
    destroy_player(p2); */

    return 0;
}

