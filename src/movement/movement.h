#ifndef MOVEMENT_H
#define MOVEMENT_H

/**
 * @brief 
 * 
 * @param players 
 * @param num_pawn 
 * @param str 
 * @param board 
 * @param nPl 
 * @return unsigned int 
 */
unsigned int move_noeat(player_t *players, unsigned int num_pawn, char *str, board_t *board, unsigned int nPl);

/**
 * @brief 
 * 
 * @param players 
 * @param str 
 * @param num_pawn 
 * @param board 
 * @param enemy_pawn 
 * @param nPl 
 * @return unsigned int 
 */
unsigned int eat(player_t *players, char *str, unsigned int num_pawn, board_t board, unsigned int enemy_pawn, unsigned int nPl);

/**
 * @brief 
 * 
 * @param players 
 * @param num_pawn 
 * @param str 
 * @param board 
 * @param nPl 
 * @return int 
 */
int move_p1 (player_t *players, unsigned int num_pawn, char *str, board_t *board, unsigned int nPl);

/**
 * @brief 
 * 
 * @param players 
 * @param num_pawn 
 * @param str 
 * @param board 
 * @return int 
 */
int move_p2(player_t *players,unsigned int num_pawn,char *str,board_t *board);

#endif