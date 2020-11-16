#include<stdio.h>
#include<stdlib.h>
#include"supp.h"
int main(){
    tcampo *t;    
    tplayer *p1,*p2;
    int exit = 0,turno = 0,round = 0;


    t = crea_campo(7,7); /* creare matrice n*m */
    inizializza_campo(t); /* inizializzare matrice */
    p1 = crea_pedine(11,'b',1,*t);/* creare n pedine di carattere c */
    p2 = crea_pedine(11,'N',2,*t);/* creare n pedine di carattere c */
      
    aggiorna_campo(t,p1,p2);
    printf("Campo di partenza : \n");
    stampa_campo(*t);
    
    turno = scelta_turno();
    printf("Il player che inizia è %d\n",turno);
    while((exit == 0)&&(!is_victory(*p1,*p2))){
        printf("Round numero : %d\n",round);
        if(turno == 1){
            exit = turno_player1(p1,p2,t);
            turno = 2;
        }else{
            exit = turno_player2(p1,p2,t);
            turno = 1;
        }

        ++round;
    }
    exit = is_victory(*p1,*p2);
    printf("Il vincitore è il player %d!\n",exit);

    return 0;
}
