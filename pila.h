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
* Rimuove l’elemento in cima alla pila iscritti, se la pila non è vuota
* Parametri:
* iscritti: la pila in cui rimuovere i partecipanti 
*
* Pre-condizione:
* iscritti è una pila inizializzata 
*
* Post-condizione:
* se iscritti->testa == 0 allora result 0 altrimenti result 1
*
* Side-effect:
* iscritti = <a2, …, an>
*/
int estrai_pila(pila iscritti);

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

/*
 * Funzione: disdici_iscrizione
 *
 * Permette di disiscrivere un partecipante da una lezione specifica, selezionata tramite indice da un calendario
 *
 * Parametri:
 * - calendario: array di strutture lezione, ognuna contenente una pila di iscritti
 * - numero_lezioni: numero totale di lezioni presenti nel calendario
 *
 * Pre-condizione:
 * - iscritti è una pila inizializzata
 * - nome deve essere presente nella pila
 * 
 * Post-condizione:
 * - 1 se il partecipante è stato trovato e rimosso
 * - 0 se il partecipante non è presente nella pila
 *
 * Side-effect:
 * - modifica la pila iscritti
 * - libera la memoria della pila di supporto
 */
int disdici_iscrizione(lezione* calendario, int numero_lezioni, const char* lezioni);

#endif
