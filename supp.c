#include<stdio.h>
#include<stdlib.h>
#include"supp.h"
#include<string.h>
#include<time.h>
tcampo *crea_campo(int r,int col){
    tcampo *t;
    
    t = (tcampo*)malloc(sizeof(tcampo));

    if(t != NULL){ 
        int i;
        t->r = r;
        t->c = col*5;
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
void inizializza_campo(tcampo *t){
    int i,j;
    
    for(i = 0 ; i < t->r ; ++i){
        for(j = 0 ; j < t->c ; j+=5){
        
          if( ((j/5)+i)%2 == 0){
                t->mat[i][j] = '#';                           
                t->mat[i][j+1] = '#';   
                t->mat[i][j+2] = '#';   
                t->mat[i][j+3] = '#'; 
                t->mat[i][j+4] = '#';   
            }else{
                t->mat[i][j] = ' ';                           
                t->mat[i][j+1] = ' ';   
                t->mat[i][j+2] = ' ';   
                t->mat[i][j+3] = ' '; 
                t->mat[i][j+4] = ' '; 
            }
        }
    }

    
}
void stampa_campo(tcampo t){
    int i,j;


    for(j=0; j<t.c; j +=5)
	{
	    printf("-----");
        printf("---");
	}
    printf("-");/* recupero angolo dx */

	printf("\n");

     /* parte centrale */
     for(i= 0; i < t.r; ++i)
    {
    	for(j=0; j<t.c; j +=5)
		{
            
         
           printf("| %c%c%c%c%c ",t.mat[i][j],t.mat[i][j+1],t.mat[i][j+2],t.mat[i][j+3],t.mat[i][j+4]);
           
		    
		}
  		printf("|\n");
  		if(i != t.r-1)
  		{
    		for(j=0; j<t.c; j +=5)
			{
		    	printf("|-------");
			}
  			printf("|\n");
		}		
	}	


    /* e infine la base*/
	for(j=0; j<t.c; j +=5)
	{
	    printf("-----");
        printf("---");
	}
    printf("-"); /* recupero angolo dx */

	printf("\n");
}
void stampa_campo_inv(tcampo t){
    int i,j;


    for(j=0; j<t.c; j +=5)
	{
	    printf("-----");
        printf("---");
	}
    printf("-");/* recupero angolo dx */

	printf("\n");

     /* parte centrale */
     for(i= t.r-1; i >= 0; --i)
    {
    	for(j= 0; j< t.c; j +=5)
		{
           
           printf("| %c%c%c%c%c ",t.mat[i][j],t.mat[i][j+1],t.mat[i][j+2],t.mat[i][j+3],t.mat[i][j+4]);
          
		    
		}
  		printf("|\n");
  		if(i != 0)
  		{
    		for(j=0; j<t.c; j +=5)
			{
		    	printf("|-------");
			}
  			printf("|\n");
		}		
	}	


    /* e infine la base*/
	for(j=0; j<t.c; j +=5)
	{
	    printf("-----");
        printf("---");
	}
    printf("-"); /* recupero angolo dx */

	printf("\n");


}
tplayer *crea_pedine(int n,char ped,int np,tcampo t){
    tplayer *p;

    p = (tplayer*)malloc(sizeof(tplayer));
    p->arr = (tpedina*)malloc(sizeof(tpedina)*n);
    if( (p != NULL) && (p->arr != NULL)){
        int i,nr,nc = 0,c = -1;
        
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
                p->arr[i].et[3] = '0' ;
                p->arr[i].et[4] = '0'+i ;
                
            }else{
                int x = i,c = 0;
                while(x > 9){
                    x-=10;  
                    ++c;
                }
                p->arr[i].et[3] = '0'+ c  ;
                p->arr[i].et[4] = '0'+ x  ;
            }
            p->arr[i].app = ped;
            p->arr[i].cima = 1 ;
            p->arr[i].numero = i ;
            p->arr[i].grado = 1 ;
            p->arr[i].r = nr;
            p->arr[i].c = nc;
            if(np == 1){
                if((nc+10 < t.c) && (nc+10 > 0)){
                    nc +=10;
                }else{
                    --nr;
                    if( c == 0){
                        c = 5 ;                             
                        nc = 5;
                    }else{
                        c = 0;
                        nc = 0;
                    }
                }
            }else{
                if((nc+10 < t.c) && (nc+10 > 0)){
                    nc +=10;
                }else{
                    nr++;
                    if( c == 0){
                        c = 5 ;                             
                        nc = 5;
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
    int i;
    for(i = 0 ; i < p.dim ; ++i){
        printf("Pedina = '%c%c%c%c%c'\n",p.arr[i].et[0],p.arr[i].et[1],p.arr[i].et[2],p.arr[i].et[3],p.arr[i].et[4]);
        printf("Cima = %d\n",p.arr[i].cima);
        printf("Numero pedina : %d \n",p.arr[i].numero);
        printf("Grado pedina : %d \n",p.arr[i].grado);
        printf("Posizione nel campo x e y : %d , %d\n",p.arr[i].r,p.arr[i].c );
        printf("\n");
    }
}
void aggiorna_campo(tcampo *t,tplayer *p1,tplayer *p2){
    int i;
    for(i = 0 ; i < p1->dim ; ++i){
        if(p1->arr[i].grado > 0){
            int j;
            for(j = 0 ; j < 5 ; ++j){
                t->mat[p1->arr[i].r][p1->arr[i].c+j] = p1->arr[i].et[j];
            }
        }
    }
    for(i = 0 ; i < p2->dim ; ++i){
        if(p2->arr[i].grado > 0){
            int j;
            for(j = 0 ; j < 5 ; ++j){
                t->mat[p2->arr[i].r][p2->arr[i].c+j] = p2->arr[i].et[j];
            }
        }
    }
    
}   
int is_pedina(tcampo t,int r,int c){
    int i,flag = 0;
    for(i = 0 ; i < 5 ; ++i){
        (t.mat[r][c+i] != ' ')&&(t.mat[r][c+i] != '#') ? flag = 1 : flag; 
    }
    return flag;
}
void togli_pedina(tcampo *t,int r,int c){
    int i;
    int x = r , y = c;
    for(i = 0 ; i < 5 ; ++i){
        if(((y/5)+x)%2 != 0){
            t->mat[r][c+i] = '#';
        }else{
            t->mat[r][c+i] = ' ';
        }
    }
}
void aggiungi_pedina(tplayer *p,int np,char ped){
    if(p->arr[np].grado < 3){
        p->arr[np].et[p->arr[np].cima] = ped;
        --p->arr[np].cima;
        ++p->arr[np].grado;
    }else{
        p->arr[np].et[2] = ped;
    }
}
int ricerca_pl(tplayer p1,tplayer p2,int x,int y){
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
int mangia_p1(tplayer *p1,tplayer *p2,char *str,int np,tcampo t){

    if(!strcmp(str,"sx")){
        int x,y,z;      
        x = p1->arr[np].r-1;
        y = p1->arr[np].c-5;
        z = ricerca_pl(*p1,*p2,x,y);
        if((z == 1) || (!z)){
            return 0;
        }else{
            int num;
            if(t.mat[p1->arr[np].r-1][p1->arr[np].c-2] == '0'){
                num = t.mat[p1->arr[np].r-1][p1->arr[np].c-1] - '0';
            }else{
                int x = t.mat[p1->arr[np].r-1][p1->arr[np].c-2] - '0';
                num = (t.mat[p1->arr[np].r-1][p1->arr[np].c-1] - '0')+(10*x) ;
            }
            
            if(p1->arr[np].grado < 3){
                p1->arr[np].et[p1->arr[np].cima] = p2->arr[num].et[p2->arr[num].cima+1];
                --p1->arr[np].cima;
                p1->arr[np].grado++;
                p2->arr[num].cima++;
                --p2->arr[num].grado;
                p2->arr[num].et[p2->arr[num].cima]= ' ';               
                p1->arr[np].r -= 2;
                p1->arr[np].c -= 10;
                
            }else{
                char c;
                c = p2->arr[num].et[p2->arr[num].cima+1];
                aggiungi_pedina(p1,np,c);
                p2->arr[num].cima++;
                --p2->arr[num].grado;
                p2->arr[num].et[p2->arr[num].cima]= ' ';               
                p1->arr[np].r -= 2;
                p1->arr[np].c -= 10;
            }
            if(p2->arr[num].grado == 0){
                togli_pedina(&t,p1->arr[np].r+1,p1->arr[np].c+5);
                
            }
            togli_pedina(&t,p1->arr[np].r+2,p1->arr[np].c+10);
            return 1;
        }
        
    }
    if(!strcmp(str,"dx")){
        int x,y,z;      
        x = p1->arr[np].r-1;
        y = p1->arr[np].c+5;
        z = ricerca_pl(*p1,*p2,x,y);
        if((z == 1) || (!z)){
            return 0;
        }else{
            int num;
            if(t.mat[p1->arr[np].r-1][p1->arr[np].c+8] == '0'){
                num = t.mat[p1->arr[np].r-1][p1->arr[np].c+9] - '0';
            }else{
                int x = t.mat[p1->arr[np].r-1][p1->arr[np].c+8] - '0';
                num = (t.mat[p1->arr[np].r-1][p1->arr[np].c+9] - '0')+(10*x) ;
            }
            if(p1->arr[np].grado < 3){
                p1->arr[np].et[p1->arr[np].cima] = p2->arr[num].et[p2->arr[num].cima+1];
                --p1->arr[np].cima;
                p1->arr[np].grado++;
                p2->arr[num].cima++;
                --p2->arr[num].grado;
                p2->arr[num].et[p2->arr[num].cima]= ' ';               
                p1->arr[np].r -= 2;
                p1->arr[np].c += 10;
                
            }else{
                char c;
                c = p2->arr[num].et[p2->arr[num].cima+1];
                aggiungi_pedina(p1,np,c);
                p2->arr[num].cima++;
                --p2->arr[num].grado;
                p2->arr[num].et[p2->arr[num].cima]= ' ';               
                p1->arr[np].r -= 2;
                p1->arr[np].c += 101;
            }
            if(p2->arr[num].grado == 0){
                togli_pedina(&t,p1->arr[np].r+1,p1->arr[np].c-5);
                
            }
            togli_pedina(&t,p1->arr[np].r+2,p1->arr[np].c-10);
            return 1;
        }
        
    }
    if(!strcmp(str,"bassodx")){
        int x,y,z;      
        x = p1->arr[np].r+1;
        y = p1->arr[np].c+5;
        z = ricerca_pl(*p1,*p2,x,y);
        if((z == 1) || (!z)){
            return 0;
        }else{
            int num;
            if(t.mat[p1->arr[np].r+1][p1->arr[np].c+8] == '0'){
                num = t.mat[p1->arr[np].r+1][p1->arr[np].c+9] - '0';
            }else{
                int x = t.mat[p1->arr[np].r+1][p1->arr[np].c+8] - '0';
                num = (t.mat[p1->arr[np].r+1][p1->arr[np].c+9] - '0')+(10*x) ;
            }
            if(p1->arr[np].grado < 3){
                p1->arr[np].et[p1->arr[np].cima] = p2->arr[num].et[p2->arr[num].cima+1];
                --p1->arr[np].cima;
                p1->arr[np].grado++;
                p2->arr[num].cima++;
                --p2->arr[num].grado;
                p2->arr[num].et[p2->arr[num].cima]= ' ';               
                p1->arr[np].r += 2;
                p1->arr[np].c += 10;
                
            }else{
                char c;
                c = p2->arr[num].et[p2->arr[num].cima+1];
                aggiungi_pedina(p1,np,c);
                p2->arr[num].cima++;
                --p2->arr[num].grado;
                p2->arr[num].et[p2->arr[num].cima]= ' ';               
                p1->arr[np].r += 2;
                p1->arr[np].c += 10;
            }
            if(p2->arr[num].grado == 0){
                togli_pedina(&t,p1->arr[np].r-1,p1->arr[np].c-5);
                
            }
            togli_pedina(&t,p1->arr[np].r-2,p1->arr[np].c-10);
            return 1;
        }
        
    }
    if(!strcmp(str,"bassosx")){
        int x,y,z;      
        x = p1->arr[np].r+1;
        y = p1->arr[np].c-5;
        z = ricerca_pl(*p1,*p2,x,y);
        if((z == 1) || (!z)){
            return 0;
        }else{
            int num;
            if(t.mat[p1->arr[np].r+1][p1->arr[np].c-2] == '0'){
                num = t.mat[p1->arr[np].r+1][p1->arr[np].c-1] - '0';
            }else{
                int x = t.mat[p1->arr[np].r+1][p1->arr[np].c-2] - '0';
                num = (t.mat[p1->arr[np].r+1][p1->arr[np].c-1] - '0')+(10*x) ;
            }
            if(p1->arr[np].grado < 3){
                p1->arr[np].et[p1->arr[np].cima] = p2->arr[num].et[p2->arr[num].cima+1];
                --p1->arr[np].cima;
                p1->arr[np].grado++;
                p2->arr[num].cima++;
                --p2->arr[num].grado;
                p2->arr[num].et[p2->arr[num].cima]= ' ';               
                p1->arr[np].r += 2;
                p1->arr[np].c -= 10;
                
            }else{
                char c;
                c = p2->arr[num].et[p2->arr[num].cima+1];
                aggiungi_pedina(p1,np,c);
                p2->arr[num].cima++;
                --p2->arr[num].grado;
                p2->arr[num].et[p2->arr[num].cima]= ' ';               
                p1->arr[np].r += 2;
                p1->arr[np].c -= 10;
            }
            if(p2->arr[num].grado == 0){
                togli_pedina(&t,p1->arr[np].r-1,p1->arr[np].c+5);
                
            }
            togli_pedina(&t,p1->arr[np].r-2,p1->arr[np].c+10);
            return 1;
        }
        
    }
    return 0;
}
int sposta_p1 (tplayer *p1,int np,char *str,tcampo *t,tplayer *p2){
    if(!strcmp(str,"dx")){
        if(is_pedina(*t,p1->arr[np].r-1,p1->arr[np].c+5)){
            if((p1->arr[np].r-2 >= 0)&&(p1->arr[np].r-2<t->r)&&(p1->arr[np].c+14 >= 0)&&(p1->arr[np].c+14< t->c)){
                    if(!is_pedina(*t,p1->arr[np].r-2,p1->arr[np].c+10)){
                        mangia_p1(p1,p2,str,np,*t);
                        return 1;
                    }else{
                        return 0;
                    }  
                }else{
                    return 0;
                }
        }else{
            if((p1->arr[np].r-1 >= 0)&&(p1->arr[np].r-1<t->r)&&(p1->arr[np].c+5 >= 0)&&(p1->arr[np].c+5 < t->c)){
                togli_pedina(t,p1->arr[np].r,p1->arr[np].c);
                --p1->arr[np].r; 
                p1->arr[np].c += 5;
                if(p1->arr[np].r == 0){
                    aggiungi_pedina(p1,np,p1->arr[np].app);
                }
                return 1;
            }else{
                return 0;
            }
        }
    }else{
        if(!strcmp(str,"sx")){
            if(is_pedina(*t,p1->arr[np].r-1,p1->arr[np].c-5)){
                if((p1->arr[np].r-2 >= 0)&&(p1->arr[np].r-2<t->r)&&(p1->arr[np].c-10 >= 0)&&(p1->arr[np].c-10 < t->c)){
                    if(!is_pedina(*t,p1->arr[np].r-2,p1->arr[np].c-10)){
                        mangia_p1(p1,p2,str,np,*t);
                        return 1;
                    }else{
                        return 0;
                    }  
                }else{
                    return 0;
                }
            }else{
                if((p1->arr[np].r-1 >= 0)&&(p1->arr[np].r-1<t->r)&&(p1->arr[np].c-5 >= 0)&&(p1->arr[np].c-5< t->c)){
                    togli_pedina(t,p1->arr[np].r,p1->arr[np].c);
                    --p1->arr[np].r; 
                    p1->arr[np].c -= 5;
                    if(p1->arr[np].r == 0){
                        aggiungi_pedina(p1,np,p1->arr[np].app);
                    }
                    return 1;
                }else{
                    return 0;
                }
            }
        }
        if(!strcmp(str,"bassodx")){
            if(is_pedina(*t,p1->arr[np].r+1,p1->arr[np].c+5)){
                if((p1->arr[np].r+2 >= 0)&&(p1->arr[np].r+2<t->r)&&(p1->arr[np].c+14 >= 0)&&(p1->arr[np].c+14< t->c)&&(p1->arr[np].grado > 1)){
                    if(!is_pedina(*t,p1->arr[np].r+2,p1->arr[np].c+10)){
                        mangia_p1(p1,p2,str,np,*t);
                        return 1;
                    }else{
                        return 0;
                    }  
                }else{
                    return 0;
                }
            }else{
                if((p1->arr[np].r+1 >= 0)&&(p1->arr[np].r+1<t->r)&&(p1->arr[np].c+5 >= 0)&&(p1->arr[np].c+5 < t->c)&&(p1->arr[np].grado > 1)){
                    togli_pedina(t,p1->arr[np].r,p1->arr[np].c);
                    p1->arr[np].r++; 
                    p1->arr[np].c += 5;
                    if(p1->arr[np].r == 0){
                        aggiungi_pedina(p1,np,p1->arr[np].app);
                    }
                    return 1;
                }else{
                    return 0;
                }
            }
        }
        if(!strcmp(str,"bassosx")){
            if(is_pedina(*t,p1->arr[np].r+1,p1->arr[np].c-5)){
                if((p1->arr[np].r+2 >= 0)&&(p1->arr[np].r+2<t->r)&&(p1->arr[np].c-10 >= 0)&&(p1->arr[np].c-10< t->c)&&(p1->arr[np].grado > 1)){
                    if(!is_pedina(*t,p1->arr[np].r+2,p1->arr[np].c-10)){
                        mangia_p1(p1,p2,str,np,*t);
                        return 1;
                    }else{
                        return 0;
                    }  
                }else{
                    return 0;
                }
            }else{
                if((p1->arr[np].r+1 >= 0)&&(p1->arr[np].r+1<t->r)&&(p1->arr[np].c-5 >= 0)&&(p1->arr[np].c-5 < t->c)&&(p1->arr[np].grado > 1)){
                    togli_pedina(t,p1->arr[np].r,p1->arr[np].c);
                    p1->arr[np].r++; 
                    p1->arr[np].c -= 5;
                    if(p1->arr[np].r == 0){
                        aggiungi_pedina(p1,np,p1->arr[np].app);
                    }
                    return 1;
                }else{
                    return 0;
                }
            }
        }
    }
    return 0;
}
int mangia_p2(tplayer *p1,tplayer *p2,char *str,int np,tcampo t){

    if(!strcmp(str,"sx")){
        int x,y,z;      
        x = p2->arr[np].r+1;
        y = p2->arr[np].c-5;
        z = ricerca_pl(*p1,*p2,x,y);
        if((z == 2) || (!z)){
            return 0;
        }else{
            int num;
            if(t.mat[p2->arr[np].r+1][p2->arr[np].c-2] == '0'){
                num = t.mat[p2->arr[np].r+1][p2->arr[np].c-1] - '0';
            }else{
                int x = t.mat[p2->arr[np].r+1][p2->arr[np].c-2] - '0';
                num = (t.mat[p2->arr[np].r+1][p2->arr[np].c-1] - '0')+(10*x) ;
            }
            if(p2->arr[np].grado < 3){
                p2->arr[np].et[p2->arr[np].cima] = p1->arr[num].et[p1->arr[num].cima+1];
                --p2->arr[np].cima;
                p2->arr[np].grado++;
                p1->arr[num].cima++;
                --p1->arr[num].grado;
                p1->arr[num].et[p1->arr[num].cima]= ' ';               
                p2->arr[np].r += 2;
                p2->arr[np].c -= 10;
            }else{
                char c;
                c = p1->arr[num].et[p2->arr[num].cima+1];
                aggiungi_pedina(p2,np,c);
                p1->arr[num].cima++;
                --p1->arr[num].grado;
                p1->arr[num].et[p2->arr[num].cima]= ' ';               
                p2->arr[np].r += 2;
                p2->arr[np].c -= 10;
            }
            if(p1->arr[num].grado == 0){
                togli_pedina(&t,p2->arr[np].r-1,p2->arr[np].c+5);
                
            }
            togli_pedina(&t,p2->arr[np].r-2,p2->arr[np].c+10);
            return 1;
        }
        
    }
    if(!strcmp(str,"dx")){
        int x,y,z;      
        x = p2->arr[np].r+1;
        y = p2->arr[np].c+5;
        z = ricerca_pl(*p1,*p2,x,y);
        if((z == 2) || (!z)){
            return 0;
        }else{
            int num = -1;
            if(t.mat[p2->arr[np].r+1][p2->arr[np].c+8] == '0'){
                num = t.mat[p2->arr[np].r+1][p2->arr[np].c+9] - '0';
                
            }else{
                int x = t.mat[p2->arr[np].r+1][p2->arr[np].c+8] - '0';
                num = (t.mat[p2->arr[np].r+1][p2->arr[np].c+8] - '0')+(10*x) ;
            }
            
            if(p2->arr[np].grado < 3){
                p2->arr[np].et[p2->arr[np].cima] = p1->arr[num].et[p1->arr[num].cima+1];
                --p2->arr[np].cima;
                p2->arr[np].grado++;
                p1->arr[num].cima++;
                --p1->arr[num].grado;
                p1->arr[num].et[p1->arr[num].cima]= ' ';               
                p2->arr[np].r += 2;
                p2->arr[np].c += 10;
            }else{
                char c;
                c = p1->arr[num].et[p2->arr[num].cima+1];
                aggiungi_pedina(p2,np,c);
                p1->arr[num].cima++;
                --p1->arr[num].grado;
                p1->arr[num].et[p2->arr[num].cima]= ' ';               
                p2->arr[np].r += 2;
                p2->arr[np].c += 10;
            }
            if(p1->arr[num].grado == 0){
                togli_pedina(&t,p2->arr[np].r-1,p2->arr[np].c-5);
                
            }
            togli_pedina(&t,p2->arr[np].r-2,p2->arr[np].c-10);
            return 1;
        }
        
    }
    if(!strcmp(str,"bassosx")){
        int x,y,z;      
        x = p2->arr[np].r-1;
        y = p2->arr[np].c-5;
        z = ricerca_pl(*p1,*p2,x,y);
        if((z == 2) || (!z)){
            return 0;
        }else{
            int num;
            if(t.mat[p2->arr[np].r-1][p2->arr[np].c-2] == '0'){
                num = t.mat[p2->arr[np].r-1][p2->arr[np].c-1] - '0';
            }else{
                int x = t.mat[p2->arr[np].r-1][p2->arr[np].c-2] - '0';
                num = (t.mat[p2->arr[np].r-1][p2->arr[np].c-1] - '0')+(10*x) ;
            }
            if(p2->arr[np].grado < 3){
                p2->arr[np].et[p2->arr[np].cima] = p1->arr[num].et[p1->arr[num].cima+1];
                --p2->arr[np].cima;
                p2->arr[np].grado++;
                p1->arr[num].cima++;
                --p1->arr[num].grado;
                p1->arr[num].et[p1->arr[num].cima]= ' ';               
                p2->arr[np].r -= 2;
                p2->arr[np].c -= 10;
            }else{
                char c;
                c = p1->arr[num].et[p2->arr[num].cima+1];
                aggiungi_pedina(p2,np,c);
                p1->arr[num].cima++;
                --p1->arr[num].grado;
                p1->arr[num].et[p2->arr[num].cima]= ' ';               
                p2->arr[np].r -= 2;
                p2->arr[np].c -= 10;
            }
            if(p1->arr[num].grado == 0){
                togli_pedina(&t,p2->arr[np].r+1,p2->arr[np].c+5);
                
            }
            togli_pedina(&t,p2->arr[np].r+2,p2->arr[np].c+10);
            return 1;
        }
        
    }
    if(!strcmp(str,"bassodx")){
        int x,y,z;      
        x = p2->arr[np].r-1;
        y = p2->arr[np].c+5;
        z = ricerca_pl(*p1,*p2,x,y);
        if((z == 2) || (!z)){
            return 0;
        }else{
            int num;
            if(t.mat[p2->arr[np].r-1][p2->arr[np].c+8] == '0'){
                num = t.mat[p2->arr[np].r-1][p2->arr[np].c+9] - '0';
            }else{
                int x = t.mat[p2->arr[np].r-1][p2->arr[np].c+8] - '0';
                num = (t.mat[p2->arr[np].r-1][p2->arr[np].c+9] - '0')+(10*x) ;
            }
            if(p2->arr[np].grado < 3){
                p2->arr[np].et[p2->arr[np].cima] = p1->arr[num].et[p1->arr[num].cima+1];
                --p2->arr[np].cima;
                p2->arr[np].grado++;
                p1->arr[num].cima++;
                --p1->arr[num].grado;
                p1->arr[num].et[p1->arr[num].cima]= ' ';               
                p2->arr[np].r -= 2;
                p2->arr[np].c += 10;
            }else{
                char c;
                c = p1->arr[num].et[p2->arr[num].cima+1];
                aggiungi_pedina(p2,np,c);
                p1->arr[num].cima++;
                --p1->arr[num].grado;
                p1->arr[num].et[p2->arr[num].cima]= ' ';               
                p2->arr[np].r -= 2;
                p2->arr[np].c += 10;
            }
            if(p1->arr[num].grado == 0){
                togli_pedina(&t,p2->arr[np].r+1,p2->arr[np].c-5);
                
            }
            togli_pedina(&t,p2->arr[np].r+2,p2->arr[np].c-10);
            return 1;
        }
        
    }

    return 0;
}
int sposta_p2(tplayer *p2,int np,char *str,tcampo *t,tplayer *p1){

    if(!strcmp(str,"sx")){
        if(is_pedina(*t,p2->arr[np].r+1,p2->arr[np].c-5)){
            if((p2->arr[np].r+2 >= 0)&&(p2->arr[np].r+2<t->r)&&(p2->arr[np].c-10 >= 0)&&(p2->arr[np].c-10< t->c)){
                    if(!is_pedina(*t,p2->arr[np].r+2,p2->arr[np].c-10)){
                        mangia_p2(p1,p2,str,np,*t);
                        return 1;
                    }else{
                        return 0;
                    }   
                }else{
                    return 0;
                }
            }else{
                if((p2->arr[np].r+1 >= 0)&&(p2->arr[np].r+1<t->r)&&(p2->arr[np].c-5 >= 0)&&(p2->arr[np].c-5 < t->c)){
                    togli_pedina(t,p2->arr[np].r,p2->arr[np].c);
                    p2->arr[np].r++; 
                    p2->arr[np].c -= 5;
                    if(p2->arr[np].r == 0){
                        aggiungi_pedina(p2,np,p2->arr[np].app);
                    }
                    return 1;
                }else{
                    return 0;
                }
            }
    }
    if(!strcmp(str,"dx")){
        if(is_pedina(*t,p2->arr[np].r+1,p2->arr[np].c+5)){
            if((p2->arr[np].r+2 >= 0)&&(p2->arr[np].r+2<t->r)&&(p2->arr[np].c+14 >= 0)&&(p2->arr[np].c+14< t->c)){
                    if(!is_pedina(*t,p2->arr[np].r+2,p2->arr[np].c+10)){
                        mangia_p2(p1,p2,str,np,*t);
                        return 1;
                    }else{
                        return 0;
                    } 
                }else{
                    return 0;
                }
            }else{
                if((p2->arr[np].r+1 >= 0)&&(p2->arr[np].r+1<t->r)&&(p2->arr[np].c+5 >= 0)&&(p2->arr[np].c+5 < t->c)){
                    togli_pedina(t,p2->arr[np].r,p2->arr[np].c);
                    p2->arr[np].r++; 
                    p2->arr[np].c += 5;
                    if(p2->arr[np].r == 0){
                        aggiungi_pedina(p2,np,p2->arr[np].app);
                    }
                    return 1;
                }else{
                    return 0;
                }
            }
    }
    if(!strcmp(str,"bassosx")){
         if(is_pedina(*t,p2->arr[np].r-1,p2->arr[np].c-5)){
             if((p2->arr[np].r-2 >= 0)&&(p2->arr[np].r-2<t->r)&&(p2->arr[np].c-10 >= 0)&&(p2->arr[np].c-10< t->c)&&(p2->arr[np].grado > 1)){
                    if(!is_pedina(*t,p2->arr[np].r-2,p2->arr[np].c-10)){
                        mangia_p2(p1,p2,str,np,*t);
                        return 1;
                    }else{
                        return 0;
                    } 
                }else{
                    return 0;
                }
            }else{
                if((p2->arr[np].r-1 >= 0)&&(p2->arr[np].r-1<t->r)&&(p2->arr[np].c-5 >= 0)&&(p2->arr[np].c-5 < t->c)&&(p2->arr[np].grado > 1)){
                    togli_pedina(t,p2->arr[np].r,p2->arr[np].c);
                    p2->arr[np].r--; 
                    p2->arr[np].c -= 5;
                    if(p2->arr[np].r == 0){
                        aggiungi_pedina(p2,np,p2->arr[np].app);
                    }
                    return 1;
                }else{
                    return 0;
                }
            }
    }
    if(!strcmp(str,"bassodx")){
        if(is_pedina(*t,p2->arr[np].r-1,p2->arr[np].c+5)){
             if((p2->arr[np].r-2 >= 0)&&(p2->arr[np].r-2<t->r)&&(p2->arr[np].c+14 >= 0)&&(p2->arr[np].c+14< t->c)&&(p2->arr[np].grado > 1)){
                    if(!is_pedina(*t,p2->arr[np].r-2,p2->arr[np].c+10)){
                        mangia_p2(p1,p2,str,np,*t);
                        return 1;
                    }else{
                        return 0;
                    } 
                }else{
                    return 0;
                }
            }else{
                if((p2->arr[np].r-1 >= 0)&&(p2->arr[np].r-1<t->r)&&(p2->arr[np].c+5 >= 0)&&(p2->arr[np].c+5 < t->c)&&(p2->arr[np].grado > 1)){
                    togli_pedina(t,p2->arr[np].r,p2->arr[np].c);
                    p2->arr[np].r--; 
                    p2->arr[np].c += 5;
                    if(p2->arr[np].r == 0){
                        aggiungi_pedina(p2,np,p2->arr[np].app);
                    }
                    return 1;
                }else{
                    return 0;
                }
            }
    }
    return 0;
} 
int is_victory(tplayer p1,tplayer p2){
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
    if((v1 == v2)){
        flag = 0;
    }else{
        v1 > v2 ? flag = 1 : flag;
        v2 > v1 ? flag = 2 : flag;
    }
    return flag;
}
int scelta_turno(){
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
int turno_player1(tplayer *p1,tplayer *p2,tcampo *t){
    char str[10];
    int np,y = 0;    
    
    printf("Turno player 1 : \n");
    stampa_campo(*t);
    
    printf("Vuoi uscire dal gioco ? ");
    scanf("%s",str);
    if((!strcmp(str,"si"))||(!strcmp(str,"Si"))||(!strcmp(str,"SI"))){
        return 1;
    }
    
    /* inserire comando per aiuto del player */
    printf("Numero di pedina da selezionare : ");
    scanf("%d",&np);
    printf("Vuoi selezionare questa pedina %d ? ",np);
    scanf("%s",str);
      
    while((!strcmp(str,"no"))||(!strcmp(str,"NO"))||(!strcmp(str,"No"))){
        printf("Numero di pedina da selezionare : ");
        scanf("%d",&np);
        printf("Vuoi selezionare questa pedina %d ? ",np);
        scanf("%s",str);
    }

    while(y==0){
        printf("Verso che direzione vuoi spostare la pedina ? ");
        scanf("%s",str);
        y = sposta_p1(p1,np,str,t,p2);
    }
    aggiorna_campo(t,p1,p2);
    stampa_campo(*t);

    return 0;
}
int turno_player2(tplayer *p1,tplayer *p2,tcampo *t){
    char str[10];
    int np,y = 0;    
    
    printf("Turno player 2 : \n");
    stampa_campo_inv(*t);
    
    printf("Vuoi uscire dal gioco ? ");
    scanf("%s",str);
    if((!strcmp(str,"si"))||(!strcmp(str,"Si"))||(!strcmp(str,"SI"))){
        return 1;
    }
    
    /* inserire comando per aiuto del player */
    printf("Numero di pedina da selezionare : ");
    scanf("%d",&np);
    printf("Vuoi selezionare questa pedina %d ? ",np);
    scanf("%s",str);
    
    while((!strcmp(str,"no"))||(!strcmp(str,"NO"))||(!strcmp(str,"No"))){
        printf("Numero di pedina da selezionare : ");
        scanf("%d",&np);
        printf("Vuoi selezionare questa pedina %d ? ",np);
        scanf("%s",str);
    }


    while(y==0){
        printf("Verso che direzione vuoi spostare la pedina ? ");
        scanf("%s",str);
        printf("%d\n",y);
        y = sposta_p2(p2,np,str,t,p1);
    }
    aggiorna_campo(t,p1,p2);
    stampa_campo_inv(*t);

    return 0;
}

