/**
 * @file user_interaction.h
 * @author Diego Passarella, Davide Pasqual, Michelle Ravagnan
 * @version 1.0.2
 * @date 2021-01-17
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef USER_INTERACTION_H
#define USER_INTERACTION_H

/**
 * @brief Print the board of game from the prospective of a given number of player.
 * 
 * @param t Instance of the board.
 * @param cifre Total number of space stored for the label of a pawn.
 * @param npl Number of the player.
 * @param char_p1 Color of the first player.
 * @param char_p2 Color of the second player.
 */
void print_board(board_t t,unsigned int cifre, unsigned npl, char char_p1, char char_p2);

/**
 * @brief Print the most important fields of a given number of player.
 * 
 * @param Players array wich contains the two players.
 * @param nPl Number that identify the player.
 */
void print_player(player_t *players,unsigned int nPl);

/**
 * @brief Ask the player for a pawn number to select.
 *
 * @param players Pointer to the players array.
 * @param nPl  Number that identify the player.
 * @return unsigned int Return a number of a pawn.
 */
unsigned int while_select_nPawn(player_t *players,unsigned int nPl);

/**
 * @brief Run the game round player.
 * 
 * @param players  Pointer to the players array.
 * @param t  Pointer to the board.
 * @param nPl Number that identify the player.
 * @return unsigned int Return 4 for continue the while loop to play the game in function game.
 */
unsigned int round_player(player_t *players,board_t *t,unsigned int nPl);

/**
 * @brief Determine which player goes first.
 *
 * @return unsigned int Return 0 if Player 1 goes first,1 if Player 2 goes first.
 */
unsigned int round_choice();

/**
 * @brief Allocate memory for structs(with call of create function), use in-game memory in any mode, and finally free up memory(with call of destroy function).
 * 
 * @param x If 0 the game mode is player vs player ,else is player vs ia.
 * @return int 
 */
int game(unsigned int x);

/**
 * @brief Check if the inserted value is an integer.
 * 
 * @param scanfValue Value of return of the scanf.
 * @return int Return correct value.
 */
int checkInt(int scanfValue);

/**
 * @brief Cleans the terminal and launches the main game menu.
 * 
 */
void menu();

#endif