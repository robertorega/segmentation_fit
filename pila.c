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
int estrai_pila(pila iscritti) 
{
	if (iscritti->testa == 0)
    return 0;

	(iscritti->testa)--;
	return 1;
}

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

/*
 * Funzione: disdici_iscrizione
 *
 * Rimuove un partecipante dalla pila degli iscritti, se presente.
 *
 * Parametri:
 * - iscritti: pila principale degli iscritti
 * - nome: stringa contenente il nome dell'utente da rimuovere
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
int disdici_iscrizione(pila iscritti, const char* nome)
{
    if (iscritti == NULL || nome == NULL)
        return 0;

    int trovato = 0;
    pila supporto = nuova_pila();
    if (supporto == NULL)
        return 0;

    partecipante corrente;

    // Sposta gli elementi dalla pila principale alla pila di supporto
    for (int i = iscritti->testa - 1; i >= 0; i--)
    {
        corrente = iscritti->vet[i];
        if (strcmp(corrente, nome) == 0 && !trovato)
        {
            // Non inserisce nella pila di supporto
            trovato = 1;
        } 
        else 
        {
            inserisci_pila(corrente, supporto);
        }
        estrai_pila(iscritti);
    }

    // Riporta gli elementi dalla pila d'appoggio alla pila principale
    while(!pila_vuota(supporto))
    {
        inserisci_pila(testa(supporto), iscritti);
        estrai_pila(supporto);
    }

    free(supporto);
    printf("Possiamo fare altro per te? Premi INVIO\n");
    getchar(); // Consuma il carattere di newline rimasto nel buffer
	getchar(); // Libera il buffer per l'input successivo
    return trovato;
}
