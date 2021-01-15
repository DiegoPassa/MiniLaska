#ifndef USER_INTERACTION_H
#define USER_INTERACTION_H

/**
 * @brief 
 * 
 * @param t 
 * @param cifre 
 * @param npl number of the player
 * @param char_p1 color of the first player
 * @param char_p2 color of the second player
 */
void print_board(board_t t,unsigned int cifre, unsigned npl, char char_p1, char char_p2);

/**
 * @brief  
 * 
 * @param players array wich contains the two players
 * @param nPl number that identify the player
 */
void print_player(player_t *players,unsigned int nPl);

/**
 * @brief 
 * 
 * @param players 
 * @param t 
 * @param nPl 
 * @return unsigned int 
 */
unsigned int round_player(player_t *players,board_t *t,unsigned int nPl);

/**
 * @brief 
 * 
 * @param x 
 * @return int 
 */
int game(unsigned int x);

/**
 * @brief 
 * 
 */
void menu();

#endif