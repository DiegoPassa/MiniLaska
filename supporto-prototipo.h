typedef unsigned int dim_board, coord, flag;

struct board{
    char **mat; /*!< Detailed description after the member */
    dim_board n_rows;
    dim_board n_cols;
} typedef board_t;

struct point{
    coord x;
    coord y;
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
board_t* create_board(unsigned int row,unsigned int col,unsigned int cifre); /* matrix creation */

void initialize_board(board_t *t,unsigned int cifre); /* initialize matrix as a chessboard */

void print_board(board_t t,unsigned int cifre,unsigned int npl); /* print the matrix changing the view according to the player */

player_t *create_pawns(unsigned int n,char ped,unsigned int np,unsigned int cifre,board_t t);/* player creation */

void print_player(player_t p); /* print the player's pawns */

void print_directions(unsigned int *arr,unsigned int dim,unsigned int np);/* print the directions when the soldier must jump over/eat an enemy */

void update_board(board_t *t,player_t p1,player_t p2);/* update the pawns position on the board */

int can_eat(player_t *p1,unsigned int np,char *str,board_t *t,player_t *p2,unsigned int pl);/* check before eating another pawn, if the pawn is an eney then you can eat it */

void must_eat(player_t *p1,player_t *p2,board_t t,unsigned int np,unsigned int npl);/* the pawn must eat the enemy */

unsigned int check_directions(unsigned int *arr,unsigned int dim,char *str);/* compare the string with the mandatory directions */

unsigned int move_noeat(player_t *p1,unsigned int np,char *str,board_t *t,player_t *p2,unsigned int pl);/* moves the pawn without eating */

unsigned int is_in(int row,int col,board_t t);/* check if the coordinates are inside the matrix */

unsigned int check_spot(board_t t,unsigned int row,unsigned int col,unsigned int cifre);/* check if in a board's spot there is a pawn */

int is_empty(player_t p);/* check if a pawn on the array has the grade = 0 */

unsigned int is_selected(player_t p1,player_t p2,unsigned int np,unsigned int npl);/* check if the pawn np can be selected */

unsigned int max_pawns(unsigned int row,unsigned int col);/* calculate the number of pawns that can be placed in an rxc dimension matrix */

unsigned int is_notstuck(player_t *p1,player_t *p2,board_t t,unsigned int nped,unsigned int npl);/* check if the pawn is stuck */

board_t* copy_board(board_t t ,board_t *newBoard);/* create a new board  copying from the variable t */

player_t* player_copy(player_t p,player_t *n,unsigned int cifre);/* create a new player copying an existing player */

unsigned int add_pawn(player_t *p1,player_t *p2,unsigned int np,char ap);/* add a pawn to the other player based on the pawn eaten */

unsigned int move_p1 (player_t *p1,unsigned int np,char *str,board_t *t,player_t *p2,unsigned int pl);/* move a player1's pawn to a direction */

unsigned int move_p2(player_t *p2,unsigned int np,char *str,board_t *t,player_t *p1);/* move a player2's pawn to a direction */

void remove_pawn(board_t *t,unsigned int row,unsigned int col,unsigned int cifre);/* modify the position before to move the pawn */

void pawn_promotion(player_t *p,unsigned int np,unsigned int numpl,unsigned int meta);/* pawn promotion */

unsigned int eat(player_t *p1,player_t *p2,char *str,unsigned int np,board_t t,unsigned int num,unsigned int npl);/* eat an enemy pawn */

unsigned int char_converter(board_t t,unsigned int row,unsigned int col,unsigned int dim,unsigned int cifre);/* convert from char to int */

char int_converter(unsigned int num,unsigned int index);/* convert num in pos from int to char*/

unsigned int check_player(player_t p1,player_t p2,unsigned int x,unsigned int y);/* check if a pawn is a player1's pawn or if is a player2's pawn */

unsigned int is_victory(player_t p1,player_t p2,board_t t);/* check if there is a winner */

unsigned int all_blocked(player_t p1,player_t p2,board_t t,unsigned int npl);/* check if all pawns are blocked */

unsigned int round_choice();/* choose who starts */

unsigned int round_player(player_t *p1,player_t *p2,board_t *t,unsigned int npl);/* round of the player */

int player_vs_player(unsigned int x );/* mode player vs player */

void player_vs_ia();/*mode player vs ia */

unsigned int round_ia_random(player_t *p1,player_t *ia,board_t *t,unsigned int npl);

int minimax(board_t board, player_t p1, player_t p2, int depth, int nPed, int nPl,valueMinimax_t *v);

int call_minimax(board_t *board_copy, player_t *p1_copy, player_t *p2_copy, int depth, int nPed, int nPl,valueMinimax_t *v,char *str,int maxEval);

void restore_copy(board_t *board_copy, player_t *p1_copy, player_t *p2_copy, board_t board, player_t p1, player_t p2);

int evaluate_score(board_t board, player_t p1, player_t p2);

unsigned int check_string(char *str);

unsigned int max(valueMinimax_t *arr,unsigned int dim);

void print_minimax(valueMinimax_t *arr,unsigned int dim);

int round_ia_minimax(player_t *p1, player_t *p2, board_t *board,unsigned int nPl);

void set_moves_pawn(player_t *pl1, player_t *pl2, board_t t, int nPl,int nPawn);

void reset_moves_paws(player_t *pl,int nPawn);

unsigned int check_canMove(player_t p, int nPed);

void destroy_player (player_t *p); /* free up memory space allocated by player */

void destroy_board(board_t *t);/* free up memory space allocated by board */

void destroy_value_minimax(valueMinimax_t *arr,unsigned int dim); /* free up memory space allocated by value_minimax*/

unsigned int check_while(player_t pl1, player_t pl2, unsigned int nPlayer, unsigned int nPawn);

int last_move(player_t p);