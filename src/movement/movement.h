/*
    ID gruppo : 51

    886711 Passarella-Diego | 882082 Pasqual-Davide | 881493 Ravagnan-Michelle

 */
#ifndef MOVEMENT_H
#define MOVEMENT_H

/**
 * @brief Move a given number of pawn without eat to a string direction.<br>
 *
 * There are 4 steps :<br>
 * -> 1 step : check with "strcmp" function( string.h library)if the given string is correct.<br>
 * -> 2 step : check if in that direction there isn't any pawn and the new coordinates of the pawn are inside the chessboard.<br>
 * -> 3 step : assign new coordinates to the pawn and remove the pawn at the old coordinates on the board.<br>
 * -> 4 step : eventually promote the num_pawn  pawn.<br>
 *
 *
 * There are 4 string directions :<br>
 * -> "l" which means left respect the num_pawn pawn.<br>
 * -> "r" which means right respect the num_pawn pawn.wn pawn.<br>
 * -> "botr"  which means bottom right respect the num_pam_pawn pawn.<br>
 * -> "botl" which means bottom left respect the num_pam_pawn pawn.<br>
 *
 * @param players Pointer to the players array.
 * @param num_pawn Number of the pawn to move.
 * @param str String of direction where to move the pawn.
 * @param board Pointer to the board.
 * @param nPl Number of player of num_pawn.
 * @return unsigned int Return 1 if the pawn moves correctly,0 else.
 */
unsigned int move_noeat(player_t *players, unsigned int num_pawn, char *str, board_t *board, unsigned int nPl);

/**
 * @brief Eat the enemy pawn respect us.<br>
 *
 * There are 4 string directions :<br>
 * -> "l" which means left respect the num_pawn pawn.<br>
 * -> "r" which means right respect the num_pawn pawn.wn pawn.<br>
 * -> "botr"  which means bottom right respect the num_pam_pawn pawn.<br>
 * -> "botl" which means bottom left respect the num_pam_pawn pawn.<br>
 *
 *
 * There are 5 steps :<br>
 * -> 1 step : calculate the number of enemy_player and save with a char array the new characters of the num_pawn(it has length 3 due to the height limitation of the pawn).<br>
 * -> 2 step : there are 2 main cases that will be analyzed below.<br>
 * -> 3 step : modify the label of num_pawn pawn(if his height < 3),then modify the other fields such as the new coordinates(according to the string direction).<br>
 * -> 4 step : remove the pawn at the old coordinates on the board.<br>
 * -> 5 step : eventually promote the num_pawn pawn.<br>
 *
 *
 * Main cases of 2 step :<br>
 * -> 1 case : the enemy pawn has grade equal to 1 so it just set it to zero to remove it from the board when the update_board("../game_engine/game_engine.h") is done.<br>
 * -> 2 case : mainly it concerns when the opponent's pawn includes more pieces and we distinguish two main sub-cases :<br>
 *              -> 1 sub cases : when the highest opponent pawn in the tower is the same as the next one, simply the control of the new opponent pawn is maintained by the opposing player who is deprived of the highest pawn of the tower.<br>
 *              -> 2 sub cases : when the highest pawn of the opposing tower is different from the next one, control of the pawn is lost and attributed to the other player.<br>
 *
 *
 * @param players Pointer to the players array.
 * @param str String of direction where to move the pawn.
 * @param num_pawn Number of the pawn to move and eat the enemy pawn.
 * @param board  Pointer to the board.
 * @param enemy_pawn  Number of the enemy pawn that will be eaten.
 * @param nPl Number of player of num_pawn.
 * @return unsigned int 
 */
unsigned int eat(player_t *players, char *str, unsigned int num_pawn, board_t board, unsigned int enemy_pawn, unsigned int nPl);

/**
 * @brief This is the main function that allows the pawn to move in the 4 available directions.
 * 
 * @param players Pointer to the players array.
 * @param num_pawn Number of the pawn to move.
 * @param str String of direction where to move the pawn.
 * @param board  Pointer to the board.
 * @param nPl Number of player of num_pawn.
 * @return int Return a number >= 0 if the num_pawn ate and matches to the number of enemy pawn that it was eaten,-1 if the num_pawn move without eat, -2 if did nothing , -4 if there is an error in can_eat function(#include "../game_engine/game_engine.h");
 */
int move_p1 (player_t *players, unsigned int num_pawn, char *str, board_t *board, unsigned int nPl);

/**
 * @brief Move a given number of pawn of the second player.<br>
 *
 *
 * It is very similar to move_p1 but it is different because the directions of player 2 move inversely with respect to player 1, for example if I have to go in the left direction of player 1, the direction of player 2 is not left, but bottom left.
 * This is due to the fact that in the chessboard player 1 is in the last lines, instead player 2 in the first ones, so if I move to the left of player 1 the y coordinate of the pawn decreases, on the contrary in player 2 that when I have to go on the left the y coordinate increases (as in fact when compared to player 1 I go to the bottom left and then reusing the functions of player 1).<br>
 *
 * There are 4 string directions :<br>
 * -> "l" which means left respect the num_pawn pawn.<br>
 * -> "r" which means right respect the num_pawn pawn.wn pawn.<br>
 * -> "botr"  which means bottom right respect the num_pam_pawn pawn.<br>
 * -> "botl" which means bottom left respect the num_pam_pawn pawn.<br>
 *
 *
 * The 4 directions of player 2 respect player 1 :<br>
 * -> "l" that respect player 1 it is "botl".<br>
 * -> "r" that respect player 1 it is "botr".<br>
 * -> "botr" that respect player 1 it is "r".<br>
 * -> "l" that respect player 1 it is "l".<br>
 *
 * @param players Pointer to the players array.
 * @param num_pawn Number of the pawn to move.
 * @param str String of direction where to move the pawn.
 * @param board Pointer to the board.
 * @return int Return a number >= 0 if the num_pawn ate and matches to the number of enemy pawn that it was eaten,-1 if the num_pawn move without eat, -2 if did nothing , -4 if there is an error in can_eat function(#include "../game_engine/game_engine.h");
 */
int move_p2(player_t *players,unsigned int num_pawn,char *str,board_t *board);

#endif