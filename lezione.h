#ifndef LEZIONE_H
#define LEZIONE_H

#include "pila.h"

// Struttura della lezione
typedef struct lezione
{
	pila iscritti; // Pila contenente i nomi dei partecipanti iscritti
	char giorno[20]; // Giorno della settimana
	char orario[20]; // Fascia oraria
	char data[11]; // Data nel formato "gg/mm/aaaa"
} lezione;

#endif
