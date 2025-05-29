#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "coda.h"
#include "lezione.h"
#include "hash.h"

#define MASSIMO_LINEA 256
#define MASSIMO_UTENTI 100

int confronta_file(const char *file1, const char *file2);

int aggiorna_input_e_oracle(const char *input_file, char utenti[][MASSIMO_LINEA]);


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

/* Funzione: caso_test_2
*
* Verifica la gestione degli abbonamenti e la prenotazione da parte di un abbonato
*
* Parametri:
* - calendario: la coda contenente le lezioni su cui effettuare il test, deve essere inizializzata e contenere almeno una lezione
*
* Pre-condizione:
* - 'calendario' deve essere inizializzato e non vuoto
* - il file "ct2_abbonati.txt" viene letto, modificato e salvato durante il test
* - il file "ct2_lezioni.txt" viene aggiornato con i nuovi dati di iscritti
*
* Side-effect:
* - Modifica e salva il file "ct2_abbonati.txt" con il nuovo abbonato e i dati aggiornati
* - Modifica e salva il file "ct2_lezioni.txt" con la prenotazione aggiornata
*/
void caso_test_2(coda calendario);