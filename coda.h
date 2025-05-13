#ifndef CODA_H
#define CODA_H

#include "lezione.h"

typedef struct c_coda *coda;

coda nuova_coda(void);
int coda_vuota(coda calendario);
int inserisci_lezione(lezione val, coda calendario);
lezione rimuovi_lezione(coda calendario);
int giorno_lezione(int giorno_settimana, char *giorno, char *orario);
void genera_lezioni(coda calendario);
void stampa_lezioni(coda calendario);
void prenota_lezione(coda calendario);

#endif
