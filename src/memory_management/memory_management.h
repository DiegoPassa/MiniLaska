/**
 * @file memory_management.h
 * @author Diego Passarella, Davide Pasqual, Michelle Ravagnan
 * @version 1.0.2
 * @date 2021-01-17
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef MEMORY_MANAGEMENT_H
#define MEMORY_MANAGEMENT_H

/**
 * @brief Create a board object.
 * 
 * @param n_rows Number of row of the new board.
 * @param n_cols Number of columns of the new board.
 * @param cifre  Number of columns that are necessary to represent a label of one pawn.
 * @return board_t* Return a pointer of the board.
 */
board_t* create_board(unsigned int n_rows,unsigned int n_cols,unsigned int cifre);

/**
 * @brief Create a pawns object.
 * 
 * @param totPawns Number of pawns for each player.
 * @param player1 Characters of the pawn of player 1,and this is helpful for the print_board("../game_engine/game_engine.h").
 * @param player2 Characters of the pawn of player 2,and this is helpful for the print_board("../game_engine/game_engine.h").
 * @param cifre Numbers of characters to represent the number of a pawn.
 * @param board Instance of the board.
 * @return player_t* Return a pointer of the array players.
 */
player_t *create_pawns(unsigned int totPawns,char player1, char player2, unsigned int cifre,board_t board);

/**
 * @brief It copy all value of board to another board,eventually allocating memory if necessary.
 * 
 * @param board Instance of a board.
 * @param newBoard Pointer of a board where do the copy.
 * @param cifre Number of columns that are necessary to represent a label of one pawn.
 * @param set If 1 then the fuction allocating memory,0 else.
 * @return board_t* Return a pointer of a board that it is the copy of chessboard.
 */
board_t *copy_board(board_t board ,board_t *newBoard,unsigned int cifre,unsigned int set);

/**
 * @brief It copy all value of array players to another array players,eventually allocating memory if necessary.
 * 
 * @param players Pointer of players array.
 * @param newPlayers Pointer of players array where to make the copy.
 * @param dim_label Dimension of label array of pawn.
 * @param set If 1 then the fuction allocating memory,0 else.
 * @return player_t* Return a pointer of a players array that is the copy of players parameter.
 */
player_t *player_copy(player_t *players, player_t *newPlayers, unsigned int dim_label,unsigned int set);

/**
 * @brief Deallocate all allocated memory by create_pawns.
 * 
 * @param players Pointer of players array.
 */
void destroy_player (player_t *players);

/**
 * @brief Deallocate all allocated memory by create_board.
 * 
 * @param board Pointer of a board.
 */
void destroy_board(board_t *board);

/**
 * @brief Calls the two copy functions to summarize the various copy calls into one.
 * 
 * @param board Instance of a board.
 * @param players Pointer of players array.
 * @param board_copy Pointer of a board where do the copy.
 * @param players_copy Pointer of players array where to make the copy.
 */
void restore_copy(board_t board, player_t *players, board_t *board_copy, player_t *players_copy);

#endif