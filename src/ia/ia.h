#ifndef IA_H
#define IA_H

/**
 * @brief 
 * 
 */
typedef struct valueMinimax valueMinimax_t;

/**
 * @brief 
 * 
 * @param players 
 * @param board 
 * @param nPl 
 * @return unsigned int 
 */
unsigned int round_ia_random(player_t *players, board_t *board, unsigned int nPl);

/**
 * @brief 
 * 
 * @param players 
 * @param nPl 
 * @return int 
 */
int last_move(player_t *players,unsigned int nPl);

/**
 * @brief 
 * 
 * @param players 
 * @param board 
 * @param nPl 
 * @param depth 
 * @return int 
 */
int round_ia_minimax(player_t *players, board_t *board,unsigned int nPl, unsigned int depth);

/**
 * @brief 
 * 
 * @param board 
 * @param players 
 * @param depth 
 * @param nPed 
 * @param nPl 
 * @param v 
 * @param cheat 
 * @param alpha 
 * @param beta 
 * @return int 
 */
int minimax(board_t board, player_t *players, int depth,unsigned  int nPed,unsigned int nPl,valueMinimax_t *v, int cheat,int *alpha,int *beta);

/**
 * @brief 
 * 
 * @param board_copy 
 * @param players_copy 
 * @param depth 
 * @param nPed 
 * @param nPl 
 * @param v 
 * @param str 
 * @param maxEval 
 * @param cheat 
 * @param alpha 
 * @param beta 
 * @return int 
 */
int call_minimax(board_t *board_copy, player_t *players_copy,unsigned int depth, unsigned int nPed,unsigned int nPl,valueMinimax_t *v,char *str,int maxEval, int cheat,int *alpha,int *beta);

/**
 * @brief 
 * 
 * @param alpha 
 * @param beta 
 * @return unsigned int 
 */
unsigned int interrupt_minimax(int *alpha ,int *beta);

/**
 * @brief 
 * 
 * @param board 
 * @param players 
 * @return int 
 */
int evaluate_score(board_t board, player_t *players);

/**
 * @brief 
 * 
 * @param value_arr 
 * @param dim_arr 
 */
void print_minimax(valueMinimax_t *value_arr,unsigned int dim_arr);

/**
 * @brief 
 * 
 * @param arr 
 * @param dim 
 * @return unsigned int 
 */
unsigned int max(valueMinimax_t *arr,unsigned int dim);

/**
 * @brief 
 * 
 * @param arr 
 * @param dim 
 */
void destroy_value_minimax(valueMinimax_t *arr,unsigned int dim);

#endif