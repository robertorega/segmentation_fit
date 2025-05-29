#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "coda.h"
#include "lezione.h"
#include "hash.h"

#define MASSIMO_LINEA 256
#define MASSIMO_UTENTI 100

/* Funzione: confronta_file
*
* Descrizione:
* Confronta due file di testo riga per riga, ignorando i caratteri di fine riga, per verificarne l’identicità.
*
* Parametri:
* - file1: percorso del primo file da confrontare
* - file2: percorso del secondo file da confrontare
*
* Pre-condizioni:
* - I file devono esistere e essere accessibili in lettura
*
* Post-condizioni:
* - Restituisce 1 se i file sono identici, 0 altrimenti
*/
int confronta_file(const char *file1, const char *file2);

/* Funzione: aggiorna_input_e_oracle
*
* Descrizione:
* Legge gli utenti da un file CSV, aggiunge un nuovo utente fittizio con nome incrementale, e riscrive il file aggiornato.
*
* Parametri:
* - input_file: percorso del file CSV da leggere e aggiornare
* - utenti: array bidimensionale dove vengono salvati i nomi degli utenti letti e quello nuovo
*
* Pre-condizioni:
* - Il file deve esistere e contenere una riga di intestazione
* - L’array 'utenti' deve avere dimensione sufficiente per contenere tutti gli utenti
*
* Post-condizioni:
* - Il file viene aggiornato con un nuovo utente
* - L’array 'utenti' contiene tutti gli utenti, incluso quello nuovo
* - Restituisce il numero totale di utenti, -1 in caso di errore
*
* Side-effect:
* - Sovrascrive il file di input con i dati aggiornati
*/
int aggiorna_input_e_oracle(const char *input_file, char utenti[][MASSIMO_LINEA]);

/* Funzione: caso_test_1
*
* Verifica la registrazione di una prenotazione e l’aggiornamento dei dati della lezione
*
* Descrizione:
* La funzione carica o genera lezioni nella coda 'calendario', aggiunge un utente fittizio alla prima lezione disponibile,
* aggiorna i file di output e oracle, e confronta i risultati per verificare la corretta registrazione della prenotazione.
*
* Side-effect:
* - Inserisce un utente fittizio nella prima lezione
* - Aggiorna i file \"caso_test_1_output.txt\" e \"caso_test_1_oracle.txt\" con i dati modificati
* - Scrive l’esito del test nei file \"esiti_test.txt\" e \"elenco_test.txt\"
*/
void caso_test_1();

/* Funzione: caso_test_2
*
* Verifica la gestione degli abbonamenti e la prenotazione automatica da parte di un abbonato
*
* Descrizione:
* La funzione crea un abbonato fittizio con 0 lezioni disponibili, verifica che non possa prenotare,
* ricarica l’abbonamento, effettua una prenotazione automatica e controlla che i dati siano aggiornati correttamente.
*
* Side-effect:
* - Crea e aggiorna un abbonato fittizio
* - Modifica i file \"caso_test_2_abbonati.txt\", \"caso_test_2_output.txt\" e \"caso_test_2_oracle.txt\"
* - Scrive l’esito del test nei file \"esiti_test.txt\" e \"elenco_test.txt\"
*/
void caso_test_2();

/* Funzione: caso_test_3
*
* Verifica la generazione del report mensile includendo lezioni passate con partecipanti
*
* Descrizione:
* La funzione genera una lezione in una data passata con partecipanti casuali, la salva nello storico,
* aggiorna i file di output e oracle, confronta i risultati e infine esegue il report mensile per verificarne la correttezza.
*
* Parametri:
* - calendario: la coda contenente le lezioni
*
* Pre-condizione:
* - 'calendario' deve essere inizializzato
*
* Side-effect:
* - Genera e salva una lezione passata
* - Aggiorna i file di output e oracle
* - Esegue il report mensile e scrive l’esito nei file \"esiti_test.txt\" e \"elenco_test.txt\"
*/
void caso_test_3(coda calendario);