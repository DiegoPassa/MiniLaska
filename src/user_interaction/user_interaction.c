#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "../colors/colors.h"
#include "../game_engine/game_engine.h"
#include "../ia/ia.h"
#include "../memory_management/memory_management.h"
#include "../movement/movement.h"
#include "user_interaction.h"

void print_board(board_t t,unsigned int cifre, unsigned npl, char char_p1, char char_p2){
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
            while (t.mat[i][l+k] != char_p2 && t.mat[i][l+k] != char_p1 && k<3){
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
                    if (topPl[j/cifre] == char_p2 || topPl[j/cifre] == char_p1){
                        setBlack();
                        if (topPl[j/cifre] == char_p2){
                            /*setRed(2);*/
                            printColor(char_p2); /** TEST */
                        }else if (topPl[j/cifre] == char_p1){
                            /*setYellow(2);*/
                            printColor(char_p1); /** TEST */
                        }
                        printf(" ");
                        for (z = 0; z < cifre; z++){
                            /*printf("%c",t.mat[i][j+z]);*/ /* STAMPA CARATTERI DELLA MATRICE */
                            if(t.mat[i][j+z] == char_p1){
                                printf("%c",'B');
                            }else{
                                if(t.mat[i][j+z] == char_p2){ /* STAMPA SEMPRE CARATTERI B/N A SECONDA DEL PLAYER*/
                                    printf("%c",'N');
                                }else{
                                    printf("%c",t.mat[i][j+z]);
                                }
                            }

                        }
                        printf(" ");
                        resetColor();
                    }
                }else{
                    if (cime[j/cifre]<l){
                        if ((t.mat[i][j+l] == char_p1 || t.mat[i][j+l] == char_p2) && t.mat[i][j+l] != topPl[j/cifre]){
                            if (topPl[j/cifre] == char_p2){
                                /*setYellow(2);*/
                                printColor(char_p1); /** TEST */
                            }else if (topPl[j/cifre] == char_p1){
                                /*setRed(2);*/
                                printColor(char_p2); /** TEST */
                            }
                            /* altrimenti stampa il colore del proprietario */
                        }else{
                            if (topPl[j/cifre] == char_p2){
                                /*setRed(2);*/
                                printColor(char_p2); /** TEST */
                            }else if (topPl[j/cifre] == char_p1){
                                /*setYellow(2);*/
                                printColor(char_p1); /** TEST */
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

void print_player(player_t *players,unsigned int nPl){
    unsigned int i,j;
    for(i = 0 ; i < players[nPl].dim_pawns; ++i){
        if (players[nPl].pawns[i].grade>0){
            printf("Pedina = ");
            for(j = 0 ; j < 3+players[nPl].pawns[i].dim_label+1 ;++j ){
                printf("%c",players[nPl].pawns[i].label[j]);
            }
            printf("\n");
            if (players[nPl].pawns[i].isPromoted){
                print_directions(players[nPl].pawns[i].canMove, 4, i);
            }else
            {
                print_directions(players[nPl].pawns[i].canMove, 2, i);
                
            }       
            printf("Cima = %d\n",players[nPl].pawns[i].cima);
            printf("grade pedina : %d \n",players[nPl].pawns[i].grade);
            printf("Posizione nel campo x: %d, y: %d\n",players[nPl].pawns[i].coordinate.x,players[nPl].pawns[i].coordinate.y);
            /*printf("Posizione nel campo x: %d, y: %d\n",(x/6)+1,(y)+1);*/
            printf("Promozione pedina : %u\n",players[nPl].pawns[i].isPromoted);
            printf("\n");
        }
    }
}

unsigned int round_player(player_t *players,board_t *t,unsigned int nPl){
    char str[10];
    unsigned int num_Pawn = 0;
    int y = -2;

    update_board(t,players);

    printTextColor(players[nPl].color);
    printf("Turno Player %d\n", nPl+1);
    resetColor();
    print_board(*t,(players[0].pawns[0].dim_label+3)+1,nPl, players[0].color, players[1].color);

    printf("Vuoi uscire dal gioco ? ");
    scanf("%s",str);
    if((!strcmp(str,"si"))||(!strcmp(str,"Si"))||(!strcmp(str,"SI"))){
        return 3;
    }

    printf("Numero di pedina da selezionare : ");
    scanf("%u",&num_Pawn);
    
    while(!check_while(players, nPl, num_Pawn) ){
        unsigned int flag = 1;
        if (nPl == 1 || nPl == 0 ){
            flag = check_canMove(players, num_Pawn,nPl);
        }
        if(!flag){
            printf("La pedina %u non puo' muoversi!\n",num_Pawn);
            printf("Numero di pedina da selezionare : ");
            scanf("%u",&num_Pawn);
        }

    }
    printf("Vuoi selezionare questa pedina %u ? ",num_Pawn);
    scanf("%s",str);

    while( (!strcmp(str,"no"))||(!strcmp(str,"NO"))||(!strcmp(str,"No")) ){
        printf("Numero di pedina da selezionare : ");
        scanf("%u",&num_Pawn);
        while(!check_while(players, nPl, num_Pawn)){
            unsigned int flag = 1;
            if (nPl == 1 || nPl == 0){
                flag = check_canMove(players, num_Pawn,nPl);
            }
            if(!flag){
                printf("La pedina %u non puo' muoversi!\n",num_Pawn);
                printf("Numero di pedina da selezionare : ");
                scanf("%u",&num_Pawn);
            }

        }
        printf("Vuoi selezionare questa pedina %u ? ",num_Pawn);
        scanf("%s",str);
    }

    while(y==-2){
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
        if(y < -1){
            char temp[2];
            printf("La pedina numero %u non si puo' spostare verso %s\n",num_Pawn,str);

            printf("Numero di pedina da selezionare : ");
            scanf("%u",&num_Pawn);
            while(!check_while(players, nPl, num_Pawn)){
                unsigned int flag = 1;
                if (nPl == 1 || nPl == 0 ){
                    flag =  check_canMove(players, num_Pawn,nPl) ;
                }
                if(!flag){
                    printf("La pedina %u non puo' muoversi!\n",num_Pawn);
                    printf("Numero di pedina da selezionare : ");
                    scanf("%u",&num_Pawn);
                }
            }

            printf("Vuoi selezionare questa pedina %d ? ",num_Pawn);
            scanf("%s",temp);

            while( (!strcmp(str,"no"))||(!strcmp(str,"NO"))||(!strcmp(str,"No")) ){
                printf("Numero di pedina da selezionare : ");
                scanf("%u",&num_Pawn);
                while(!check_while(players, nPl, num_Pawn)){
                    unsigned int flag = 1;
                    if (nPl == 1 || nPl == 0){
                        flag =  check_canMove(players, num_Pawn,nPl);
                    }
                    if(!flag){
                        printf("La pedina %u non puo' muoversi!\n",num_Pawn);
                        printf("Numero di pedina da selezionare : ");
                        scanf("%u",&num_Pawn);
                    }

                }
                printf("Vuoi selezionare questa pedina %u ? ",num_Pawn);
                scanf("%s",str);
            }
        }
    }
    update_board(t,players);
    if(nPl == 1 || nPl == 0){
        print_board(*t,(players[nPl].pawns[num_Pawn].dim_label+3)+1,1, players[0].color, players[1].color);
    }

    return 4;
}

int player_vs_player(unsigned int x ){
    board_t *t = NULL;
    player_t *players = NULL;
    unsigned int exit = 4,turno = 0,round = 0;
    unsigned int cifre,conta = 2,numped = 11;

    srand(time(0));
    
    /*char char_p1, char_p2;*/
    if(x == 0){
        t = create_board(7,7,3+conta+1);
        initialize_board(t,3+conta+1);
        players = create_pawns(11,'Y','R',conta,*t); /* create array[2] of player_t type */
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

            /*
            printf("[" RED "R" reset "] [" GRN "G" reset "] ["MAG "M" reset "] ["BLU "B" reset "] ["CYN "C" reset "] ["YEL "Y" reset "]\n");

            printf("Seleziona colore pedina Player1: ");
            scanf("%s", &char_p1);

            printf("Seleziona colore pedina Player2: ");
            scanf("%s", &char_p2);*/
            /*  IMPLEMENTARE CONTROLLI CARATTERI*/

            players = create_pawns(numped,'M', 'G', conta,*t); /* create array[2] of player_t type */
            print_player(players,0);
            print_player(players,1);

        }else{
            printf("Non ha senso giocare con %u pedine !\n",cifre);
            return 0;
        }
    }

    /* turno = round_choice(); */
    printf("Il player che inizia e' %u\n",turno+1);
    while((exit == 4)&&(is_victory(players)>2)){
        set_moves_pawn(players,t,0,-1);
        set_moves_pawn(players,t,1,-1);
        if(all_blocked(players,*t,turno)  && (turno == 0 || turno == 1)){
            exit = 2;
        }
        if(exit == 4){
            printf("Round numero : %u\n",round);
            if (turno == 0){
                /* exit = round_player(players,t,turno); */
                exit = round_ia_minimax(players,t,turno, 11);
                /* exit = round_ia_random(players, t, 0); */
                turno = 1;
            }else{
                /* exit = round_player(players,t,turno); */
                /*exit = round_ia_minimax(players,t,turno, 3);*/
                 exit = round_ia_random(players, t, 1);
                turno = 0;
            }
            printPlayerTurn(players[turno].color);
            /* print_player(players,0);
            print_player(players,1); */
            update_board(t, players);
            print_board(*t, players[turno].pawns[0].dim_label+1+3, 0, players[0].color, players[1].color);
            /*printMatrix(*t);*/
            sleep(0);
            ++round;
        }
    }
    if(x == 2){
        printf("Entrambi i giocatori hanno le pedine bloccate\n");
    }
    if(exit == 3){
        printf("Hai abbandonato la partita\n");
    }else{
        if(exit == 4 ){
            exit = is_victory(players);
        }
        printf("Round totali della partita : %u\n",round);
        printf("Il vincitore e' il player %d!\n",exit);
    }

    destroy_board(t);
    destroy_player(players);

    return 1;
}

void menu(){
    int choice=0;
    system("clear");
    while(choice!='3')
    {
        printf("\n\t\t\t\t\t\t+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+\n\t\t\t\t\t\t|M|i|n|i||L|a|s|k|a||G|a|m|e|\n\t\t\t\t\t\t+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+");
        printf("\n\n\t\t\t\t\t\t 1. PLAYER VS PLAYER");
        printf("\n\t\t\t\t\t\t 2. PLAYER VS IA");
        printf("\n\t\t\t\t\t\t 3. EXIT");
        printf("\n\n Enter Your Choice: ");
        choice = getchar();
        switch(choice)
        {
            case '1':
                system("clear");
                printf("\n\t\t\t\t\t\tYOU SELECTED OPTION 1 : PLAYER VS PLAYER\n");
                printf("\t\t\t\t\t\t----------------------------------------\n");
                break;
            case '2':
                system("clear");
                printf("\n\nYOU SELECTED OPTION 2 : PLAYER VS IA\n");
                break;
            case '3':
                break;
            default:
                printf("\n\nINVALID SELECTION...Please try again\n");
        };



    }
}