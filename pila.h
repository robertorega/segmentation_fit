#ifndef PILA_H
#define PILA_H

#include "partecipante.h"
#define MASSIMO_PILA 20 //numero massimo partecipanti

typedef struct c_pila *pila;

/* Funzione: nuova_pila
*
* Crea e inizializza una nuova pila vuota
* Post-condizione:
* Restituisce un puntatore a una pila vuota chiamata iscritti
*
* Side-effect:
* Alloca memoria dinamica per la pila
*/
pila nuova_pila(void);

/* Funzione: pila_vuota
*
* controlla se la pila iscritti è vuota
* Parametri:
* iscritti: pila da controllare
*
* Pre-condizione:
* iscritti è una pila inizializzata
*
* Post-condizione:
* Il valore restituito è 1 se e solo se la pila è vuota (iscritti->testa == 0), altrimenti 0.
*/
int pila_vuota(pila iscritti);

/* Funzione: inserisci_pila
*
* Inserisce un partecipante in cima alla pila iscritti, se la pila non è piena
* Parametri:
* persona: il partecipante da inserire
* iscritti: la pila in cui inserire i partecipanti 
*
* Pre-condizione:
* iscritti è una pila inizializzata 
*
* Post-condizione:
* Restituisce 1 se persona viene copia in cima altrimenti restituisce 0
*
* Side-effect:
* Modifica la pila iscritti incrementando testa e scrivendo in persona[testa].
*/
int inserisci_pila(partecipante val, pila iscritti);

/* Funzione: estrai_pila
*
* Rimuove l’elemento in cima alla pila iscritti, se la pila non è vuota, e lo copia nel partecipante estratto
*
* Parametri:
* iscritti: pila da cui estrarre l’elemento
* estratto: variabile in cui salvare il partecipante rimosso dalla pila (passata per valore)
*
* Pre-condizione:
* iscritti è una pila inizializzata e valida
*
* Post-condizione:
* Se la pila non è vuota, l’elemento in cima viene copiato in estratto e rimosso dalla pila (ritorna 1)
* Se la pila è vuota, estratto rimane inalterato (ritorna 0)
*
* Side-effect:
* iscritti viene modificata: la sua cima viene decrementata e l’elemento rimosso
*/
int estrai_pila(pila iscritti, partecipante estratto);

/* Funzione: testa
*
* Restituisce l’elemento in cima alla pila iscritti senza rimuoverlo
* Parametri:
* iscritti: pila da cui leggere l’elemento in cima
*
* Pre-condizione:
* iscritti deve essere una pila inizializzata e non nulla
*
* Post-condizione:
* se top>0  ritorna un puntatore al partecipante in cima alla pila altrimenti NESSUN_PARTECIPANTE
*/
char* testa(pila iscritti);

/* Funzione: dimensione_pila
*
* Restituisce il numero di elementi attualmente presenti nella pila iscritti
* Parametri:
* iscritti:  pila da analizzare
*
* Pre-condizione:
* iscritti = <a1, a2, ..., an> n>0
*
* Post-condizione:
* Restituisce il numero di partecipanti, se la pila è vuota restituisce return -1
*/
int dimensione_pila(pila iscritti);

#endif
