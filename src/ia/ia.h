
typedef struct valueMinimax valueMinimax_t;

unsigned int round_ia_random(player_t *players, board_t *board, unsigned int nPl);

int last_move(player_t *players,unsigned int nPl);

int round_ia_minimax(player_t *players, board_t *board,unsigned int nPl, unsigned int depth);

int minimax(board_t board, player_t *players, int depth,unsigned  int nPed,unsigned int nPl,valueMinimax_t *v, int cheat,int *alpha,int *beta);

int call_minimax(board_t *board_copy, player_t *players_copy,unsigned int depth, unsigned int nPed,unsigned int nPl,valueMinimax_t *v,char *str,int maxEval, int cheat,int *alpha,int *beta);

unsigned int interrupt_minimax(int *alpha ,int *beta);

int evaluate_score(board_t board, player_t *players);

void print_minimax(valueMinimax_t *value_arr,unsigned int dim_arr);

unsigned int max(valueMinimax_t *arr,unsigned int dim);

void destroy_value_minimax(valueMinimax_t *arr,unsigned int dim);