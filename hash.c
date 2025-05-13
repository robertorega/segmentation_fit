#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"  

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
tabella_hash nuova_hash(int dimensione) 
{

	tabella_hash h = malloc(sizeof(struct hash));
	if (h == NULL) 
    return NULL;

	h->dimensione = dimensione;
	h->tabella = calloc(dimensione, sizeof(abbonato *));
	if (h->tabella == NULL) 
    {
    	free(h);
    	return NULL;
	}

	return h;
}

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
int calcola_indice(char *chiave, int dimensione)
{
	unsigned int hash = 0;

	while (*chiave)
    {
    	hash = hash * 31 + *chiave++;
	}

	return hash % dimensione;
}

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
tabella_hash inserisci_hash(abbonato nuovo, tabella_hash h) 
{
	int indice = calcola_indice(nuovo.chiave, h->dimensione);
	abbonato *corrente = h->tabella[indice];

	while (corrente != NULL)
     {
    	if (strcmp(corrente->chiave, nuovo.chiave) == 0)
        {
        	return h;  // Chiave già presente
    	}

    	corrente = corrente->prossimo;
	}

	abbonato *nodo = malloc(sizeof(abbonato));

	if (nodo == NULL) 
    return h;

	nodo->chiave = strdup(nuovo.chiave);
	strncpy(nodo->nomeutente, nuovo.nomeutente, MAX_CARATTERI - 1);
	nodo->nomeutente[MAX_CARATTERI - 1] = '\0';
	strncpy(nodo->password, nuovo.password, MAX_CARATTERI - 1);
	nodo->password[MAX_CARATTERI - 1] = '\0';

	nodo->lezioni_rimanenti = nuovo.lezioni_rimanenti;
	nodo->prossimo = h->tabella[indice];
	h->tabella[indice] = nodo;

	return h;
}

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
abbonato* cerca_hash(char *chiave, tabella_hash h) 
{
	int indice = calcola_indice(chiave, h->dimensione);
	abbonato *corrente = h->tabella[indice];

	while (corrente != NULL) 
    {
    	if (strcmp(corrente->chiave, chiave) == 0) 
        return corrente;

    	corrente = corrente->prossimo;
	}

	return NULL;
}

/* Funzione: elimina_hash
*
* Rimuove dalla tabella hash h l’elemento con chiave uguale a chiave, se presente
* Parametri:
* chiave: elemento da eliminare nella tabella h
* h: tabella hash da cui elimare l'elemento 
*
* Pre-condizione:
* chiave è una stringa non vuota e h è una tabella hash valida
*
* Post-condizione:
*  l’elemento viene rimosso dalla tabella, se non è presente non accade nulla
*
* Side-effect:
* viene deallocata la memoria associata all’elemento rimosso
*/
tabella_hash elimina_hash(char *chiave, tabella_hash h) 
{
	int indice = calcola_indice(chiave, h->dimensione);
	abbonato *corrente = h->tabella[indice];
	abbonato *precedente = NULL;

	while (corrente != NULL)
     {
    	if (strcmp(corrente->chiave, chiave) == 0) 
        {
        	if (precedente == NULL) 
            {
            	h->tabella[indice] = corrente->prossimo;
        	} 
            else
            {
            	precedente->prossimo = corrente->prossimo;
        	}
        	free(corrente->chiave);
        	free(corrente);
        	return h;
    	}
    	precedente = corrente;
    	corrente = corrente->prossimo;
	}

	return h;
}
