#include <stdio.h>
#include <stdlib.h>
#include "supporto.h"
#include <math.h>

/*
int main()
{
    tcampo *t;
    tplayer *p1 = NULL, *p2 = NULL;
    int exit = 0, turno, round = 0;
    int cifre, conta = 0, numped = 0, mod = 0, flag_mod = 0;
    unsigned int nBoard;

    system("clear");

    printf("Progetto MiniLasca 51\n\nBenvenuto!\n  [1] Player vs Player\n  [2] Player vs AI\nSeleziona modalità di gioco: ");

    while (mod != 1 && mod != 2)
    {
        if (flag_mod == 0)
        {
            scanf("%d", &mod);
            flag_mod = 1;
        }
        else
        {
            printf("\nSelezione non in elenco!\nNuova selezione: ");
            scanf("%d", &mod);
        }
    }

    if (mod == 1)
    {
        printf("\nSelezionato: [Player vs Player]\n\n");
        printf("* Creazione campo *\nDimensione scacchiera? : ");
        scanf("%u", &nBoard);

        printf("Numero pedine ? : ");
        scanf("%d", &cifre);
        numped = cifre;
        if (cifre > 0)
        {
            while (cifre != 0)
            {
                cifre /= 10;
                ++conta;
            }
            if ((pow(10,conta-1) == numped)&&(numped != 1))
            {
                --conta;
            }
            printf("(Numero cifre %d)\n", conta);

            t = crea_campo(nBoard, nBoard, 3 + conta);
            inizializza_campo(t, 3 + conta);

            p1 = crea_pedine(numped, 'B', 1, conta, *t);
            p2 = crea_pedine(numped, 'N', 2, conta, *t);

            stampa_player(*p1);
            stampa_player(*p2);

            aggiorna_campo(t, *p1, *p2);
            printf("\nCampo di partenza : \n");
            stampa_campo(*t, 3 + conta, 1);

            turno = scelta_turno();
            printf("Il player che inizia è %d\n", turno);
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
    }
    else if (mod == 2)
    {
        printf("\nSelezionato: [Player vs AI]\n\n");
        printf("Non ancora implementato u.u\n");
        return 0;
    }

    return 0;
}
*/

int main()
{
    tcampo *t;
    tplayer *p1 = NULL,*p2 = NULL;
    unsigned int exit = 0,turno,round = 0;
    unsigned int cifre,conta = 0,numped = 0;


    printf("Numero pedine ? : ");
    scanf("%u",&cifre);
    numped = cifre;
    if(cifre > 0){
        while(cifre != 0){
            cifre /= 10;
            ++conta;
        }
        if((pow(10,conta-1) == numped)&&(numped != 1)){
            --conta;
        }
        printf("Numero cifre %d\n",conta);

        t = crea_campo(7,7,3+conta);
        inizializza_campo(t,3+conta);

        /* p1->arr[2].grado = 2;
       p1->arr[2].r = 5;
       p1->arr[2].et[0] = 'N';
       p1->arr[2].et[1] = 'B';
       p1->arr[2].et[2] = 'N';
       p1->arr[2].grado = 3;
       p1->arr[2].cima = 0;
       p2->arr[2].grado = 2;
       p2->arr[2].cima = 1;
       p2->arr[2].et[1]  = 'B';
       p2->arr[2].et[2]  = 'N';
       p2->arr[2].r = 6;
       p2->arr[2].c = 16;
       aggiorna_campo(t,*p1,*p2);
       printf("Campo di partenza : \n");
       stampa_campo(*t,3+conta);
       turno_player1(p1,p2,t);
       stampa_player(*p1);
       turno_player1(p1,p2,t);
       stampa_player(*p1);
       */

        p1 = crea_pedine(numped,'N',1,conta,*t);/* creare n pedine di carattere c */
        p2 = crea_pedine(numped,'B',2,conta,*t);/* creare n pedine di carattere c */




        aggiorna_campo(t,*p1,*p2);


        turno = scelta_turno();
        printf("Il player che inizia è %d\n",turno);
        while((exit == 0)&&(!is_victory(*p1,*p2))){
            printf("Round numero : %d\n",round);
            if(turno == 1){
                exit = turno_player(p1,p2,t,1);
                turno = 2;
            }else{
                exit = turno_player(p1,p2,t,2);

                turno = 1;
            }
            ++round;
        }
        exit = is_victory(*p1,*p2);
        printf("Il vincitore è il player %d!\n",exit);
    }else{
        printf("Non ha senso giocare con %u pedine !\n",cifre);
    }


    return 0;
}

