struct campo{
    char **mat;
    int r;
    int c;

};
typedef struct campo tcampo;
struct pedina{
    char et[5];
    char app;
    int cima;
    int numero;
    int grado;
    int r;
    int c;
};
typedef struct pedina tpedina;
struct player{
    tpedina *arr;
    int dim;
};
typedef struct player tplayer;
tcampo *crea_campo(int r,int c); /* creazione matrice */

void inizializza_campo(tcampo *t); /* inizializza matrice come scacchiera*/

void stampa_campo(tcampo t); /* stampa la matrice */

void stampa_campo_inv(tcampo t);/* stampa la matrice invertita */

tplayer *crea_pedine(int n,char ped,int np,tcampo t);/*creazione del giocatore */

void stampa_player(tplayer p); /* stampa pedine di un player */

void aggiorna_campo(tcampo *t,tplayer *p1,tplayer *p2);/* aggiornare posizione pedine sul campo */

int is_pedina(tcampo t,int r,int c);/* trovare se in una certa posizione c'è una pedina*/

int sposta_p1 (tplayer *p1,int np,char *str,tcampo *t,tplayer *p2);/* spostare una pedina pl1 verso un posizione */

int sposta_p2(tplayer *p2,int np,char *str,tcampo *t,tplayer *p1);/* spostare una pedina pl2 verso un posizione */

void togli_pedina(tcampo *t,int r,int c);/* modificare posizione prima di spostare la pedina*/

void aggiungi_pedina(tplayer *p,int np,char ped);/* aggiungere la pedina ped sopra la pedina n. np*/

int mangia_p1(tplayer *p1,tplayer *p2,char *str,int np,tcampo t);/* conquistare una pedina veros una certa posizone*/

int mangia_p2(tplayer *p1,tplayer *p2,char *str,int np,tcampo t);/* conquistare una pedina veros una certa posizone*/

int ricerca_pl(tplayer p1,tplayer p2,int x,int y);/*trovare se una pedina in una posizione è del player 1 o 2*/

int is_victory(tplayer p1,tplayer p2);/* controlla se un giocatore o l'altro ha vinto oppure no*/

int scelta_turno();/* decidere a chi va il primo turno */

int turno_player1(tplayer *p1,tplayer *p2,tcampo *t);/* turno del player 1*/

int turno_player2(tplayer *p1,tplayer *p2,tcampo *t);/* turno del player 2*/
