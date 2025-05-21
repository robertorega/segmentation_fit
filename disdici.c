#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "disdici.h"
#include "pila.h"
#include "partecipante.h"

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