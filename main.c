#include <stdio.h>
#include <stdlib.h>
#include "supporto.h"

int main()
{

   /* player_vs_player(0);*/

    tcampo *t = NULL;
    tplayer *p1 = NULL,*p2 = NULL;
    t = crea_campo(5,5,5);
    inizializza_campo(t,5);
    p1 = crea_pedine(2,'B',1,1,*t);
    p2 = crea_pedine(2,'N',1,1,*t);
    aggiorna_campo(t,*p1,*p2);
    ped_noblock(*p1,*p2,*t,1,1);

    destroy_player(p1);
    destroy_player(p2);
    destroy_campo(t);

    return 0;
}

