#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "coda.h"
#include "lezione.h"
#include "hash.h"

int confronta_file(const char *file1, const char *file2);

int aggiorna_input_e_oracle(const char *input_file, const char *oracle_file, char utenti[][MAX_LINE])


/* Funzione: caso_test_1
*
* Verifica la corretta registrazione di una prenotazione e l’aggiornamento della disponibilità
*
* Parametri:
* - calendario: la coda contenente le lezioni su cui effettuare il test, deve essere inizializzata e non vuota
*
* Pre-condizione:
* - 'calendario' deve contenere almeno una lezione disponibile
* - il file "ct1_lezioni.txt" viene creato o aggiornato durante il test
*
* Side-effect:
* - Inserisce un partecipante fittizio nella prima lezione della coda in memoria
* - Aggiorna il file "ct1_lezioni.txt" con i dati modificati (iscritti e lista utenti)
*/
void caso_test_1(coda calendario);