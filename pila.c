#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "partecipante.h"
#include "pila.h"

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
	pila iscritti;
	iscritti = malloc(sizeof(struct c_pila));

	if (iscritti == NULL)
	return NULL;

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
* Restituisce 1 se persona viene copia in cima altrimenti restituisce 0
*
* Side-effect:
* Modifica la pila iscritti incrementando testa e scrivendo in persona[testa].
*/
int inserisci_pila(partecipante val, pila iscritti) 
{
	if (iscritti->testa == MASSIMO_PILA)
    return 0;

	strcpy(iscritti->vet[iscritti->testa], val);
	(iscritti->testa)++;
	return 1;
}

/* Funzione: estrai_pila
*
* Rimuove l’elemento in cima alla pila iscritti, se la pila non è vuota, e lo copia nel partecipante estratto
*
* Descrizione:
* La funzione controlla se la pila è vuota.
* Se lo è, restituisce 0 e non viene effettuata alcuna estrazione.
* Altrimenti, l’elemento in cima alla pila viene copiato nella variabile locale estratto
* e rimosso dalla pila, decrementando l'indice della cima.
*
* Parametri:
* iscritti: pila da cui estrarre l’elemento
* estratto: variabile in cui salvare il partecipante rimosso dalla pila (passata per valore)
*
* Pre-condizione:
* iscritti è una pila inizializzata e valida
*
* Post-condizione:
* Se la pila non è vuota, l’elemento in cima viene copiato in estratto e rimosso dalla pila (ritorna 1)
* Se la pila è vuota, estratto rimane inalterato (ritorna 0)
*
* Side-effect:
* iscritti viene modificata: la sua cima viene decrementata e l’elemento rimosso
*/
int estrai_pila(pila iscritti, partecipante estratto) {
	if (iscritti->testa == 0)
		return 0;

    	iscritti->testa--;
    	strcpy(estratto, iscritti->vet[iscritti->testa]);
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
* se top>0  ritorna un puntatore al partecipante in cima alla pila altrimenti NESSUN_PARTECIPANTE
*/
char* testa(pila iscritti)
 {
	if (iscritti->testa > 0)
    return iscritti->vet[iscritti->testa - 1];

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
* Restituisce il numero di partecipanti, se la pila è vuota restituisce return -1
*/
int dimensione_pila(pila iscritti)
 {
	if (iscritti == NULL)
    return -1;  

	return iscritti->testa; 
}
