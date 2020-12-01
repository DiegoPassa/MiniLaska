//
// Created by Matteo on 28/11/2020.
//

#ifndef UNTITLED_SUPPORTO_H
#define UNTITLED_SUPPORTO_H
struct campo{
    char **mat;
    unsigned int r;
    unsigned int c;

};
typedef struct campo tcampo;
struct pedina{
    char *et ;
    char app;
    unsigned int dim;
    unsigned int cima;
    unsigned int numero;
    unsigned int grado;
    unsigned int r;
    unsigned int c;
};
typedef struct pedina tpedina;
struct player{
    tpedina *arr;
    unsigned int dim;
};
typedef struct player tplayer;
tcampo *crea_campo(unsigned int r,unsigned int c,unsigned int cifre); /* creazione matrice */

void inizializza_campo(tcampo *t,unsigned int cifre); /* inizializza matrice come scacchiera*/

void stampa_campo(tcampo t,unsigned int cifre); /* stampa la matrice */

void stampa_campo_inv(tcampo t,unsigned int cifre);/* stampa la matrice invertita */

tplayer *crea_pedine(unsigned int n,char ped,unsigned int np,unsigned int cifre,tcampo t);/*creazione del giocatore */

void stampa_player(tplayer p); /* stampa pedine di un player */

void aggiorna_campo(tcampo *t,tplayer p1,tplayer p2);/* aggiornare posizione pedine sul campo */

unsigned int is_pedina(tcampo t,unsigned int r,unsigned int c,unsigned int cifre);/* trovare se in una certa posizione c'è una pedina*/

unsigned int sposta_p1 (tplayer *p1,unsigned int np,char *str,tcampo *t,tplayer *p2);/* spostare una pedina pl1 verso un posizione */

unsigned int sposta_p2(tplayer *p2,unsigned int np,char *str,tcampo *t,tplayer *p1);/* spostare una pedina pl2 verso un posizione */

void togli_pedina(tcampo *t,unsigned int r,unsigned int c,unsigned int cifre);/* modificare posizione prima di spostare la pedina*/

void aggiungi_pedina(tplayer *p,unsigned int np,char ped);/* aggiungere la pedina ped sopra la pedina n. np*/

unsigned int mangia_p1(tplayer *p1,tplayer *p2,char *str,unsigned int np,tcampo t);/* conquistare una pedina veros una certa posizone*/

unsigned int convert(tcampo t,unsigned int r,unsigned int c,unsigned int dim);/* converte il numero in da char ad int */

unsigned int mangia_p2(tplayer *p1,tplayer *p2,char *str,unsigned int np,tcampo t);/* conquistare una pedina veros una certa posizone*/

unsigned int ricerca_pl(tplayer p1,tplayer p2,unsigned int x,unsigned int y);/*trovare se una pedina in una posizione è del player 1 o 2*/

unsigned int is_victory(tplayer p1,tplayer p2);/* controlla se un giocatore o l'altro ha vinto oppure no*/

unsigned int scelta_turno();/* decidere a chi va il primo turno */

unsigned int turno_player1(tplayer *p1,tplayer *p2,tcampo *t);/* turno del player 1*/

unsigned int turno_player2(tplayer *p1,tplayer *p2,tcampo *t);/* turno del player 2*/
#endif //UNTITLED_SUPPORTO_H
