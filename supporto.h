struct campo
{
    char **mat;
    unsigned int r;
    unsigned int c;
};
typedef struct campo tcampo;
struct pedina
{
    char *et; /* etichetta della pedina Es.|  BN07 | */
    unsigned int dim;
    unsigned int cima;
    unsigned int grado;
    unsigned int r;
    unsigned int c;
    unsigned int isPromoted; /* Es: |  BN07^ | */
};
typedef struct pedina tpedina;
struct player
{
    char colore;
    tpedina *arr;
    unsigned int dim;
};
typedef struct player tplayer;

tcampo* crea_campo(unsigned int r,unsigned int c,unsigned int cifre); /* creazione matrice */

void inizializza_campo(tcampo *t,unsigned int cifre); /* inizializza matrice come scacchiera*/

void stampa_campo(tcampo t,unsigned int cifre,unsigned int npl); /* stampa la matrice  cambiando visuale in base al player*/

tplayer *crea_pedine(unsigned int n,char ped,unsigned int np,unsigned int cifre,tcampo t);/*creazione del giocatore */

void stampa_player(tplayer p); /* stampa pedine di un player */

void stampa_dir(unsigned int *arr,unsigned int dim,unsigned int np);/* stampa le direzioni che devo fare per la mangiata obbligatoria*/

void aggiorna_campo(tcampo *t,tplayer p1,tplayer p2);/* aggiornare posizione pedine sul campo */

int can_eat(tplayer *p1,unsigned int np,char *str,tcampo *t,tplayer *p2,unsigned int pl);/* controlli prima di mangiare un'altra pedina */

unsigned int *obl_eat(tplayer p1,tplayer p2,tcampo t,unsigned int np,unsigned int npl);/* mangiata obbligatoria*/

unsigned int contr_dir(unsigned int *arr,unsigned int dim,char *str);/* confronta la stringa con le direzioni obbligatorie*/

unsigned int move_noeat(tplayer *p1,unsigned int np,char *str,tcampo *t,tplayer *p2,unsigned int pl);/*si muove la pedina senza mangiare*/

unsigned int is_in(int r,int c,tcampo t);/*controlla se le coordinate sono all'interno della matrice*/

unsigned int is_pedina(tcampo t,unsigned int r,unsigned int c,unsigned int cifre);/* trovare se in una certa posizione c'è una pedina*/

int is_empty(tplayer p);/* controllare se l'array ha pedina con grado 0*/

unsigned int is_sel(tplayer p1,tplayer p2,unsigned int np,unsigned int npl);/* controlla se la pedina np si può selezionare*/

unsigned int max_pedine(unsigned int r,unsigned int c);/* calccolare il numero di pedine che si possono mettere in una matrice dimensione rxc */

unsigned int ped_noblock(tplayer p1,tplayer p2,tcampo t,unsigned int nped,unsigned int npl);/*determinare se la pedina è bloccata o no*/

tcampo* campo_copy(tcampo t ,tcampo *new);/*creare un nuovo campo copiando dalla variabile t */

tplayer* player_copy(tplayer p,tplayer *n,unsigned int cifre);/* creare un nuovo player copiando da player p già esistente*/

unsigned int controllo_pedina(tplayer *p,tplayer *p2,unsigned int np);/* aggiunge una pedina all'altro player in base alla pedina mangiata*/

unsigned int sposta_p1 (tplayer *p1,unsigned int np,char *str,tcampo *t,tplayer *p2,unsigned int pl);/* spostare una pedina pl1 verso un posizione */

unsigned int sposta_p2(tplayer *p2,unsigned int np,char *str,tcampo *t,tplayer *p1);/* spostare una pedina pl2 verso un posizione */

void togli_pedina(tcampo *t,unsigned int r,unsigned int c,unsigned int cifre);/* modificare posizione prima di spostare la pedina*/

void promuovi_pedina(tplayer *p,unsigned int np,unsigned int numpl,unsigned int meta);/* promozione di una pedina*/

unsigned int mangia(tplayer *p1,tplayer *p2,char *str,unsigned int np,tcampo t,unsigned int num,unsigned int npl);/* conquistare una pedina veros una certa posizone*/

unsigned int convert(tcampo t,unsigned int r,unsigned int c,unsigned int dim,unsigned int cifre);/* converte il numero in da char ad int */

unsigned int ricerca_pl(tplayer p1,tplayer p2,unsigned int x,unsigned int y);/*trovare se una pedina in una posizione è del player 1 o 2*/

unsigned int is_victory(tplayer p1,tplayer p2,tcampo t);/* controlla se un giocatore o l'altro ha vinto oppure no*/

unsigned int all_block(tplayer p1,tplayer p2,tcampo t,unsigned int npl);/* controlla se tutte le pedine sono bloccate o no */

unsigned int scelta_turno();/* decidere a chi va il primo turno */

unsigned int turno_player(tplayer *p1,tplayer *p2,tcampo *t,unsigned int npl);/* turno dei vari  player */

int player_vs_player(unsigned int x );/* modalità giocatore vs giocatore */

unsigned int ia(tplayer *p,tcampo *t);

int minimax();

void player_vs_ia();

void destroy_player (tplayer *p); /* liberare spazio di memoria allocata da player*/

void destroy_campo(tcampo *t);/* liberare spazio di memoria allocata da campo*/