#ifndef MOVEMENT_H
#define MOVEMENT_H

unsigned int move_noeat(player_t *players, unsigned int num_pawn, char *str, board_t *board, unsigned int nPl);

unsigned int eat(player_t *players, char *str, unsigned int num_pawn, board_t board, unsigned int enemy_pawn, unsigned int nPl);

int move_p1 (player_t *players, unsigned int num_pawn, char *str, board_t *board, unsigned int nPl);

int move_p2(player_t *players,unsigned int num_pawn,char *str,board_t *board);

#endif