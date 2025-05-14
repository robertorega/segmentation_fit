#ifndef CODA_H
#define CODA_H

#include "lezione.h"

typedef struct c_coda *coda;

/* Funzione: nuova_coda
*
* Crea e inizializza una nuova coda vuota
*
* Post-condizione:
* Restituisce un puntatore a una coda vuota chiamata calendario
*
* Side-effect:
* Alloca memoria dinamica per la coda
*/
coda nuova_coda(void);

/* Funzione: coda_vuota
*
* Verifica se la coda calendario è vuota
*
* Parametri:
* calendario: la coda da controllare
*
* Pre-condizione:
* calendario deve essere una coda valida e inizializzata
*
* Post-condizione:
* Restituisce 1 se la coda è vuota, 0 se contiene elementi, -1 se la coda è NULL
*/
int coda_vuota(coda calendario);

/* Funzione: inserisci_lezione
*
* Inserisce una nuova lezione in fondo alla coda calendario
*
* Parametri:
* val: la lezione da inserire
* calendario: la coda dove aggiungere la lezione
*
* Pre-condizione:
* calendario deve essere una coda inizializzata
*
* Post-condizione:
* Restituisce 1 se l’inserimento è riuscito, 0 se fallisce per allocazione, -1 se la coda è NULL
*
* Side-effect:
* Modifica la coda calendario aggiungendo un nodo in fondo e incrementando il numero di elementi
*/
int inserisci_lezione(lezione val, coda calendario);

/* Funzione: rimuovi_lezione
*
* Rimuove e restituisce la prima lezione presente nella coda calendario
*
* Parametri:
* calendario: la coda da cui rimuovere la lezione
*
* Pre-condizione:
* calendario deve essere una coda inizializzata e non vuota
*
* Post-condizione:
* Se la coda è vuota restituisce ELEMENTO_NULLO, altrimenti restituisce la lezione rimossa
*
* Side-effect:
* Modifica la coda rimuovendo il primo nodo e aggiornando testa e numero di elementi
*/
lezione rimuovi_lezione(coda calendario);

/* Funzione: giorno_lezione
*
* Verifica se il giorno della settimana corrente è previsto per una lezione
*
* Parametri:
* giornoSettimana: intero rappresentante il giorno della settimana (0 = Domenica, 6 = Sabato)
* giorno: stringa dove verrà salvato il nome del giorno
* orario: stringa dove verrà salvata la fascia oraria della lezione
*
* Pre-condizione:
* Le stringhe giorno e orario devono essere allocate correttamente
*
* Post-condizione:
* Se il giorno è valido per una lezione, restituisce 1 e riempie le stringhe giorno e orario, altrimenti 0
*/
int giorno_lezione(int giorno_settimana, char *giorno, char *orario);

/* Funzione: genera_lezioni
*
* Popola la coda calendario con tutte le lezioni previste nei prossimi 30 giorni
*
* Parametri:
* calendario: la coda dove inserire le lezioni generate
*
* Pre-condizione:
* calendario deve essere una coda inizializzata
*
* Post-condizione:
* Aggiunge in calendario tutte le lezioni che cadono nei giorni validi (Lun, Mer, Ven, Sab)
*
* Side-effect:
* Inserisce dinamicamente nuove lezioni nella coda
*/
void genera_lezioni(coda calendario);

/* Funzione: stampa_lezioni
*
* Stampa l’elenco delle lezioni presenti nella coda, con data, giorno, orario e disponibilità
*
* Parametri:
* calendario: la coda contenente le lezioni da stampare
*
* Pre-condizione:
* calendario deve essere una coda inizializzata
*
* Post-condizione:
* Stampa sullo schermo l’elenco delle lezioni, indicando se i posti sono esauriti o disponibili
*/
void stampa_lezioni(coda calendario);

/* Funzione: prenota_lezione
*
* Permette all’utente di prenotare una lezione tra quelle disponibili nella coda
*
* Parametri:
* calendario: la coda da cui selezionare la lezione da prenotare
*
* Pre-condizione:
* calendario deve essere una coda inizializzata e contenere almeno una lezione
*
* Post-condizione:
* Se la prenotazione ha successo, aggiunge il partecipante alla pila degli iscritti per quella lezione
*
* Side-effect:
* Modifica la pila degli iscritti per la lezione scelta, interagisce con l’utente tramite input/output
*/
void prenota_lezione(coda calendario);

#endif
