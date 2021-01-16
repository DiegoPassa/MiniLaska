/*
    ID gruppo : 51

    886711 Passarella-Diego | 882082 Pasqual-Davide | 881493 Ravagnan-Michelle

 */
#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H
typedef unsigned int dim_board, coord, flag;

/**
 * @brief 
 * 
 */
struct board{
    char **mat; /*!< Detailed description after the member */
    dim_board n_rows;
    dim_board n_cols;
}typedef board_t;

/**
 * @brief 
 * 
 */
struct point{
    coord x; /* cols */
    coord y; /* rows */
}typedef point_t;

/**
 * @brief 
 * 
 */
struct pawn{
    char *label; /* etichetta della pedina Es.|  BN07 | */
    unsigned int dim_label;
    point_t coordinate;
    unsigned int cima;
    unsigned int grade;
    flag isPromoted; /* Es: |  BN07^ | */
    unsigned int *canMove; /* 0010 -> bassodx */
}typedef pawn_t;

/**
 * @brief 
 * 
 */
struct player{
    char color;
    pawn_t *pawns;
    unsigned int dim_pawns;
}typedef player_t;

/**
 * @brief Set char on the board.
 * 
 * '#' white cell, it's where pawns can move
 * ' ' black cell, it's where pawns cannot move
 * 
 * @param board Pointer to the board.
 * @param cifre Number of colums for the label.
 */
void initialize_board(board_t *board,unsigned int cifre);

/**
 * @brief Print hints for the movements of a given pawn.
 * 
 * @param arr Array of the avaiable movements of a pawn
 * @param dim Dimension of the array 'arr', 4 if the pawn is promoted, 2 if the pawn isn't promoted.
 * @param np Number of the pawn.
 */
void print_directions(unsigned int *arr,unsigned int dim,unsigned int np);

/**
 * @brief Update the board after a player move.
 * 
 * @param t Pointer to the board.
 * @param player Pointer of players array.
 */
void update_board(board_t *t,player_t *player);

/**
 * @brief Check if in a given coordinate on the board there is a pawn or not.
 * 
 * @param board Instance of the board.
 * @param row Number of the row (y).
 * @param col Number of the column (x).
 * @param dim_label Total number of space stored for the label of the pawn.
 * @return unsigned int Return 1 if there is a pawn, 0 else.
 */
unsigned int check_spot(board_t board,unsigned int row,unsigned int col,unsigned int dim_label);

/**
 * @brief Check if a given pawn exists in the board.
 * 
 * @param player Pointer to the players array.
 * @param num_pawn Number of the pawn to check.
 * @param nPl Number of the player.
 * @return unsigned int Return 1 if the pawn exists in the board, 0 else.
 */
unsigned int is_selected(player_t *player, int num_pawn, unsigned int nPl);

/**
 * @brief Reset label from a given coordinate.
 * 
 * @param board Pointer to the board.
 * @param row Number of the row (y).
 * @param col Number of the column (x).
 * @param dim_label Total number of space stored for the label of the pawn.
 */
void remove_pawn(board_t *board, unsigned int row, unsigned int col, unsigned int dim_label);

/**
 * @brief Promote a given pawn.
 * 
 * @param players Pointer to the players array.
 * @param num_pawn Number of the pawn to promote.
 * @param nPl Number of the player.
 * @param last_row Check if a player pawn reaches the end of the board from the perspective of the player.
 */
void pawn_promotion(player_t *players, unsigned int num_pawn, unsigned int nPl, unsigned int last_row);

/**
 * @brief Check if in a given coordinate there is an enemy pawn.
 * 
 * @param players Pointer to the players array.
 * @param x Number of the column (x).
 * @param y Number of the row (y).
 * @param nPl Number of the player.
 * @return int Return -1 if a there isn't any enemy pawn, else the number of the enemy player.
 */
int check_player(player_t *players, unsigned int x, unsigned int y,unsigned int nPl);

/**
 * @brief Check if a given coordinate are included in the board.
 * 
 * @param r Number of the row (y).
 * @param c Number of the column (x).
 * @param board Instance of the board.
 * @return unsigned int Return 1 if the coordinate are inside the board, 0 else.
 */
unsigned int is_in(int r, int c, board_t board);

/**
 * @brief Check if a given string is setted in the pawn's possible movements.
 * 
 * @param canMove_arr Pointer to the canMove array of a pawn.
 * @param dim_canMove Dimension of the canMove array, 4 if the pawn is promoted, 2 else.
 * @param str String of the direction to compare.
 * @return unsigned int Return 1 if the corresponding string is setted on the canMove array, 0 else.
 */
unsigned int check_directions(unsigned int *canMove_arr, unsigned int dim_canMove, char *str);

/**
 * @brief Set mandatory eat if possible.
 * 
 * @param players Pointer to the players array.
 * @param board Pointer to the board.
 * @param n_pawn Number of the pawn to check.
 * @param nPl Number of the player.
 */
void must_eat(player_t *players, board_t *board, unsigned int n_pawn, unsigned int nPl);

/**
 * @brief Check enemy pawns in a given direction.
 * 
 * @param players Pointer to the players array.
 * @param num_pawn Number of the pawn to check.
 * @param str Direction to check from the player's pawn.
 * @param board Pointer to the board.
 * @param nPl Number of the player.
 * @return int Return enemy pawn number that can be eaten, else negative numbers.
 */
int can_eat(player_t *players, unsigned int num_pawn, char *str, board_t *board, unsigned int nPl);

/**
 * @brief Check if a player can move.
 * 
 * @param players Pointer to the players array.
 * @param nPl Number of the player.
 * @return unsigned int Return 1 if there is at least one pawn can move, 0 else.
 */
unsigned int all_blocked(player_t *players, unsigned int nPl);

/**
 * @brief Check if there is a winner.
 * 
 * @param players Pointer to the players array.
 * @return unsigned int Return 1 if player1 won, 2 if player2 won, 17 else.
 */
unsigned int is_victory(player_t *players);

/**
 * @brief Check if in the player's array there is an unused pawn.
 * 
 * @param p Instance of a player.
 * @return int Return the position of the first unused pawn in the array, -1 else.
 */
int is_empty(player_t p);

/**
 * @brief Calculate the max number of pawns in a given space.
 * 
 * @param r Total number of rows.
 * @param c Total number of columns.
 * @return unsigned int Return the max number of pawns avaiable.
 */
unsigned int max_pawns(unsigned int r,unsigned int c);

/**
 * @brief Set possible movements of a given pawn.
 * 
 * @param players Pointer to the players array.
 * @param board Instance of the board.
 * @param nPawn Number of the pawn to set.
 * @param nPl Number of the player.
 * @return unsigned int Return 1 if the function runs succesfully, 0 else.
 */
unsigned int is_notstuck(player_t *players, board_t board, unsigned int nPawn, unsigned int nPl);

/**
 * @brief 
 * 
 * @param players 
 * @param enemy_pawn 
 * @param nPl 
 * @param c 
 * @return unsigned int 
 */
unsigned int add_pawn(player_t *players, unsigned int enemy_pawn, unsigned int nPl,char c );

/**
 * @brief Set possible movements of a given pawn and set mandatory eat.
 * 
 * Calls to is_notstuck, must_eat and reset_moves_pawns.
 * 
 * @param players Pointer to the players array.
 * @param board Pointer to the board.
 * @param nPl Number of the player.
 * @param nPawn If -1 set movements of all pawns of a player, else set movements of the given pawn.
 */
void set_moves_pawn(player_t *players, board_t *board, unsigned int nPl, int nPawn);

/**
 * @brief Reset possible movements of a given pawn.
 * 
 * @param players Pointer to the players array.
 * @param nPawn If -1 reset movements of all pawns of a player, else reset movements of the given pawn.
 * @param nPl Number of the player.
 */
void reset_moves_pawns(player_t *players, int nPawn, unsigned int nPl);

/**
 * @brief Check if a pawn is able to move.
 * 
 * @param players Pointer to the players array.
 * @param nPed Number of the pawn to check.
 * @param nPl Number of the player.
 * @return unsigned int Return 1 if the pawn can move, 0 otherwise.
 */
unsigned int check_canMove(player_t *players, unsigned int nPed,unsigned int nPl);

/**
 * @brief Check if a pawn is selectable.
 * 
 * @param players Pointer to the players array.
 * @param nPl Number of the player.
 * @param nPawn Number of the pawn to check.
 * @return unsigned int Return 1 if the pawn is selectable, 0 otherwise.
 */
unsigned int check_while(player_t *players, unsigned int nPl, unsigned int nPawn);

/**
 * @brief Compare if the a given string equals to a valid movement.
 * 
 * @param str String to compare.
 * @return unsigned int Return 1 if the string correspond, 0 otherwise.
 */
unsigned int check_string(char *str);

/**
 * @brief Convert a given char on a label to int.
 * 
 * @param board Instance of the board.
 * @param r Number of the row (y). 
 * @param c Number of the column (x).
 * @param dim_label Dimension of the label of the pawn.
 * @return unsigned int Return the conversion of the char to int.
 */
unsigned int char_converter(board_t board, unsigned int r, unsigned int c, unsigned int dim_label);

/**
 * @brief Convert a given int to a char.
 * 
 * @param num Number to be converted.
 * @param index Index of the pow of 10.
 * @return char Return the conversion of the int to a char.
 */
char int_converter(int num,unsigned int index);

/**
 * @brief Uppercase a given char.
 *
 * @param c Char to be uppercased.
 * @return char Return the uppercased char.
 */
char uppercase(char c);

/**
 * @brief Check if a given char matches a color.
 *
 * @param c Char to check.
 * @return unsigned int Return 1 if the char matches, 2 if the char mathes being uppercase, 0 otherwise. 
 */
unsigned int check_char_color(char c);


#endif
