#include <stdio.h>
#include <stdlib.h>
#include "lezione.h"
#include "coda.h"
#define ELEMENTO_NULLO ((lezione){ NULL, "", "", "" })

struct nodo {
    lezione valore;
    struct nodo *prossimo;
};

struct c_coda {
	struct nodo *testa,*coda;
	int numel;
};

/* Funzione: nuova_coda
*
* Crea e inizializza una nuova coda vuota
*
* Post-condizione:
* Restituisce un puntatore a una coda vuota chiamata calendario
*
* Side-effect:
* Alloca memoria dinamica per la coda
*/
coda nuova_coda(void) {
	struct c_coda *calendario;
	calendario = malloc(sizeof(struct c_coda));
	if (calendario == NULL)
		return NULL;
	
	calendario->numel = 0;
	calendario->testa = NULL;
	calendario->coda = NULL;
	return calendario;
}

/* Funzione: coda_vuota
*
* Verifica se la coda calendario è vuota
*
* Parametri:
* calendario: la coda da controllare
*
* Pre-condizione:
* calendario deve essere una coda valida e inizializzata
*
* Post-condizione:
* Restituisce 1 se la coda è vuota, 0 se contiene elementi, -1 se la coda è NULL
*/
int coda_vuota(coda calendario) {
	if (calendario == NULL)
		return -1;
	return calendario->numel == 0;
}

/* Funzione: inserisci_elemento
*
* Inserisce un nuovo elemento in fondo alla coda calendario
*
* Parametri:
* val: l'elemento da inserire
* calendario: la coda dove aggiungere l'elemento
*
* Pre-condizione:
* calendario deve essere una coda inizializzata
*
* Post-condizione:
* Restituisce 1 se l’inserimento è riuscito, 0 se fallisce per allocazione, -1 se la coda è NULL
*
* Side-effect:
* Modifica la coda calendario aggiungendo un nodo in fondo e incrementando il numero di elementi
*/
int inserisci_elemento(lezione val, coda calendario) { 
	if (calendario == NULL)
		return -1;

	struct nodo *nuovo;
	nuovo = malloc(sizeof(struct nodo));
	if (nuovo == NULL)
		return 0;

	nuovo->valore = val;
	nuovo->prossimo = NULL;

	if (calendario->testa == NULL)
    		calendario->testa = nuovo;
	else
    		calendario->coda->prossimo = nuovo;

	calendario->coda = nuovo;
	(calendario->numel)++;
	return 1;
}

/* Funzione: rimuovi_elemento
*
* Rimuove e restituisce il primo elemento presente nella coda calendario
*
* Parametri:
* calendario: la coda da cui rimuovere l'elemento
*
* Pre-condizione:
* calendario deve essere una coda inizializzata e non vuota
*
* Post-condizione:
* Se la coda è vuota restituisce ELEMENTO_NULLO, altrimenti restituisce l'elemento rimosso
*
* Side-effect:
* Modifica la coda rimuovendo il primo nodo e aggiornando testa e numero di elementi
*/
lezione rimuovi_elemento(coda calendario) {
	if (calendario == NULL)
		return ELEMENTO_NULLO;
	if (calendario->numel == 0)
        	return ELEMENTO_NULLO; 

	lezione risultato = calendario->testa->valore;
	struct nodo *temp = calendario->testa; 
	calendario->testa = calendario->testa->prossimo; 
	free(temp); 

	if (calendario->testa == NULL)
		calendario->coda = NULL;

	(calendario->numel)--;
	return risultato;
}
