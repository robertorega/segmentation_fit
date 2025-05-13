#ifndef HASH_H
#define HASH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "abbonati.h"
#include "partecipante.h"

typedef struct hash 
{

	int dimensione;
	abbonato **tabella; 

} *tabella_hash;

// Funzioni per la gestione della tabella hash
tabella_hash nuova_hash(int dimensione);
int calcola_indice(char *chiave, int dimensione);
tabella_hash inserisci_hash(abbonato item, tabella_hash tabella);
abbonato *cerca_hash(char *chiave, tabella_hash tabella);
tabella_hash elimina_hash(char *chiave, tabella_hash tabella);

#endif
