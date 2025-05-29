#ifndef PILA_H
#define PILA_H

#include "partecipante.h"
#define MASSIMO_PILA 20 // Capacità massima della pila

typedef struct c_pila *pila;

/* Funzione: nuova_pila
*
* Crea e inizializza una nuova pila vuota
*
* Post-condizione:
* Restituisce un puntatore a una pila vuota chiamata iscritti
*
* Side-effect:
* Alloca memoria dinamica per la pila
*/
pila nuova_pila(void);

/* Funzione: pila_vuota
*
* Controlla se la pila iscritti è vuota
*
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
*
* Parametri:
* persona: il partecipante da inserire
* iscritti: la pila in cui inserire i partecipanti 
*
* Pre-condizione:
* iscritti è una pila inizializzata 
*
* Post-condizione:
* Restituisce 1 se il partecipante viene copiato in cima altrimenti restituisce 0
*
* Side-effect:
* Modifica la pila iscritti incrementando testa e scrivendo in vet[testa].
*/
int inserisci_pila(partecipante val, pila iscritti);

/* Funzione: estrai_pila
*
* Estrae l'elemento in cima alla pila iscritti, se presente
*
* Parametri:
* iscritti: pila da cui estrarre il partecipante
* estratto: array di caratteri dove verrà copiato il partecipante rimosso dalla cima
*
* Pre-condizione:
* iscritti è una pila inizializzata e `estratto` è una variabile di tipo partecipante
*
* Post-condizione:
* Se la pila contiene almeno un elemento, `estratto` conterrà una copia del partecipante in cima
* e la funzione restituirà 1. Se la pila è vuota, `estratto` non sarà modificato e la funzione restituirà 0.
*
* Side-effect:
* Modifica la pila decrementando `testa`
*/
int estrai_pila(pila iscritti, partecipante estratto);

/* Funzione: testa
*
* Restituisce l’elemento in cima alla pila iscritti senza rimuoverlo
*
* Parametri:
* iscritti: pila da cui leggere l’elemento in cima
*
* Pre-condizione:
* iscritti deve essere una pila inizializzata e non nulla
*
* Post-condizione:
* se iscritti->testa>0  ritorna un puntatore al partecipante in cima alla pila altrimenti NESSUN_PARTECIPANTE
*/
char* testa(pila iscritti);

/* Funzione: dimensione_pila
*
* Restituisce il numero di elementi attualmente presenti nella pila iscritti
*
* Parametri:
* iscritti:  pila da analizzare
*
* Pre-condizione:
* iscritti è una pila inizializzata (può essere vuota)
*
* Post-condizione:
* Se iscritti == NULL ritorna -1, altrimenti ritorna iscritti->testa (che può essere 0 se vuota)
*/
int dimensione_pila(pila iscritti);

#endif
