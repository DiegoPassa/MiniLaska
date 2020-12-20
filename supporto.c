#include<stdio.h>
#include<stdlib.h>
#include"supporto.h"
#include<string.h>
#include<time.h>
#include <math.h>
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
void stampa_campo(tcampo t,unsigned int cifre,unsigned int npl){
    unsigned int j ;
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
    if(npl == 1){
        i = 0;
    }else{
        i = t.r-1;
    }

    while( (((npl == 1)&&(i < t.r))||((npl == 2)&&(i >= 0))) )
    {

        for(j=0; j<t.c;j +=cifre)
        {
            unsigned int z;
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
        if(((npl == 1)&&(i != t.r-1))||((npl == 2)&&(i != 0)))
        {
            printf("|");
            for(j=0; j<t.c; j +=cifre)
            {
                if(j != 0){
                    unsigned int z;
                    for(z = 0 ; z < cifre ; ++z){
                        printf("-");
                    }
                    printf("---");
                }else{
                    unsigned int z;
                    for(z = 1 ; z < cifre ; ++z){
                        printf("-");
                    }
                    printf("---");
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
            p->arr[i].cima = 2 ;
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
    unsigned int i,flag = 0;
    for(i = 0 ; i < cifre ; ++i){
        if((t.mat[r][c+i] != ' ')&&(t.mat[r][c+i] != '#') ){
            flag = 1;
        }
    }
    printf("\n");
    return flag;
}
void togli_pedina(tcampo *t,unsigned int r,unsigned int c,unsigned cifre){
    unsigned int x = r , y = c,i;
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
unsigned int is_in(int r,int c,tcampo t){
    if( (r < t.r)&&(c<t.c)){
        return 1;
    }else {
        return 0;
    }
}
int can_eat(tplayer *p1,unsigned int np,char *str,tcampo *t,tplayer *p2,unsigned int pl){
    if(!strcmp(str,"sx")){
        if((is_in(p1->arr[np].r-2,p1->arr[np].c-((p1->arr[np].dim+3)*2),*t))&&((is_in(p1->arr[np].r-1,p1->arr[np].c-(p1->arr[np].dim+3),*t)))){
            unsigned x,y,z;
            x = p1->arr[np].r-1;
            y = p1->arr[np].c-(p1->arr[np].dim+3);
            z = ricerca_pl(*p1,*p2,x,y);
            if((z == 2)&&(is_pedina(*t,p1->arr[np].r-1,p1->arr[np].c-(p1->arr[np].dim+3),(p1->arr[np].dim+3)))&&(!is_pedina(*t,p1->arr[np].r-2,p1->arr[np].c-((p1->arr[np].dim+3)*2),(p1->arr[np].dim+3)))){
                int num = -1 ;
                num = convert(*t,p1->arr[np].r-1,p1->arr[np].c-(p1->arr[np].dim+3),2+p1->arr[np].dim,3);
                if((num > -1)&&(num < p1->dim)){
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
            if ((is_in(p1->arr[np].r-2, p1->arr[np].c + ((p1->arr[np].dim + 3) * 3-1 ), *t))&&((is_in(p1->arr[np].r - 1, p1->arr[np].c + (p1->arr[np].dim + 3), *t)))) {
                unsigned x, y, z;
                x = p1->arr[np].r - 1;
                y = p1->arr[np].c + (p1->arr[np].dim + 3);
                z = ricerca_pl(*p1, *p2, x, y);
                if ((z == 2) && (is_pedina(*t, p1->arr[np].r - 1, p1->arr[np].c + (p1->arr[np].dim + 3),p1->arr[np].dim + 3)) &&(!is_pedina(*t, p1->arr[np].r - 2, p1->arr[np].c + ((p1->arr[np].dim + 3) * 2),(p1->arr[np].dim + 3)))) {
                    int num = -1;
                    num = convert(*t, p1->arr[np].r - 1, p1->arr[np].c + (p1->arr[np].dim + 3), 2 + p1->arr[np].dim,3);
                    if((num > -1)&&(num < p1->dim)){
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
                    if((num > -1)&&(num < p1->dim)){
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
                    if((num > -1)&&(num < p1->dim)){
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
            promuovi_pedina(p1,np,pl,t->r-1);
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
                promuovi_pedina(p1,np,pl,t->r-1);
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
unsigned int mangia(tplayer *p1,tplayer *p2,char *str,unsigned np,tcampo t,unsigned int num){

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
        togli_pedina(&t,p1->arr[np].r+2,p1->arr[np].c+((p1->arr[np].dim+3)*2),p1->arr[np].dim+3);
    }else{
        if(!strcmp(str,"dx")){
            togli_pedina(&t,p1->arr[np].r+2,p1->arr[np].c-((p1->arr[np].dim+3)*2),(p1->arr[np].dim+3));
        }
        if(!strcmp(str,"bassosx")){
            togli_pedina(&t,p1->arr[np].r-2,p1->arr[np].c+((p1->arr[np].dim+3)*2),p1->arr[np].dim+3);
        }
        if(!strcmp(str,"bassodx")){
            togli_pedina(&t,p1->arr[np].r-2,p1->arr[np].c-((p1->arr[np].dim+3)*2),(p1->arr[np].dim+3));
        }

    }
    promuovi_pedina(p1,np,1,t.r-1);
    promuovi_pedina(p2,np,2,t.r-1);
    return 1;

}
unsigned int sposta_p1 (tplayer *p1,unsigned int np,char *str,tcampo *t,tplayer *p2,unsigned int pl){
    int num;
    num = can_eat(p1,np,str,t,p2,pl);
    if(num > -1){
        mangia(p1,p2,str,np,*t,num);
        return 1;
    }else{
        if(num == -1){
            printf("Errore nella convert\n");
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
unsigned int turno_player(tplayer *p1,tplayer *p2,tcampo *t,unsigned int npl){
    char str[10];
    unsigned int y = 0,np;

    aggiorna_campo(t,*p1,*p2);
    if(npl == 1){
        printf("Turno player 1 : \n");
        stampa_campo(*t,(p1->arr[0].dim+3),1);
    }else{
        printf("Turno player 2 : \n");
        stampa_campo(*t,(p2->arr[0].dim+3),2);
    }


    printf("Vuoi uscire dal gioco ? ");
    scanf("%s",str);
    if((!strcmp(str,"si"))||(!strcmp(str,"Si"))||(!strcmp(str,"SI"))){
        return 1;
    }

    printf("Numero di pedina da selezionare : ");
    scanf("%u",&np);
    while( !((np >= 0)&&( ((npl == 1)&&(np < p1->dim)) || ((npl == 2)&&(np < p2->dim)))) || (!ped_noblock(*p1,*p2,*t,np,npl))){

        if(!ped_noblock(*p1,*p2,*t,np,npl)){
            printf("La pedina %u non puo' fare nessuna mossa!\n",np);
        }else{
            printf("Non puoi selezionare la pedina n. %u",np);
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
        while( (!((np >= 0)&&( ((npl == 1)&&(np < p1->dim)) || ((npl == 2)&&(np < p2->dim))))) ||(!ped_noblock(*p1,*p2,*t,np,npl))){
            if(!ped_noblock(*p1,*p2,*t,np,npl)){
                printf("La pedina %u non puo' fare nessuna mossa!\n",np);
            }else{
                printf("Non puoi selezionare la pedina n. %u",np);
            }
            printf("Numero di pedina da selezionare : ");
            scanf("%u",&np);
        }
        printf("Vuoi selezionare questa pedina %d ? ",np);
        scanf("%s",str);
    }

    while(y==0){
        printf("Verso che direzione vuoi spostare la pedina ? ");
        scanf("%s",str);
        if(npl == 1){
            y = sposta_p1(p1,np,str,t,p2,1);
        }else{
            y = sposta_p2(p2,np,str,t,p1);
        }
        if(y == 0){
            printf("La pedina numero %u non si puo' spostare verso %s\n",np,str);
            char temp[2];

            printf("Numero di pedina da selezionare : ");
            scanf("%u",&np);
            while( !((np >= 0)&&( ((npl == 1)&&(np < p1->dim)) || ((npl == 2)&&(np < p2->dim)))) || (!ped_noblock(*p1,*p2,*t,np,npl))){

                if(!ped_noblock(*p1,*p2,*t,np,npl)){
                    printf("La pedina %u non puo' fare nessuna mossa!\n",np);
                }else{
                    printf("Non puoi selezionare la pedina n. %u",np);
                }
                printf("Numero di pedina da selezionare : ");
                scanf("%u",&np);
            }
            printf("Vuoi selezionare questa pedina %d ? ",np);
            scanf("%s",temp);

            while( !((np >= 0)&&( ((npl == 1)&&(np < p1->dim)) || ((npl == 2)&&(np < p2->dim)))) || (!ped_noblock(*p1,*p2,*t,np,npl))){

                if(!ped_noblock(*p1,*p2,*t,np,npl)){
                    printf("La pedina %u non puo' fare nessuna mossa!\n",np);
                }else{
                    printf("Non puoi selezionare la pedina n. %u",np);
                }
                printf("Numero di pedina da selezionare : ");
                scanf("%u",&np);
            }
        }
    }
    aggiorna_campo(t,*p1,*p2);
    if(npl == 1){
        stampa_campo(*t,(p1->arr[0].dim+3),1);
    }else{
        stampa_campo(*t,(p1->arr[0].dim+3),2);
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
unsigned int max_pedine(unsigned int r,unsigned int c){
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
tcampo *campo_copy(tcampo t ,tcampo *new){
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
            new->mat = (char**)malloc(sizeof(char*)*(new->r));
            for(i = 0 ; i < new->r ; ++i){
                new->mat[i] = (char*)malloc(sizeof(char)*(new->c));
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
        if(flag == 1){
            unsigned int m,l;
            n->dim = p.dim;
            n->arr = (tpedina*)malloc(sizeof(tpedina)*(n->dim));
            for(l = 0 ; l < p.dim ; ++l){
                n->arr[l].et = (char*)malloc(sizeof(char)*(cifre));
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
unsigned int ped_noblock(tplayer p1,tplayer p2,tcampo t,unsigned int nped,unsigned int npl){
    tcampo *new = NULL;
    tplayer *n1 = NULL,*n2 = NULL;
    new = campo_copy(t,new);
    n1 = player_copy(p1,n1,p1.arr[0].dim+3);
    n2 = player_copy(p2,n2,p2.arr[0].dim+3);
    if(new != NULL && n1 != NULL && n2 != NULL){
        aggiorna_campo(new,p1,p2);
        if(npl == 1){
            unsigned int flag = 0;
            if(sposta_p1(n1,nped,"sx",new,n2,1)){
                flag = 1;
                new = campo_copy(t,new);
                n1 = player_copy(p1,n1,p1.arr[0].dim+3);
                n2 = player_copy(p2,n2,p2.arr[0].dim+3);
            }else{
                if(sposta_p1(n1,nped,"dx",new,n2,1)){
                    flag = 1;
                    new = campo_copy(t,new);
                    n1 = player_copy(p1,n1,p1.arr[0].dim+3);
                    n2 = player_copy(p2,n2,p2.arr[0].dim+3);
                }
                if(sposta_p1(n1,nped,"bassosx",new,n2,1)){
                    flag = 1;
                    new = campo_copy(t,new);
                    n1 = player_copy(p1,n1,p1.arr[0].dim+3);
                    n2 = player_copy(p2,n2,p2.arr[0].dim+3);
                }
                if(sposta_p1(n1,nped,"bassodx",new,n2,1)){
                    flag = 1;
                    new = campo_copy(t,new);
                    n1 = player_copy(p1,n1,p1.arr[0].dim+3);
                    n2 = player_copy(p2,n2,p2.arr[0].dim+3);
                }
                destroy_campo(new);
                destroy_player(n1);
                destroy_player(n2);
                return flag;
            }
        }else{
            unsigned int flag = 0;
            if(sposta_p2(n2,nped,"sx",new,n1)){
                flag = 1;
                new = campo_copy(t,new);
                n1 = player_copy(p1,n1,p1.arr[0].dim+3);
                n2 = player_copy(p2,n2,p2.arr[0].dim+3);
            }else{
                if(sposta_p2(n2,nped,"dx",new,n1)){
                    flag = 1;
                    new = campo_copy(t,new);
                    n1 = player_copy(p1,n1,p1.arr[0].dim+3);
                    n2 = player_copy(p2,n2,p2.arr[0].dim+3);
                }
                if(sposta_p2(n2,nped,"bassosx",new,n1)){
                    flag = 1;
                    new = campo_copy(t,new);
                    n1 = player_copy(p1,n1,p1.arr[0].dim+3);
                    n2 = player_copy(p2,n2,p2.arr[0].dim+3);
                }
                if(sposta_p2(n2,nped,"bassodx",new,n1)){
                    flag = 1;
                    new = campo_copy(t,new);
                    n1 = player_copy(p1,n1,p1.arr[0].dim+3);
                    n2 = player_copy(p2,n2,p2.arr[0].dim+3);
                }
                destroy_campo(new);
                destroy_player(n1);
                destroy_player(n2);
                return flag;
            }

        }
    }else{
        printf("Errore nella ped_noblock\n");
        return 0;
    }


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
int player_vs_player(unsigned int x ){
    tcampo *t;
    tplayer *p1 = NULL,*p2 = NULL;
    unsigned int exit = 0,turno,round = 0;
    unsigned int cifre,conta = 0,numped = 11;

    if(x == 0){
        t = crea_campo(7,7,3+conta);
        inizializza_campo(t,3+conta);
        p1 = crea_pedine(11,'B',1,conta,*t);/* creare n pedine di carattere c */
        p2 = crea_pedine(11,'N',2,conta,*t);/* creare n pedine di carattere c */
    }else{
        unsigned int w,h,max_ped = 0;
        printf("Altezza della scacchiera : ");
        scanf("%u",&h);
        printf("Larghezza della scacchiera : ");
        scanf("%u",&w);
        while(w < 3 || h < 3){
            printf("Larghezza e altezza della scacchiera non soddisfa requisiti minimi(h >= 3,w >= 3)\n");
            printf("Rinserire altezza e larghezza\n ");
            printf("Altezza della scacchiera : ");
            scanf("%u",&h);
            printf("Larghezza della scacchiera : ");
            scanf("%u",&w);
        }
        max_ped = max_pedine(h,w);
        printf("Numero di pedine massimo per giocatore : %u\n",max_ped);
        printf("Numero pedine ?(ovviamente minore o guale al massimo numero) : ");
        scanf("%u",&cifre);
        while(cifre > max_ped){
            printf("Rinserire numero pedine : ");
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
            t = crea_campo(h,w,3+conta);
            inizializza_campo(t,3+conta);
            p1 = crea_pedine(numped,'B',1,conta,*t);/* creare n pedine di carattere c */
            p2 = crea_pedine(numped,'N',2,conta,*t);/* creare n pedine di carattere c */

        }else{
            printf("Non ha senso giocare con %u pedine !\n",cifre);
            return 0;
        }
    }
    turno = scelta_turno();
    printf("Il player che inizia e' %d\n",turno);
    while((exit == 0)&&(!is_victory(*p1,*p2))){
        printf("Round numero : %u\n",round);
        if(turno == 1){
            exit = turno_player(p1,p2,t,turno);
            turno = 2;
        }else{
            exit = turno_player(p1,p2,t,turno);

            turno = 1;
        }
        ++round;
    }
    exit = is_victory(*p1,*p2);
    if(exit == 0){
        printf("Hai abbandonato la partita\n");
    }else{
        printf("Il vincitore e' il player %d!\n",exit);
    }

    destroy_campo(t);
    destroy_player(p1);
    destroy_player(p2);

    return 1;
}
unsigned int ia(tplayer *p,tcampo *t){

    unsigned int i,*pos;
    int *punteggio;

    pos = (unsigned int *)malloc(sizeof(unsigned int)*p->dim);
    punteggio = (int *)malloc(sizeof(int)*p->dim);
    for(i = 0 ; i < p->dim ; ++i){
        /* if pedina non  bloccata
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
         */
    }
    for(i = 0 ; i < p->dim ; ++i){
        /* trovo max punteggio */
        /* m = i (indice max punteggio )*/
    }

    /* return m*/
    return 0;


    /* liberare punt e pos con free*/

}
void destroy_player (tplayer *p){

    unsigned int i;
    for(i = 0 ; i < p->dim ;++i){
        free(p->arr[i].et);
    }
    free(p->arr);
    free(p);
}
void destroy_campo(tcampo *t){
    unsigned int i;

    for(i = 0 ; i < t->r ; ++i){
        free(t->mat[i]);
    }
    free(t);

}

