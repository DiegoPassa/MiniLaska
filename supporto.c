#include<stdio.h>
#include<stdlib.h>
#include"supporto.h"
#include<string.h>
#include<time.h>
#include <math.h>
#include "lib/colori.h"

tcampo *crea_campo(unsigned int r,unsigned int col,unsigned int cifre){
    tcampo *t;

    t = (tcampo*)malloc(sizeof(tcampo));

    if(t != NULL){
        unsigned int i;
        t->r = r;
        t->c = col*cifre;
        t->mat = (char**)malloc(sizeof(char*)*(t->r));
        for(i = 0 ; i < t->r ; ++i){
            t->mat[i] = (char*)malloc(sizeof(char)*(t->c));

        }

        return t;

    }else{
        printf("Errore nella malloc nella funzione crea_campo\n");
        return NULL;
    }
}
void inizializza_campo(tcampo *t,unsigned int cifre){
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
void stampa_campo(tcampo t,unsigned int cifre){
    unsigned int i,j;


    for(j=0; j<t.c; j +=cifre)
    {
        int z;
        for(z = 0 ; z < cifre ; ++z){
            printf("-");
        }
        printf("---");
    }
    printf("-");/* recupero angolo dx */

    printf("\n");

    /* parte centrale */
    for(i= 0; i < t.r; ++i)
    {
        for(j=0; j<t.c; j +=cifre)
        {
            int z;
            for(z = 0 ; z < cifre; ++z){
                if(z == 0){
                    printf("| %c",t.mat[i][j]);
                }else{
                    if(z == cifre-1){
                        printf("%c ",t.mat[i][j+z]);
                    }else{
                        printf("%c",t.mat[i][j+z]);
                    }
                }

            }
        }

        printf("|\n");
        if(i != t.r-1)
        {
            printf("|");
            for(j=0; j<t.c; j +=cifre)
            {
                if(j != 0){
                    int z;
                    for(z = 0 ; z < cifre ; ++z){
                        printf("-");
                    }
                    printf("---");
                }else{
                    int z;
                    for(z = 1 ; z < cifre ; ++z){
                        printf("-");
                    }
                    printf("---");
                }

            }
            printf("|\n");
        }
    }


    /* e infine la base*/

    for(j=0; j<t.c; j +=cifre)
    {
        int z;
        for(z = 0 ; z < cifre ; ++z){
            printf("-");
        }
        printf("---");
    }
    printf("-");/* recupero angolo dx */

    printf("\n");

}
void stampa_campo_inv(tcampo t,unsigned int cifre){
    unsigned int j;
    int i;

    for(j=0; j<t.c; j +=cifre)
    {
        int z;
        for(z = 0 ; z < cifre ; ++z){
            printf("-");
        }
        printf("---");
    }
    printf("-");/* recupero angolo dx */

    printf("\n");

    /* parte centrale */
    for(i= t.r-1; i > -1 ; --i)
    {
        for(j=0; j<t.c; j +=cifre)
        {
            int z;
            for(z = 0 ; z < cifre; ++z){
                if(z == 0){
                    printf("| %c",t.mat[i][j]);
                }else{
                    if(z == cifre-1){
                        printf("%c ",t.mat[i][j+z]);
                    }else{
                        printf("%c",t.mat[i][j+z]);
                    }
                }

            }
        }

        printf("|\n");
        if(i != 0)
        {
            printf("|");
            for(j=0; j<t.c; j +=cifre)
            {
                if(j != 0){
                    int z;
                    for(z = 0 ; z < cifre ; ++z){
                        printf("-");
                    }
                    printf("---");
                }else{
                    int z;
                    for(z = 1 ; z < cifre ; ++z){
                        printf("-");
                    }
                    printf("---");
                }

            }
            printf("|\n");
        }
    }


    /* e infine la base*/

    for(j=0; j<t.c; j +=cifre)
    {
        int z;
        for(z = 0 ; z < cifre ; ++z){
            printf("-");
        }
        printf("---");
    }
    printf("-");/* recupero angolo dx */

    printf("\n");

}
tplayer *crea_pedine(unsigned int n,char ped,unsigned int np,unsigned int cifre,tcampo t){
    tplayer *p;
    unsigned int h;

    p = (tplayer*)malloc(sizeof(tplayer));
    p->arr = (tpedina*)malloc(sizeof(tpedina)*n);
    for(h = 0 ; h < n ; ++h){
        p->arr[h].et = (char*)malloc(sizeof(char)*(3+cifre));
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
            p->arr[i].et[0] = ' ';
            p->arr[i].et[1] = ' ' ;
            p->arr[i].et[2] = ped ;
            if(i < 10){
                unsigned int z;
                for(z = 3 ; z < (3+cifre)-1 ; ++z){
                    p->arr[i].et[z] = '0';
                }
                p->arr[i].et[(3+cifre)-1] = '0'+i;
            }else {
                unsigned int x = 1, f = 3, z,m = i;
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
                }
            }
            p->arr[i].dim = cifre;
            p->arr[i].app = ped;
            p->arr[i].cima = 2 ;
            p->arr[i].numero = i ;
            p->arr[i].grado = 1 ;
            p->arr[i].r = nr;
            p->arr[i].c = nc;
            if(np == 1){
                if((nc+((3+cifre)*2) < t.c) && (nc+((3+cifre)*2) > 0)){
                    nc +=((3+cifre)*2);
                }else{
                    --nr;
                    if( c == 0){
                        c = (3+cifre) ;
                        nc = (3+cifre);
                    }else{
                        c = 0;
                        nc = 0;
                    }
                }
            }else{
                if((nc+((3+cifre)*2) < t.c) && (nc+((3+cifre)*2) > 0)){
                    nc +=((3+cifre)*2);
                }else{
                    ++nr;
                    if( c == 0){
                        c = (3+cifre) ;
                        nc = (3+cifre);
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

void stampa_player(tplayer p){
    unsigned int i,j;
    for(i = 0 ; i < p.dim ; ++i){

        printf("Pedina = ");
        for(j = 0 ; j < 3+p.arr[i].dim ;++j ){
            printf("%c",p.arr[i].et[j]);
        }
        printf("\n");
        printf("Cima = %d\n",p.arr[i].cima);
        printf("Numero pedina : %d \n",p.arr[i].numero);
        printf("Grado pedina : %d \n",p.arr[i].grado);
        printf("Posizione nel campo x e y : %d , %d\n",p.arr[i].r,p.arr[i].c );
        printf("\n");
    }
}

void aggiorna_campo(tcampo *t,tplayer p1,tplayer p2){
    unsigned int i;
    for(i = 0 ; i < p1.dim ; ++i){
        if(p1.arr[i].grado > 0){
            unsigned int j;
            for(j = 0 ; j < 3+p1.arr[i].dim ; ++j){
                t->mat[p1.arr[i].r][p1.arr[i].c+j] = p1.arr[i].et[j];
            }
        }
    }

    for(i= 0 ; i < p2.dim ; ++i){
        if(p2.arr[i].grado > 0){
            unsigned int j;
            for(j = 0 ; j < 3+p2.arr[i].dim ; ++j){
                t->mat[p2.arr[i].r][p2.arr[i].c+j] = p2.arr[i].et[j];
            }
        }
    }

}

unsigned int is_pedina(tcampo t,unsigned int r,unsigned int c,unsigned int cifre){
    int i,flag = 0;
    for(i = 0 ; i < cifre ; ++i){
        (t.mat[r][c+i] != ' ')&&(t.mat[r][c+i] != '#') ? flag = 1 : flag;
    }
    return flag;
}
void togli_pedina(tcampo *t,unsigned int r,unsigned int c,unsigned cifre){
    unsigned int x = r , y = c,i;
    printf("Non torna : %d e %d e %d\n",x,y,cifre);
    for(i = 0 ; i < cifre ; ++i){
        t->mat[x][y+i] = '#';
    }
    /*if(((y/cifre)+x)%2 == 0){
            t->mat[r][c+i] = '#';
        }else{
            t->mat[r][c+i] = ' ';
        }*/
}

void promuovi_pedina(tplayer *p,unsigned int np,unsigned int numpl,unsigned int meta){
    if((numpl == 1)&&(p->arr[np].r == 0)){
        p->arr[np].isPromoted = 1;
    }else{
        if((numpl == 2)&&(p->arr[np].r == meta)){
            p->arr[np].isPromoted = 1;
        }

    }
}
unsigned int ricerca_pl(tplayer p1,tplayer p2,unsigned int x,unsigned int y){
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
unsigned int convert(tcampo t,unsigned int r,unsigned int c,unsigned int dim,unsigned int cifre){
    unsigned int i,num = 0,z = 0;

    for(i = dim ; i > cifre-1 ; --i){
        num += (t.mat[r][c+i]-'0')*pow(10,z);
        z++;

    }

    return num;
}
unsigned int is_in(unsigned int r,unsigned int c,tcampo t){
    if( (r < t.r)&&(c<t.c)){
        return 1;
    }else {
        return 0;
    }
}
int is_eat(tplayer *p1,unsigned int np,char *str,tcampo *t,tplayer *p2,unsigned int pl){
    if(!strcmp(str,"sx")){
        if((is_in(p1->arr[np].r-2,p1->arr[np].c-((p1->arr[np].dim+3)*2),*t))&&((is_in(p1->arr[np].r-1,p1->arr[np].c-(p1->arr[np].dim+3),*t)))){
            unsigned x,y,z;
            x = p1->arr[np].r-1;
            y = p1->arr[np].c-(p1->arr[np].dim+3);
            z = ricerca_pl(*p1,*p2,x,y);
            if((z == 2)&&(is_pedina(*t,p1->arr[np].r-1,p1->arr[np].c-(p1->arr[np].dim+3),(p1->arr[np].dim+3)))&&(!is_pedina(*t,p1->arr[np].r-2,p1->arr[np].c-((p1->arr[np].dim+3)*2),(p1->arr[np].dim+3)))){
                int num = -1 ;
                num = convert(*t,p1->arr[np].r-1,p1->arr[np].c-(p1->arr[np].dim+3),2+p1->arr[np].dim,3);
                if((num > 0)&&(num < p1->dim)){
                    return num;
                }else{
                    return -1;
                }
            }else{
                return -2;
            }
        }else{
            return -3;
        }
    }else {
        if (!strcmp(str, "dx")) {
            if ((is_in(p1->arr[np].r - 2, p1->arr[np].c + ((p1->arr[np].dim + 3) * 3 - 1), *t))&&((is_in(p1->arr[np].r - 1, p1->arr[np].c + (p1->arr[np].dim + 3), *t)))) {
                unsigned x, y, z;
                x = p1->arr[np].r - 1;
                y = p1->arr[np].c + (p1->arr[np].dim + 3);
                z = ricerca_pl(*p1, *p2, x, y);
                if ((z == 2) && (is_pedina(*t, p1->arr[np].r - 1, p1->arr[np].c + (p1->arr[np].dim + 3),p1->arr[np].dim + 3)) &&(!is_pedina(*t, p1->arr[np].r - 2, p1->arr[np].c + ((p1->arr[np].dim + 3) * 2),(p1->arr[np].dim + 3)))) {
                    int num = -1;
                    num = convert(*t, p1->arr[np].r - 1, p1->arr[np].c + (p1->arr[np].dim + 3), 2 + p1->arr[np].dim,3);
                    if((num > 0)&&(num < p1->dim)){
                        return num;
                    }else{
                        return -1;
                    }

                } else {
                    return -2;
                }
            } else {
                return -3;
            }
        }
        if (!strcmp(str, "bassosx") && ((pl == 2) || (p1->arr[np].isPromoted))) {
            if ((is_in(p1->arr[np].r+2,p1->arr[np].c-((p1->arr[np].dim+3)*2),*t))&&((is_in(p1->arr[np].r+1,p1->arr[np].c-(p1->arr[np].dim+3),*t)))) {
                unsigned x, y, z;
                x = p1->arr[np].r+1;
                y = p1->arr[np].c-(p1->arr[np].dim+3);
                z = ricerca_pl(*p1, *p2, x, y);
                if ((z == 2)&&(is_pedina(*t,p1->arr[np].r+1,p1->arr[np].c-(p1->arr[np].dim+3),(p1->arr[np].dim+3)))&&(!is_pedina(*t,p1->arr[np].r+2,p1->arr[np].c-((p1->arr[np].dim+3)*2),(p1->arr[np].dim+3)))) {
                    int num = -1 ;
                    num = convert(*t,p1->arr[np].r+1,p1->arr[np].c-(p1->arr[np].dim+3),2+p1->arr[np].dim,3);
                    if((num > 0)&&(num < p1->dim)){
                        return num;
                    }else{
                        return -1;
                    }
                } else {
                    return -2;
                }
            } else {
                return -3;
            }
        }
        if (!strcmp(str, "bassodx") && ((pl == 2) || (p1->arr[np].isPromoted))) {
            if ((is_in(p1->arr[np].r+2, p1->arr[np].c + ((p1->arr[np].dim + 3) * 3 - 1), *t))&&((is_in(p1->arr[np].r+ 1, p1->arr[np].c +(p1->arr[np].dim + 3) , *t)))) {
                unsigned x, y, z;
                x = p1->arr[np].r +1;
                y = p1->arr[np].c + (p1->arr[np].dim + 3);
                z = ricerca_pl(*p1, *p2, x, y);
                if ((z == 2) && (is_pedina(*t,p1->arr[np].r+1,p1->arr[np].c+(p1->arr[np].dim+3),(p1->arr[np].dim+3)) &&(!is_pedina(*t, p1->arr[np].r+2, p1->arr[np].c + ((p1->arr[np].dim + 3) * 2),(p1->arr[np].dim + 3))))) {
                    int num = -1;
                    num = convert(*t, p1->arr[np].r +1, p1->arr[np].c + (p1->arr[np].dim + 3), 2 + p1->arr[np].dim,3);
                    if((num > 0)&&(num < p1->dim)){
                        return num;
                    }else{
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
    return -4;
}
unsigned int move_noeat(tplayer *p1,unsigned int np,char *str,tcampo *t,tplayer *p2,unsigned int pl){
    if(!strcmp(str,"sx")){
        if((is_in(p1->arr[np].r-1,p1->arr[np].c-(p1->arr[np].dim+3),*t))&&(!is_pedina(*t,p1->arr[np].r-1,p1->arr[np].c-(p1->arr[np].dim+3),(p1->arr[np].dim+3)))){
            togli_pedina(t,p1->arr[np].r,p1->arr[np].c,(p1->arr[np].dim+3));
            --p1->arr[np].r;
            p1->arr[np].c -= (p1->arr[np].dim+3);
            promuovi_pedina(p1,np,1,t->r-1);
            return 1;
        }else{
            return 0;
        }
    }else{
        if (!strcmp(str, "dx")) {
            if((is_in(p1->arr[np].r-1, p1->arr[np].c + (p1->arr[np].dim + 3), *t))&&(!is_pedina(*t, p1->arr[np].r - 1, p1->arr[np].c + (p1->arr[np].dim + 3),p1->arr[np].dim+3))){
                togli_pedina(t,p1->arr[np].r,p1->arr[np].c,(p1->arr[np].dim+3));
                --p1->arr[np].r;
                p1->arr[np].c += (p1->arr[np].dim+3);
                promuovi_pedina(p1,np,1,t->r-1);
                return 1;
            }else{
                return 0;
            }
        }
        if (!strcmp(str, "bassosx") && ((pl == 2) || (p1->arr[np].isPromoted))) {
            if((is_in(p1->arr[np].r+1,p1->arr[np].c-(p1->arr[np].dim+3),*t))&&(!is_pedina(*t,p1->arr[np].r+1,p1->arr[np].c-(p1->arr[np].dim+3),(p1->arr[np].dim+3)))){
                togli_pedina(t,p1->arr[np].r,p1->arr[np].c,(p1->arr[np].dim+3));
                p1->arr[np].r++;
                p1->arr[np].c -= (p1->arr[np].dim+3);
                return 1;
            }else{
                return 0;
            }
        }
        if (!strcmp(str, "bassodx") && ((pl == 2) || (p1->arr[np].isPromoted))) {
            if((is_in(p1->arr[np].r+1, p1->arr[np].c + (p1->arr[np].dim + 3), *t))&&(!is_pedina(*t, p1->arr[np].r+1, p1->arr[np].c + (p1->arr[np].dim + 3),p1->arr[np].dim + 3))){
                togli_pedina(t,p1->arr[np].r,p1->arr[np].c,(p1->arr[np].dim+3));
                p1->arr[np].r++;
                p1->arr[np].c += (p1->arr[np].dim+3);
                return 1;
            }else{
                return 0;
            }
        }

    }

    return 0;

}
unsigned int mangia_p1(tplayer *p1,tplayer *p2,char *str,unsigned np,tcampo t,unsigned int num){

    char temp[3];
    unsigned int x,f,z;
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
                controllo_pedina(p1, p2,num);
            } else {
                unsigned int pos, i;
                pos = is_empty(*p1);
                p2->arr[num].et[p2->arr[num].cima]= ' ';
                ++p2->arr[num].cima;
                --p2->arr[num].grado;
                for (i = 0; i < 3; ++i) {
                    p1->arr[pos].et[i] = p2->arr[num].et[i];
                }
                p1->arr[pos].grado += -p2->arr[num].grado;
                p1->arr[pos].r = p2->arr[num].r;
                p1->arr[pos].c = p2->arr[num].c;
                i = p1->arr[pos].numero ;
                z = p1->arr[pos].dim-1;
                x = pow(10,z);
                for(f = 3 ; f < 3+p1->arr[num].dim ; ++f){
                    unsigned int div = i/x;
                    if (div > 0) {
                        p1->arr[pos].et[f] = '0' + div;
                    } else {
                        p1->arr[pos].et[f] = '0';
                    }
                    i-= x *div ;
                    --z;
                    x = pow(10,z);
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
        p1->arr[np].c -= (p1->arr[np].dim+3)*2;
    }else{
        if(!strcmp(str,"dx")){
            p1->arr[np].r -= 2;
            p1->arr[np].c += (p1->arr[np].dim+3)*2;
        }
        if(!strcmp(str,"bassosx")){
            p1->arr[np].r += 2;
            p1->arr[np].c -= (p1->arr[np].dim+3)*2;
        }
        if(!strcmp(str,"bassodx")){
            p1->arr[np].r += 2;
            p1->arr[np].c += (p1->arr[np].dim+3)*2;
        }

    }

    if(p2->arr[num].grado < 1){
        togli_pedina(&t,p2->arr[num].r,p2->arr[num].c,p2->arr[num].dim+3);
    }
    if(!strcmp(str,"sx")){
        togli_pedina(&t,p1->arr[np].r+2,p1->arr[np].c+(p1->arr[np].dim+3)*2,p1->arr[np].dim+3);
    }else{
        if(!strcmp(str,"dx")){
            togli_pedina(&t,p1->arr[np].r+2,p1->arr[np].c-(p1->arr[np].dim+3)*2,(p1->arr[np].dim+3));
        }
        if(!strcmp(str,"bassosx")){
            togli_pedina(&t,p1->arr[np].r-2,p1->arr[np].c+(p1->arr[np].dim+3)*2,p1->arr[np].dim+3);
        }
        if(!strcmp(str,"bassodx")){
            togli_pedina(&t,p1->arr[np].r-2,p1->arr[np].c-(p1->arr[np].dim+3)*2,(p1->arr[np].dim+3));
        }

    }
    promuovi_pedina(p1,np,1,t.r-1);

    return 1;

}
unsigned int sposta_p1 (tplayer *p1,unsigned int np,char *str,tcampo *t,tplayer *p2,unsigned int pl){
    int num;
    num = is_eat(p1,np,str,t,p2,pl);
    if(num > -1){
        mangia_p1(p1,p2,str,np,*t,num);
        return 1;
    }else{
        if(num == -1){
            printf("Errore nella convert\n");
            return 0;
        }else{
            if(num == -4){
                printf("Errore nella is_ate\n");
                return 0;
            }else{
                if(move_noeat(p1,np,str,t,p2,pl)){
                    return 1;
                }else{
                    return 0;
                }

            }
        }

    }

}
unsigned int sposta_p2(tplayer *p2,unsigned int np,char *str,tcampo *t,tplayer *p1){
    if(!strcmp(str,"sx")) {
        if(sposta_p1(p2,np,"bassosx",t,p1,2)){
            return 1;
        }else{
            return 0;
        }

    }else{
        if(!strcmp(str,"dx")){
            if(sposta_p1(p2,np,"bassodx",t,p1,2)){
                return 1;
            }else{
                return 0;
            }
        }
        if(!strcmp(str,"bassosx")&&(p2->arr[np].isPromoted)) {
            if(sposta_p1(p2,np,"sx",t,p1,2)){
                return 1;
            }else{
                return 0;
            }
        }
        if(!strcmp(str,"bassodx")&&(p2->arr[np].isPromoted)) {
            if(sposta_p1(p2,np,"dx",t,p1,2)){
                return 1;
            }else{
                return 0;
            }
        }

    }

    return 0;
}
unsigned int is_victory(tplayer p1,tplayer p2){
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
unsigned int scelta_turno(){
    char str[2];

    printf("Inizia il turno come da predefinito (quindi primo giocatore)? ");
    scanf("%s",str);
    if((!strcmp(str,"si"))||(!strcmp(str,"Si"))||(!strcmp(str,"SI"))){
        return 1;
    }else{
        printf("Lancio monetina ? ");
        scanf("%s",str);
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
unsigned int turno_player1(tplayer *p1,tplayer *p2,tcampo *t){
    char str[10];
    unsigned int np,y = 0;

    printf("Turno player 1 : \n");
    stampa_campo(*t,(p1->arr[0].dim+3));

    printf("Vuoi uscire dal gioco ? ");
    scanf("%s",str);
    if((!strcmp(str,"si"))||(!strcmp(str,"Si"))||(!strcmp(str,"SI"))){
        return 1;
    }


    printf("Numero di pedina da selezionare : ");
    scanf("%u",&np);
    printf("Vuoi selezionare questa pedina %d ? ",np);
    scanf("%s",str);

    while((!strcmp(str,"no"))||(!strcmp(str,"NO"))||(!strcmp(str,"No"))){
        printf("Numero di pedina da selezionare : ");
        scanf("%u",&np);
        printf("Vuoi selezionare questa pedina %d ? ",np);
        scanf("%s",str);
    }

    while(y==0){
        printf("Verso che direzione vuoi spostare la pedina ? ");
        scanf("%s",str);
        y = sposta_p1(p1,np,str,t,p2,1);
    }
    aggiorna_campo(t,*p1,*p2);
    stampa_campo(*t,(p1->arr[0].dim+3));

    return 0;
}
unsigned int turno_player2(tplayer *p1,tplayer *p2,tcampo *t){
    char str[10];
    unsigned int np,y = 0;

    printf("Turno player 2 : \n");
    stampa_campo_inv(*t,(p2->arr[0].dim+3));

    printf("Vuoi uscire dal gioco ? ");
    scanf("%s",str);
    if((!strcmp(str,"si"))||(!strcmp(str,"Si"))||(!strcmp(str,"SI"))){
        return 1;
    }


    printf("Numero di pedina da selezionare : ");
    scanf("%u",&np);
    printf("Vuoi selezionare questa pedina %d ? ",np);
    scanf("%s",str);

    while((!strcmp(str,"no"))||(!strcmp(str,"NO"))||(!strcmp(str,"No"))){
        printf("Numero di pedina da selezionare : ");
        scanf("%u",&np);
        printf("Vuoi selezionare questa pedina %d ? ",np);
        scanf("%s",str);
    }


    while(y==0){
        printf("Verso che direzione vuoi spostare la pedina ? ");
        scanf("%s",str);
        printf("%u\n",y);
        y = sposta_p2(p2,np,str,t,p1);
    }
    aggiorna_campo(t,*p1,*p2);
    stampa_campo_inv(*t,(p2->arr[np].dim+3));

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
unsigned int controllo_pedina(tplayer *p,tplayer *p2,unsigned int np){


    p->arr = (tpedina*)realloc(p->arr,(p->dim+1)*sizeof(tpedina));
    p->arr[p->dim].et = (char*)malloc(sizeof(char)*(3+p2->arr[np].dim));

    if((p->arr) &&(p->arr[p->dim].et)) {
        unsigned int i,x,f,z,cifre;

        p2->arr[np].et[p2->arr[np].cima]= ' ';
        ++p2->arr[np].cima;
        --p2->arr[np].grado;
        p->arr[p->dim].dim = p2->arr[np].dim;
        p->arr[p->dim].cima = p2->arr[np].cima;
        p->arr[p->dim].numero = p->dim;
        p->arr[p->dim].grado = p2->arr[np].grado;
        p->arr[p->dim].c = p2->arr[np].c;
        p->arr[p->dim].r = p2->arr[np].r;

        for(i = 0 ; i < 3 ; ++i){
            p->arr[p->dim].et[i] = p2->arr[np].et[i];
        }
        i = 0;
        cifre = p->dim;
        while(cifre != 0){
            cifre /= 10;
            ++i;
        }
        printf("%u\n",cifre);
        if(cifre != p2->arr[np].dim){
            printf("un fottuto casino\n");
        }
        i = p->dim;
        printf("%u\n",p->dim);
        z = p->arr[p->dim].dim-1;
        x = pow(10,z);
        for(f = 3 ; f < 3+p->arr[p->dim].dim ; ++f){
            unsigned int div = i/x;
            if (div > 0) {
                p->arr[p->dim].et[f] = '0' + div;
            } else {
                p->arr[p->dim].et[f] = '0';
            }
            i-= x *div ;
            --z;
            x = pow(10,z);
        }
        ++p->dim;

        return 1;
    }else{
        printf("Errore nella realloc\n");
        return 0;
    }
}