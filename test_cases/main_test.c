#include <stdio.h>
#include <stdlib.h>
#include "../supporto.h"
#include <math.h>

int main()
{
    tcampo *t;
    tplayer *p1 = NULL, *p2 = NULL;
    int exit = 0, turno = 1, round = 0, test = 1;
    int cifre = 11, conta = 0, numped, nBoard;

    scanf("%d", &nBoard);
    scanf("%d", &numped);

    system("clear");

    if (cifre > 0)
    {
        while (cifre != 0)
        {
            cifre /= 10;
            ++conta;
        }
        if (pow(10, conta - 1) == 11)
        {
            --conta;
        }
        printf("(Numero cifre %d)\n", conta);

        t = crea_campo(nBoard, nBoard, 3 + conta);
        inizializza_campo(t, 3 + conta);

        p1 = crea_pedine(numped, 'B', 1, conta, *t); /* creare n pedine di carattere c */
        p2 = crea_pedine(numped, 'N', 2, conta, *t); /* creare n pedine di carattere c */

        /*
        stampa_player(*p1);
        stampa_player(*p2);
        */

        aggiorna_campo(t, *p1, *p2);
        printf("\nCampo di partenza : \n");
        stampa_campo(*t, 3 + conta);

        printf("Il player che inizia è %d\n", 1);

        while ((exit == 0) && (!is_victory(*p1, *p2)))
        {
            printf("Round numero : %d\n", round);
            if (turno == 1)
            {
                exit = turno_player1(p1, p2, t);
                turno = 2;
            }
            else
            {
                exit = turno_player2(p1, p2, t);
                turno = 1;
            }
            ++round;
        }
        exit = is_victory(*p1, *p2);
        printf("Il vincitore è il player %d!\n", exit);
    }
    else
    {
        printf("Non ha senso giocare con %d pedine !\n", cifre);
    }

    return 0;
}