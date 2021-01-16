/*
    ID gruppo : 51

    886711 Passarella-Diego | 882082 Pasqual-Davide | 881493 Ravagnan-Michelle

 */
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
        for (l = 0; l < t.n_cols; l+=cifre){
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
                            printColor(char_p2);
                        }else if (topPl[j/cifre] == char_p1){
                            printColor(char_p1);
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
                                printColor(char_p1);
                            }else if (topPl[j/cifre] == char_p1){
                                printColor(char_p2);
                            }
                            /* altrimenti stampa il colore del proprietario */
                        }else{
                            if (topPl[j/cifre] == char_p2){
                                printColor(char_p2);
                            }else if (topPl[j/cifre] == char_p1){
                                printColor(char_p1);
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
unsigned int while_select_nPawn(player_t *players,unsigned int nPl){
    unsigned int nPawn;
    printf("Numero di pedina da selezionare : ");
    scanf("%u",&nPawn);

    while(!check_while(players, nPl,nPawn) ){
        unsigned int flag = 1;
        if (nPl == 1 || nPl == 0 ){
            flag = check_canMove(players, nPawn,nPl);
        }
        if(!flag){
            printf("La pedina %u non puo' muoversi!\n",nPawn);
            printf("Numero di pedina da selezionare : ");
            scanf("%u",&nPawn);
        }

    }
    return nPawn;
}
unsigned int round_player(player_t *players,board_t *t,unsigned int nPl){
    char str[10];
    unsigned int num_Pawn = 0;
    int y = -2;

    update_board(t,players);
    print_board(*t,(players[0].pawns[0].dim_label+3)+1,nPl, players[0].color, players[1].color);

    printf("Vuoi uscire dal gioco ? ");
    scanf("%s",str);
    if((!strcmp(str,"si"))||(!strcmp(str,"Si"))||(!strcmp(str,"SI"))){
        return 3;
    }

    num_Pawn = while_select_nPawn(players,nPl);
    printf("Vuoi selezionare questa pedina %u ? ",num_Pawn);
    scanf("%s",str);

    while( (!strcmp(str,"no"))||(!strcmp(str,"NO"))||(!strcmp(str,"No")) ){
        num_Pawn = while_select_nPawn(players,nPl);
        printf("Vuoi selezionare questa pedina %u ? ",num_Pawn);
        scanf("%s",str);
    }

    while(y==-2){
        unsigned int tentativi = 3;
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
            while(!check_directions(players[nPl].pawns[num_Pawn].canMove,index,str) && tentativi != 0){
                printf("Tentativi rimasti prima di selezione un'altra pedina : %u\n",tentativi);
                printf("Verso che direzione vuoi spostare la pedina %u? ",num_Pawn);
                scanf("%s",str);
                --tentativi;
            }
            if(!tentativi){
                y = -3;
            }
        }
        if(nPl == 0 && y != -3){
            y = move_p1(players,num_Pawn,str,t,nPl);
        }
        if(nPl == 1 && y != -3){
            y = move_p2(players, num_Pawn, str, t);
        }
        if(y < -1){
            char temp[2];
            y = -2;
            printf("Seleziona un'altra pedina\n");
            num_Pawn = while_select_nPawn(players,nPl);

            printf("Vuoi selezionare questa pedina %d ? ",num_Pawn);
            scanf("%s",temp);

            while( (!strcmp(str,"no"))||(!strcmp(str,"NO"))||(!strcmp(str,"No")) ){
                num_Pawn = while_select_nPawn(players,nPl);
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
unsigned int round_choice(){
    char str[2];

    printf("Inizia il turno come da predefinito (quindi primo giocatore)? ");
    scanf("%s",str);
    if((!strcmp(str,"si"))||(!strcmp(str,"Si"))||(!strcmp(str,"SI"))){
        return 0;
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

            return npl-1;
        }
        if((!strcmp(str,"si"))||(!strcmp(str,"Si"))||(!strcmp(str,"SI"))){
            int x = 0 ;
            srand(time(NULL));
            while(x == 0){
                x = rand()%10;
            }
            if(x%2 == 0){
                x = 0;
            }else{
                x = 1;
            }
            return x;
        }
    }
    return 0;
}

int game(unsigned int gameMode){
    board_t *t = NULL;
    player_t *players = NULL;
    int isCustom, depth;
    unsigned int exit = 4,turno = 0,round = 0;
    unsigned int cifre,conta = 2,numped = 11;

    srand(time(0));

    if (gameMode){
        printf("\n\tSelect difficulty: \n\n");
        printf(" [0] "GRN"Easy"reset"   (random IA)\n");
        printf(" [1] "YEL"Medium"reset" (low-depth minimax)\n");
        printf(" [2] "RED"Hard"reset"   (high-depth minimax)\n");
        printf(" [3] Custom (custom-depth minimax)\n");
        printf("\n Selection: ");

        scanf("%d", &depth);
        if (depth == 1){
            depth = 5;
            printf(" Selected "YEL"medium"reset".\n");
        }else if(depth == 2){
            depth = 11;
            printf(" Selected "RED"hard"reset".\n");
        }else if (depth == 3){
            printf(" Select depth: ");
            scanf("%d", &depth);
            while(depth%2 == 0 ){
                printf(" Depth deve essere numero dispari\n");
                printf(" Select depth: ");
                scanf("%d", &depth);
            }
        }else{
            depth = 0;
            printf(" Selected"GRN"easy"reset".\n");
        }
    
    }
    
    printf("\n\tSelect gamemode:\n");
    printf(" [0] Classic (11 vs 11, board 7x7)\n");
    printf(" [1] Custom\n");
    printf("\n Selection: ");

    scanf("%d", &isCustom);
    

    if(isCustom == 0){
        t = create_board(7,7,3+conta+1);
        initialize_board(t,3+conta+1);
        players = create_pawns(11,'Y','R',conta,*t); /* create array[2] of player_t type */
    }else{
        unsigned int w,h,max_ped = 0;
        char char_p1, char_p2;
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


            printf("[" RED "R" reset "] [" GRN "G" reset "] ["MAG "M" reset "] ["BLU "B" reset "] ["CYN "C" reset "] ["YEL "Y" reset "]\n");

            printf("Seleziona colore pedina Player1: ");
            scanf("%s", &char_p1);
            if(check_char_color(char_p1) == 2){
                char temp;
                temp = uppercase(char_p1);
                char_p1 = temp;
            }

            printf("Seleziona colore pedina Player2: ");
            scanf("%s", &char_p2);
            if(check_char_color(char_p2) == 2){
                char temp;
                temp = uppercase(char_p2);
                char_p2 = temp;
            }


            while(check_char_color(char_p1)!=1 || check_char_color(char_p2)!=1){
                if(!check_char_color(char_p1) ){
                    printf("Hai sbagliato ad inserire carattere Player 1\n");
                    printf("Seleziona colore pedina Player1: ");
                    scanf("%s", &char_p1);
                }else{
                    if(check_char_color(char_p1) == 2){
                        char temp;
                        temp = uppercase(char_p1);
                        char_p1 = temp;
                    }
                }
                if(!check_char_color(char_p2)){
                    printf("Hai sbagliato ad inserire carattere Player n\n");
                    printf("Seleziona colore pedina Player2: ");
                    scanf("%s", &char_p2);
                }else{
                    printf("%u",check_char_color(char_p2));
                    if(check_char_color(char_p2) == 2){
                        char temp;
                        temp = uppercase(char_p2);
                        char_p2 = temp;
                    }
                }
            }

            players = create_pawns(numped,char_p1, char_p2, conta,*t); /* create array[2] of player_t type */
            print_player(players,0);
            print_player(players,1);

        }else{
            printf("Non ha senso giocare con %u pedine !\n",cifre);
            return 0;
        }
    }

     turno = round_choice();
    printf("Il player che inizia e' %u\n",turno+1);
    while((exit == 4)&&(is_victory(players)>2)){
        set_moves_pawn(players,t,0,-1);
        set_moves_pawn(players,t,1,-1);
        if( all_blocked(players,turno) ){
            unsigned int turno_next = 1;
            if(turno){
                turno_next = 0;
            }
            if(all_blocked(players,turno_next)){
                exit = 2;
            }else{
                exit = turno;
            }
        }
        if(exit == 4){
            printf("Round numero : %u\n",round);
            printTextColor(players[turno].color);
            printf("Turno Player %d\n", turno+1);
            resetColor();
            if (turno == 0 ){
                exit = round_player(players,t,turno);
                turno = 1;
            }else{
                if (gameMode){
                    if (depth == 0){
                        exit = round_ia_random(players, t, turno);
                    }else{
                        exit = round_ia_minimax(players,t,turno, depth);                
                    }                
                }else{            
                    exit = round_player(players,t,turno);
                }
                turno = 0;
            }
            /* print_player(players,0);
            print_player(players,1); */
            update_board(t, players);
            print_board(*t, players[turno].pawns[0].dim_label+1+3, 0, players[0].color, players[1].color);
            /*printMatrix(*t);*/
            sleep(0);
            ++round;
        }
    }
    if(exit == 2){
        printf("Entrambi i giocatori hanno le pedine bloccate\n");
    }
    if(exit == 3){
        printf("Hai abbandonato la partita\n");
    }else{
        if(exit == 1 || exit  == 0){
            ++exit;
        }
        if(exit == 4){
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
    int choice = 0;
    system("clear");
    printf(" #886711 Diego    Passarella\n");
    printf(" #882082 Davide   Pasqual\n");
    printf(" #881493 Michelle Ravagnan\n");
    printf("\n\t+-+-+-+-+-+-+-+-+-+-+-+-+-+\n"
             "\t|M|i|n|i||L|a|s|k|a|  |5|1|\n"
             "\t+-+-+-+-+-+-+-+-+-+-+-+-+-+");
    printf("\n\n [1] Player vs. Player");
    printf("\n [2] Player vs. IA");
    printf("\n [3] Exit");
    while(choice != 1 && choice != 2 && choice != 3){
        printf("\n\n Select mode: ");
        scanf("%d", &choice);
        switch(choice){
            case 1:
                system("clear");
                printf("\nSelected Player vs. Player\n");
                game(0);
                break;
            case 2:
                printf("\nSelected Player vs. IA\n");
                system("clear");
                game(1);
                break;
            case 3:
                system("clear");
                break;
            default:
                printf("\nINVALID SELECTION...Please try again\n");
        };
    }
}