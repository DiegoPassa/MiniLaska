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
    printf(" +");
    for(z = 0 ; z < cifre+2; ++z){ /* 2 = spazio a destra e sinistra */
        printf("-");
    }
    for(j=1; j<t.n_cols-cifre; j +=cifre){
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
                if (j == 0){
                    printf(" |");
                }else{
                    printf("|");
                }
                
                /* stampa le torri */
                if (cime[j/cifre]==l){
                    if (topPl[j/cifre] == char_p2 || topPl[j/cifre] == char_p1){                
                        printf(BLK"");
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
                        printf(reset"");
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
                        printf(reset"");
                    }    /* stampa le caselle bianche */
                    else if (topPl[j/cifre] == '#' || (cime[j/cifre]!=3)){
                        setWhite();
                        for(z = 0 ; z < cifre+2; ++z){
                            printf(" ");
                        }
                        printf(reset"");
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
            printf(" |");
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
    printf(" +");
    for(z = 0 ; z < cifre+2 ; ++z){
        printf("-");
    }
    for(j=1; j<t.n_cols-cifre; j +=cifre){
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

void print_player(player_t *players, unsigned int nPl){
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
    int scanfValue ;
    printf(" Select no. pawn to move : ");

    printTextColor(players[nPl].color);
    scanfValue = scanf("%u", &nPawn);
    if (scanfValue != 1) nPawn = checkInt(scanfValue);
    printf(reset);

    while(!check_while(players, nPl,nPawn) ){
        unsigned int flag = 1;
        if (nPl == 1 || nPl == 0 ){
            flag = check_canMove(players, nPawn,nPl);
        }
        if(!flag){
            printf(" Pawn no. %u is unable to move!\n",nPawn);
            printf(" Select no. pawn to move : ");
            printTextColor(players[nPl].color);
            scanfValue = scanf("%u", &nPawn);
            if (scanfValue != 1) nPawn = checkInt(scanfValue);
            printf(reset);
        }

    }
    return nPawn;
}

unsigned int round_player(player_t *players, board_t *t, unsigned int nPl){
    char str[10];
    unsigned int num_Pawn = 0;
    int y = -2;

    update_board(t,players);
    print_board(*t,(players[0].pawns[0].dim_label+3)+1,nPl, players[0].color, players[1].color);

    printf(" Surrender? (y/n): ");
    printTextColor(players[nPl].color);
    scanf("%s",str);
    printf(reset);
    if((!strcmp(str,"y"))||(!strcmp(str,"yes"))||(!strcmp(str,"Y"))||(!strcmp(str,"YES"))){
        return 3;
    }

    num_Pawn = while_select_nPawn(players,nPl);
    printf(" Confirm selection? (y/n): ");
    printTextColor(players[nPl].color);
    scanf("%s",str);
    printf(reset);

    while((!strcmp(str,"n"))||(!strcmp(str,"NO"))||(!strcmp(str,"No")) ||(!strcmp(str,"no"))){
        num_Pawn = while_select_nPawn(players,nPl);
        printf(" Confirm selection? (y/n): ");
        printTextColor(players[nPl].color);
        scanf("%s",str);
        printf(reset);
    }

    while(y==-2){
        unsigned int tentativi = 3;
        if(nPl == 1 || nPl == 0 ){
            unsigned int index = 2;
            players[nPl].pawns[num_Pawn].isPromoted ? index = 4 : index;
            print_directions(players[nPl].pawns[num_Pawn].canMove,index,num_Pawn);
        }
        printf(" Which direction you want to move? ");
        printTextColor(players[nPl].color);
        scanf("%s",str);
        printf(reset);
        if(nPl == 1 || nPl == 0){
            unsigned int index = 2;
            players[nPl].pawns[num_Pawn].isPromoted ? index = 4 : index;
            while(!check_directions(players[nPl].pawns[num_Pawn].canMove,index,str) && tentativi != 0){
                printf(" Number of attempts remained : %u\n",tentativi);
                printf(" Which direction you want to move? ");
                printTextColor(players[nPl].color);
                scanf("%s",str);
                printf(reset);
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
            printf(" Select another pawn..\n");
            num_Pawn = while_select_nPawn(players,nPl);

            printf(" Confirm selection? (y/n): ");
            printTextColor(players[nPl].color);
            scanf("%s",temp);
            printf(reset);

            while((!strcmp(str,"no"))||(!strcmp(str,"NO"))||(!strcmp(str,"No"))){
                num_Pawn = while_select_nPawn(players,nPl);
                printf(" Confirm selection? (y/n): ");
                printTextColor(players[nPl].color);
                scanf("%s",str);
                printf(reset);
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
    int scanfValue;
    char str[2];

    printf(" Start as first player? (y/n): ");
    printf(YEL);
    scanf("%s",str);
    printf(reset);
    if((!strcmp(str,"y"))||(!strcmp(str,"yes"))||(!strcmp(str,"Y"))||(!strcmp(str,"YES"))){
        return 0;
    }else{
        printf(" Flip coin (y/n): ? ");
        printf(YEL);
        scanf("%s",str);
        printf(reset);
        if((!strcmp(str,"n"))||(!strcmp(str,"NO"))||(!strcmp(str,"No")) ||(!strcmp(str,"no"))){
            unsigned int npl = 0;
            printf(" Which player goes first? (1/2): ");
            printf(YEL);
            scanfValue = scanf("%u", &npl);
            if (scanfValue != 1){
                npl = checkInt(scanfValue);
            }
            printf(reset);
            while(npl != 1 && npl != 2){
                printf(" Invalid input..\n Which player goes first? (1/2): ");
                printf(YEL);
                scanfValue = scanf("%u", &npl);
                if (scanfValue != 1){
                    npl = checkInt(scanfValue);
                }
                printf(reset);
            }

            return npl-1;
        }
        if((!strcmp(str,"y"))||(!strcmp(str,"yes"))||(!strcmp(str,"Y"))||(!strcmp(str,"YES"))){
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
    int isCustom = 3, depth;
    unsigned int exit = 4,turno = 0,round = 0;
    unsigned int cifre,conta = 2,numped = 11;
    int scanfValue;

    srand(time(0));

    if (gameMode){
        printf("\n\t"MAG"Select difficulty:"reset" \n\n");
        printf(" ["YEL"1"reset"] "GRN"Easy"reset"   (random IA)\n");
        printf(" ["YEL"2"reset"] "YEL"Medium"reset" (low-depth minimax)\n");
        printf(" ["YEL"3"reset"] "RED"Hard"reset"   (high-depth minimax)\n");
        printf(" ["YEL"4"reset"] "CYN"Custom"reset" (custom-depth minimax)\n");
        printf("\n Selection: ");

        printf(YEL);
        scanfValue = scanf("%d", &depth);
        if (scanfValue != 1) depth = checkInt(scanfValue);
        printf(reset);
        while (depth > 4 || depth < 1){
            printf("\n Invalid selection.. try again: ");
            printf(YEL);
            scanfValue = scanf("%d", &depth);
            if (scanfValue != 1) depth = checkInt(scanfValue);
            printf(reset);
        }
        
        if (depth == 2){
            depth = 5;
            printf(" Selected "YEL"medium"reset".\n");
        }else if(depth == 3){
            depth = 11;
            printf(" Selected "RED"hard"reset".\n");
        }else if (depth == 4){
            printf(" Select depth: ");
            printf(YEL);
            scanfValue = scanf("%d", &depth);
            if (scanfValue != 1) depth = checkInt(scanfValue);
            printf(reset);
            while(depth%2 == 0 ){
                printf(" Depth must to be an odd number\n");
                printf(" Select depth: ");
                printf(YEL);
                scanfValue = scanf("%d", &depth);
                if (scanfValue != 1) depth = checkInt(scanfValue);
                printf(reset);
            }
        }else{
            depth = 0;
            printf(" Selected "GRN"easy"reset".\n");
        }
    
    }
    
    printf("\n\t"MAG"Select gamemode:"reset"\n\n");
    printf(" ["YEL"1"reset"] Classic (11 vs 11, board 7x7)\n");
    printf(" ["YEL"2"reset"] Custom\n");
    printf("\n Selection: ");


    while (isCustom != 1 && isCustom != 2){
        printf(YEL);
        scanfValue = scanf("%d", &isCustom);
        if (scanfValue != 1) isCustom = checkInt(scanfValue);
        printf(reset);
    }
    
    if(isCustom == 1){
        t = create_board(7,7,3+conta+1);
        initialize_board(t,3+conta+1);
        players = create_pawns(11,'Y','R',conta,*t); /* create array[2] of player_t type */
    }else{
        unsigned int w,h,max_ped = 0;
        char char_p1, char_p2;
        conta = 0;
        printf("\n Board height : ");

        printf(YEL);
        scanfValue = scanf("%u", &h);
        if (scanfValue != 1) h = checkInt(scanfValue);
        printf(reset);

        printf(" Board width : ");

        printf(YEL);
        scanfValue = scanf("%u", &w);
        if (scanfValue != 1) w = checkInt(scanfValue);
        printf(reset);

        while(w < 3 || h < 3){
            printf(" The board must be high and wide at least 3\n");
            printf(" Reselect board size.. \n");
            printf(" Board height : ");
            printf(YEL);
            scanfValue = scanf("%u", &h);
            if (scanfValue != 1) h = checkInt(scanfValue);
            printf(reset);

            printf(" Board width : ");
            printf(YEL);
            scanfValue = scanf("%u", &w);
            if (scanfValue != 1) w = checkInt(scanfValue);
            printf(reset);
        }
        max_ped = max_pawns(h,w);
        printf(" %u is the maximum number of pawns\n",max_ped);
        printf(" Select number of pawns : ");
        printf(YEL);
        scanfValue = scanf("%u", &cifre);
        if (scanfValue != 1) cifre = checkInt(scanfValue);
        printf(reset);
        while(cifre > max_ped){
            printf(" Reselect number of pawns : ");
            printf(YEL);
            scanfValue = scanf("%u", &cifre);
            if (scanfValue != 1) cifre = checkInt(scanfValue);
            printf(reset);
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


            printf("\n [" BLK REDB" R " reset "] ["BLK YELB" Y " reset "] ["BLK GRNB" G " reset "] ["BLK CYNB" C " reset "] ["BLK BLUB" B " reset "] ["BLK MAGB" M " reset "]\n");

            printf(" Choose player 1 pawn color: ");
            printf(YEL);
            scanf("%s", &char_p1);
            printf(reset);
            if(check_char_color(char_p1) == 2){
                char temp;
                temp = uppercase(char_p1);
                char_p1 = temp;
            }

            printf(" Choose player 2 pawn color: ");
            printf(YEL);
            scanf("%s", &char_p2);
            printf(reset);
            if(check_char_color(char_p2) == 2){
                char temp;
                temp = uppercase(char_p2);
                char_p2 = temp;
            }

            while(check_char_color(char_p1)!=1 || check_char_color(char_p2)!=1){
                if(!check_char_color(char_p1) ){
                    printf(" Invalid input.. \n Choose another color for player 1's pawns: ");
                    printf(YEL);
                    scanf("%s", &char_p1);
                    printf(reset);
                }else{
                    if(check_char_color(char_p1) == 2){
                        char temp;
                        temp = uppercase(char_p1);
                        char_p1 = temp;
                    }
                }
                if(!check_char_color(char_p2)){
                    printf(" Invalid input.. \n Choose another color for player 2's pawns: ");
                    printf(YEL);
                    scanf("%s", &char_p2);
                    printf(reset);
                }else{
                    printf("%u",check_char_color(char_p2));
                    if(check_char_color(char_p2) == 2){
                        char temp;
                        temp = uppercase(char_p2);
                        char_p2 = temp;
                    }
                }
            }

            players = create_pawns(numped,char_p1, char_p2, conta,*t);

        }else{
            printf(" It doesn't have any sense playing with %d pawns",cifre);
            return 0;
        }
    }

    turno = round_choice();
    printf("\n Starting player is %u\n",turno+1);
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
            printf(" Round number : %u\n",round);
            printTextColor(players[turno].color);
            printf(" Player %d turn\n", turno+1);
            printf(reset);
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
            sleep(0);
            ++round;
        }
    }
    if(exit == 2){
        printf(" Both players are unable to move\n");
    }
    if(exit == 3){
        printf(" You left the game\n");
        sleep(3);
        system("clear");
    }else{
        if(exit == 1 || exit  == 0){
            ++exit;
        }
        if(exit == 4){
            exit = is_victory(players);
        }
        printf(" Total rounds : %u\n",round);
        printf(" Player %d won!\n",exit);
    }

    destroy_board(t);
    destroy_player(players);

    return 1;
}

int checkInt(int scanfValue){
    int value;
    while(scanfValue != 1)
    {
        printf(RED" Please enter an integer: ");
        printf(YEL);
        while(getchar() != '\n');
        scanfValue = scanf("%d",&value);
        printf(reset);
    }
    return value;
}

void menu(){
    int choice = 0;
    system("clear");
    printf(" #886711 Diego    Passarella\n");
    printf(" #882082 Davide   Pasqual\n");
    printf(" #881493 Michelle Ravagnan\n");
    printf("\n +-+-+-+-+-+-+-+-+-+-+-+-+-+\n"
             " |"RED"M"reset"|"YEL"i"reset"|"GRN"n"reset"|"CYN"i"reset"| |"BLU"L"reset"|"MAG"a"reset"|"RED"s"reset"|"YEL"k"reset"|"GRN"a"reset"| |"CYN"5"reset"|"BLU"1"reset"|\n"
             " +-+-+-+-+-+-+-+-+-+-+-+-+-+\n");
             
    printf("\n ["YEL"1"reset"] Player vs. Player");
    printf("\n ["YEL"2"reset"] Player vs. IA");
    printf("\n ["YEL"3"reset"] Exit");
    while(choice != 1 && choice != 2 && choice != 3){
        int scanfValue;
        printf("\n\n Select mode: "YEL);
        scanfValue = scanf("%d", &choice);
        if (scanfValue != 1) choice = checkInt(scanfValue);
        switch(choice){
            case 1:
                system("clear");
                printf("\n Selected Player vs. Player\n");
                game(0);
                break;
            case 2:
                system("clear");
                printf("\n Selected Player vs. IA\n");
                game(1);
                break;
            case 3:
                system("clear");
                break;
            default:
                printf("\n INVALID SELECTION...Please try again\n");
        };
    }
}