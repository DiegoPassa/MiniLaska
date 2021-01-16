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
 * @brief 
 * 
 * @param board 
 * @param cifre 
 */
void initialize_board(board_t *board,unsigned int cifre);

/**
 * @brief 
 * 
 * @param arr 
 * @param dim 
 * @param np 
 */
void print_directions(unsigned int *arr,unsigned int dim,unsigned int np);

/**
 * @brief 
 * 
 * @param t 
 * @param player 
 */
void update_board(board_t *t,player_t *player);

/**
 * @brief 
 * 
 * @param board 
 * @param row 
 * @param col 
 * @param dim_label 
 * @return unsigned int 
 */
unsigned int check_spot(board_t board,unsigned int row,unsigned int col,unsigned int dim_label);

/**
 * @brief 
 * 
 * @param player 
 * @param num_pawn 
 * @param nPl 
 * @return unsigned int 
 */
unsigned int is_selected(player_t *player, int num_pawn, unsigned int nPl);

/**
 * @brief 
 * 
 * @param board 
 * @param row 
 * @param col 
 * @param dim_label 
 */
void remove_pawn(board_t *board, unsigned int row, unsigned int col, unsigned int dim_label);

/**
 * @brief 
 * 
 * @param players 
 * @param num_pawn 
 * @param nPl 
 * @param last_row 
 */
void pawn_promotion(player_t *players, unsigned int num_pawn, unsigned int nPl, unsigned int last_row);

/**
 * @brief 
 * 
 * @param players 
 * @param x 
 * @param y 
 * @param nPl 
 * @return int 
 */
int check_player(player_t *players, unsigned int x, unsigned int y,unsigned int nPl);

/**
 * @brief 
 * 
 * @param r 
 * @param c 
 * @param board 
 * @return unsigned int 
 */
unsigned int is_in(int r, int c, board_t board);

/**
 * @brief 
 * 
 * @param canMove_arr 
 * @param dim_canMove 
 * @param str 
 * @return unsigned int 
 */
unsigned int check_directions(unsigned int *canMove_arr, unsigned int dim_canMove, char *str);

/**
 * @brief 
 * 
 * @param players 
 * @param board 
 * @param n_pawn 
 * @param nPl 
 */
void must_eat(player_t *players, board_t *board, unsigned int n_pawn, unsigned int nPl);

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
int can_eat(player_t *players, unsigned int num_pawn, char *str, board_t *board, unsigned int nPl);

/**
 * @brief 
 * 
 * @param players 
 * @param board 
 * @param nPl 
 * @return unsigned int 
 */
unsigned int all_blocked(player_t *players, unsigned int nPl);

/**
 * @brief 
 * 
 * @param players 
 * @return unsigned int 
 */
unsigned int is_victory(player_t *players);

/**
 * @brief 
 * 
 * @param p 
 * @return int 
 */
int is_empty(player_t p);

/**
 * @brief 
 * 
 * @param r 
 * @param c 
 * @return unsigned int 
 */
unsigned int max_pawns(unsigned int r,unsigned int c);

/**
 * @brief 
 * 
 * @param players 
 * @param board 
 * @param nPawn 
 * @param nPl 
 * @return unsigned int 
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
 * @brief Set the moves pawn object
 * 
 * @param players 
 * @param board 
 * @param nPl 
 * @param nPawn 
 */
void set_moves_pawn(player_t *players, board_t *board, unsigned int nPl, int nPawn);

/**
 * @brief 
 * 
 * @param players 
 * @param nPawn 
 * @param nPl 
 */
void reset_moves_pawns(player_t *players, int nPawn, unsigned int nPl);

/**
 * @brief 
 * 
 * @param players 
 * @param nPed 
 * @param nPl 
 * @return unsigned int 
 */
unsigned int check_canMove(player_t *players, unsigned int nPed,unsigned int nPl);

/**
 * @brief 
 * 
 * @param players 
 * @param nPl 
 * @param nPawn 
 * @return unsigned int 
 */
unsigned int check_while(player_t *players, unsigned int nPl, unsigned int nPawn);

/**
 * @brief 
 * 
 * @param str 
 * @return unsigned int 
 */
unsigned int check_string(char *str);

/**
 * @brief 
 * 
 * @param board 
 * @param r 
 * @param c 
 * @param dim_label 
 * @return unsigned int 
 */
unsigned int char_converter(board_t board, unsigned int r, unsigned int c, unsigned int dim_label);

/**
 * @brief 
 * 
 * @param num 
 * @param index 
 * @return char 
 */
char int_converter(int num,unsigned int index);

/**
 * @brief
 *
 * @param c
 * @return char
 */
char uppercase(char c);
/**
 * @brief
 *
 * @param c
 * @return unsigned int
 */
unsigned int check_char_color(char c);


#endif
