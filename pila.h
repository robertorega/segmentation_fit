#ifndef PILA_H
#define PILA_H

#include "partecipante.h"
#define MASSIMO_PILA 20 //numero massimo partecipanti

typedef struct c_pila *pila;

pila nuova_pila(void);
int pila_vuota(pila iscritti);
int inserisci_pila(partecipante val, pila iscritti);
int estrai_pila(pila iscritti);
char* testa(pila iscritti);
int dimensione_pila(pila iscritti);

#endif
