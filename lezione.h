#ifndef LEZIONE_H
#define LEZIONE_H

#include "pila.h"

typedef struct lezione
{
	pila iscritti; 
	char giorno[20]; //Giorno della settimana in cui si tiene la lezione
	char orario[20]; //Fascia oraria della lezione
	char data[11]; //gg/mm/aa
} lezione;

#endif
