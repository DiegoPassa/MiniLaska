#ifndef MEMORY_MANAGEMENT_H
#define MEMORY_MANAGEMENT_H

/**
 * @brief Create a board object
 * 
 * @param n_rows 
 * @param n_cols 
 * @param cifre 
 * @return board_t* 
 */
board_t* create_board(unsigned int n_rows,unsigned int n_cols,unsigned int cifre);

/**
 * @brief Create a pawns object
 * 
 * @param totPawns 
 * @param player1 
 * @param player2 
 * @param cifre 
 * @param board 
 * @return player_t* 
 */
player_t *create_pawns(unsigned int totPawns,char player1, char player2, unsigned int cifre,board_t board);

/**
 * @brief 
 * 
 * @param board 
 * @param newBoard 
 * @param cifre 
 * @param set 
 * @return board_t* 
 */
board_t *copy_board(board_t board ,board_t *newBoard,unsigned int cifre,unsigned int set);

/**
 * @brief 
 * 
 * @param players 
 * @param newPlayers 
 * @param dim_label 
 * @param set 
 * @return player_t* 
 */
player_t *player_copy(player_t *players, player_t *newPlayers, unsigned int dim_label,unsigned int set);

/**
 * @brief 
 * 
 * @param players 
 */
void destroy_player (player_t *players);

/**
 * @brief 
 * 
 * @param board 
 */
void destroy_board(board_t *board);

/**
 * @brief 
 * 
 * @param board 
 * @param players 
 * @param board_copy 
 * @param players_copy 
 */
void restore_copy(board_t board, player_t *players, board_t *board_copy, player_t *players_copy);

#endif