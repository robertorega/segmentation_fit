#ifndef DISDICI_H
#define DISDICI_H

#include "pila.h"

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
int disdici_iscrizione(pila iscritti, const char* nome);

#endif