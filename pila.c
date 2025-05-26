#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "partecipante.h"
#include "pila.h"

// Struttura della pila
struct c_pila
 {
	partecipante vet[MASSIMO_PILA];
	int testa;
};

/* Funzione: nuova_pila
*
* Crea e inizializza una nuova pila vuota
*
* Descrizione:
* Alloca dinamicamente una struttura di tipo pila, inizializza l'indice della cima a 0
* Per indicare che la pila è vuota e restituisce un puntatore alla nuova pila
*
* Post-condizione:
* Restituisce un puntatore a una pila vuota chiamata iscritti
*
* Side-effect:
* Alloca memoria dinamica per la pila
*/
pila nuova_pila(void)
 {
	// Alloca la struttura pila
	pila iscritti;
	iscritti = malloc(sizeof(struct c_pila));

	if (iscritti == NULL)
	return NULL;

	// Inizializza l'indice di testa
	iscritti->testa = 0;
	return iscritti;
}

/* Funzione: pila_vuota
*
* controlla se la pila iscritti è vuota
*
*Descrizione:
* Controlla se l'indice della cima (`testa`) è uguale a zero, condizione che indica che non ci sono elementi nella pila
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
int pila_vuota(pila iscritti) 
{
	return iscritti->testa == 0;
}

/* Funzione: inserisci_pila
*
* Inserisce un partecipante in cima alla pila iscritti, se la pila non è piena
*
* Descrizione:
* Verifica se la pila ha raggiunto la dimensione massima
* Se piena, restituisce 0 per indicare che l'inserimento non è avvenuto
* Altrimenti, copia il nome del partecipante nella posizione corrente della cima e incrementa l'indice
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
int inserisci_pila(partecipante val, pila iscritti) 
{
	// Verifica se c'è spazio
	if (iscritti->testa == MASSIMO_PILA)
    		return 0;

	// Copia il partecipante nella posizione corrente
	strcpy(iscritti->vet[iscritti->testa], val);
	
	// Incrementa l'indice di testa
	(iscritti->testa)++;
	return 1;
}

/* Funzione: estrai_pila
*
* Estrae l'elemento in cima alla pila iscritti, se presente
*
* Descrizione:
* Verifica se la pila contiene almeno un elemento
* Se sì, decrementa l'indice della cima (`testa`), copia il valore dell'elemento in cima 
* nella variabile `estratto`, e restituisce 1 per indicare il successo.
* Se la pila è vuota, restituisce 0.
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
int estrai_pila(pila iscritti, partecipante estratto)
{
	// Verifica se la pila è vuota
	if (iscritti->testa == 0)
		return 0;

    	iscritti->testa--; // Decrementa l'indice
    	strcpy(estratto, iscritti->vet[iscritti->testa]); // Copia il partecipante estratto
    	return 1;
}

/* Funzione: testa
*
* Restituisce l’elemento in cima alla pila iscritti senza rimuoverlo
*
* Descrizione:
* Verifica se la pila contiene almeno un elemento 
* Se sì, restituisce l'elemento all'indice testa - 1, ovvero l'ultimo inserito
* Se la pila è vuota, restituisce un valore predefinito
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
char* testa(pila iscritti)
 {
	 // Verifica se la pila è vuota
	if (iscritti->testa > 0)
    		return iscritti->vet[iscritti->testa - 1]; // Elemento in cima

	else
    		return NESSUN_PARTECIPANTE;
}

/* Funzione: dimensione_pila
*
* Restituisce il numero di elementi attualmente presenti nella pila iscritti
*
* Descrizione:
* Verifica che la pila sia inizializzata
* Se la pila è NULL, restituisce -1 come segnale di errore
* Altrimenti, restituisce il numero di elementi contenuti nella pila
* Parametri:
* iscritti:  pila da analizzare
*
* Pre-condizione:
* iscritti = <a1, a2, ..., an> n>0
*
* Post-condizione:
* Se iscritti == NULL ritorna -1, altrimenti ritorna iscritti->testa (che può essere 0 se vuota)
*/
int dimensione_pila(pila iscritti)
 {
	// Controllo parametro NULL
	if (iscritti == NULL)
    		return -1;  

	return iscritti->testa; 
}
