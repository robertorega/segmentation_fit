#ifndef UTILE_HASH_H
#define UTILE_HASH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "abbonati.h"
#include "hash.h"
#include "partecipante.h"

/* Funzione: carica_abbonati
*
* Carica da file i dati degli abbonati e li inserisce in una nuova tabella hash
*
* Parametri:
* nome_file: nome del file da cui leggere i dati
*
* Pre-condizione:
* nome_file è un puntatore a stringa non nullo
*
* Post-condizione:
* Restituisce una tabella hash inizializzata contenente tutti gli abbonati letti dal file.
* Se il file non esiste, la tabella restituita è vuota.
*
* Side-effect:
* Lettura da file e allocazione dinamica di memoria per ciascun abbonato caricato
*/
tabella_hash carica_abbonati(const char *nome_file);

/* Funzione: salva_abbonati
*
* Salva su file i dati degli abbonati presenti nella tabella hash
*
* Parametri:
* h: tabella hash contenente gli abbonati da salvare
* nome_file: nome del file su cui salvare i dati
*
* Pre-condizione:
* h è una tabella hash valida e nome_file è un puntatore a stringa non nullo
*
* Side-effect:
* Scrittura su file. Se il file non può essere aperto, viene stampato un messaggio di errore
*/
void salva_abbonati(tabella_hash h, const char *nome_file);

#endif
