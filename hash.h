#ifndef HASH_H
#define HASH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "abbonati.h"
#include "partecipante.h"

typedef struct c_hash *tabella_hash;

// Funzioni per la gestione della tabella hash
/* Funzione: nuova_hash
*
* Crea e inizializza una nuova tabella hash
* Parametri:
* dimensione: numero di slot nella tabella hash
*
* Pre-condizione:
* dimensione>0
*
* Post-condizione:
* Restituisce una tabella hash con i puntatori inizializzati a 0
*
* Side-effect:
* Alloca memoria dinamica per la nuova tabella hash
*/
tabella_hash nuova_hash(int dimensione);

/* Funzione: calcola_indice
*
* Calcola l'indice nella tabella hash associato alla stringa chiave
* Parametri:
* chiave: la stringa di cui si vuole calcolare l'indice 
* dimensione: numero di slot nella tabella hash
*
* Pre-condizione:
* chiave è una stringa non nulla che termina con \0 e dimensione>0
*
* Post-condizione:
* 0<=indice<dimensione (l'indice denota quale slot della tabella andare a leggere o scrivere)
*/
int calcola_indice(char *chiave, int dimensione);

/* Funzione: inserisci_hash
*
* Inserisce un nuovo elemento (nuovo) nella tabella hash h
* Parametri:
* nuovo: elemento da inserire (contiene: chiave, nomeutente, password)
* h: tabella hash in cui inserire l'oggetto
*
* Pre-condizione:
* nuovo.chiave è una stringa non vuota, h deve essere una tabella hash valida
*
* Post-condizione:
* se nuovo.chiave non è presente nella tabella, viene inserito un nuovo nodo.                                 
* Altrimenti la tabella rimane invariata
*
* Side-effect:
* Viene allocata memoria dinamicamente per un nuovo nodo e duplicata la chiave.
*/
tabella_hash inserisci_hash(abbonato item, tabella_hash tabella);

/* Funzione: cerca_hash
* Cerca nella tabella hash h un elemento con chiave uguale a chiave e lo restituisce se trovato
* 
* Parametri:
* chiave: elemento da cercare nella tabella 
* h: tabella hash in cui si cerca l'elemento
*
* Pre-condizione:
* chiave è una stringa non vuota e h è una tabella hash valida
*
* Post-condizione:
* restituisce l'elemento se presente nella tabella, altrimenti NULL
*/
abbonato *cerca_hash(char *chiave, tabella_hash tabella);


/* Funzione: carica_abbonati
*
* Carica da file i dati degli abbonati e li inserisce in una nuova tabella hash
*
* Parametri:
* filename: nome del file da cui leggere i dati
*
* Pre-condizione:
* filename è un puntatore a stringa non nullo
*
* Post-condizione:
* Restituisce una tabella hash inizializzata contenente tutti gli abbonati letti dal file.
* Se il file non esiste, la tabella restituita è vuota.
*
* Side-effect:
* Lettura da file e allocazione dinamica di memoria per ciascun abbonato caricato
*/
tabella_hash carica_abbonati(const char *filename);

/* Funzione: salva_abbonati
*
* Salva su file i dati degli abbonati presenti nella tabella hash
*
* Parametri:
* h: tabella hash contenente gli abbonati da salvare
* filename: nome del file su cui salvare i dati
*
* Pre-condizione:
* h è una tabella hash valida e filename è un puntatore a stringa non nullo
*
* Post-condizione:
* Se il file è accessibile in scrittura, i dati degli abbonati sono salvati correttamente
*
* Side-effect:
* Scrittura su file. Se il file non può essere aperto, viene stampato un messaggio di errore
*/
void salva_abbonati(tabella_hash h, const char *filename);

#endif
