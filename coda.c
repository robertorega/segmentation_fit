#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "coda.h"
#include "lezione.h"
#include "hash.h"

// Nodo della coda
struct nodo
{
	lezione valore;
	struct nodo *prossimo;
};

// Struttura della coda
struct c_coda
{
	struct nodo *testa,*coda;
	int numel;
};

/* Funzione: nuova_coda
*
* Crea e inizializza una nuova coda vuota
*
* Descrizione:
* La funzione alloca dinamicamente memoria per una struttura di tipo c_coda
* Inizializza il numero di elementi a zero e i puntatori testa e coda a NULL
* Restituisce un puntatore alla nuova coda vuota creata
*
* Post-condizione:
* - Restituisce un puntatore a una coda vuota chiamata 'calendario'
*
* Side-effect:
* - Alloca memoria dinamica per la coda
*/
coda nuova_coda(void)
{
	// Alloca la struttura principale
	struct c_coda *calendario;
	calendario = malloc(sizeof(struct c_coda));
	if (calendario == NULL)
		return NULL;

	// Inizializza i campi
	calendario->numel = 0;
	calendario->testa = NULL;
	calendario->coda = NULL;
	return calendario;
}

/* Funzione: coda_vuota
*
* Verifica se la coda calendario è vuota
*
* Descrizione:
* La funzione controlla se il puntatore alla coda è NULL
* In tal caso restituisce -1 per segnalare un errore
* Altrimenti restituisce 1 se la coda è vuota o 0 se contiene elementi
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
int coda_vuota(coda calendario)
{
	// Controllo parametro NULL
	if (calendario == NULL)
		return -1;
	return calendario->numel == 0;
}

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
int inserisci_lezione(lezione val, coda calendario)
{ 
	if (calendario == NULL)
		return -1;

	// Crea nuovo nodo
	struct nodo *nuovo;
	nuovo = malloc(sizeof(struct nodo));
	if (nuovo == NULL)
		return 0;

	// Inizializza nodo
	nuovo->valore = val;
	nuovo->prossimo = NULL;

	// Inserimento in coda
	if (calendario->testa == NULL)
    		calendario->testa = nuovo;
	else
    		calendario->coda->prossimo = nuovo;

	// Aggiorna puntatore coda e contatore
	calendario->coda = nuovo;
	(calendario->numel)++;
	return 1;
}

/* Funzione: rimuovi_lezione
*
* Rimuove e restituisce la prima lezione presente nella coda calendario
*
* Descrizione:
* La funzione controlla se la coda è NULL o vuota e in tal caso restituisce ELEMENTO_NULLO
* Altrimenti salva la lezione del primo nodo, aggiorna il puntatore alla testa
* Dealloca il nodo rimosso e aggiorna il numero di elementi nella coda
* Se la coda diventa vuota aggiorna anche il puntatore alla coda
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
lezione rimuovi_lezione(coda calendario)
{
	// Controllo coda vuota o NULL
	if (calendario == NULL)
		return ELEMENTO_NULLO;
	if (calendario->numel == 0)
        	return ELEMENTO_NULLO; 

	lezione risultato = calendario->testa->valore; // Salva il valore da restituire
	struct nodo *temp = calendario->testa; // Salva il nodo da eliminare
	calendario->testa = calendario->testa->prossimo; // Aggiorna la testa
	free(temp); // Libera la memoria

	// Se la coda è vuota, aggiorna anche il puntatore coda
	if (calendario->testa == NULL)
		calendario->coda = NULL;

	(calendario->numel)--; // Decrementa il contatore
	return risultato;
}
