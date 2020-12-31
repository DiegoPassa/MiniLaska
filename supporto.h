/**
 * @brief Struttura campo.
 * 
 */
struct campo
{
    char **mat; /*!< Detailed description after the member */
    unsigned int r;
    unsigned int c;
};
typedef struct campo tcampo;
struct pedina
{
    char *et; /* etichetta della pedina Es.|  BN07 | */
    unsigned int dim;
    unsigned int cima;
    unsigned int grado;
    unsigned int r;
    unsigned int c;
    unsigned int isPromoted; /* Es: |  BN07^ | */
    unsigned int *canMove; /* 0010 -> bassodx */
};
typedef struct pedina tpedina;
struct player
{
    char colore;
    tpedina *arr;
    unsigned int dim;
};
typedef struct player tplayer;

/**
 * @brief Creazione del campo di gioco.
 * 
 * Crea una matrice r*c e per ogni "cella" alloca abbastanza spazio da rappresentare correttamente la pedina.
 * Lo spazio è dato da "altezza massima della torre(3)" + "spazio per la promozione(1)" + "spazio per rappresentare le cifre(variabile)"
 * 
 * @param r Numero di righe della schacchiera.
 * @param c Numero di colonne della scacchiera.
 * @param cifre Numero di cifre da allocare in modo da rappresentare il numero delle pedine nella scacchiera.
 * @return tcampo* Ritorna il puntatore al campo.
 */
tcampo* create_board(unsigned int r,unsigned int c,unsigned int cifre); /* matrix creation */

void initialize_board(tcampo *t,unsigned int cifre); /* initialize matrix as a chessboard */

void print_board(tcampo t,unsigned int cifre,unsigned int npl); /* print the matrix changing the view according to the player */

tplayer *create_pawns(unsigned int n,char ped,unsigned int np,unsigned int cifre,tcampo t);/* player creation */

void print_player(tplayer p); /* print the player's pawns */

void print_directions(unsigned int *arr,unsigned int dim,unsigned int np);/* print the directions when the soldier must jump over/eat an enemy */

void update_board(tcampo *t,tplayer p1,tplayer p2);/* update the pawns position on the board */

int can_eat(tplayer *p1,unsigned int np,char *str,tcampo *t,tplayer *p2,unsigned int pl);/* check before eating another pawn, if the pawn is an eney then you can eat it */

void must_eat(tplayer *p1,tplayer *p2,tcampo t,unsigned int np,unsigned int npl);/* the pawn must eat the enemy */

unsigned int check_directions(unsigned int *arr,unsigned int dim,char *str);/* compare the string with the mandatory directions */

unsigned int move_noeat(tplayer *p1,unsigned int np,char *str,tcampo *t,tplayer *p2,unsigned int pl);/* moves the pawn without eating */

unsigned int is_in(int r,int c,tcampo t);/* check if the coordinates are inside the matrix */

unsigned int check_spot(tcampo t,unsigned int r,unsigned int c,unsigned int cifre);/* check if in a board's spot there is a pawn */

int is_empty(tplayer p);/* check if a pawn on the array has the grade = 0 */

unsigned int is_selected(tplayer p1,tplayer p2,unsigned int np,unsigned int npl);/* check if the pawn np can be selected */

unsigned int max_pawns(unsigned int r,unsigned int c);/* calculate the number of pawns that can be placed in an rxc dimension matrix */

unsigned int is_notstuck(tplayer *p1,tplayer *p2,tcampo t,unsigned int nped,unsigned int npl);/* check if the pawn is stuck */

tcampo* copy_board(tcampo t ,tcampo *new);/* create a new board  copying from the variable t */

tplayer* player_copy(tplayer p,tplayer *n,unsigned int cifre);/* create a new player copying an existing player */

unsigned int add_pawn(tplayer *p1,tplayer *p2,unsigned int np);/* add a pawn to the other player based on the pawn eaten */

unsigned int move_p1 (tplayer *p1,unsigned int np,char *str,tcampo *t,tplayer *p2,unsigned int pl);/* move a player1's pawn to a direction */

unsigned int move_p2(tplayer *p2,unsigned int np,char *str,tcampo *t,tplayer *p1);/* move a player2's pawn to a direction */

void remove_pawn(tcampo *t,unsigned int r,unsigned int c,unsigned int cifre);/* modify the position before to move the pawn */

void pawn_promotion(tplayer *p,unsigned int np,unsigned int numpl,unsigned int meta);/* pawn promotion */

unsigned int eat(tplayer *p1,tplayer *p2,char *str,unsigned int np,tcampo t,unsigned int num,unsigned int npl);/* eat an enemy pawn */

unsigned int char_converter(tcampo t,unsigned int r,unsigned int c,unsigned int dim,unsigned int cifre);/* convert from char to int */

char int_converter(unsigned int num,unsigned int index);/* convert num in pos from int to char*/

unsigned int check_player(tplayer p1,tplayer p2,unsigned int x,unsigned int y);/* check if a pawn is a player1's pawn or if is a player2's pawn */

unsigned int is_victory(tplayer p1,tplayer p2,tcampo t);/* check if there is a winner */

unsigned int all_blocked(tplayer p1,tplayer p2,tcampo t,unsigned int npl);/* check if all pawns are blocked */

unsigned int round_choice();/* choose who starts */

unsigned int round_player(tplayer *p1,tplayer *p2,tcampo *t,unsigned int npl);/* round of the player */

int player_vs_player(unsigned int x );/* mode player vs player */

void player_vs_ia();/*mode player vs ia */

unsigned int round_ia(tplayer *p1,tplayer *ia,tcampo *t,unsigned int npl);

int minimax();

void set_moves_pawn(tplayer *pl1, tplayer *pl2, tcampo t, int nPl);

void reset_moves_paws(tplayer *pl,int nPawn);

unsigned int check_canMove(tplayer *p, int nPed);

void destroy_player (tplayer *p); /* free up memory space allocated by player */

void destroy_board(tcampo *t);/* free up memory space allocated by board */

unsigned int check_while(tplayer pl1, tplayer pl2, unsigned int nPlayer, unsigned int nPawn);