#include<stdio.h>
#include <unistd.h>
#include<stdlib.h>
#include"supporto.h"
#include<string.h>
#include<time.h>
#include <math.h>
#include "src/colors/colors.h"
#include <ncurses.h>


board_t* create_board(unsigned int n_rows,unsigned int n_cols,unsigned int cifre){
    board_t *t = NULL;

    t = (board_t*)malloc(sizeof(board_t));
    if(t != NULL){
        unsigned int i;
        t->n_rows = n_rows;
        t->n_cols = (n_cols*cifre);
        t->mat = (char**)calloc((t->n_rows),sizeof(char*));
        for(i = 0 ; i < t->n_rows ; ++i){
            t->mat[i] = (char*)calloc((t->n_cols),sizeof(char));

        }

        return t;
    }else{
        printf("Errore nella malloc nella funzione crea_campo\n");
        return NULL;
    }
}

void initialize_board(board_t *board,unsigned int cifre){
    unsigned int i,j;

    for(i = 0 ; i < board->n_rows ; ++i) {
        for (j = 0; j < board->n_cols; j += cifre) {

            if (((j / cifre) + i) % 2 == 0) {
                int z;
                for (z = 0; z < cifre; ++z) {
                    board->mat[i][j+z] = '#';
                }

            } else {
                int z;
                for (z = 0; z < cifre; ++z) {
                    board->mat[i][j+z] = ' ';
                }

            }
        }
    }
}

void print_board(board_t t,unsigned int cifre, unsigned npl){
    int i, j, k = 0, z, l;
    char *topPl = (char*) malloc((t.n_cols)*sizeof(char));
    int *cime = (int*) malloc((t.n_cols)*sizeof(int));
    /* stampo prima riga */
    for(j=0; j<t.n_cols; j +=cifre){
        printf("+");
        for(z = 0 ; z < cifre+2; ++z){ /* 2 = spazio a destra e sinistra */
            printf("-");
        }
    }
    printf("+");/* recupero angolo dx */
    printf("\n");

    /* parte centrale */
    if(npl == 0){
        i = 0;
    }else{
        i = t.n_rows-1;
    }
    while( (((npl == 0)&&(i < t.n_rows))||((npl == 1)&&(i >= 0))) ){
        for (l = 0; l < t.n_cols; l+=cifre)
        {
            /* controllo dov'è la cima */      
            while (t.mat[i][l+k] != 'N' && t.mat[i][l+k] != 'B' && k<3){
                k++;
            }
            cime[l/cifre] = k;
            /* indica il possessore della torre */
            topPl[l/cifre] = t.mat[i][l+k];
            k=0;
        }
        
        for (l = 0; l < 3; l++){
            for(j=0; j<t.n_cols; j +=cifre){
                printf("|");
                /* stampa le torri */
                if (cime[j/cifre]==l){
                    if (topPl[j/cifre] == 'N' || topPl[j/cifre] == 'B'){
                        setBlack();
                        if (topPl[j/cifre] == 'N'){
                            /*setRed(2);*/
                            printColor('G'); /** TEST */
                        }else if (topPl[j/cifre] == 'B'){
                            /*setYellow(2);*/
                            printColor('C'); /** TEST */
                        }
                        printf(" ");
                        for (z = 0; z < cifre; z++){
                            printf("%c",t.mat[i][j+z]);
                        }
                        printf(" ");
                        resetColor();
                    }
                }else{
                    if (cime[j/cifre]<l){
                        if ((t.mat[i][j+l] == 'B' || t.mat[i][j+l] == 'N') && t.mat[i][j+l] != topPl[j/cifre]){
                            if (topPl[j/cifre] == 'N'){
                                /*setYellow(2);*/
                                printColor('C'); /** TEST */
                            }else if (topPl[j/cifre] == 'B'){
                                /*setRed(2);*/
                                printColor('G'); /** TEST */
                            }
                            /* altrimenti stampa il colore del proprietario */
                        }else{
                            if (topPl[j/cifre] == 'N'){
                                /*setRed(2);*/
                                printColor('G'); /** TEST */
                            }else if (topPl[j/cifre] == 'B'){
                                /*setYellow(2);*/
                                printColor('C'); /** TEST */
                            }
                        }
                        for(z = 0 ; z < cifre+2; ++z){
                            printf(" ");
                        }
                        resetColor();
                    }    /* stampa le caselle bianche */
                    else if (topPl[j/cifre] == '#' || (cime[j/cifre]!=3)){
                        setWhite();
                        for(z = 0 ; z < cifre+2; ++z){
                            printf(" ");
                        }
                        resetColor();
                    }
                    /* stampa le caselle nere */
                    else{
                        for(z = 0 ; z < cifre+2; ++z){
                            printf(" ");
                        }
                    }
                }          
            }
            printf("|\n");

        }
        
        /* stampa separatore tra righe */
        if(((npl == 0)&&(i != t.n_rows-1))||((npl == 1)&&(i != 0))){
            printf("|");
            for(j=0; j<t.n_cols; j +=cifre){
                if(j != 0){
                    printf("+");
                }
                for(z = 0 ; z < cifre+2 ; ++z){
                    printf("-");
                }
            }
            printf("|\n");
        }

        if(npl == 0){
            ++i;
        }else{
            --i;
        }
    }

    /* stampa la base */
    for(j=0; j<t.n_cols; j +=cifre){
        printf("+");
        for(z = 0 ; z < cifre+2 ; ++z){
            printf("-");
        }
    }
    printf("+");/* recupero angolo dx */
    printf("\n");

    free(cime);
    free(topPl);
}

void print_directions(unsigned int *arr,unsigned int dim,unsigned int np){
    unsigned int i,flag = 0;
    for(i = 0 ; i < dim ;++i){
        if(arr[i]){
            ++flag;
        }
        printf("Move %u : %u\n",i,arr[i]);
    }
    if(flag != 0){
        if(flag == 1){
            printf("La pedina %u puo' muoversi solo in questa direzione : \n",np);
        }else{
            printf("La pedina %u puo' muoversi in queste direzioni : \n",np);
        }
        for(i = 0 ; i < dim ; ++i){
            if(i == 0 && arr[0] == 1){
                printf("-> sx\n");
            }
            if(i == 1 && arr[1] == 1){
                printf("-> dx\n");
            }
            if(i == 2 && arr[2] == 1){
                printf("-> bassodx\n");
            }
            if(i == 3 && arr[3] == 1){
                printf("-> bassosx\n");
            }
        }
    }
}

/* DONE */
player_t *create_pawns(unsigned int totPawns,char player1, char player2, unsigned int cifre,board_t board){
    player_t *players = NULL;
    int nPl;
    unsigned int h;

    players = (player_t*)calloc(2, sizeof(player_t));

    for (nPl = 0; nPl < 2; nPl++){
        players[nPl].pawns = (pawn_t*)calloc(totPawns,sizeof(pawn_t));
        for(h = 0 ; h < totPawns ; ++h){
            players[nPl].pawns[h].label = (char*)calloc((cifre+3+1),sizeof(char));
        }
        if( (players != NULL) && (players[nPl].pawns != NULL)){
            unsigned int i,nr,nc = 0;
            int c = -1;

            if(nPl == 0){
                nr = board.n_rows-1;
            }else{
                nr = 0;
            }
            while(c == -1){
                if(board.mat[nr][nc] == '#'){
                    c = nc;
                }
                ++nc;
            }
            nc = c ;

            for(i = 0 ; i < totPawns ; ++i){
                players[nPl].pawns[i].canMove = (unsigned int*) calloc(2, sizeof(unsigned int));
                players[nPl].pawns[i].label[0] = ' ';
                players[nPl].pawns[i].label[1] = ' ';
                if (nPl == 0){
                    players[nPl].pawns[i].label[2] = player1;
                }else{
                    players[nPl].pawns[i].label[2] = player2;                 
                }
                  
                if(i < 10){
                    unsigned int z;
                    for(z = 3 ; z < (3+cifre)-1 ; ++z){
                        players[nPl].pawns[i].label[z] = '0';
                    }
                    players[nPl].pawns[i].label[(3+cifre)-1] = '0'+i;
                }else {
                    unsigned int dest,index,num;
                    index = cifre-1;
                    if ((pow(10, index-1) == i) && (i != 1)) {
                        --index;
                    }
                    num = i;
                    for(dest = 3 ; dest < cifre+3 ; ++dest){
                        players[nPl].pawns[i].label[dest] = int_converter(num,index);
                        num -= pow(10,index)*(players[nPl].pawns[i].label[dest]-'0');
                        --index;
                    }
                }
                players[nPl].pawns[i].label[3+cifre] = ' ';
                players[nPl].pawns[i].dim_label = cifre;
                players[nPl].pawns[i].cima = 2 ;
                players[nPl].pawns[i].grade = 1 ;
                players[nPl].pawns[i].coordinate.y = nr;
                players[nPl].pawns[i].coordinate.x = nc;
                if (nPl == 0){
                    players[nPl].color = player1;
                }else{
                    players[nPl].color = player2;
                }
                
                if(nPl == 0){
                    if((nc+((3+cifre+1)*2) < board.n_cols) && (nc+((3+cifre+1)*2) > 0)){
                        nc +=((3+cifre+1)*2);
                    }else{
                        --nr;
                        if( c == 0){
                            c = (3+cifre+1) ;
                            nc = (3+cifre+1);
                        }else{
                            c = 0;
                            nc = 0;
                        }
                    }
                }else{
                    if((nc+((3+cifre+1)*2) < board.n_cols) && (nc+((3+cifre+1)*2) > 0)){
                        nc +=((3+cifre+1)*2);
                    }else{
                        ++nr;
                        if( c == 0){
                            c = (3+cifre+1) ;
                            nc = (3+cifre+1);
                        }else{
                            c = 0;
                            nc = 0;
                        }

                    }
                }

            }
            players[nPl].dim_pawns = totPawns;
        }else{
            printf("Errore malloc funzione crea_pedine\totPawns");
            return NULL;
        }
    }
    return players;  
}

/* DONE */
void print_player(player_t player){
    unsigned int i,j;
    for(i = 0 ; i < player.dim_pawns ; ++i){

        printf("Pedina = ");
        for(j = 0 ; j < 3+player.pawns[i].dim_label+1 ;++j ){
            printf("%c",player.pawns[i].label[j]);
        }
        printf("\n");
        print_directions(player.pawns[i].canMove, 2, i);
        printf("Cima = %d\n",player.pawns[i].cima);
        printf("grade pedina : %d \n",player.pawns[i].grade);
        printf("Posizione nel campo x: %d, y: %d\n",(player.pawns[i].coordinate.x/6)+1,(player.pawns[i].coordinate.y)+1);
        printf("Promozione pedina : %u\n",player.pawns[i].isPromoted);
        printf("\n");
    }
}

/* DONE */
void update_board(board_t *t,player_t *player){
    unsigned int i;
    int pl;
    for (pl = 0; pl < 2; pl++){
        for(i = 0 ; i < player[pl].dim_pawns ; ++i){
            if(player[pl].pawns[i].grade > 0){
                unsigned int j;
                for(j = 0 ; j < 3+player[pl].pawns[i].dim_label+1 ; ++j){
                    t->mat[player[pl].pawns[i].coordinate.y][player[pl].pawns[i].coordinate.x+j] = player[pl].pawns[i].label[j];
                }
            }
        }
    }

}

/* DONE */
unsigned int check_spot(board_t board,unsigned int row,unsigned int col,unsigned int dim_label){
    unsigned int i,flag = 0;
    for(i = 0 ; i < dim_label ; ++i){
        if((board.mat[row][col+i] != ' ')&&(board.mat[row][col+i] != '#') ){
            flag = 1;
        }
    }
    return flag;
}

/* DONE */
unsigned int is_selected(player_t *player, unsigned int num_pawn, unsigned int nPl){
    if(player[nPl].pawns[num_pawn].grade > 0 && (nPl == 0 || nPl == 0)){
        return 1;
    }else{
        return 0;
    }
}

/* DONE */
void remove_pawn(board_t *board, unsigned int row, unsigned int col, unsigned dim_label){
    unsigned int i;
    for(i = 0 ; i < dim_label ; ++i){
        board->mat[row][col+i] = '#';
    }
}

/* DONE */
void pawn_promotion(player_t *players, unsigned int num_pawn, unsigned int nPl, unsigned int last_row){
    if(((nPl == 0)&&(players[nPl].pawns[num_pawn].coordinate.y == 0)) || ((nPl == 0)&&(players[nPl].pawns[num_pawn].coordinate.y == last_row))){
        players[nPl].pawns[num_pawn].isPromoted = 1;
        players[nPl].pawns[num_pawn].label[players[nPl].pawns[num_pawn].dim_label+3] = '^';
        free(players[nPl].pawns[num_pawn].canMove);
        players[nPl].pawns[num_pawn].canMove = (unsigned int*)calloc(4 ,sizeof(unsigned int));
    }
}

/* DONE */
int check_player(player_t *players, unsigned int x, unsigned int y){
    unsigned int nPl, i;
    int flag = -1;
    for (nPl = 0; nPl < 2; nPl++){
        for(i = 0 ; i < players[nPl].dim_pawns ; ++i){
            if((players[nPl].pawns[i].coordinate.y == x)&&(players[nPl].pawns[i].coordinate.x == y)){
                flag = nPl;
            }
        }
    }
    return flag;
}

/* DONE */
unsigned int char_converter(board_t board, unsigned int r, unsigned int c, unsigned int dim_label){
    unsigned int i,num = 0,z = 0;
    for(i = dim_label ; i > 2 ; --i){
        num += ((board.mat[r][c+i]-'0')*pow(10,z));
        z++;
    }
    return num;
}

/* DONE */
unsigned int is_in(int r, int c, board_t board){
    if( (r < board.n_rows)&&(c<board.n_cols)){
        return 1;
    }else {
        return 0;
    }
}

/* DONE */
unsigned int check_directions(unsigned int *canMove_arr, unsigned int dim_canMove, char *str){
    unsigned int flag = 0, index = 5;
    for(index = 0 ; index < dim_canMove ; ++index){
        if(canMove_arr[index]){
            flag = 1;
        }
    }
    if(!flag){
        return 1;
    }
    if(!strcmp(str, "sx")){
        index = 0;
    }
    if(!strcmp(str, "dx")){
        index = 1;
    }
    if(!strcmp(str, "bassodx")){
        index = 2;
    }
    if(!strcmp(str, "bassosx")){
        index = 3;
    }
    if( index < dim_canMove && canMove_arr[index] == 1 ){
        return 1;
    }else{
        return 0;
    }
}

/* DONE */
void must_eat(player_t *players, board_t board, unsigned int n_pawn, unsigned int nPl){

        unsigned int flag = 1; 
        if( ((nPl == 0)&&(can_eat(players,n_pawn,"sx",&board, 0) >= 0)) || ((nPl == 1)&&(can_eat(players, n_pawn, "bassosx", &board,1)>=0))  ){
            if((nPl == 0 || nPl == 1) && flag == 1){
                reset_moves_pawns(players, n_pawn, nPl);
                flag = 0;
            }
            players[nPl].pawns[n_pawn].canMove[0] = 1;
        }

        if( ((nPl == 0)&&(can_eat(players,n_pawn,"dx",&board, 0) >= 0)) || ((nPl == 1)&&(can_eat(players, n_pawn, "bassodx", &board,1)>=0))  ){
            if((nPl == 0 || nPl == 1) && flag == 1){
                reset_moves_pawns(players, n_pawn, nPl);
                flag = 0;
            }
            players[nPl].pawns[n_pawn].canMove[1] = 1;
        }

        if (((players[0].pawns[n_pawn].isPromoted) || (players[1].pawns[n_pawn].isPromoted))){

            if( ((nPl == 0)&&(can_eat(players,n_pawn,"bassodx",&board, 0) >= 0)) || ((nPl == 1)&&(can_eat(players, n_pawn, "dx", &board,1)>=0))  ){
                if((nPl == 0 || nPl == 1) && flag == 1){
                    reset_moves_pawns(players, n_pawn, nPl);
                    flag = 0;
                }
                players[nPl].pawns[n_pawn].canMove[2] = 1;
            }

            if( ((nPl == 0)&&(can_eat(players,n_pawn,"bassosx",&board, 0) >= 0)) || ((nPl == 1)&&(can_eat(players, n_pawn, "sx", &board,1)>=0))){
                if((nPl == 0 || nPl == 1) && flag == 1){
                    reset_moves_pawns(players, n_pawn, nPl);
                    flag = 0;
                }
                players[nPl].pawns[n_pawn].canMove[3] = 1;
            }
        }
}

/* DONE */
int can_eat(player_t *players, unsigned int num_pawn, char *str, board_t *board, unsigned int nPl) {
    unsigned int nPl2 = 1;
    if(nPl == 1){
        nPl2 = 0;
    }
    if((nPl == 0)||(players[nPl].pawns[num_pawn].isPromoted)) {
        if ((!strcmp(str, "sx"))) {
            if ((is_in(players[nPl].pawns[num_pawn].coordinate.y - 2, players[nPl].pawns[num_pawn].coordinate.x - ((players[nPl].pawns[num_pawn].dim_label + 3 + 1) * 2), *board)) &&
                ((is_in(players[nPl].pawns[num_pawn].coordinate.y - 1, players[nPl].pawns[num_pawn].coordinate.x - (players[nPl].pawns[num_pawn].dim_label + 3 + 1), *board)))) {
                unsigned x, y, z;
                x = players[nPl].pawns[num_pawn].coordinate.y - 1;
                y = players[nPl].pawns[num_pawn].coordinate.x - (players[nPl].pawns[num_pawn].dim_label + 3 + 1);
                z = check_player(players, x, y);
                if ((z == nPl2) &&
                    (check_spot(*board, players[nPl].pawns[num_pawn].coordinate.y - 1, players[nPl].pawns[num_pawn].coordinate.x - (players[nPl].pawns[num_pawn].dim_label + 3 + 1),
                                (players[nPl].pawns[num_pawn].dim_label + 3 + 1))) &&
                    (!check_spot(*board, players[nPl].pawns[num_pawn].coordinate.y - 2, players[nPl].pawns[num_pawn].coordinate.x - ((players[nPl].pawns[num_pawn].dim_label + 3 + 1) * 2),
                                 (players[nPl].pawns[num_pawn].dim_label + 3 + 1)))) {
                    int num = -1;
                    num = char_converter(*board, players[nPl].pawns[num_pawn].coordinate.y - 1, players[nPl].pawns[num_pawn].coordinate.x - (players[nPl].pawns[num_pawn].dim_label + 3 + 1),
                                         2 + players[nPl].pawns[num_pawn].dim_label);
                    if ((num > -1) && (num < players[nPl].dim_pawns)) {
                        return num;
                    } else {
                        return -1;
                    }
                } else {
                    return -2;
                }
            } else {
                return -3;
            }
        }
        if ((!strcmp(str, "dx"))) {
            if ((is_in(players[nPl].pawns[num_pawn].coordinate.y - 2, players[nPl].pawns[num_pawn].coordinate.x + ((players[nPl].pawns[num_pawn].dim_label + 3) * 3), *board)) &&
                ((is_in(players[nPl].pawns[num_pawn].coordinate.y - 1, players[nPl].pawns[num_pawn].coordinate.x + (players[nPl].pawns[num_pawn].dim_label + 3 + 1), *board)))) {
                unsigned x, y, z;
                x = players[nPl].pawns[num_pawn].coordinate.y - 1;
                y = players[nPl].pawns[num_pawn].coordinate.x + (players[nPl].pawns[num_pawn].dim_label + 3 + 1);
                z = check_player(players, x, y);
                if ((z ==  nPl2) &&
                    (check_spot(*board, players[nPl].pawns[num_pawn].coordinate.y - 1, players[nPl].pawns[num_pawn].coordinate.x + (players[nPl].pawns[num_pawn].dim_label + 3 + 1),
                                players[nPl].pawns[num_pawn].dim_label + 3 + 1)) &&
                    (!check_spot(*board, players[nPl].pawns[num_pawn].coordinate.y - 2, players[nPl].pawns[num_pawn].coordinate.x + ((players[nPl].pawns[num_pawn].dim_label + 3 + 1) * 2),
                                 (players[nPl].pawns[num_pawn].dim_label + 3 + 1)))) {
                    int num = -1;
                    num = char_converter(*board, players[nPl].pawns[num_pawn].coordinate.y - 1, players[nPl].pawns[num_pawn].coordinate.x + (players[nPl].pawns[num_pawn].dim_label + 3 + 1),
                                         2 + players[nPl].pawns[num_pawn].dim_label);
                    if ((num > -1) && (num < players[nPl].dim_pawns)) {
                        return num;
                    } else {
                        return -1;
                    }

                } else {
                    return -2;
                }
            } else {
                return -3;
            }
        }
    }
    if (((nPl == 1) || (players[nPl].pawns[num_pawn].isPromoted))) {
        if ((!strcmp(str, "bassosx")) ) {
            if ((is_in(players[nPl].pawns[num_pawn].coordinate.y + 2, players[nPl].pawns[num_pawn].coordinate.x - ((players[nPl].pawns[num_pawn].dim_label + 3 + 1) * 2), *board)) &&
                ((is_in(players[nPl].pawns[num_pawn].coordinate.y + 1, players[nPl].pawns[num_pawn].coordinate.x - (players[nPl].pawns[num_pawn].dim_label + 3 + 1), *board)))) {
                unsigned x, y, z;
                x = players[nPl].pawns[num_pawn].coordinate.y + 1;
                y = players[nPl].pawns[num_pawn].coordinate.x - (players[nPl].pawns[num_pawn].dim_label + 3 + 1);
                z = check_player(players, x, y);
                if ((z ==  nPl2) && (check_spot(*board, players[nPl].pawns[num_pawn].coordinate.y + 1, players[nPl].pawns[num_pawn].coordinate.x - (players[nPl].pawns[num_pawn].dim_label + 3 + 1),
                                           (players[nPl].pawns[num_pawn].dim_label + 3 + 1))) &&
                    (!check_spot(*board, players[nPl].pawns[num_pawn].coordinate.y + 2, players[nPl].pawns[num_pawn].coordinate.x - ((players[nPl].pawns[num_pawn].dim_label + 3 + 1) * 2),
                                (players[nPl].pawns[num_pawn].dim_label + 3 + 1)))) {
                    int num = -1;
                    num =  char_converter(*board, players[nPl].pawns[num_pawn].coordinate.y + 1, players[nPl].pawns[num_pawn].coordinate.x - (players[nPl].pawns[num_pawn].dim_label + 3 + 1), 2 + players[nPl].pawns[num_pawn].dim_label);
                    if ((num > -1) && (num < players[nPl].dim_pawns)) {
                        return num;
                    } else {
                        return -1;
                    }
                } else {
                    return -2;
                }
            } else {
                return -3;
            }
        }
        if ((!strcmp(str, "bassodx")) ) {
            if ((is_in(players[nPl].pawns[num_pawn].coordinate.y + 2, players[nPl].pawns[num_pawn].coordinate.x + ((players[nPl].pawns[num_pawn].dim_label + 3) * 3), *board)) &&
                ((is_in(players[nPl].pawns[num_pawn].coordinate.y + 1, players[nPl].pawns[num_pawn].coordinate.x + (players[nPl].pawns[num_pawn].dim_label + 3 + 1), *board)))) {
                unsigned x, y, z;
                x = players[nPl].pawns[num_pawn].coordinate.y + 1;
                y = players[nPl].pawns[num_pawn].coordinate.x + (players[nPl].pawns[num_pawn].dim_label + 3 + 1);
                z = check_player(players, x, y);
                if ((z ==  nPl2) && (check_spot(*board, players[nPl].pawns[num_pawn].coordinate.y + 1, players[nPl].pawns[num_pawn].coordinate.x + (players[nPl].pawns[num_pawn].dim_label + 3 + 1),
                                           (players[nPl].pawns[num_pawn].dim_label + 3 + 1)) &&
                                 (!check_spot(*board, players[nPl].pawns[num_pawn].coordinate.y + 2, players[nPl].pawns[num_pawn].coordinate.x + ((players[nPl].pawns[num_pawn].dim_label + 3 + 1) * 2),
                                             (players[nPl].pawns[num_pawn].dim_label + 3 + 1))))) {
                    int num = -1;
                    num =  char_converter(*board, players[nPl].pawns[num_pawn].coordinate.y + 1, players[nPl].pawns[num_pawn].coordinate.x + (players[nPl].pawns[num_pawn].dim_label + 3 + 1), 2 + players[nPl].pawns[num_pawn].dim_label);
                    if ((num > -1) && (num < players[nPl].dim_pawns)) {
                        return num;
                    } else {
                        return -1;
                    }
                } else {
                    return -2;
                }
            } else {
                return -3;
            }
        } else {
            return -4;
        }
    }
    return -3;
}

/* DONE */
unsigned int move_noeat(player_t *players, unsigned int num_pawn, char *str, board_t *board, unsigned int nPl){
    if(!strcmp(str,"sx")){
        if((is_in(players[nPl].pawns[num_pawn].coordinate.y-1,players[nPl].pawns[num_pawn].coordinate.x-(players[nPl].pawns[num_pawn].dim_label+3+1),*board))&&(!check_spot(*board,players[nPl].pawns[num_pawn].coordinate.y-1,players[nPl].pawns[num_pawn].coordinate.x-(players[nPl].pawns[num_pawn].dim_label+3+1),(players[nPl].pawns[num_pawn].dim_label+3+1)))){
            remove_pawn(board,players[nPl].pawns[num_pawn].coordinate.y,players[nPl].pawns[num_pawn].coordinate.x,(players[nPl].pawns[num_pawn].dim_label+3+1));
            --players[nPl].pawns[num_pawn].coordinate.y;
            players[nPl].pawns[num_pawn].coordinate.x -= (players[nPl].pawns[num_pawn].dim_label+3+1);
            pawn_promotion(players,num_pawn,nPl,board->n_rows-1);
            return 1;
        }else{
            return 0;
        }
    }else{
        if (!strcmp(str, "dx")) {
            if((is_in(players[nPl].pawns[num_pawn].coordinate.y-1, players[nPl].pawns[num_pawn].coordinate.x + (players[nPl].pawns[num_pawn].dim_label + 3+1), *board))&&(!check_spot(*board, players[nPl].pawns[num_pawn].coordinate.y - 1, players[nPl].pawns[num_pawn].coordinate.x + (players[nPl].pawns[num_pawn].dim_label + 3+1),players[nPl].pawns[num_pawn].dim_label+3+1))){
                remove_pawn(board,players[nPl].pawns[num_pawn].coordinate.y,players[nPl].pawns[num_pawn].coordinate.x,(players[nPl].pawns[num_pawn].dim_label+3+1));
                --players[nPl].pawns[num_pawn].coordinate.y;
                players[nPl].pawns[num_pawn].coordinate.x += (players[nPl].pawns[num_pawn].dim_label+3+1);
                pawn_promotion(players,num_pawn,nPl,board->n_rows-1);
                return 1;
            }else{
                return 0;
            }
        }
        if (!strcmp(str, "bassosx") && ((nPl == 1) || (players[nPl].pawns[num_pawn].isPromoted))) {
            if((is_in(players[nPl].pawns[num_pawn].coordinate.y+1,players[nPl].pawns[num_pawn].coordinate.x-(players[nPl].pawns[num_pawn].dim_label+3+1),*board))&&(!check_spot(*board,players[nPl].pawns[num_pawn].coordinate.y+1,players[nPl].pawns[num_pawn].coordinate.x-(players[nPl].pawns[num_pawn].dim_label+3+1),(players[nPl].pawns[num_pawn].dim_label+3+1)))){
                remove_pawn(board,players[nPl].pawns[num_pawn].coordinate.y,players[nPl].pawns[num_pawn].coordinate.x,(players[nPl].pawns[num_pawn].dim_label+3+1));
                players[nPl].pawns[num_pawn].coordinate.y++;
                players[nPl].pawns[num_pawn].coordinate.x -= (players[nPl].pawns[num_pawn].dim_label+3+1);
                if(nPl == 0){
                    pawn_promotion(players,num_pawn,nPl,board->n_rows-1);
                }
                return 1;
            }else{
                return 0;
            }
        }
        if (!strcmp(str, "bassodx") && ((nPl == 1) || (players[nPl].pawns[num_pawn].isPromoted))) {
            if((is_in(players[nPl].pawns[num_pawn].coordinate.y+1, players[nPl].pawns[num_pawn].coordinate.x + (players[nPl].pawns[num_pawn].dim_label + 3+1), *board))&&(!check_spot(*board, players[nPl].pawns[num_pawn].coordinate.y+1, players[nPl].pawns[num_pawn].coordinate.x + (players[nPl].pawns[num_pawn].dim_label + 3+1),players[nPl].pawns[num_pawn].dim_label + 3+1))){
                remove_pawn(board,players[nPl].pawns[num_pawn].coordinate.y,players[nPl].pawns[num_pawn].coordinate.x,(players[nPl].pawns[num_pawn].dim_label+3+1));
                players[nPl].pawns[num_pawn].coordinate.y++;
                players[nPl].pawns[num_pawn].coordinate.x += (players[nPl].pawns[num_pawn].dim_label+3+1);
                if(nPl == 0){
                    pawn_promotion(players,num_pawn,nPl,board->n_rows-1);
                }
                return 1;
            }else{
                return 0;
            }
        }

    }

    return 0;
}

/* DONE */
unsigned int eat(player_t *players, char *str, unsigned int num_pawn, board_t board, unsigned int enemy_pawn, unsigned int nPl){
    unsigned int nPl2 = 0;
    if (nPl == 0){
        nPl2 = 1;
    }
    
    if(players[nPl2].pawns[enemy_pawn].label[players[nPl2].pawns[enemy_pawn].cima] == players[nPl2].pawns[enemy_pawn].label[players[nPl2].pawns[enemy_pawn].cima+1]) {
        players[nPl2].pawns[enemy_pawn].label[players[nPl2].pawns[enemy_pawn].cima] = ' ';
        ++players[nPl2].pawns[enemy_pawn].cima;
        --players[nPl2].pawns[enemy_pawn].grade;
    }else{
        char temp[3];
        unsigned int f;
        temp[0] = players[nPl].pawns[num_pawn].label[1];
        temp[1] = players[nPl].pawns[num_pawn].label[2];
        temp[2] = players[nPl2].pawns[enemy_pawn].label[players[nPl2].pawns[enemy_pawn].cima];

        if(players[nPl2].pawns[enemy_pawn].grade == 1){
            --players[nPl2].pawns[enemy_pawn].grade;
        }else{
            if (is_empty(players[nPl]) == -1) {
                add_pawn(players, enemy_pawn, nPl);
                /*remove_pawn(&board,players[nPl2].pawns[pos].coordinate.y,players[nPl2].pawns[pos].coordinate.x,players[nPl2].pawns[enemy_pawn].dim_label+3+1);
                players[nPl2].pawns[enemy_pawn].grade = 0;*/
            } else {
                unsigned int pos, i,index;

                pos = is_empty(players[nPl]);
                players[nPl2].pawns[enemy_pawn].label[players[nPl2].pawns[enemy_pawn].cima]= ' ';
                ++players[nPl2].pawns[enemy_pawn].cima;
                --players[nPl2].pawns[enemy_pawn].grade;
                for (i = 0; i < 3; ++i) {
                    players[nPl].pawns[pos].label[i] = players[nPl2].pawns[enemy_pawn].label[i];
                }
                players[nPl2].pawns[enemy_pawn].isPromoted = 0;
                players[nPl2].pawns[enemy_pawn].label[players[nPl2].pawns[enemy_pawn].dim_label+3] = ' ';
                players[nPl].pawns[pos].isPromoted = 0;
                players[nPl].pawns[pos].label[players[nPl2].pawns[enemy_pawn].dim_label+3] = ' ';

                players[nPl].pawns[pos].dim_label = players[nPl2].pawns[enemy_pawn].dim_label;
                players[nPl].pawns[pos].cima = players[nPl2].pawns[enemy_pawn].cima;
                players[nPl].pawns[pos].grade = players[nPl2].pawns[enemy_pawn].grade;
                players[nPl2].pawns[enemy_pawn].grade = 0;
                players[nPl].pawns[pos].coordinate.y = players[nPl2].pawns[pos].coordinate.y;
                players[nPl].pawns[pos].coordinate.x = players[nPl2].pawns[pos].coordinate.x;
                index = players[nPl].pawns[pos].dim_label;
                for(i = 3 ; i < players[nPl].pawns[pos].dim_label+3 ; ++i){
                    int_converter(pos,index);
                    --index;
                }
                if(players[nPl2].pawns[enemy_pawn].grade < 1){
                    remove_pawn(&board,players[nPl2].pawns[pos].coordinate.y,players[nPl2].pawns[pos].coordinate.x,players[nPl2].pawns[enemy_pawn].dim_label+3+1);
                }
            }
        }
        if(((is_empty(players[nPl]) != -1)||(players[nPl2].pawns[enemy_pawn].grade < 3)) && players[nPl].pawns[num_pawn].grade  < 3){
            if(players[nPl].pawns[num_pawn].grade  < 3){
                for(f = 0 ; f < 3 ; ++f ){
                    players[nPl].pawns[num_pawn].label[f] = temp[f];
                }
                ++players[nPl].pawns[num_pawn].grade;
                --players[nPl].pawns[num_pawn].cima;
            }
        }
    }
    if(!strcmp(str,"sx")){
        players[nPl].pawns[num_pawn].coordinate.y -= 2;
        players[nPl].pawns[num_pawn].coordinate.x -= (players[nPl].pawns[num_pawn].dim_label+3+1)*2;
    }else{
        if(!strcmp(str,"dx")){
            players[nPl].pawns[num_pawn].coordinate.y -= 2;
            players[nPl].pawns[num_pawn].coordinate.x += (players[nPl].pawns[num_pawn].dim_label+3+1)*2;
        }
        if(!strcmp(str,"bassosx")){
            players[nPl].pawns[num_pawn].coordinate.y += 2;
            players[nPl].pawns[num_pawn].coordinate.x -= (players[nPl].pawns[num_pawn].dim_label+3+1)*2;
        }
        if(!strcmp(str,"bassodx")){
            players[nPl].pawns[num_pawn].coordinate.y += 2;
            players[nPl].pawns[num_pawn].coordinate.x += (players[nPl].pawns[num_pawn].dim_label+3+1)*2;
        }

    }
    if(!strcmp(str,"sx")){
        remove_pawn(&board,players[nPl].pawns[num_pawn].coordinate.y+2,players[nPl].pawns[num_pawn].coordinate.x+((players[nPl].pawns[num_pawn].dim_label+3+1)*2),players[nPl].pawns[num_pawn].dim_label+3+1);
    }else{
        if(!strcmp(str,"dx")){
            remove_pawn(&board,players[nPl].pawns[num_pawn].coordinate.y+2,players[nPl].pawns[num_pawn].coordinate.x-((players[nPl].pawns[num_pawn].dim_label+3+1)*2),(players[nPl].pawns[num_pawn].dim_label+3+1));
        }
        if(!strcmp(str,"bassosx")){
            remove_pawn(&board,players[nPl].pawns[num_pawn].coordinate.y-2,players[nPl].pawns[num_pawn].coordinate.x+((players[nPl].pawns[num_pawn].dim_label+3+1)*2),players[nPl].pawns[num_pawn].dim_label+3+1);
        }
        if(!strcmp(str,"bassodx")){
            remove_pawn(&board,players[nPl].pawns[num_pawn].coordinate.y-2,players[nPl].pawns[num_pawn].coordinate.x-((players[nPl].pawns[num_pawn].dim_label+3+1)*2),(players[nPl].pawns[num_pawn].dim_label+3+1));
        }
    }
    pawn_promotion(players,num_pawn,nPl,board.n_rows-1);
    return 1;
}

/* DONE */
int move_p1 (player_t *players, unsigned int num_pawn, char *str, board_t *board, unsigned int nPl){
    int enemy_pawn;
    enemy_pawn = can_eat(players,num_pawn,str,board, nPl);
    if(enemy_pawn > -1){
        eat(players, str, num_pawn, *board, enemy_pawn, nPl);
        return enemy_pawn;
    }else{
        if(enemy_pawn == -1){
            printf("Errore nella char_convert\n");
            return -2;
        }else{
            if(enemy_pawn == -4){
                printf("Errore nella can_eat\n");
            }else{
                if(move_noeat(players, num_pawn, str, board, nPl)){
                    return -1;
                }else{
                    return -2;
                }

            }
        }
    }
    return 0;
}

/* DONE */
int move_p2(player_t *players,unsigned int num_pawn,char *str,board_t *board){
    if(!strcmp(str,"sx")) {
        return move_p1(players,num_pawn,"bassosx",board,1);
    }else{
        if(!strcmp(str,"dx")){
            return move_p1(players,num_pawn,"bassodx",board,1);
        }
        if(!strcmp(str,"bassodx")&&(players->pawns[num_pawn].isPromoted)) {
            return move_p1(players,num_pawn,"dx",board,1);
        }
        if(!strcmp(str,"bassosx")&&(players->pawns[num_pawn].isPromoted)) {
            return move_p1(players,num_pawn,"sx",board,1);
        }
    }

    return 0;
}

/* DONE */
unsigned int all_blocked(player_t *players, board_t board, unsigned int nPl){
    unsigned int i, flag = 1;
    for(i = 0 ; i < players[nPl].dim_pawns ; ++i){
        if(players[nPl].pawns[i].grade > 0 && check_canMove(players[nPl], i)){
            flag = 0;
        }
    }
    return flag;
}

/* DONE */
unsigned int is_victory(player_t *players){
    int i, nPl, winner_p1 = 0, winner_p2 = 0, flag = -1 ;

    for (nPl = 0; nPl < 2; nPl++){
        for(i = 0 ; i < players[nPl].dim_pawns ; ++i){
            players[nPl].pawns[i].grade == 0 && nPl == 0 ? ++winner_p1 : winner_p1;
            players[nPl].pawns[i].grade == 0 && nPl == 1 ? ++winner_p2 : winner_p2;
        }
        if(winner_p1 == players[nPl].dim_pawns && nPl == 0){
            winner_p1 = 2;
        }else if (winner_p2 == players[nPl].dim_pawns && nPl == 1){
            winner_p2 = 1;
        }   
    }

    if(winner_p1 == winner_p2){
        flag = 0;
    }else{
        winner_p1 > winner_p2 ? flag = 1 : flag;
        winner_p2 > winner_p1 ? flag = 2 : flag;
    }

    return flag;
}

unsigned int round_choice(){
    char str[2];

    printf("Inizia il turno come da predefinito (quindi primo giocatore)? ");
    scanf("%s",str);
    if((!strcmp(str,"si"))||(!strcmp(str,"Si"))||(!strcmp(str,"SI"))){
        return 0;
    }else{
        printf("Lancio monetina ? ");
        scanf("%s",str);
        if((!strcmp(str,"no"))||(!strcmp(str,"NO"))||(!strcmp(str,"No")) ){
            unsigned int npl = 0;
            printf("Giocatore 1 o 2 inizia per primo? : ");
            scanf("%u",&npl);
            while(npl != 1 && npl != 2){
                printf("Quale giocatore inizia per primo(1/2) ? ");
                scanf("%u",&npl);
            }

            return npl-1;
        }
        if((!strcmp(str,"si"))||(!strcmp(str,"Si"))||(!strcmp(str,"SI"))){
            int x = 0 ;
            srand(time(NULL));
            while(x == 0){
                x = rand()%10;
            }
            if(x%2 == 0){
                x = 0;
            }else{
                x = 1;
            }
            return x;
        }
    }
    return 0;
}


unsigned int round_player(player_t *players,board_t *t,unsigned int nPl){
    char str[10];
    unsigned int num_Pawn = 0;
    int y = -2;

    update_board(t,players);
    if(nPl == 0){
        printPlayerTurn(players[0].color);
        printf("Turno player 1 : \n");
        resetColor();
        print_board(*t,(players[0].pawns[0].dim_label+3)+1,0);
    }else{
        printPlayerTurn(players[1].color);
        printf("Turno player 2 : \n");
        resetColor();
        print_board(*t,(players[1].pawns[0].dim_label+3)+1,1);
    }



    printf("Vuoi uscire dal gioco ? ");
    scanf("%s",str);
    if((!strcmp(str,"si"))||(!strcmp(str,"Si"))||(!strcmp(str,"SI"))){
        return 3;
    }

    printf("Numero di pedina da selezionare : ");
    scanf("%u",&num_Pawn);
    
    while(!check_while(players, nPl, num_Pawn)){
        unsigned int flag = 1;
        if (nPl == 1 || nPl == 0 ){
            flag = check_canMove(players[nPl], num_Pawn);
        }
        if(!flag){
            printf("La pedina %u non puo' muoversi!\n",num_Pawn);
        }
        /*else{
            printf("Non puoi selezionare la pedina n. %u\n",num_Pawn);
        }*/
        printf("Numero di pedina da selezionare : ");
        scanf("%u",&num_Pawn);
    }
    printf("Vuoi selezionare questa pedina %u ? ",num_Pawn);
    scanf("%s",str);

    /* (!((np >= 0)&&( ((npl == 1)&&(np < p1->dim)) || ((npl == 2)&&(np < p2->dim))))) || */
    /*while( (!((np >= 0)&&( ((npl == 1)&&(np < p1->dim)) || ((npl == 2)&&(np < p2->dim))))) ||(!ped_noblock(*p1,*p2,*t,np,npl))){
        if(!ped_noblock(*p1,*p2,*t,np,npl)){
            printf("La pedina %u non puo' fare nessuna mossa!\n",np);
        }else{
            printf("Non puoi selezionare la pedina n. %u",np);
        }
        printf("Seleziona un'altra pedina : ");
        scanf("%u",&np);
    }*/

    while( (!strcmp(str,"no"))||(!strcmp(str,"NO"))||(!strcmp(str,"No")) ){
        printf("Numero di pedina da selezionare : ");
        scanf("%u",&num_Pawn);
        while(!check_while(players, nPl, num_Pawn)){
            unsigned int flag = 1;
            if (nPl == 1 || nPl == 0){
                flag = check_canMove(players[nPl], num_Pawn);
            }
            if(!flag){
                printf("La pedina %u non puo' muoversi!\n",num_Pawn);
            }
            /*else{
                printf("Non puoi selezionare la pedina n. %u\n",num_Pawn);
            }*/
            printf("Numero di pedina da selezionare : ");
            scanf("%u",&num_Pawn);
        }
        printf("Vuoi selezionare questa pedina %u ? ",num_Pawn);
        scanf("%s",str);
    }

    while(y==-2){
        /*must_eat(players,*t,num_Pawn,nPl);*/
        if(nPl == 1 || nPl == 0 ){
            unsigned int index = 2;
            players[nPl].pawns[num_Pawn].isPromoted ? index = 4 : index;
            print_directions(players[nPl].pawns[num_Pawn].canMove,index,num_Pawn);
        }
        printf("Verso che direzione vuoi spostare la pedina %u? ",num_Pawn);
        scanf("%s",str);
        if(nPl == 1 || nPl == 0){
            unsigned int index = 2;
            players[nPl].pawns[num_Pawn].isPromoted ? index = 4 : index;
            while(!check_directions(players[nPl].pawns[num_Pawn].canMove,index,str)){
                printf("Verso che direzione vuoi spostare la pedina %u? ",num_Pawn);
                scanf("%s",str);
            }
        }
        if(nPl == 0){
            y = move_p1(players,num_Pawn,str,t,nPl);
        }else{
            y = move_p2(players,num_Pawn,str,t);
        }
        if(y == 0){
            char temp[2];
            printf("La pedina numero %u non si puo' spostare verso %s\n",num_Pawn,str);

            printf("Numero di pedina da selezionare : ");
            scanf("%u",&num_Pawn);
            while(!check_while(players, nPl, num_Pawn)){
                unsigned int flag = 1;
                if (nPl == 1 || nPl == 0 ){
                    flag = check_canMove(players[nPl], num_Pawn);
                }
                if(!flag){
                    printf("La pedina %u non puo' muoversi!\n",num_Pawn);
                }else{
                    printf("Non puoi selezionare la pedina n. %u\n",num_Pawn);
                }
                printf("Numero di pedina da selezionare : ");
                scanf("%u",&num_Pawn);
            }

            printf("Vuoi selezionare questa pedina %d ? ",num_Pawn);
            scanf("%s",temp);

            while( (!strcmp(str,"no"))||(!strcmp(str,"NO"))||(!strcmp(str,"No")) ){
                printf("Numero di pedina da selezionare : ");
                scanf("%u",&num_Pawn);
                while(!check_while(players, nPl, num_Pawn)){
                    unsigned int flag = 1;
                    if (nPl == 1 || nPl == 0){
                        flag = check_canMove(players[nPl], num_Pawn);
                    }
                    if(!flag){
                        printf("La pedina %u non puo' muoversi!\n",num_Pawn);
                    }else{
                        printf("Non puoi selezionare la pedina n. %u\n",num_Pawn);
                    }
                    printf("Numero di pedina da selezionare : ");
                    scanf("%u",&num_Pawn);
                }
                printf("Vuoi selezionare questa pedina %u ? ",num_Pawn);
                scanf("%s",str);
            }
        }
    }
    update_board(t,players);
    if(nPl == 1 || nPl == 0){
        print_board(*t,(players[nPl].pawns[num_Pawn].dim_label+3)+1,1);
    }

    return 4;
}


int is_empty(player_t p){
    int pos = -1;
    unsigned int i;
    for(i = 0 ; i < p.dim_pawns ; ++i){
        if((p.pawns[i].grade == 0)&&(pos == -1)){
            pos = i;
        }
    }
    return pos;
}

unsigned int max_pawns(unsigned int r,unsigned int c){
    unsigned int k,l,t = 0,numped = 0;

    l = ((r+1)/2)-1;
    k = (c+1)/2;
    if(r%2 == 0){
        --r;
    }
    while(r-1 > l){
        if(!t){
            numped += k;
            t = 1;
        }else{
            if(c%2 != 0){
                numped += k-1;
            }else{
                numped += k;
            }
            t = 0;
        }
        --r;
    }

    return numped;
}

board_t *copy_board(board_t board ,board_t *newBoard){
    unsigned int flag = 0;
    if(newBoard == NULL){
        flag = 1;
        newBoard = (board_t*)malloc(sizeof(board_t));
    }
    if(newBoard != NULL){
        unsigned int j,k;
        newBoard->n_rows = board.n_rows;
        newBoard->n_cols = board.n_cols;
        if(flag == 1){
            unsigned int i;
            newBoard->mat = (char**)calloc((newBoard->n_rows),sizeof(char*));
            for(i = 0 ; i < newBoard->n_rows ; ++i){
                newBoard->mat[i] = (char*)calloc((newBoard->n_cols),sizeof(char));
            }
        }
        for(k = 0 ; k < newBoard->n_rows ; ++k){
            for(j = 0 ; j < newBoard->n_cols ; ++j){
                newBoard->mat[k][j] = board.mat[k][j];
            }
        }
        return newBoard;
        if(!(newBoard->mat)){
            printf("Errore nella campo_copy(malloc della matrice di char)");
            return NULL;
        }
    }else{
        printf("Errore nella campo_copy (malloc di newBoard)");
        return NULL;
    }
}

/* DONE
   ricordarsi canMove !! */
player_t *player_copy(player_t *players, player_t *newPlayers, unsigned int dim_label){
    unsigned int flag = 0;
    if(newPlayers == NULL){
        newPlayers = (player_t*)calloc(2, sizeof(player_t));
        flag = 1;
    }
    if(newPlayers != NULL){
        unsigned int  nPl;
        for (nPl = 0; nPl < 2; nPl++){
            unsigned int i,j;
            newPlayers[nPl].dim_pawns = players[nPl].dim_pawns;
            newPlayers[nPl].color = players[nPl].color;
            if(flag == 1){
                unsigned int l;
                newPlayers[nPl].pawns = (pawn_t*)calloc((newPlayers[nPl].dim_pawns),sizeof(pawn_t));
                for(l = 0 ; l < players[nPl].dim_pawns ; ++l){
                    newPlayers[nPl].pawns[l].label = (char*)calloc((dim_label),sizeof(char));
                }
                /**/
                for(l = 0 ; l < players[nPl].dim_pawns ; ++l){
                    /*unsigned int dim = 2;*/
                /*    if(players[nPl].pawns[l].isPromoted == 1){
                        dim = 4;
                    }*/
                    newPlayers[nPl].pawns[l].canMove = (unsigned int*)calloc(4,sizeof(unsigned int));
                }
                /**/

            }
            for(i = 0 ; i < newPlayers[nPl].dim_pawns ; ++i){
                unsigned int dim = 2;
                if(players[nPl].pawns[i].isPromoted == 1){
                    dim = 4;
                }

                /**/
                for(j = 0 ; j < dim ; ++j){
                    newPlayers[nPl].pawns[i].canMove[j] = players[nPl].pawns[i].canMove[j];
                }
                /**/

                for(j = 0 ; j < dim_label ; ++j){
                    newPlayers[nPl].pawns[i].label[j] = players[nPl].pawns[i].label[j];
                }
                newPlayers[nPl].pawns[i].dim_label = players[nPl].pawns[i].dim_label;
                newPlayers[nPl].pawns[i].cima = players[nPl].pawns[i].cima;
                newPlayers[nPl].pawns[i].grade = players[nPl].pawns[i].grade;
                newPlayers[nPl].pawns[i].coordinate.y = players[nPl].pawns[i].coordinate.y;
                newPlayers[nPl].pawns[i].coordinate.x = players[nPl].pawns[i].coordinate.x;
                newPlayers[nPl].pawns[i].isPromoted = players[nPl].pawns[i].isPromoted;
            }
        }       
        return newPlayers;
    }else{
        printf("Errore calloc player_copy");
        return NULL;
    }
}

unsigned int is_notstuck(player_t *players, board_t board, unsigned int nPawn, unsigned int nPl){
    board_t *newBoard = NULL;
    player_t *newPlayers = NULL;
    unsigned int dim_label = 0;

    dim_label = players[nPl].pawns[0].dim_label+3+1;
  
    newBoard = copy_board(board, newBoard);

    newPlayers = player_copy(players, newPlayers, dim_label);

    if(newBoard != NULL && newPlayers != NULL){
        unsigned int flag = 0;
        update_board(newBoard, newPlayers);
        if( ( (nPl == 0)&&(move_p1(newPlayers, nPawn, "sx", newBoard, 0) > -2)) || ((nPl == 1)&&(move_p2(newPlayers, nPawn, "sx", newBoard) > -2)) ){
            players[nPl].pawns[nPawn].canMove[0] = 1;
            flag = 1;
            copy_board(board, newBoard);
            player_copy(players, newPlayers, dim_label);
        }

        if( ((nPl == 0)&&(move_p1(newPlayers, nPawn, "dx", newBoard, 0) > -2)) || ((nPl == 1)&&(move_p2(newPlayers, nPawn, "dx", newBoard) > -2))){
            players[nPl].pawns[nPawn].canMove[1] = 1;
            flag = 1;
            copy_board(board, newBoard);
            player_copy(players, newPlayers, dim_label);
        }

        if (newPlayers[nPl].pawns[nPawn].isPromoted){
            if( ((nPl == 0)&&(move_p1(newPlayers, nPawn, "bassodx", newBoard, 0) > -2)) || ((nPl == 1)&&(move_p2(newPlayers, nPawn, "bassodx", newBoard) > -2))){
                players[nPl].pawns[nPawn].canMove[2] = 1;
                flag = 1;
                copy_board(board, newBoard);
                player_copy(players, newPlayers, dim_label);
            }
            if( ((nPl == 0)&&(move_p1(newPlayers, nPawn, "bassosx", newBoard, 0) > -2)) || ((nPl == 1)&&(move_p2(newPlayers, nPawn, "bassosx", newBoard) > -2))){
                players[nPl].pawns[nPawn].canMove[3] = 1;
                flag = 1;
                copy_board(board, newBoard);
                player_copy(players, newPlayers, dim_label);
            }
        }       
        destroy_board(newBoard);
        destroy_player(newPlayers);
        return flag;

    }else{
        printf("Errore nella ped_noblock\n");
        if(newBoard != NULL){
            destroy_board(newBoard);
        }
        if(newPlayers != NULL){
            destroy_player(newPlayers);
        }
        return 0;
    }
}

char int_converter(unsigned int num,unsigned int index){

    char let;
    let = '0';
    if((num/pow(10,index)) > 0){
        return let+(num/pow(10,index));
    }else{
        return '0';
    }
}

/* DONE */
unsigned int add_pawn(player_t *players, unsigned int enemy_pawn, unsigned int nPl){
    int nPl2 = 1;

    if (nPl == 1){
        nPl2 = 0;
    }
    
    players[nPl].pawns = (pawn_t*)realloc(players[nPl].pawns,(players[nPl].dim_pawns+1)*sizeof(pawn_t));
    players[nPl].pawns[players[nPl].dim_pawns].label = (char*)calloc((players[nPl2].pawns[enemy_pawn].dim_label+3+1),sizeof(char));
    players[nPl].pawns[players[nPl].dim_pawns].canMove = (unsigned int*)calloc(2,sizeof(unsigned int));

    if((players[nPl].pawns) &&(players[nPl].pawns[players[nPl].dim_pawns].label)) {
        unsigned int i,index;
        char temp[3];


        for(i = 0 ; i < 3-players[nPl2].pawns[enemy_pawn].grade ; ++i ){
            temp[i] = ' ';
        }
        i = (3-players[nPl2].pawns[enemy_pawn].grade)+1;
        ++i;
        while(i < 3){
            temp[i] = players[nPl2].pawns[enemy_pawn].label[players[nPl2].pawns[enemy_pawn].cima+i];
            ++i;
        }


        players[nPl2].pawns[enemy_pawn].label[players[nPl2].pawns[enemy_pawn].cima]= ' ';
        ++players[nPl2].pawns[enemy_pawn].cima;
        --players[nPl2].pawns[enemy_pawn].grade;
        players[nPl].pawns[players[nPl].dim_pawns].dim_label = players[nPl2].pawns[enemy_pawn].dim_label;
        players[nPl].pawns[players[nPl].dim_pawns].cima = players[nPl2].pawns[enemy_pawn].cima;
        players[nPl].pawns[players[nPl].dim_pawns].grade = players[nPl2].pawns[enemy_pawn].grade;
        players[nPl2].pawns[enemy_pawn].grade = 0;
        players[nPl].pawns[players[nPl].dim_pawns].coordinate.x = players[nPl2].pawns[enemy_pawn].coordinate.x;
        players[nPl].pawns[players[nPl].dim_pawns].coordinate.y = players[nPl2].pawns[enemy_pawn].coordinate.y;
        players[nPl2].pawns[enemy_pawn].isPromoted = 0;
        players[nPl2].pawns[enemy_pawn].label[players[nPl2].pawns[enemy_pawn].dim_label+3+1] = ' ';


        /* in caso if per cifre e riadattare cifre*/
        for(i = 0 ; i < 3 ; ++i){
            players[nPl].pawns[players[nPl].dim_pawns].label[i] = temp[i];
        }
        index = players[nPl2].pawns[enemy_pawn].dim_label;
        for(i = 3 ; i < players[nPl2].pawns[enemy_pawn].dim_label+3 ; ++i){
            players[nPl].pawns[players[nPl].dim_pawns].label[i] = players[nPl2].pawns[enemy_pawn].label[i];
            --index;
        }

        ++players[nPl].dim_pawns;
        return 1;
    }else{
        printf("Errore nella realloc\n");
        return 0;
    }
}


int player_vs_player(unsigned int x ){
    board_t *t = NULL;
    player_t *players = NULL;
    unsigned int exit = 4,turno,round = 0;
    unsigned int cifre,conta = 2,numped = 11;
    refresh();
    if(x == 0){
        t = create_board(7,7,3+conta+1);
        initialize_board(t,3+conta+1);
        players = create_pawns(11,'B','N',conta,*t); /* create array[2] of player_t type */
    }else{
        unsigned int w,h,max_ped = 0;
        char m;
        conta = 0;
        addstr("Ehi bello\n");
        printw("Altezza della scacchiera : ");
        scanw("%u",&h);
        /*getstr(&m);
        h = m-'0';*/
        /*scanw("%u",&h);*/
        printf("ciao %u",h);
        printw("Larghezza della scacchiera : ");
        /*getstr(&m);
        h = m-'0';*/
        scanw("%u",&w);
        printw("ciao %u\n",w);
        addstr("%d e BN0\n");
        printw("Ciao %d\n",17);
        while(w < 3 || h < 3){
            printw("Larghezza e altezza della scacchiera non soddisfa requisiti minimi(h >= 3,w >= 3)\n");
            printw("Reinserire altezza e larghezza\n ");
            printw("Altezza della scacchiera : ");
            /*scanf("%u",&h);*/
            scanw("%u",&h);
            printw("Larghezza della scacchiera : ");
            /*scanf("%u",&w);*/
            scanw("%u",&w);
            printw("ciao %u\n",w);
        }
        max_ped = max_pawns(h,w);
        printw("Numero di pedine massimo per giocatore : %u\n",max_ped);
        printw("Numero pedine ?(ovviamente minore o guale al massimo numero) : ");
        scanw("%u",&cifre);
        printf("ciao %u\n",cifre);
        /*scanf("%u",&cifre);*/
        while(cifre > max_ped){
            printf("Reinserire numero pedine : ");
            scanf("%u",&cifre);
        }
        numped = cifre;
        if(cifre > 0) {
            while (cifre != 0) {
                cifre /= 10;
                ++conta;
            }
            if ((pow(10, conta - 1) == numped) && (numped != 1)) {
                --conta;
            }
            t = create_board(h,w,3+conta+1);
            initialize_board(t,3+conta+1);
            players = create_pawns(numped,'B','N',conta,*t); /* create array[2] of player_t type */

        }else{
            printf("Non ha senso giocare con %u pedine !\n",cifre);
            return 0;
        }
    }

    turno = round_choice();
    printf("Il player che inizia e' %u\n",turno+1);
    /* &&(!is_victory(players)) */
    while((exit == 4)){
        set_moves_pawn(players,*t,0,-1);
        set_moves_pawn(players,*t,1,-1);
        /*if(all_blocked(players,*t,turno) == 0 && turno == 0){
            exit = 1;
        }
        if(all_blocked(players,*t,turno) == 1 && turno ==1){
            exit = 0;
        }*/
        if(exit == 4 ){
            printf("Round numero : %u\n",round);
            exit = round_player(players,t,turno);
            if(turno == 1){
                turno = 0;
            }else{
                turno = 1;
            }
            ++round;
        }
    }

    if(exit == 3){
        printf("Hai abbandonato la partita\n");
    }else{
        if(!exit){
            exit = is_victory(players);
        }
        printf("Round totali della partita : %u\n",round);
        printf("Il vincitore e' il player %d!\n",exit+1);
    }

    destroy_board(t);
    destroy_player(players);

    return 1;
}

/*
unsigned int round_ia_random(player_t *p1,player_t *ia,board_t *t,unsigned int npl){
    int np = -1, dim = 2;
    int newMove;
    char* move;
    srand(time(NULL));
    np = rand()%(ia->dim);

    while (!check_canMove(*ia,np) ||(!is_selected(*p1,*ia,np,npl))){
        if(last_move(*ia) == -1){
            np = rand()%(ia->dim);
        }else{
            np = last_move(*ia);
        }

    }

    if (ia->arr[np].isPromoted){
        dim = 4;
    }

    newMove = rand()%(dim);

    while(ia->arr[np].canMove[newMove] == 0){
        newMove = rand()%(dim);    
    }

    if (newMove == 0){
        move = "sx";
    }else if (newMove == 1){
        move = "dx";
    }else if (newMove == 2){
        move = "bassodx";
    }else if (newMove == 3){
        move = "bassosx";
    }
    if(npl == 2){
        move_p2(ia,np,move,t,p1);
    }else{
        move_p1(ia,np,move,t,p1,npl);
    }


    if( (move_p2(ia,np,"sx",t,p1)) || (move_p2(ia,np,"dx",t,p1))){
        return 0;
    }else{
        return 1;
    }*//*
    printf("Num ped : %u\n",np);

    return 0;

}
*/
/*
void player_vs_ia(){
    board_t *t = NULL;
    player_t *p1 = NULL,*ia = NULL;
     unsigned int exit = 0,turno,round = 0;
    unsigned int conta = 2;

    t = create_board(7,7,conta+3+1);
    initialize_board(t,conta+3+1);
    p1 = create_pawns(11,'B',1,conta,*t);*//* creare n pedine di carattere c *//*
    ia = create_pawns(11,'N',2,conta,*t);*//* creare n pedine di carattere c *//*
    update_board(t, *p1, *ia);


    turno = round_choice();
    printf("Il player che inizia e' %d\n",turno);
    while((exit == 0)&&(!is_victory(*p1,*ia,*t))) {
        set_moves_pawn(p1, ia, *t, 1, -1);
        set_moves_pawn(p1, ia, *t, 2, -1);
        if (all_blocked(*p1, *ia, *t, turno) == 1 && turno == 1) {
            exit = 2;
        }
        if (all_blocked(*p1, *ia, *t, turno) == 2 && turno == 2) {
            exit = 1;
        }
        if (!exit) {

            printf("Round numero : %u\n", round);
            if (turno == 1) {
                exit = round_ia(ia, p1, t, turno);
                exit = round_player(p1, ia, t, turno);
                exit = round_ia_minimax(p1,ia,t,turno);
                turno = 2;
            } else {
                exit = round_player(p1, ia, t, turno);
                turno = 1;
            }

        getchar();
        update_board(t, *p1, *ia);
        print_board(*t, 6, 1);
        sleep(5);
        ++round;
        }
    }
    if(exit == 3){
        printf("Hai abbandonato la partita\n");
    }else{
        if(!exit){
            exit = is_victory(*p1,*ia,*t);
        }
        printf("Round totali della partita : %u\n",round);
        if(all_blocked(*p1, *ia, *t, turno) == all_blocked(*ia, *p1, *t, turno)){
            printf("Nessun vincitore,entrambi i player bloccati\n");
        }else{
            printf("Il vincitore e' il player %d!\n",exit);
        }
    }
    print_player(*p1);
    printf("\n");
    print_player(*ia);

    destroy_board(t);
    destroy_player(p1);
    destroy_player(ia);
}*/

/* DONE */
void destroy_player (player_t *players){
    unsigned int i, nPl;

    for (nPl = 0; nPl < 2; nPl++){
        for(i = 0 ; i < players[nPl].dim_pawns ;++i){
            if (players[nPl].pawns[i].canMove){
                free(players[nPl].pawns[i].canMove);
            }
            
            free(players[nPl].pawns[i].label);
        }
        free(players[nPl].pawns);
    }
    
    free(players);
}

void destroy_board(board_t *board) {
    unsigned int i;

    for (i = 0; i < board->n_rows ;++i) {
        free(board->mat[i]);
    }
    free(board->mat);
    free(board);
}

void destroy_value_minimax(valueMinimax_t *arr,unsigned int dim){
    unsigned int i;
    for(i = 0 ; i < dim ; ++i){
        free(arr[i].directions);
    }
    free(arr);
}
/* DONE */
void reset_moves_pawns(player_t *players, int nPawn, unsigned int nPl){
    unsigned int i;
    if (nPawn == -1){
        for(i = 0 ; i < players[nPl].dim_pawns ; ++i){
            unsigned int j,z;
            if(players[nPl].pawns[i].isPromoted == 1){
                z = 4;
            }else{
                z = 2;
            }
            for(j = 0; j < z ; ++j){
                players[nPl].pawns[i].canMove[j] = 0;
            }
        }
    }else{
        unsigned int j,z;
        if(players[nPl].pawns[nPawn].isPromoted == 1){
            z = 4;
        }else{
            z = 2;
        }
        for(j = 0; j < z ; ++j){
            players[nPl].pawns[nPawn].canMove[j] = 0;
        }   
    } 
}

/* DONE */
void set_moves_pawn(player_t *players, board_t board, unsigned int nPl, int nPawn){
    unsigned int i;
    if(nPawn == -1){
        reset_moves_pawns(players, -1, nPl);
        for(i = 0; i < players[nPl].dim_pawns; ++i){
            if(players[nPl].pawns[i].grade > 0){
                is_notstuck(players, board, i, nPl);
                must_eat(players, board, i, nPl);

            }
        }
    }else{
        if(nPawn > 0 && nPawn < players[nPl].dim_pawns){
            reset_moves_pawns(players, nPawn, nPl);
            if(players[nPl].pawns[nPawn].grade > 0){
                is_notstuck(players, board, nPawn, nPl);
                must_eat(players, board, nPawn, nPl);
            }
        }
    }
}

/**
 * @brief Ritorna 0 se tutti gli elementi di canMove sono 0. 
 * 
 * @param p 
 * @param nPed 
 * @return unsigned int 
 */
unsigned int check_canMove(player_t player, int nPed){
    unsigned int i = 0, dim = 2, flag = 0;
    if (player.pawns[nPed].isPromoted == 1){
        dim = 4;
    }
    while (i < dim && flag == 0){
        if (player.pawns[nPed].canMove[i] == 1){
            flag = 1;
        }

        i++;
    }
    return flag;
}

int last_move(player_t player){
    unsigned int flag = 0 ,pos = 0,i;
    for(i = 0 ; i < player.dim_pawns ; ++i){
        if(check_canMove(player,i)){
            ++flag ;
            pos = i;
        }
    }
    if(flag < 2){
        return pos;
    }else{
        return -1;
    }
}


unsigned int check_while(player_t *players, unsigned int nPl, unsigned int nPawn){

    if (  (nPl == 0 || nPl ==1) && ( nPawn > -1 && nPawn < players[nPl].dim_pawns)  ){
        return check_canMove(players[nPl], nPawn);
    }else{
        return 1;
    }
}

unsigned int check_string(char *str){
    unsigned int flag = 0;
    if(!strcmp(str,"sx")){
        flag = 1;
    }
    if(!strcmp(str,"dx")){
        flag = 1;
    }
    if(!strcmp(str,"bassosx")){
        flag = 1;
    }
    if(!strcmp(str,"bassodx")){
        flag = 1;
    }
    return flag;
}

unsigned int max(valueMinimax_t *arr,unsigned int dim){
    unsigned int i,pos = 0;
    int max;
    max = arr[0].value;
    for(i = 1 ; i < dim ; ++i){
        if(arr[i].value != -17){
            if((check_string(arr[i].directions))&&(max < arr[i].value)){
                max = arr[i].value;
                pos = i;
            }
        }
    }
    return pos;
}
/*
int round_ia_minimax(player_t *p1, player_t *p2, board_t *board,unsigned int nPl){
    valueMinimax_t *arr;
    unsigned int pos;
    arr = (valueMinimax_t*)calloc(p1->dim,sizeof(valueMinimax_t));
    for(pos = 0 ; pos < p1->dim ; ++pos){
        arr[pos].direction = calloc(7,sizeof(char));
    }
    if(arr){
        for(pos = 0; pos < p1->dim ; ++pos){
            if(!check_canMove(*p1,pos)|| p1->arr[pos].grado < 1){
                arr[pos].value = -17;
            }else{
                minimax(*board,*p1,*p2,3,pos,1,&(arr[pos]));
            }
        }
        print_minimax(arr,p1->dim);
        pos = max(arr,p1->dim);
        printf("Pos e dir : %u e %s\n",pos,arr[pos].direction);
        move_p1(p1,pos,arr[pos].direction,board,p2,nPl);
        destroy_value_minimax(arr,p1->dim);
        return 0;
    }else{
        printf("Errore calloc round_ia_minimax\n");
        return 3;
    }

}
void print_minimax(valueMinimax_t *arr,unsigned int dim){
    unsigned int i;
    for(i = 0 ; i < dim ; ++i){
        if(arr[i].value == -17){
            printf("\n\n*** MINIMAX ped. %u: %d ***\n\n",i,arr[i].value);
        }else{
            printf("\n\n*** MINIMAX ped. %u: %d e %s***\n\n",i,arr[i].value,arr[i].direction );
        }
    }
}
int evaluate_score(board_t board, player_t p1, player_t p2){
    int i, val = 0;
    for ( i = 0; i < p1.dim; i++){
        if (p1.arr[i].grado>0){
            val++;
        }
    }
    for ( i = 0; i < p2.dim; i++){
        if (p2.arr[i].grado>0){
            val--;
        }
    }
    return val;
}

void restore_copy(board_t *board_copy, player_t *p1_copy, player_t *p2_copy, board_t board, player_t p1, player_t p2){
    board_copy = copy_board(board, board_copy);
    p1_copy = player_copy(p1, p1_copy, 6);
    p2_copy = player_copy(p2, p2_copy, 6);
}
int call_minimax(board_t *board_copy, player_t *p1_copy, player_t *p2_copy, int depth, int nPed, int nPl,valueMinimax_t *v,char *str,int maxEval){
    int x,eval;
    if(nPl == 0){
        x = move_p1(p1_copy, nPed, str, board_copy, p2_copy, 1);
    }else{
        x = move_p2(p2_copy, nPed, str, board_copy, p1_copy);
    }

    update_board(board_copy, *p1_copy, *p2_copy);

    if(nPl == 0){
        set_moves_pawn(p1_copy, p2_copy, *board_copy, 1, nPed);
        if (x > -1 && x < p1_copy->dim) {
            set_moves_pawn(p1_copy, p2_copy, *board_copy, 2, x);
        }
        eval = minimax(*board_copy, *p1_copy, *p2_copy, depth - 1, nPed, 2, v);
        if ( maxEval < eval ) {
            maxEval = eval;
            v->value = eval;
            strcpy(v->direction, str);
            return eval;
        }
    }else{
        set_moves_pawn(p1_copy, p2_copy, *board_copy, 2, nPed);
        if(x > -1 && x < p2_copy->dim){
            set_moves_pawn(p1_copy, p2_copy, *board_copy, 1, x);
        }
        eval = minimax(*board_copy, *p1_copy, *p2_copy, depth-1, nPed, 1,v);
        if ( maxEval > eval ) {
            maxEval = eval;
            v->value = eval;
            strcpy(v->direction, str);
            return eval;
        }
    }
    return -1;
}
int minimax(board_t board, player_t p1, player_t p2, int depth, int nPed, int nPl,valueMinimax_t *v){
    board_t *board_copy = NULL;
    player_t *p1_copy = NULL;
    player_t *p2_copy = NULL;

    if (depth == 0 || ( (!check_canMove(p1, nPed)||(p1.arr[nPed].grado<1)) && nPl == 0)|| ( (!check_canMove(p2, nPed)||(p2.arr[nPed].grado<1)) && nPl == 0)){
        v->value = evaluate_score(board, p1, p2);
        return v->value;
        return evaluate_score(board, p1, p2);*/ /*
    }

    board_copy = copy_board(board, board_copy);
    p1_copy = player_copy(p1, p1_copy, 6);
    p2_copy = player_copy(p2, p2_copy, 6);

    if (nPl == 0){

        int maxEval;
        int eval;

        maxEval = -9999;

            if (p1_copy->arr[nPed].canMove[0] == 1) {
                int x;
                x = call_minimax(board_copy,p1_copy,p2_copy,depth,nPed,1,v,"sx",maxEval);
                maxEval < x ?  maxEval = x : maxEval ;
                int x; */ /*
                x = move_p1(p1_copy, nPed, "sx", board_copy, p2_copy, 1);
                update_board(board_copy, *p1_copy, *p2_copy);
                set_moves_pawn(p1_copy, p2_copy, *board_copy, 1, nPed);
                if (x > -1 && x < p2.dim) {
                    set_moves_pawn(p1_copy, p2_copy, *board_copy, 2, x);
                }
                eval = minimax(*board_copy, *p1_copy, *p2_copy, depth - 1, nPed, 2, v);
                if (maxEval < eval) {
                    maxEval = eval;
                    v->value = eval;
                    strcpy(v->direction, "sx");

                }

            }
            restore_copy(board_copy, p1_copy, p2_copy, board, p1, p2);

            if (p1_copy->arr[nPed].canMove[1] == 1) {
                */ /* int x;
                x = call_minimax(board_copy,p1_copy,p2_copy,depth,nPed,1,v,"dx",maxEval);
                maxEval < x ?  maxEval = x : maxEval ; */ /*
                int x;
                x = move_p1(p1_copy, nPed, "dx", board_copy, p2_copy, 1);
                update_board(board_copy, *p1_copy, *p2_copy);
                set_moves_pawn(p1_copy, p2_copy, *board_copy, 1, nPed);
                if (x > -1 && x < p2.dim) {
                    set_moves_pawn(p1_copy, p2_copy, *board_copy, 2, x);
                }
                eval = minimax(*board_copy, *p1_copy, *p2_copy, depth - 1, nPed, 2, v);

                if (maxEval < eval ) {
                    maxEval = eval;
                    v->value = eval;
                    strcpy(v->direction, "dx");

                }
            }
            restore_copy(board_copy, p1_copy, p2_copy, board, p1, p2);

            if (p1_copy->arr[nPed].isPromoted == 1) {
                if (p1_copy->arr[nPed].canMove[2] == 1) {
                    */ /* int x;
                    x = call_minimax(board_copy,p1_copy,p2_copy,depth,nPed,1,v,"bassosx",maxEval);
                    maxEval < x ?  maxEval =x : maxEval ; */ /*
                    int x;
                    x = move_p1(p1_copy, nPed, "bassosx", board_copy, p2_copy, 1);
                    update_board(board_copy, *p1_copy, *p2_copy);
                    set_moves_pawn(p1_copy, p2_copy, *board_copy, 1, nPed);
                    if (x > -1 && x < p2.dim) {
                        set_moves_pawn(p1_copy, p2_copy, *board_copy, 2, x);
                    }
                    eval = minimax(*board_copy, *p1_copy, *p2_copy, depth - 1, nPed, 2, v);

                    if (maxEval < eval ) {
                        maxEval = eval;
                        v->value = eval;
                        strcpy(v->direction, "bassosx");

                    }
                }
                restore_copy(board_copy, p1_copy, p2_copy, board, p1, p2);

                if (p1_copy->arr[nPed].canMove[3] == 1) {
                     *//* int x;
                    x = call_minimax(board_copy,p1_copy,p2_copy,depth,nPed,1,v,"bassodx",maxEval);
                    maxEval < x  ?  maxEval = x : maxEval ; */ /*
                    int x;
                    x = move_p1(p1_copy, nPed, "bassodx", board_copy, p2_copy, 1);
                    update_board(board_copy, *p1_copy, *p2_copy);
                    set_moves_pawn(p1_copy, p2_copy, *board_copy, 1, nPed);
                    if (x > -1 && x < p2.dim) {
                        set_moves_pawn(p1_copy, p2_copy, *board_copy, 2, x);
                    }
                    eval = minimax(*board_copy, *p1_copy, *p2_copy, depth - 1, nPed, 2, v);

                    if (maxEval < eval ) {
                        maxEval = eval;
                        v->value = eval;
                        strcpy(v->direction, "bassodx");

                    }
                }
                restore_copy(board_copy, p1_copy, p2_copy, board, p1, p2);
            }

        destroy_player(p1_copy);
        destroy_player(p2_copy);
        destroy_board(board_copy);

        return maxEval;

    }else{
        int maxEval,i;
        int eval;

        maxEval = +9999;

        restore_copy(board_copy, p1_copy, p2_copy, board, p1, p2);

        for (i = 0; i < p2_copy->dim; i++){
            
            if (p2_copy->arr[i].grado > 0 ){
                if (p2_copy->arr[i].canMove[0] == 1){
                    int x;
                    x = call_minimax(board_copy,p1_copy,p2_copy,depth,nPed,2,v,"sx",maxEval);
                    maxEval > x  ?  maxEval = x : maxEval ; */ /*
                    int x;
                    x = move_p2(p2_copy, i, "sx", board_copy, p1_copy);
                    update_board(board_copy, *p1_copy, *p2_copy);
                    if(x > -1 && x < p1.dim){
                        set_moves_pawn(p1_copy, p2_copy, *board_copy, 1, x);
                    }
                    set_moves_pawn(p1_copy, p2_copy, *board_copy, 2, i);
                    eval = minimax(*board_copy, *p1_copy, *p2_copy, depth-1, nPed, 1,v);

                    if(maxEval > eval ){
                        maxEval = eval;
                        v->value = eval;
                        strcpy( v->direction,"sx");

                    }
                }
                restore_copy(board_copy, p1_copy, p2_copy, board, p1, p2);

                if (p2_copy->arr[i].canMove[1] == 1){
                    */ /* int x;
                    x = call_minimax(board_copy,p1_copy,p2_copy,depth,nPed,2,v,"sx",maxEval);
                    maxEval > x  ?  maxEval = x : maxEval ; *//*
                    int x;
                    x = move_p2(p2_copy, i, "dx", board_copy, p1_copy);
                    update_board(board_copy, *p1_copy, *p2_copy);
                    if(x > -1 && x < p1.dim){
                        set_moves_pawn(p1_copy, p2_copy, *board_copy, 1, x);
                    }
                    set_moves_pawn(p1_copy, p2_copy, *board_copy, 2, i);
                    eval = minimax(*board_copy, *p1_copy, *p2_copy, depth-1, nPed, 1,v);

                    if(maxEval > eval){
                        maxEval = eval;
                        v->value = eval;
                        strcpy( v->direction,"dx");

                    }
                }
                restore_copy(board_copy, p1_copy, p2_copy, board, p1, p2);

                if (p2_copy->arr[i].isPromoted == 1){
                    if (p2_copy->arr[i].canMove[2] == 1){
                        */ /* int x;
                        x = call_minimax(board_copy,p1_copy,p2_copy,depth,nPed,2,v,"sx",maxEval);
                        maxEval > x  ?  maxEval = x : maxEval ; *//*
                        int x;
                        x = move_p2(p2_copy, i, "bassosx", board_copy, p1_copy);
                        update_board(board_copy, *p1_copy, *p2_copy);
                        if(x > -1 && x < p1.dim){
                            set_moves_pawn(p1_copy, p2_copy, *board_copy, 1, x);
                        }
                        set_moves_pawn(p1_copy, p2_copy, *board_copy, 2, i);
                        eval = minimax(*board_copy, *p1_copy, *p2_copy, depth-1, nPed, 1,v);

                        if(maxEval > eval ){
                            maxEval = eval;
                            v->value = eval;
                            strcpy( v->direction,"bassosx");

                        }
                    }
                    restore_copy(board_copy, p1_copy, p2_copy, board, p1, p2);

                    if (p2_copy->arr[i].canMove[3] == 1){
                        int x;
                        x = call_minimax(board_copy,p1_copy,p2_copy,depth,nPed,2,v,"sx",maxEval);
                        maxEval > x ?  maxEval = x : maxEval ; */ /*
                        int x;
                        x = move_p2(p2_copy, i, "bassodx", board_copy, p1_copy);
                        update_board(board_copy, *p1_copy, *p2_copy);
                        if(x > -1 && x < p1.dim){
                            set_moves_pawn(p1_copy, p2_copy, *board_copy, 1, x);
                        }
                        set_moves_pawn(p1_copy, p2_copy, *board_copy, 2, i);
                        eval = minimax(*board_copy, *p1_copy, *p2_copy, depth-1, nPed, 1,v);

                        if(maxEval > eval ){
                            maxEval = eval;
                            v->value = eval;
                            strcpy( v->direction,"bassodx");

                        }
                    }
                    restore_copy(board_copy, p1_copy, p2_copy, board, p1, p2);
                }
            }
        }
        destroy_player(p1_copy);
        destroy_player(p2_copy);
        destroy_board(board_copy);
       
        return maxEval;

    }
}*/
    
    

/*
    function minimax(nodo, profondità)
    SE nodo è un nodo terminale OPPURE profondità = 0
        return il valore euristico del nodo
    SE l'avversario deve giocare
        α := +∞
        PER OGNI figlio di nodo
            α := min(α, minimax(figlio, profondità-1))
    ALTRIMENTI dobbiamo giocare noi
        α := -∞
        PER OGNI figlio di nodo
            α := max(α, minimax(figlio, profondità-1))
    return α
*/

/*

    function minimax(position, depth, maximizingPlayer)
        if depth == 0 or game over in position
            return static evaluation of position
    
        if maximizingPlayer
            maxEval = -infinity
            for each child of position
                eval = minimax(child, depth - 1, false)
                maxEval = max(maxEval, eval)
            return maxEval
    
        else
            minEval = +infinity
            for each child of position
                eval = minimax(child, depth - 1, true)
                minEval = min(minEval, eval)
            return minEval
    
    
    // initial call
    minimax(currentPosition, 3, true)

*/


/*unsigned int i; ,*pos;
 int *punteggio;

 pos = (unsigned int *)malloc(sizeof(unsigned int)*p->dim);
 punteggio = (int *)malloc(sizeof(int)*p->dim);

for(i = 0 ; i < p->dim ; ++i){
if pedina non  bloccata
 int p,j;
 p = minimax (sx);
 j = minimax (dx);
 if  p > j
     punteggio[i] = p;
     pos[i] = 0;
     if(minimax(bassosx) > minimax(bassodx) && ispromoted)
         punteggio[i] < minimax(bassosx) ? punteggio[i] = minimax(bassosx) : 0;
         pos[i] = 3;
      else
         ...
 else
     ...

}
for(i = 0 ; i < p->dim ; ++i){
trovo max punteggio
m = i (indice max punteggio )
}

return m
return 0;*/


/* liberare punt e pos con free*/