typedef unsigned int dim_board, coord, flag;

struct board{
    char **mat; /*!< Detailed description after the member */
    dim_board n_rows;
    dim_board n_cols;
} typedef board_t;

struct point{
    coord x; /* cols */
    coord y; /* rows */
} typedef point_t;

struct pawn{
    char *label; /* etichetta della pedina Es.|  BN07 | */
    unsigned int dim_label;
    point_t coordinate;
    unsigned int cima;
    unsigned int grade;
    flag isPromoted; /* Es: |  BN07^ | */
    unsigned int *canMove; /* 0010 -> bassodx */
} typedef pawn_t;

struct player{
    char color;
    pawn_t *pawns;
    unsigned int dim_pawns;
} typedef player_t;

struct valueMinimax{
    int value;
    char* directions;
} typedef valueMinimax_t;

/**
 * @brief Creazione del campo di gioco.
 * 
 * Crea una matrice row*col e per ogni "cella" alloca abbastanza spazio da rappresentare correttamente la pedina.
 * Lo spazio è dato da "altezza massima della torre(3)" + "spazio per la promozione(1)" + "spazio per rappresentare le cifre(variabile)"
 * 
 * @param row Numero di righe della schacchiera.
 * @param col Numero di colonne della scacchiera.
 * @param cifre Numero di cifre da allocare in modo da rappresentare il numero delle pedine nella scacchiera.
 * @return board_t* Ritorna il puntatore al campo.
 */
board_t* create_board(unsigned int n_rows,unsigned int n_cols,unsigned int cifre);/* matrix creation */

void initialize_board(board_t *board,unsigned int cifre); /* initialize matrix as a chessboard */

void print_board(board_t t,unsigned int cifre, unsigned npl, char char_p1, char char_p2); /* print the matrix changing the view according to the player */

player_t *create_pawns(unsigned int totPawns,char player1, char player2,unsigned int cifre,board_t board);/* player creation */

void print_player(player_t *players,unsigned int nPl); /* print the player's pawns */

void print_directions(unsigned int *arr,unsigned int dim,unsigned int np);/* print the directions when the soldier must jump over/eat an enemy */

void update_board(board_t *t,player_t *player);/* update the pawns position on the board */

int can_eat(player_t *players, unsigned int num_pawn, char *str, board_t *board, unsigned int nPl);/* check before eating another pawn, if the pawn is an eney then you can eat it */

void must_eat(player_t *players, board_t *board, unsigned int n_pawn, unsigned int nPl);/* the pawn must eat the enemy */

unsigned int check_directions(unsigned int *canMove_arr, unsigned int dim_canMove, char *str);/* compare the string with the mandatory directions */

unsigned int move_noeat(player_t *players, unsigned int num_pawn, char *str, board_t *board, unsigned int nPl);/* moves the pawn without eating */

unsigned int is_in(int r, int c, board_t board);/* check if the coordinates are inside the matrix */

unsigned int check_spot(board_t board,unsigned int row,unsigned int col,unsigned int dim_label);/* check if in a board's spot there is a pawn */

int is_empty(player_t p);/* check if a pawn on the array has the grade = 0 */

unsigned int is_selected(player_t *player,int num_pawn, unsigned int nPl);/* check if the pawn np can be selected */

unsigned int max_pawns(unsigned int r,unsigned int c);/* calculate the number of pawns that can be placed in an rxc dimension matrix */

unsigned int is_notstuck(player_t *players, board_t board, unsigned int nPawn, unsigned int nPl);/* check if the pawn is stuck */

board_t *copy_board(board_t board ,board_t *newBoard,unsigned int cifre,unsigned int set);/* create a new board  copying from the variable t */

player_t *player_copy(player_t *players, player_t *newPlayers, unsigned int dim_label,unsigned int set);/* create a new player copying an existing player */

unsigned int add_pawn(player_t *players, unsigned int enemy_pawn, unsigned int nPl,char c);/* add a pawn to the other player based on the pawn eaten */

int move_p1 (player_t *players, unsigned int num_pawn, char *str, board_t *board, unsigned int nPl);/* move a player1's pawn to a direction */

int move_p2(player_t *players,unsigned int num_pawn,char *str,board_t *board);/* move a player2's pawn to a direction */

void remove_pawn(board_t *board, unsigned int row, unsigned int col, unsigned int dim_label);/* modify the position before to move the pawn */

void pawn_promotion(player_t *players, unsigned int num_pawn, unsigned int nPl, unsigned int last_row);/* pawn promotion */

void pawn_remove_promotion(player_t *players ,int num_pawn,unsigned int nPl);/* remove promotion of num_pawn pawn*/

unsigned int eat(player_t *players, char *str, unsigned int num_pawn, board_t board, unsigned int enemy_pawn, unsigned int nPl);/* eat an enemy pawn */

unsigned int char_converter(board_t board, unsigned int r, unsigned int c, unsigned int dim_label);/* convert from char to int */

char int_converter(int num,unsigned int index);/* convert num in pos from int to char*/

int check_player(player_t *players, unsigned int x, unsigned int y,unsigned int nPl);/* check if a pawn is a player1's pawn or if is a player2's pawn */

unsigned int is_victory(player_t *players);/* check if there is a winner */

unsigned int all_blocked(player_t *players, board_t board, unsigned int nPl);/* check if all pawns are blocked */

unsigned int round_choice();/* choose who starts */

unsigned int round_player(player_t *players,board_t *t,unsigned int nPl);/* round of the player */

int player_vs_player(unsigned int x );/* mode player vs player */

void player_vs_ia();/*mode player vs ia */

unsigned int round_ia_random(player_t *players, board_t *board, unsigned int nPl);

unsigned int interropt_minimax(int *alpha ,int *beta);

int minimax(board_t board, player_t *players, int depth,unsigned  int nPed,unsigned int nPl,valueMinimax_t *v, int cheat,int *alpha,int *beta);

int call_minimax(board_t *board_copy, player_t *players_copy,unsigned int depth, unsigned int nPed,unsigned int nPl,valueMinimax_t *v,char *str,int maxEval, int cheat,int *alpha,int *beta);

void restore_copy(board_t board, player_t *players, board_t *board_copy, player_t *players_copy);

int evaluate_score(board_t board, player_t *players);

unsigned int check_string(char *str);

unsigned int max(valueMinimax_t *arr,unsigned int dim);

void print_minimax(valueMinimax_t *value_arr,unsigned int dim_arr);

int round_ia_minimax(player_t *players, board_t *board,unsigned int nPl,unsigned int depth);

void set_moves_pawn(player_t *players, board_t *board, unsigned int nPl,int nPawn);

void reset_moves_pawns(player_t *players, int nPawn, unsigned int nPl);

unsigned int check_canMove(player_t *players, unsigned int nPed,unsigned int nPl);

void destroy_player (player_t *players); /* free up memory space allocated by player */

void destroy_board(board_t *board);/* free up memory space allocated by board */

void destroy_value_minimax(valueMinimax_t *arr,unsigned int dim); /* free up memory space allocated by value_minimax*/

unsigned int check_while(player_t *players, unsigned int nPl, unsigned int nPawn);

void printMatrix(board_t board);

int last_move(player_t *players,unsigned int nPl);

void menu();