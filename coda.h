#ifndef CODA_H
#define CODA_H

#include "abbonati.h"
#include "lezione.h"
#define ELEMENTO_NULLO ((lezione){ NULL, "", "", "" }) // Lezione nulla/vuota

typedef struct c_coda *coda;

/* Funzione: nuova_coda
*
* Crea e inizializza una nuova coda vuota
*
* Post-condizione:
* - Restituisce un puntatore a una coda vuota chiamata 'calendario'
*
* Side-effect:
* - Alloca memoria dinamica per la coda
*/
coda nuova_coda(void);

/* Funzione: coda_vuota
*
* Verifica se la coda calendario è vuota
*
* Parametri:
* calendario: la coda da controllare
*
* Pre-condizione:
* - 'calendario' deve essere una coda valida e inizializzata
*
* Post-condizione:
* - Restituisce 1 se la coda è vuota, 0 se contiene elementi, -1 se la coda è NULL
*/
int coda_vuota(coda calendario);

/* Funzione: inserisci_lezione
*
* Inserisce una nuova lezione in fondo alla coda calendario
*
* Descrizione:
* La funzione alloca dinamicamente un nuovo nodo contenente la lezione da inserire
* Se la coda è vuota imposta il nuovo nodo come testa della coda
* Altrimenti lo collega in fondo alla coda esistente
* In entrambi i casi aggiorna il puntatore alla coda e incrementa il numero di elementi
* Restituisce 1 in caso di successo 0 se l'allocazione fallisce -1 se la coda è NULL
*
* Parametri:
* val: la lezione da inserire
* calendario: la coda dove aggiungere la lezione
*
* Pre-condizione:
* - 'calendario' deve essere una coda inizializzata
*
* Post-condizione:
* - Restituisce 1 se l’inserimento è riuscito, 0 se fallisce per allocazione, -1 se la coda è NULL
*
* Side-effect:
* - Modifica la coda calendario aggiungendo un nodo in fondo e incrementando il numero di elementi
*/
int inserisci_lezione(lezione val, coda calendario);

/* Funzione: rimuovi_lezione
*
* Rimuove e restituisce la prima lezione presente nella coda calendario
*
* Parametri:
* calendario: la coda da cui rimuovere la lezione
*
* Pre-condizione:
* - 'calendario' deve essere una coda inizializzata e non vuota
*
* Post-condizione:
* - Se la coda è vuota restituisce ELEMENTO_NULLO, altrimenti restituisce la lezione rimossa
*
* Side-effect:
* - Modifica la coda rimuovendo il primo nodo e aggiornando testa e numero di elementi
*/
lezione rimuovi_lezione(coda calendario);

#endif
