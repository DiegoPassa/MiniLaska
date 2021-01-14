
typedef unsigned int dim_board, coord, flag;

typedef struct board board_t;

typedef struct point point_t;

typedef struct pawn pawn_t;

typedef struct player player_t;

void initialize_board(board_t *board,unsigned int cifre);

void print_directions(unsigned int *arr,unsigned int dim,unsigned int np);

void update_board(board_t *t,player_t *player);

unsigned int check_spot(board_t board,unsigned int row,unsigned int col,unsigned int dim_label);

unsigned int is_selected(player_t *player, int num_pawn, unsigned int nPl);

void remove_pawn(board_t *board, unsigned int row, unsigned int col, unsigned int dim_label);

void pawn_promotion(player_t *players, unsigned int num_pawn, unsigned int nPl, unsigned int last_row);

int check_player(player_t *players, unsigned int x, unsigned int y,unsigned int nPl);

unsigned int is_in(int r, int c, board_t board);

unsigned int check_directions(unsigned int *canMove_arr, unsigned int dim_canMove, char *str);

void must_eat(player_t *players, board_t *board, unsigned int n_pawn, unsigned int nPl);

int can_eat(player_t *players, unsigned int num_pawn, char *str, board_t *board, unsigned int nPl);

unsigned int all_blocked(player_t *players, board_t board, unsigned int nPl);

unsigned int is_victory(player_t *players);

int is_empty(player_t p);

unsigned int max_pawns(unsigned int r,unsigned int c);

unsigned int round_choice();

unsigned int is_notstuck(player_t *players, board_t board, unsigned int nPawn, unsigned int nPl);

unsigned int add_pawn(player_t *players, unsigned int enemy_pawn, unsigned int nPl,char c );

void set_moves_pawn(player_t *players, board_t *board, unsigned int nPl, int nPawn);

void reset_moves_pawns(player_t *players, int nPawn, unsigned int nPl);

unsigned int check_canMove(player_t *players, unsigned int nPed,unsigned int nPl);

unsigned int check_while(player_t *players, unsigned int nPl, unsigned int nPawn);

unsigned int check_string(char *str);

unsigned int char_converter(board_t board, unsigned int r, unsigned int c, unsigned int dim_label);

char int_converter(int num,unsigned int index);