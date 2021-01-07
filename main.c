#include <stdio.h>
#include <stdlib.h>
#include "supporto.h"
#include <ncurses.h>
#include <string.h>
#include <menu.h>


void fail(char *msg) {
    endwin();
    puts(msg);
    exit(EXIT_FAILURE);
}

int main()
{
    char * choices[]= {"ONE PLAYER","TWO PLAYERS","QUIT"};
    char title[]="LASKA GAME";
    char title_playone[]="One player mode";
    char title_2players[]="Two players mode";
    WINDOW * menuwin;
    int yMax, xMax;
    int i;
    int choice;
    int selected=0;
    initscr();
    raw();
    noecho();
    keypad(stdscr, TRUE);

    /* Test to see if terminal has colors */
    if (start_color() != OK) {
        fail("Unable to start colors\n");
    }

    getmaxyx(stdscr, yMax, xMax);
    move(yMax/2, (xMax-strlen(title))/2); /*moves the cursor at the centre */

    start_color();
    init_pair(1,COLOR_RED, COLOR_GREEN); /*the second attr is the text color, the third one is the background color*/
    attron(COLOR_PAIR(1));
    printw(title);
    attroff(COLOR_PAIR(1));
    refresh();
    menuwin =newwin(7, xMax-12, yMax-9, 6);
    box(menuwin, 0, 0);
    refresh();
    wrefresh(menuwin);
    keypad(menuwin, TRUE);

    while(1)
    {
        for(i = 0; i < 3; i++) {
            if(i == selected)
                wattron(menuwin, A_REVERSE);
            mvwprintw(menuwin, i+1, 1, choices[i]); /*sposta le scritte del menu (finestra, verticale, orizzontale, scritte)*/
            if (i == selected)
                wattroff(menuwin, A_REVERSE);
        }

        choice = wgetch(menuwin);
        switch(choice)
        {
            case KEY_UP:
                selected--;
                if(selected < 0) selected = 0;
                break;
            case KEY_DOWN:
                selected++;
                if(selected > 2) selected = 2;
                break;
            default:
                break;
        }

        if(choice==10){ /* = tasto invio */
            if(selected==0){
                initscr();
                clear();
                refresh();
                mvprintw(yMax/2,(xMax-strlen(title_playone))/2,"%s", title_playone);
                clear();
                refresh();
                player_vs_player(1);
                break;
            }
            if(selected==1){
                initscr();
                clear();
                mvprintw(yMax/2,(xMax-strlen(title_2players))/2,"%s", title_2players);
                break;

            }
            /*if(selected==2){
                initscr();
                clear();
                mvprintw(yMax/2,(xMax-strlen(title_creategame))/2,"%s", title_creategame);
                break;
            }*/
        }
    }

    refresh();
    /* Wait for user to press enter to exit */
    getch();
    /* Need to cleanup before exit */
    endwin();

    return 0;
}

/*
int main()
{







     player_vs_player(1);*/



    /*player_vs_ia();*/

    /*board_t *board;
    player_t *players;

    board = create_board(7,7,6);
    initialize_board(board, 6);

    players = create_pawns(11, 'B', 'N', 2, *board);

    update_board(board, players);

    print_player(players[0]);
    print_player(players[1]);

    print_board(*board, 6, 0);*/
/*  tcampo *board;

    tplayer *p1;
    tplayer *p2;
    board = create_board(7, 7, 6);
    initialize_board(board, 6);
    p1 = create_pawns(11, 'B', 1, 2, *board);
    p2 = create_pawns(11, 'N', 2, 2, *board);

    update_board(board, *p1, *p2);

    set_moves_pawn(p1, p2, *board, 1);
    set_moves_pawn(p1, p2, *board, 2);

    print_board(*board, 6, 1);

    print_player(*p1);
    printf("\n");
    print_player(*p2);

    destroy_board(board);
    destroy_player(p1);
    destroy_player(p2); */

/*

    return 0;
}*/

