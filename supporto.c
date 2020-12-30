#include<stdio.h>
#include<stdlib.h>
#include"supporto.h"
#include<string.h>
#include<time.h>
#include <math.h>
#include "src/colors/colors.h"

tcampo* create_board(unsigned int r,unsigned int col,unsigned int cifre){
    tcampo *t = NULL;

    t = (tcampo*)malloc(sizeof(tcampo));
    if(t != NULL){
        unsigned int i;
        t->r = r;
        t->c = (col*cifre);
        t->mat = (char**)calloc((t->r),sizeof(char*));
        for(i = 0 ; i < t->r ; ++i){
            t->mat[i] = (char*)calloc((t->c),sizeof(char));

        }
        return t;
    }else{
        printf("Errore nella malloc nella funzione crea_campo\n");
        return NULL;
    }

}
void initialize_board(tcampo *t,unsigned int cifre){
    unsigned int i,j;

    for(i = 0 ; i < t->r ; ++i) {
        for (j = 0; j < t->c; j += cifre) {

            if (((j / cifre) + i) % 2 == 0) {
                int z;
                for (z = 0; z < cifre; ++z) {
                    t->mat[i][j+z] = '#';
                }

            } else {
                int z;
                for (z = 0; z < cifre; ++z) {
                    t->mat[i][j+z] = ' ';
                }

            }
        }
    }

}

void print_board(tcampo t,unsigned int cifre, unsigned npl){
    int i, j, k = 0, z;
    char topPl;

    /* stampo prima riga */
    for(j=0; j<t.c; j +=cifre){
        printf("+");
        for(z = 0 ; z < cifre+2; ++z){ /* 2 = spazio a destra e sinistra */
            printf("-");
        }
    }
    printf("+");/* recupero angolo dx */
    printf("\n");

    /* parte centrale */
    if(npl == 1){
        i = 0;
    }else{
        i = t.r-1;
    }
    while( (((npl == 1)&&(i < t.r))||((npl == 2)&&(i >= 0))) ){
        for(j=0; j<t.c; j +=cifre){
            printf("|");

            /* controllo dov'è la cima */
            while (t.mat[i][j+k] != 'N' && t.mat[i][j+k] != 'B' && k<3){
                k++;
            }
            topPl = t.mat[i][j+k]; /* indica il possessore della torre */

            /* stampa le torri */
            if (topPl == 'N' || topPl == 'B'){
                setBlack();
                if (topPl == 'N'){
                    setRed(2);
                }else if (topPl == 'B'){
                    setYellow(2);
                }
                printf(" ");
                for (z = 0; z < cifre; z++){
                    /* controlla se all'interno della torre c'è una pedina avversaria */
                    if ((t.mat[i][j+z] == 'B' || t.mat[i][j+z] == 'N') && t.mat[i][j+z] != topPl){
                        if (topPl == 'N'){
                            setYellow(2);
                        }else if (topPl == 'B'){
                            setRed(2);
                        }
                        /* altrimenti stampa il colore del proprietario */
                    }else{
                        if (topPl == 'N'){
                            setRed(2);
                        }else if (topPl == 'B'){
                            setYellow(2);
                        }
                    }
                    printf("%c",t.mat[i][j+z]);
                }
                printf(" ");
                resetColor();
            }
                /* stampa le caselle bianche */
            else if (topPl == '#'){
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
            k = 0;
        }
        printf("|\n");

        /* stampa separatore tra righe */
        if(((npl == 1)&&(i != t.r-1))||((npl == 2)&&(i != 0))){
            printf("|");
            for(j=0; j<t.c; j +=cifre){
                if(j != 0){
                    printf("+");
                }
                for(z = 0 ; z < cifre+2 ; ++z){
                    printf("-");
                }
            }
            printf("|\n");
        }

        if(npl == 1){
            ++i;
        }else{
            --i;
        }
    }

    /* stampa la base */
    for(j=0; j<t.c; j +=cifre){
        printf("+");
        for(z = 0 ; z < cifre+2 ; ++z){
            printf("-");
        }
    }
    printf("+");/* recupero angolo dx */
    printf("\n");

}
void print_directions(unsigned int *arr,unsigned int dim,unsigned int np){
    unsigned int i,flag = 0;
    for(i = 0 ; i < dim ;++i){
        if(arr[i]){
            flag = 1;
        }
    }
    if(flag == 1){
        printf("La pedina %u puo' muoversi in queste direzioni : \n",np);
        for(i = 0 ; i < dim ; ++i){
            if(i == 0 && arr[0] == 1){
                printf("sx\n");
            }
            if(i == 1 && arr[1] == 1){
                printf("dx\n");
            }
            if(i == 2 && arr[2] == 1){
                printf("bassosx\n");
            }
            if(i == 3 && arr[3] == 1){
                printf("bassodx\n");
            }
        }
    }


}
tplayer *create_pawns(unsigned int n,char ped,unsigned int np,unsigned int cifre,tcampo t){
    tplayer *p = NULL;
    unsigned int h;

    p = (tplayer*)malloc(sizeof(tplayer));
    p->arr = (tpedina*)calloc(n,sizeof(tpedina));
    for(h = 0 ; h < n ; ++h){
        p->arr[h].et = (char*)calloc((cifre+3+1),sizeof(char));
    }
    if( (p != NULL) && (p->arr != NULL)){
        unsigned int i,nr,nc = 0;
        int c = -1;

        if(np == 1){
            nr = t.r-1;
            while(c == -1){
                if(t.mat[nr][nc] == '#'){
                    c = nc;
                }
                ++nc;
            }
            nc = c ;
        }else{
            nr = 0;
            while(c == -1){
                if(t.mat[nr][nc] == '#'){
                    c = nc;
                }
                ++nc;
            }
            nc = c ;
        }

        for(i = 0 ; i < n ; ++i){
            p->arr[i].canMove = (unsigned int*) calloc(2, sizeof(unsigned int));
            p->arr[i].et[0] = ' ';
            p->arr[i].et[1] = ' ' ;
            p->arr[i].et[2] = ped;
            if(i < 10){
                unsigned int z;
                for(z = 3 ; z < (3+cifre)-1 ; ++z){
                    p->arr[i].et[z] = '0';
                }
                p->arr[i].et[(3+cifre)-1] = '0'+i;
            }else {
                unsigned int dest,index,num;
                index = cifre-1;
                if ((pow(10, index-1) == i) && (i != 1)) {
                    --index;
                }
                num = i;
                for(dest = 3 ; dest < cifre+3 ; ++dest){
                    p->arr[i].et[dest] = int_converter(num,index);
                    num -= pow(10,index)*(p->arr[i].et[dest]-'0');
                    --index;
                }
            /*    unsigned int x = 1, f = 3, z,m = i;
                z = cifre-1;
                x = pow(10,z);
                for(f = 3 ; f < 3+cifre ; ++f){
                    unsigned int div = m/x;
                    if (div > 0) {
                        p->arr[i].et[f] = '0' + div;
                    } else {
                        p->arr[i].et[f] = '0';
                    }
                    m -= x *div ;
                    --z;
                    x = pow(10,z);
                }*/
            }
            p->arr[i].et[3+cifre] = ' ';
            p->arr[i].dim = cifre;
            p->arr[i].cima = 2 ;
            p->arr[i].grado = 1 ;
            p->arr[i].r = nr;
            p->arr[i].c = nc;
            p->colore = ped;
            if(np == 1){
                if((nc+((3+cifre+1)*2) < t.c) && (nc+((3+cifre+1)*2) > 0)){
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
                if((nc+((3+cifre+1)*2) < t.c) && (nc+((3+cifre+1)*2) > 0)){
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
        p->dim = n;
        return p;
    }else{
        printf("Errore malloc funzione crea_pedine\n");
        return NULL;
    }
}

void print_player(tplayer p){
    unsigned int i,j;
    for(i = 0 ; i < p.dim ; ++i){

        printf("Pedina = ");
        for(j = 0 ; j < 3+p.arr[i].dim+1 ;++j ){
            printf("%c",p.arr[i].et[j]);
        }
        printf("\n");

        print_directions(p.arr[i].canMove, 2, i);
        
        printf("Cima = %d\n",p.arr[i].cima);
        printf("Grado pedina : %d \n",p.arr[i].grado);
        printf("Posizione nel campo x e y : %d , %d\n",p.arr[i].r,p.arr[i].c );
        printf("\n");
    }
}

void update_board(tcampo *t,tplayer p1,tplayer p2){
    unsigned int i;
    for(i = 0 ; i < p1.dim ; ++i){
        if(p1.arr[i].grado > 0){
            unsigned int j;
            for(j = 0 ; j < 3+p1.arr[i].dim+1 ; ++j){
                t->mat[p1.arr[i].r][p1.arr[i].c+j] = p1.arr[i].et[j];
            }
        }
    }

    for(i= 0 ; i < p2.dim ; ++i){
        if(p2.arr[i].grado > 0){
            unsigned int j;
            for(j = 0 ; j < 3+p2.arr[i].dim+1 ; ++j){
                t->mat[p2.arr[i].r][p2.arr[i].c+j] = p2.arr[i].et[j];
            }
        }
    }

}

unsigned int check_spot(tcampo t,unsigned int r,unsigned int c,unsigned int cifre){
    unsigned int i,flag = 0;
    for(i = 0 ; i < cifre ; ++i){
        if((t.mat[r][c+i] != ' ')&&(t.mat[r][c+i] != '#') ){
            flag = 1;
        }
    }
    return flag;
}
unsigned int is_selected(tplayer p1,tplayer p2,unsigned int np,unsigned int npl){
    if(npl == 1 && p1.arr[np].grado > 0){
        return 1;
    }
    if(npl == 2 && p2.arr[np].grado > 0){
        return 1;
    }
    return 0;
}
void remove_pawn(tcampo *t,unsigned int r,unsigned int c,unsigned cifre){
    unsigned int i;
    for(i = 0 ; i < cifre ; ++i){
        t->mat[r][c+i] = '#';
    }
    /*if(((y/cifre)+x)%2 == 0){
            t->mat[r][c+i] = '#';
        }else{
            t->mat[r][c+i] = ' ';
        }*/
}

void pawn_promotion(tplayer *p,unsigned int np,unsigned int numpl,unsigned int meta){
    if(((numpl == 1)&&(p->arr[np].r == 0)) || ((numpl == 2)&&(p->arr[np].r == meta))){
        p->arr[np].isPromoted = 1;
        p->arr[np].et[p->arr[np].dim+3] = '^';
        p->arr[np].canMove = (unsigned int*) realloc(p->arr[np].canMove ,4*sizeof(unsigned int));
    }
}
unsigned int check_player(tplayer p1,tplayer p2,unsigned int x,unsigned int y){
    int i,flag = 0;
    for(i = 0 ; i < p1.dim ; ++i){
        if((p1.arr[i].r == x)&&(p1.arr[i].c == y)){
            flag = 1;
        }
    }
    if(flag){
        return 1;
    }else{
        for(i = 0 ; i < p2.dim ; ++i){
            if((p2.arr[i].r == x)&&(p2.arr[i].c == y)){
                flag = 2;
            }
        }
    }
    return flag;
}
unsigned int char_converter(tcampo t,unsigned int r,unsigned int c,unsigned int dim,unsigned int cifre){
    unsigned int i,num = 0,z = 0;
    for(i = dim ; i >cifre-1 ; --i){
        num += ((t.mat[r][c+i]-'0')*pow(10,z));
        z++;
    }
    return num;
}
unsigned int is_in(int r,int c,tcampo t){
    if( (r < t.r)&&(c<t.c)){
        return 1;
    }else {
        return 0;
    }
}
unsigned int check_directions(unsigned int *arr,unsigned int dim,char *str){
    unsigned int i,flag = 0,j;
    for(i = 0 ; i < dim ; ++i){
        if(arr[i]){
            flag = 1;
        }
    }
    if(!flag){
        return 1;
    }
    if(!strcmp(str, "sx")){
        j = 0;
    }
    if(!strcmp(str, "dx")){
        j = 1;
    }
    if(!strcmp(str, "bassosx")){
        j = 2;
    }
    if(!strcmp(str, "bassodx")){
        j = 3;
    }
    if(arr[j] == 1 && j < dim){
        return 1;
    }else{
        return 0;
    }


}
unsigned int *must_eat(tplayer p1,tplayer p2,tcampo t,unsigned int np,unsigned int npl){
    unsigned int *arr,dim;
    if(npl == 1){
        if(p1.arr[np].isPromoted ){
            dim = 4;
        }else{
            dim = 2;
        }
    }
    if(npl == 2){
        if(p2.arr[np].isPromoted){
            dim = 4;
        }else{
            dim = 2;
        }
    }
    arr = (unsigned int*)calloc(dim,sizeof(unsigned int));
    if(arr){

        if( ((npl == 1)&&(can_eat(&p1,np,"sx",&t,&p2,1) >= 0)) || ((npl == 2)&&(can_eat(&p2,np,"bassosx",&t,&p1,2)>=0))  ){
            arr[0] = 1;
        }
        if( ((npl == 1)&&(can_eat(&p1,np,"dx",&t,&p2,1) >= 0)) || ((npl == 2)&&(can_eat(&p2,np,"bassodx",&t,&p1,2)>=0)) ){
            arr[1] = 1;
        }
        if( (((npl == 1)&&(can_eat(&p1,np,"bassosx",&t,&p2,1) >= 0)) || ((npl == 2)&&(can_eat(&p2,np,"sx",&t,&p1,2)>=0))) && (dim == 4) ){
            arr[2] = 1;
        }
        if( (((npl == 1)&&(can_eat(&p1,np,"bassodx",&t,&p2,1) >= 0)) || ((npl == 2)&&(can_eat(&p2,np,"dx",&t,&p1,2)>=0))) && (dim == 4) ){
            arr[3] = 1;
        }

        return arr;
    }else{
        printf("Errore nella obl_eat\n");
        return NULL;
    }


}
int can_eat(tplayer *p1,unsigned int np,char *str,tcampo *t,tplayer *p2,unsigned int pl) {

    if ( (!strcmp(str, "sx")) ) {
        if ((is_in(p1->arr[np].r - 2, p1->arr[np].c - ((p1->arr[np].dim + 3+1) * 2), *t)) &&
            ((is_in(p1->arr[np].r - 1, p1->arr[np].c - (p1->arr[np].dim + 3+1), *t)))) {
            unsigned x, y, z;
            x = p1->arr[np].r - 1;
            y = p1->arr[np].c - (p1->arr[np].dim + 3+1);
            z = check_player(*p1, *p2, x, y);
            if ((z == 2) &&
                (check_spot(*t, p1->arr[np].r - 1, p1->arr[np].c - (p1->arr[np].dim + 3+1), (p1->arr[np].dim + 3+1))) &&
                (!check_spot(*t, p1->arr[np].r - 2, p1->arr[np].c - ((p1->arr[np].dim + 3+1) * 2),
                            (p1->arr[np].dim + 3+1)))) {
                int num = -1;
                num =  char_converter(*t, p1->arr[np].r - 1, p1->arr[np].c - (p1->arr[np].dim + 3+1), 2 + p1->arr[np].dim, 3);
                if ((num > -1) && (num < p1->dim)) {
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
    if ((!strcmp(str, "dx")) ) {
        if ((is_in(p1->arr[np].r - 2, p1->arr[np].c + ((p1->arr[np].dim + 3) * 3 ), *t)) &&
            ((is_in(p1->arr[np].r - 1, p1->arr[np].c + (p1->arr[np].dim + 3+1), *t)))) {
            unsigned x, y, z;
            x = p1->arr[np].r - 1;
            y = p1->arr[np].c + (p1->arr[np].dim + 3+1);
            z = check_player(*p1, *p2, x, y);
            if ((z == 2) &&
                (check_spot(*t, p1->arr[np].r - 1, p1->arr[np].c + (p1->arr[np].dim + 3+1), p1->arr[np].dim + 3+1)) &&
                (!check_spot(*t, p1->arr[np].r - 2, p1->arr[np].c + ((p1->arr[np].dim + 3+1) * 2),
                            (p1->arr[np].dim + 3+1)))) {
                int num = -1;
                num =  char_converter(*t, p1->arr[np].r - 1, p1->arr[np].c + (p1->arr[np].dim + 3+1), 2 + p1->arr[np].dim, 3);
                if ((num > -1) && (num < p1->dim)) {
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

    if (((pl == 2) || (p1->arr[np].isPromoted))) {
        if ((!strcmp(str, "bassosx")) ) {
            if ((is_in(p1->arr[np].r + 2, p1->arr[np].c - ((p1->arr[np].dim + 3 + 1) * 2), *t)) &&
                ((is_in(p1->arr[np].r + 1, p1->arr[np].c - (p1->arr[np].dim + 3 + 1), *t)))) {
                unsigned x, y, z;
                x = p1->arr[np].r + 1;
                y = p1->arr[np].c - (p1->arr[np].dim + 3 + 1);
                z = check_player(*p1, *p2, x, y);
                if ((z == 2) && (check_spot(*t, p1->arr[np].r + 1, p1->arr[np].c - (p1->arr[np].dim + 3 + 1),
                                           (p1->arr[np].dim + 3 + 1))) &&
                    (!check_spot(*t, p1->arr[np].r + 2, p1->arr[np].c - ((p1->arr[np].dim + 3 + 1) * 2),
                                (p1->arr[np].dim + 3 + 1)))) {
                    int num = -1;
                    num =  char_converter(*t, p1->arr[np].r + 1, p1->arr[np].c - (p1->arr[np].dim + 3 + 1), 2 + p1->arr[np].dim,3);
                    if ((num > -1) && (num < p1->dim)) {
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
            if ((is_in(p1->arr[np].r + 2, p1->arr[np].c + ((p1->arr[np].dim + 3) * 3), *t)) &&
                ((is_in(p1->arr[np].r + 1, p1->arr[np].c + (p1->arr[np].dim + 3 + 1), *t)))) {
                unsigned x, y, z;
                x = p1->arr[np].r + 1;
                y = p1->arr[np].c + (p1->arr[np].dim + 3 + 1);
                z = check_player(*p1, *p2, x, y);
                if ((z == 2) && (check_spot(*t, p1->arr[np].r + 1, p1->arr[np].c + (p1->arr[np].dim + 3 + 1),
                                           (p1->arr[np].dim + 3 + 1)) &&
                                 (!check_spot(*t, p1->arr[np].r + 2, p1->arr[np].c + ((p1->arr[np].dim + 3 + 1) * 2),
                                             (p1->arr[np].dim + 3 + 1))))) {
                    int num = -1;
                    num =  char_converter(*t, p1->arr[np].r + 1, p1->arr[np].c + (p1->arr[np].dim + 3 + 1), 2 + p1->arr[np].dim,3);
                    if ((num > -1) && (num < p1->dim)) {
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
unsigned int move_noeat(tplayer *p1,unsigned int np,char *str,tcampo *t,tplayer *p2,unsigned int pl){
    if(!strcmp(str,"sx")){
        if((is_in(p1->arr[np].r-1,p1->arr[np].c-(p1->arr[np].dim+3+1),*t))&&(!check_spot(*t,p1->arr[np].r-1,p1->arr[np].c-(p1->arr[np].dim+3+1),(p1->arr[np].dim+3+1)))){
            remove_pawn(t,p1->arr[np].r,p1->arr[np].c,(p1->arr[np].dim+3+1));
            --p1->arr[np].r;
            p1->arr[np].c -= (p1->arr[np].dim+3+1);
            pawn_promotion(p1,np,pl,t->r-1);
            return 1;
        }else{
            return 0;
        }
    }else{
        if (!strcmp(str, "dx")) {
            if((is_in(p1->arr[np].r-1, p1->arr[np].c + (p1->arr[np].dim + 3+1), *t))&&(!check_spot(*t, p1->arr[np].r - 1, p1->arr[np].c + (p1->arr[np].dim + 3+1),p1->arr[np].dim+3+1))){
                remove_pawn(t,p1->arr[np].r,p1->arr[np].c,(p1->arr[np].dim+3+1));
                --p1->arr[np].r;
                p1->arr[np].c += (p1->arr[np].dim+3+1);
                pawn_promotion(p1,np,pl,t->r-1);
                return 1;
            }else{
                return 0;
            }
        }
        if (!strcmp(str, "bassosx") && ((pl == 2) || (p1->arr[np].isPromoted))) {
            if((is_in(p1->arr[np].r+1,p1->arr[np].c-(p1->arr[np].dim+3+1),*t))&&(!check_spot(*t,p1->arr[np].r+1,p1->arr[np].c-(p1->arr[np].dim+3+1),(p1->arr[np].dim+3+1)))){
                remove_pawn(t,p1->arr[np].r,p1->arr[np].c,(p1->arr[np].dim+3+1));
                p1->arr[np].r++;
                p1->arr[np].c -= (p1->arr[np].dim+3+1);
                if(pl == 2){
                    pawn_promotion(p1,np,pl,t->r-1);
                }
                return 1;
            }else{
                return 0;
            }
        }
        if (!strcmp(str, "bassodx") && ((pl == 2) || (p1->arr[np].isPromoted))) {
            if((is_in(p1->arr[np].r+1, p1->arr[np].c + (p1->arr[np].dim + 3+1), *t))&&(!check_spot(*t, p1->arr[np].r+1, p1->arr[np].c + (p1->arr[np].dim + 3+1),p1->arr[np].dim + 3+1))){
                remove_pawn(t,p1->arr[np].r,p1->arr[np].c,(p1->arr[np].dim+3+1));
                p1->arr[np].r++;
                p1->arr[np].c += (p1->arr[np].dim+3+1);
                if(pl == 2){
                    pawn_promotion(p1,np,pl,t->r-1);
                }
                return 1;
            }else{
                return 0;
            }
        }

    }

    return 0;

}
unsigned int eat(tplayer *p1,tplayer *p2,char *str,unsigned int np,tcampo t,unsigned int num,unsigned int npl){

    char temp[3];
    unsigned int f;
    temp[0] = p1->arr[np].et[1];
    temp[1] = p1->arr[np].et[2];
    temp[2] = p2->arr[num].et[p2->arr[num].cima];

    if(p2->arr[num].grado == 1){
        --p2->arr[num].grado;
    }else{
        if(p2->arr[num].et[p2->arr[num].cima] == p2->arr[num].et[p2->arr[num].cima+1]){
            p2->arr[num].et[p2->arr[num].cima]= ' ';
            ++p2->arr[num].cima;
            --p2->arr[num].grado;
        }else {
            if (is_empty(*p1) == -1) {
                /*controllo_pedina(p1, p2,num);*/
                remove_pawn(&t,p2->arr[num].r,p2->arr[num].c,p2->arr[num].dim+3+1);
                p2->arr[num].grado = 0;
            } else {
                unsigned int pos, i,index;
                pos = is_empty(*p1);
                p2->arr[num].et[p2->arr[num].cima]= ' ';
                ++p2->arr[num].cima;
                --p2->arr[num].grado;
                for (i = 0; i < 3; ++i) {
                    p1->arr[pos].et[i] = p2->arr[num].et[i];
                }
                p2->arr[num].isPromoted = 0;
                p2->arr[num].et[3+p2->arr[num].dim] = ' ';
                p1->arr[pos].isPromoted = 0;
                p1->arr[pos].et[3+p2->arr[num].dim] = ' ';

                p1->arr[pos].grado = p2->arr[num].grado;
                p2->arr[num].grado = 0;
                p1->arr[pos].r = p2->arr[num].r;
                p1->arr[pos].c = p2->arr[num].c;
                index = p1->arr[pos].dim;
                for(i = 3 ; i < p1->arr[pos].dim+3 ; ++i){
                    int_converter(pos,index);
                    --index;
                }
            }
        }
    }
    if(p1->arr[np].grado  < 3){
        for(f = 0 ; f < 3 ; ++f ){
            p1->arr[np].et[f] = temp[f];
        }
        ++p1->arr[np].grado;
        --p1->arr[np].cima;
    }
    if(!strcmp(str,"sx")){
        p1->arr[np].r -= 2;
        p1->arr[np].c -= (p1->arr[np].dim+3+1)*2;
    }else{
        if(!strcmp(str,"dx")){
            p1->arr[np].r -= 2;
            p1->arr[np].c += (p1->arr[np].dim+3+1)*2;
        }
        if(!strcmp(str,"bassosx")){
            p1->arr[np].r += 2;
            p1->arr[np].c -= (p1->arr[np].dim+3+1)*2;
        }
        if(!strcmp(str,"bassodx")){
            p1->arr[np].r += 2;
            p1->arr[np].c += (p1->arr[np].dim+3+1)*2;
        }

    }
    /*togli_pedina(&t,p2->arr[num].r,p2->arr[num].c,p2->arr[num].dim+3+1);*/
    if(p2->arr[num].grado < 1){
        remove_pawn(&t,p2->arr[num].r,p2->arr[num].c,p2->arr[num].dim+3+1);
    }
    if(!strcmp(str,"sx")){
        remove_pawn(&t,p1->arr[np].r+2,p1->arr[np].c+((p1->arr[np].dim+3+1)*2),p1->arr[np].dim+3+1);
    }else{
        if(!strcmp(str,"dx")){
            remove_pawn(&t,p1->arr[np].r+2,p1->arr[np].c-((p1->arr[np].dim+3+1)*2),(p1->arr[np].dim+3+1));
        }
        if(!strcmp(str,"bassosx")){
            remove_pawn(&t,p1->arr[np].r-2,p1->arr[np].c+((p1->arr[np].dim+3+1)*2),p1->arr[np].dim+3+1);
        }
        if(!strcmp(str,"bassodx")){
            remove_pawn(&t,p1->arr[np].r-2,p1->arr[np].c-((p1->arr[np].dim+3+1)*2),(p1->arr[np].dim+3+1));
        }

    }
    if(npl == 1 ){
        pawn_promotion(p1,np,1,t.r-1);
    }else{
        pawn_promotion(p1,np,2,t.r-1);
    }
    return 1;

}
unsigned int move_p1 (tplayer *p1,unsigned int np,char *str,tcampo *t,tplayer *p2,unsigned int pl){
    int num;
    num = can_eat(p1,np,str,t,p2,pl);
    if(num > -1){
        eat(p1,p2,str,np,*t,num,pl);
        return 1;
    }else{
        if(num == -1){
            printf("Errore nella char_convert\n");
            return 0;
        }else{
            if(num == -4){
                printf("Errore nella can_eat\n");
            }else{
                if(move_noeat(p1,np,str,t,p2,pl)){
                    return 1;
                }else{
                    return 0;
                }

            }
        }

    }
    return 0;
}
unsigned int move_p2(tplayer *p2,unsigned int np,char *str,tcampo *t,tplayer *p1){
    if(!strcmp(str,"sx")) {
        if(move_p1(p2,np,"bassosx",t,p1,2)){
            return 1;
        }else{
            return 0;
        }

    }else{
        if(!strcmp(str,"dx")){
            if(move_p1(p2,np,"bassodx",t,p1,2)){
                return 1;
            }else{
                return 0;
            }
        }
        if(!strcmp(str,"bassosx")&&(p2->arr[np].isPromoted)) {
            if(move_p1(p2,np,"sx",t,p1,2)){
                return 1;
            }else{
                return 0;
            }
        }
        if(!strcmp(str,"bassodx")&&(p2->arr[np].isPromoted)) {
            if(move_p1(p2,np,"dx",t,p1,2)){
                return 1;
            }else{
                return 0;
            }
        }

    }

    return 0;
}
unsigned int all_blocked(tplayer p1,tplayer p2,tcampo t,unsigned int npl){
    unsigned int i,flag;
    if(npl == 1){
        flag = 1;
    }else{
        flag = 2;
    }
    for(i = 0 ; i < p1.dim ; ++i){
        if(p1.arr[i].grado > 0 && npl == 1 && check_canMove(&p1, i)){
            flag = 0;
        }
        if(p2.arr[i].grado > 0 && npl == 2 && check_canMove(&p2, i)){
            flag = 0;
        }
    }
    return flag;
}
unsigned int is_victory(tplayer p1,tplayer p2,tcampo t){
    int i,v1 = 0,v2 = 0,flag = -1 ;

    for(i = 0 ; i < p1.dim ; ++i){
        p1.arr[i].grado == 0 ? ++v1 : v1;
    }
    if(v1 == p1.dim){
        v1 = 1;
    }else{
        v1 = 0 ;
    }

    for(i = 0 ; i < p2.dim ; ++i){
        p2.arr[i].grado == 0 ? ++v2 : v2;
    }
    if(v2 == p2.dim){
        v2 = 2;
    }else{
        v2 = 0 ;
    }
    if(v1 == v2){
        flag = 0;
    }else{
        v1 > v2 ? flag = 1 : flag;
        v2 > v1 ? flag = 2 : flag;
    }

    return flag;
}
unsigned int round_choice(){
    char str[2];

    printf("Inizia il turno come da predefinito (quindi primo giocatore)? ");
    scanf("%s",str);
    if((!strcmp(str,"si"))||(!strcmp(str,"Si"))||(!strcmp(str,"SI"))){
        return 1;
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
            return npl;
        }
        if((!strcmp(str,"si"))||(!strcmp(str,"Si"))||(!strcmp(str,"SI"))){
            int x = 0 ;
            srand(time(NULL));
            while(x == 0){
                x = rand()%10;
            }
            if(x%2 == 0){
                x = 1;
            }else{
                x = 2;
            }
            return x;
        }
    }
    return 1;
}
unsigned int round_player(tplayer *p1,tplayer *p2,tcampo *t,unsigned int npl){
    char str[10];
    unsigned int y = 0,np;

    update_board(t,*p1,*p2);
    if(npl == 1){
        printPlayerTurn(p1->colore);
        printf("Turno player 1 : \n");
        resetColor();
        print_board(*t,(p1->arr[0].dim+3)+1,1);
    }else{
        printPlayerTurn(p2->colore);
        printf("Turno player 2 : \n");
        resetColor();
        print_board(*t,(p2->arr[0].dim+3)+1,2);
    }


 /* printf("Vuoi uscire dal gioco ? ");
    scanf("%s",str);
    if((!strcmp(str,"si"))||(!strcmp(str,"Si"))||(!strcmp(str,"SI"))){
        return 3;
    } */

    printf("Numero di pedina da selezionare : ");
    scanf("%u",&np);
    
    while(!check_while(*p1, *p2, npl, np)){
        unsigned int flag = 1;
        if (npl == 1){
            flag = check_canMove(p1, np);
        }else{
            flag = check_canMove(p2, np);              
        }    
        if(!flag){
            printf("La pedina %u non puo' muoversi!\n",np);
        }else{
            printf("Non puoi selezionare la pedina n. %u\n",np);
        }
        printf("Numero di pedina da selezionare : ");
        scanf("%u",&np);
    }
    printf("Vuoi selezionare questa pedina %d ? ",np);
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
        scanf("%u",&np);
        while(!check_while(*p1, *p2, npl, np)){
            unsigned int flag = 1;
            if (npl == 1){
                flag = check_canMove(p1, np);
            }else{
                flag = check_canMove(p2, np);              
            }    
            if(!flag){
                printf("La pedina %u non puo' muoversi!\n",np);
            }else{
                printf("Non puoi selezionare la pedina n. %u\n",np);
            }
            printf("Numero di pedina da selezionare : ");
            scanf("%u",&np);
        }
        printf("Vuoi selezionare questa pedina %d ? ",np);
        scanf("%s",str);
    }

    while(y==0){
        unsigned int *arr,dim;
        if(npl == 1){
            if(p1->arr[np].isPromoted ){
                dim = 4;
            }else{
                dim = 2;
            }
        }
        if(npl == 2){
            if(p2->arr[np].isPromoted){
                dim = 4;
            }else{
                dim = 2;
            }
        }
        arr = must_eat(*p1,*p2,*t,np,npl);
        print_directions(arr,dim,np);
        printf("Verso che direzione vuoi spostare la pedina ? ");
        scanf("%s",str);
        while(!check_directions(arr,dim,str)){
            printf("Verso che direzione vuoi spostare la pedina ? ");
            scanf("%s",str);
        }
        if(npl == 1){
            y = move_p1(p1,np,str,t,p2,npl);
        }else{
            y = move_p2(p2,np,str,t,p1);
        }
        if(y == 0){
            char temp[2];
            printf("La pedina numero %u non si puo' spostare verso %s\n",np,str);

            printf("Numero di pedina da selezionare : ");
            scanf("%u",&np);
            while(!check_while(*p1, *p2, npl, np)){
                unsigned int flag = 1;
                if (npl == 1){
                    flag = check_canMove(p1, np);
                }else{
                    flag = check_canMove(p2, np);              
                }    
                if(!flag){
                    printf("La pedina %u non puo' muoversi!\n",np);
                }else{
                    printf("Non puoi selezionare la pedina n. %u\n",np);
                }
                printf("Numero di pedina da selezionare : ");
                scanf("%u",&np);
            }
            printf("Vuoi selezionare questa pedina %d ? ",np);
            scanf("%s",temp);

            while( (!strcmp(str,"no"))||(!strcmp(str,"NO"))||(!strcmp(str,"No")) ){
                printf("Numero di pedina da selezionare : ");
                scanf("%u",&np);
                while(!check_while(*p1, *p2, npl, np)){
                    unsigned int flag = 1;
                    if (npl == 1){
                        flag = check_canMove(p1, np);
                    }else{
                        flag = check_canMove(p2, np);              
                    }    
                    if(!flag){
                        printf("La pedina %u non puo' muoversi!\n",np);
                    }else{
                        printf("Non puoi selezionare la pedina n. %u\n",np);
                    }
                    printf("Numero di pedina da selezionare : ");
                    scanf("%u",&np);
                }
                printf("Vuoi selezionare questa pedina %d ? ",np);
                scanf("%s",str);
            }
        }
        free(arr);
    }
    update_board(t,*p1,*p2);
    if(npl == 1){
        print_board(*t,(p1->arr[0].dim+3)+1,1);
    }else{
        print_board(*t,(p1->arr[0].dim+3)+1,2);
    }


    return 0;
}

int is_empty(tplayer p){
    int pos = -1;
    unsigned int i;
    for(i = 0 ; i < p.dim ; ++i){
        if((p.arr[i].grado == 0)&&(pos == -1)){
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
tcampo *copy_board(tcampo t ,tcampo *new){
    unsigned int flag = 0;
    if(new == NULL){
        flag = 1;
        new = (tcampo*)malloc(sizeof(tcampo));
    }
    if(new != NULL){
        unsigned int j,k;
        new->r = t.r;
        new->c = t.c;
        if(flag == 1){
            unsigned int i;
            new->mat = (char**)calloc((new->r),sizeof(char*));
            for(i = 0 ; i < new->r ; ++i){
                new->mat[i] = (char*)calloc((new->c),sizeof(char));
            }
        }
        for(k = 0 ; k < new->r ; ++k){
            for(j = 0 ; j < new->c ; ++j){
                new->mat[k][j] = t.mat[k][j];
            }
        }
        return new;
        if(!(new->mat)){
            printf("Errore nella campo_copy(malloc della matrice di char)");
            return NULL;
        }
    }else{
        printf("Errore nella campo_copy (malloc di new)");
        return NULL;
    }

}
tplayer *player_copy(tplayer p,tplayer *n,unsigned int cifre){
    unsigned int flag = 0;
    if(n == NULL){
        n = (tplayer*)malloc(sizeof(tplayer));
        flag = 1;
    }
    if(n != NULL){
        unsigned int i,j;
        n->dim = p.dim;
        n->colore = p.colore;
        if(flag == 1){
            unsigned int m,l;
            n->arr = (tpedina*)calloc((n->dim),sizeof(tpedina));
            for(l = 0 ; l < p.dim ; ++l){
                n->arr[l].et = (char*)calloc((cifre),sizeof(char));
            }
            for(l = 0 ; l < p.dim ; ++l){
                for(m = 0 ; m < cifre ; ++m){
                    n->arr[l].et[m] = p.arr[l].et[m];
                }
            }
        }
        for(i = 0 ; i < n->dim ; ++i){
            for(j = 0 ; j < cifre ; ++j){
                n->arr[i].et[j] = p.arr[i].et[j];
            }
            n->arr[i].dim = p.arr[i].dim;
            n->arr[i].cima = p.arr[i].cima;
            n->arr[i].grado = p.arr[i].grado;
            n->arr[i].r = p.arr[i].r;
            n->arr[i].c = p.arr[i].c;
            n->arr[i].isPromoted = p.arr[i].isPromoted;
        }
        return n;
    }else{
        printf("Errore malloc player_copy");
        return NULL;
    }

}
unsigned int is_notstuck(tplayer *p1,tplayer *p2,tcampo t,unsigned int nped,unsigned int npl){
    tcampo *new = NULL;
    tplayer *n1 = NULL,*n2 = NULL;
    unsigned int cifre = 0;

    if(npl == 1){
        cifre = p1->arr[0].dim+3+1;
    }else{
        cifre = p2->arr[0].dim+3+1;
    }


    new = copy_board(t,new);
    n1 = player_copy(*p1,n1,p1->arr[0].dim+3+1);
    n2 = player_copy(*p2,n2,p2->arr[0].dim+3+1);

    if(new != NULL && n1 != NULL && n2 != NULL){
        unsigned int flag = 0;
        update_board(new,*n1,*n2);
        if( ((npl == 1)&&(move_p1(n1,nped,"sx",new,n2,1))) || ((npl == 2)&&(move_p2(n2,nped,"sx",new,n1))) ){
            if (npl == 1)
            {
                p1->arr[nped].canMove[0] = 1;
            }else
            {
                p2->arr[nped].canMove[0] = 1;
            }
            flag = 1;
            copy_board(t,new);
            player_copy(*p1,n1,cifre);
            player_copy(*p2,n2,cifre);
        }else
        {
            p1->arr[nped].canMove[0] = 0;
            p2->arr[nped].canMove[0] = 0;
        }
        
        if ( ((npl == 1)&&(move_p1(n1,nped,"dx",new,n2,1))) || ((npl == 2)&&(move_p2(n2,nped,"dx",new,n1))) ){
            if (npl == 1)
            {
                p1->arr[nped].canMove[1] = 1;
            }else
            {
                p2->arr[nped].canMove[1] = 1;
            }       
            flag = 1;
            copy_board(t,new);
            player_copy(*p1,n1,cifre);
            player_copy(*p2,n2,cifre);
        }else{
            p1->arr[nped].canMove[1] = 0;
            p2->arr[nped].canMove[1] = 0;
        }
        if ((p1->arr[nped].isPromoted && npl==1) || (p2->arr[nped].isPromoted && npl==2)){
            if( ((npl == 1)&&(move_p1(n1,nped,"bassosx",new,n2,1))) || ((npl == 2)&&(move_p2(n2,nped,"bassosx",new,n1))) ){
                if (npl == 1)
                {
                    p1->arr[nped].canMove[2] = 1;
                }else
                {
                    p2->arr[nped].canMove[2] = 1;
                }  
                flag = 1;
                copy_board(t,new);
                player_copy(*p1,n1,cifre);
                player_copy(*p2,n2,cifre);
            }else{
                p1->arr[nped].canMove[2] = 0;
                p2->arr[nped].canMove[2] = 0;
            }
            if( ((npl == 1)&&(move_p1(n1,nped,"bassodx",new,n2,1))) || ((npl == 2)&&(move_p2(n2,nped,"bassodx",new,n1))) ){
                if (npl == 1)
                {
                    p1->arr[nped].canMove[3] = 1;
                }else
                {
                    p2->arr[nped].canMove[3] = 1;
                }       
                flag = 1;
                copy_board(t,new);
                player_copy(*p1,n1,cifre);
                player_copy(*p2,n2,cifre);
            }else{
                p1->arr[nped].canMove[3] = 0;
                p2->arr[nped].canMove[3] = 0;
            }
        }       
        destroy_board(new);
        destroy_player(n1);
        destroy_player(n2);
        return flag;

    }else{
        printf("Errore nella ped_noblock\n");
        if(new != NULL){
            destroy_board(new);
        }
        if(n1 != NULL){
            destroy_player(n1);
        }
        if(n2 != NULL){
            destroy_player(n2);
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

    /*
    for(f = 3 ; f < 3+cifre ; ++f){
        unsigned int div = m/x;
        if (div > 0) {
            p->arr[i].et[f] = '0' + div;
        } else {
            p->arr[i].et[f] = '0';
        }
        m -= x *div ;
        --z;
        x = pow(10,z);
    } */


}
unsigned int add_pawn(tplayer *p1,tplayer *p2,unsigned int np){

    p1->arr = (tpedina*)realloc(p1->arr,(p1->dim+1)*sizeof(tpedina));
    p1->arr[p1->dim].et = (char*)calloc((p2->arr[np].dim+3+1),sizeof(char));

    if((p1->arr) &&(p1->arr[p1->dim].et)) {
        unsigned int i,index;

        p2->arr[np].et[p2->arr[np].cima]= ' ';
        ++p2->arr[np].cima;
        --p2->arr[np].grado;
        p1->arr[p1->dim].dim = p2->arr[np].dim;
        p1->arr[p1->dim].cima = p2->arr[np].cima;
        p1->arr[p1->dim].grado = p2->arr[np].grado;
        p1->arr[p1->dim].c = p2->arr[np].c;
        p1->arr[p1->dim].r = p2->arr[np].r;
        p2->arr[np].isPromoted = 0;
        p2->arr[np].et[p2->arr[np].dim+3+1] = ' ';

        /* in caso if per cifre e riadattare cifre*/
        for(i = 0 ; i < 3 ; ++i){
            p1->arr[p1->dim].et[i] = p2->arr[np].et[i];
        }
        index = p2->arr[np].dim;
        for(i = 3 ; i < p2->arr[np].dim+3 ; ++i){
            p1->arr[p1->dim].et[i] = p2->arr[np].et[i];
            --index;
        }

        ++p1->dim;
        return 1;
    }else{
        printf("Errore nella realloc\n");
        return 0;
    }
}

int player_vs_player(unsigned int x ){
    tcampo *t = NULL;
    tplayer *p1 = NULL,*p2 = NULL;
    unsigned int exit = 0,turno,round = 0;
    unsigned int cifre,conta = 2,numped = 11;

    if(x == 0){
        t = create_board(7,7,3+conta+1);
        initialize_board(t,3+conta+1);
        p1 = create_pawns(11,'B',1,conta,*t);/* creare n pedine di carattere c */
        p2 = create_pawns(11,'N',2,conta,*t);/* creare n pedine di carattere c */
    }else{
        unsigned int w,h,max_ped = 0;
        conta = 0;
        printf("Altezza della scacchiera : ");
        scanf("%u",&h);
        printf("Larghezza della scacchiera : ");
        scanf("%u",&w);
        while(w < 3 || h < 3){
            printf("Larghezza e altezza della scacchiera non soddisfa requisiti minimi(h >= 3,w >= 3)\n");
            printf("Reinserire altezza e larghezza\n ");
            printf("Altezza della scacchiera : ");
            scanf("%u",&h);
            printf("Larghezza della scacchiera : ");
            scanf("%u",&w);
        }
        max_ped = max_pawns(h,w);
        printf("Numero di pedine massimo per giocatore : %u\n",max_ped);
        printf("Numero pedine ?(ovviamente minore o guale al massimo numero) : ");
        scanf("%u",&cifre);
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
            p1 = create_pawns(numped,'B',1,conta,*t);/* creare n pedine di carattere c */
            p2 = create_pawns(numped,'N',2,conta,*t);/* creare n pedine di carattere c */

        }else{
            printf("Non ha senso giocare con %u pedine !\n",cifre);
            return 0;
        }
    }
    turno = round_choice();
    printf("Il player che inizia e' %d\n",turno);
    while((exit == 0)&&(!is_victory(*p1,*p2,*t))){
        if(all_blocked(*p1,*p2,*t,turno) == 1 && turno == 1){
            exit = 2;
        }
        if(all_blocked(*p1,*p2,*t,turno) == 2 && turno == 2){
            exit = 1;
        }
        if(!exit ){
            printf("Round numero : %u\n",round);
            if(turno == 1){
                exit = round_player(p1,p2,t,turno);
                turno = 2;
            }else{
                exit = round_player(p1,p2,t,turno);
                turno = 1;
            }
            ++round;
        }
    }

    if(exit == 3){
        printf("Hai abbandonato la partita\n");
    }else{
        if(!exit){
            exit = is_victory(*p1,*p2,*t);
        }
        printf("Round totali della partita : %u\n",round);
        printf("Il vincitore e' il player %d!\n",exit);
    }

    destroy_board(t);
    destroy_player(p1);
    destroy_player(p2);

    return 1;
}

unsigned int round_ia(tplayer *p1,tplayer *ia,tcampo *t,unsigned int npl){
    int np = -1, dim = 2;
    int newMove;
    char* move;
    srand(time(NULL));
    np = rand()%(ia->dim);

    while (!check_canMove(ia, np)){
        np = rand()%(ia->dim);      
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
        move = "bassosx";
    }else if (newMove == 3){
        move = "bassodx";
    }

    move_p2(ia,np,move,t,p1);

/*  if( (move_p2(ia,np,"sx",t,p1)) || (move_p2(ia,np,"dx",t,p1))){
        return 0;
    }else{
        return 1;
    }*/
    printf("Num ped : %u\n",np);

    return 0;

}
void player_vs_ia(){
    tcampo *t = NULL;
    tplayer *p1 = NULL,*ia = NULL;
    unsigned int exit = 0,turno,round = 0;
    unsigned int conta = 2;


    t = create_board(7,7,conta+3+1);
    initialize_board(t,conta+3+1);
    p1 = create_pawns(11,'B',1,conta,*t);/* creare n pedine di carattere c */
    ia = create_pawns(11,'N',2,conta,*t);/* creare n pedine di carattere c */


    turno = round_choice();
    printf("Il player che inizia e' %d\n",turno);
    while((exit == 0)&&(!is_victory(*p1,*ia,*t))) {
        set_moves_pawn(p1, ia, *t, turno);
        
        if (all_blocked(*p1, *ia, *t, turno) == 1 && turno == 1) {
            exit = 2;
        }
        if (all_blocked(*p1, *ia, *t, turno) == 2 && turno == 2) {
            exit = 1;
        }
        if (!exit) {
            printf("Round numero : %u\n", round);
            if (turno == 1) {
                exit = round_player(p1, ia, t, turno);
                turno = 2;
            } else {
                exit = round_ia(p1, ia, t, turno);
                turno = 1;
            }
            ++round;
        }
    }
    destroy_board(t);
    destroy_player(p1);
    destroy_player(ia);
}
void destroy_player (tplayer *p){

    unsigned int i;
    for(i = 0 ; i < p->dim ;++i){
        if (p->arr[i].canMove){
            free(p->arr[i].canMove);
        }
        
        free(p->arr[i].et);
    }
    free(p->arr);
    free(p);
}
void destroy_board(tcampo *t) {
    unsigned int i;

    for (i = 0; i < t->r ;++i) {
        free(t->mat[i]);
    }
    free(t->mat);
    free(t);
}

void set_moves_pawn(tplayer *pl1, tplayer *pl2, tcampo t, int nPl){
    int i;
    for(i = 0; i < pl1->dim; i++){
        is_notstuck(pl1, pl2, t, i, nPl);
    }
}

/**
 * @brief Ritorna 0 se tutti gli elementi di canMove sono 0. 
 * 
 * @param p 
 * @param nPed 
 * @return unsigned int 
 */
unsigned int check_canMove(tplayer *p, int nPed){
    int i = 0, dim = 2, flag = 0;
    if (p->arr[nPed].isPromoted){
        dim = 4;
    }
    while (i < dim && flag == 0){
        if (p->arr[nPed].canMove[i] == 1){
            flag = 1;
        }
        
        /* p->arr[nPed].canMove[i] = 1 ? flag = 1 : flag; */
        i++;
    }
    return flag;
}

unsigned int check_while(tplayer pl1, tplayer pl2, unsigned int nPlayer, unsigned int nPawn){
    if ((!((nPawn >= 0)&&(((nPlayer == 1)&&(nPawn < pl1.dim)) && ((nPlayer == 2)&&(nPawn < pl2.dim)))))|| (!is_selected(pl1, pl2, nPawn, nPlayer))){
        if (nPlayer == 1){
            return check_canMove(&pl1, nPawn);
        }else{
            return check_canMove(&pl2, nPawn);              
        }     
    }else{
        return 1;
    }
}

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