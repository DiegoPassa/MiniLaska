#ifndef MEMORY_MANAGEMENT_H
#define MEMORY_MANAGEMENT_H

board_t* create_board(unsigned int n_rows,unsigned int n_cols,unsigned int cifre);

player_t *create_pawns(unsigned int totPawns,char player1, char player2, unsigned int cifre,board_t board);

board_t *copy_board(board_t board ,board_t *newBoard,unsigned int cifre,unsigned int set);

player_t *player_copy(player_t *players, player_t *newPlayers, unsigned int dim_label,unsigned int set);

void destroy_player (player_t *players);

void destroy_board(board_t *board);

void restore_copy(board_t board, player_t *players, board_t *board_copy, player_t *players_copy);

#endif