#include <stdio.h>
#include <stdlib.h>
#include "supporto.h"

int main()
{

 /*   player_vs_player(1);*/

    tcampo *t ;
    tplayer *p1 ,*p2 ;
    t = crea_campo(5,5,5);
    inizializza_campo(t,5);
    p1 = crea_pedine(5,'B',1,1,*t);
    p2 = crea_pedine(5,'N',2,1,*t);
    aggiorna_campo(t,*p1,*p2);

    stampa_player(*p1);
    turno_player(p1,p2,t,1);


    destroy_player(p1);
    destroy_player(p2);
    destroy_campo(t);

    return 0;
}

