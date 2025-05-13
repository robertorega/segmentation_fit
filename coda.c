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

int coda_vuota(coda calendario) {
	if (calendario == NULL)
		return -1;
	return calendario->numel == 0;
}

int inserisci_lezione(lezione val, coda calendario) { 
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

lezione rimuovi_lezione(coda calendario) {
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
