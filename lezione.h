#include "stack.h"

typedef struct lezione {
	stack iscritti; 
	char giorno[20]; //Giorno della settimana in cui si tiene la lezione
	char orario[20]; //Fascia oraria della lezione
	char data[11]; //gg/mm/aa
} lezione;
