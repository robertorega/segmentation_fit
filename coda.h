#ifndef CODA_H
#define CODA_H

#include "abbonati.h"
#include "lezione.h"
#define ELEMENTO_NULLO ((lezione){ NULL, "", "", "" }) // Lezione nulla/vuota

typedef struct c_coda *coda;

/* Funzione: carica_lezioni
*
* Carica le lezioni salvate da un file e le inserisce nella coda calendario.
*
* Parametri:
* calendario: la coda dove verranno inserite le lezioni lette dal file.
* nome_file: nome del file da cui leggere le lezioni e gli iscritti.
*
* Pre-condizioni:
* - 'calendario' deve essere una coda inizializzata.
* - 'nome_file' deve essere un puntatore valido a una stringa non nulla.
*
* Side-effect:
* - Legge da file.
* - Alloca dinamicamente memoria per le pile di iscritti e per i nodi della coda.
*/
void carica_lezioni(coda calendario, const char *nome_file);

/* Funzione: nuova_coda
*
* Crea e inizializza una nuova coda vuota
*
* Post-condizione:
* - Restituisce un puntatore a una coda vuota chiamata 'calendario'
*
* Side-effect:
* - Alloca memoria dinamica per la coda
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
* - 'calendario' deve essere una coda valida e inizializzata
*
* Post-condizione:
* - Restituisce 1 se la coda è vuota, 0 se contiene elementi, -1 se la coda è NULL
*/
int coda_vuota(coda calendario);

/* Funzione: inserisci_lezione
*
* Inserisce una nuova lezione in fondo alla coda calendario
*
* Descrizione:
* La funzione alloca dinamicamente un nuovo nodo contenente la lezione da inserire
* Se la coda è vuota imposta il nuovo nodo come testa della coda
* Altrimenti lo collega in fondo alla coda esistente
* In entrambi i casi aggiorna il puntatore alla coda e incrementa il numero di elementi
* Restituisce 1 in caso di successo 0 se l'allocazione fallisce -1 se la coda è NULL
*
* Parametri:
* val: la lezione da inserire
* calendario: la coda dove aggiungere la lezione
*
* Pre-condizione:
* - 'calendario' deve essere una coda inizializzata
*
* Post-condizione:
* - Restituisce 1 se l’inserimento è riuscito, 0 se fallisce per allocazione, -1 se la coda è NULL
*
* Side-effect:
* - Modifica la coda calendario aggiungendo un nodo in fondo e incrementando il numero di elementi
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
* - 'calendario' deve essere una coda inizializzata e non vuota
*
* Post-condizione:
* - Se la coda è vuota restituisce ELEMENTO_NULLO, altrimenti restituisce la lezione rimossa
*
* Side-effect:
* - Modifica la coda rimuovendo il primo nodo e aggiornando testa e numero di elementi
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
* - Le stringhe 'giorno' e 'orario' devono essere allocate correttamente
*
* Post-condizione:
* - Se il giorno è valido per una lezione, restituisce 1 e riempie le stringhe giorno e orario, altrimenti 0
*/
int giorno_lezione(int giorno_settimana, char *giorno, char *orario, int *ora_inizio);

/* Funzione: genera_lezioni
*
* Genera e aggiunge alla coda calendario le lezioni previste nei prossimi 30 giorni, evitando duplicati.
*
* Parametri:
* - calendario: la coda dove inserire le nuove lezioni generate.
*
* Pre-condizione:
* - 'calendario' deve essere una coda inizializzata, eventualmente già contenente lezioni caricate da file.
*
* Side-effect:
* - Analizza le prossime 30 date a partire da oggi.
* - Verifica i giorni validi per le lezioni.
* - Controlla la presenza di duplicati nella coda.
* - Alloca dinamicamente nuove lezioni da inserire nella coda.
*/
void genera_lezioni(coda calendario);

/* Funzione: stampa_lezioni
*
* Stampa l’elenco delle lezioni presenti nella coda, con data, giorno, orario e disponibilità.
*
* Parametri:
* calendario: la coda contenente le lezioni da stampare.
*
* Pre-condizione:
* - 'calendario' deve essere una coda inizializzata.
*
* Side-effect:
* - Stampa a schermo le informazioni delle lezioni contenute nella coda.
*/
void stampa_lezioni(coda calendario);

/* Funzione: prenota_lezione
*
* Permette all’utente di prenotare una lezione tra quelle disponibili nella coda.
*
* Parametri:
* calendario: la coda da cui selezionare la lezione da prenotare.
*
* Pre-condizione:
* - 'calendario' deve essere una coda inizializzata e contenere almeno una lezione.
*
* Side-effect:
* - Interagisce con l’utente tramite input/output.
* - Modifica la pila degli iscritti della lezione scelta aggiungendo un nuovo partecipante.
*/
void prenota_lezione(coda calendario);

/* Funzione: prenota_lezione_abbonato
*
* Consente a un utente abbonato di prenotare una lezione tra quelle disponibili.
*
* Parametri:
* calendario: la coda contenente le lezioni disponibili.
* utente_loggato: puntatore alla struttura dell'abbonato che sta effettuando la prenotazione.
*
* Pre-condizioni:
* - 'calendario' deve essere inizializzato e non vuoto.
* - 'utente_loggato' deve essere un puntatore valido a un abbonato autenticato.
*
* Side-effect:
* - Interagisce con l’utente tramite input/output.
* - Modifica la pila degli iscritti della lezione selezionata.
* - Decrementa il numero di lezioni rimanenti dell’abbonato.
*/
void prenota_lezione_abbonato(coda calendario, abbonato *utente_loggato);

/* Funzione: disdici_iscrizione
*
* Consente a un utente (abbonato o non) di annullare l’iscrizione a una lezione precedentemente prenotata.
*
* Parametri:
* calendario: la coda contenente le lezioni.
* lezioni: il nome (percorso) del file da aggiornare con la nuova lista degli iscritti.
*
* Pre-condizioni:
* - 'calendario' inizializzato e contenente almeno una lezione.
* - 'lezioni' deve essere un percorso valido al file delle lezioni.
*
* Side-effect:
* - Interazione con l’utente tramite input/output.
* - Modifica la pila degli iscritti della lezione selezionata.
* - Scrive sul file 'lezioni' e su 'abbonati.txt' (se l’utente è abbonato).
*/
void disdici_iscrizione(coda calendario, const char* lezioni);

/* Funzione: salva_lezioni
*
* Salva tutte le lezioni presenti nella coda calendario su file, includendo anche gli iscritti.
*
* Parametri:
* calendario: la coda contenente le lezioni da salvare.
* nome_file: nome del file su cui salvare i dati (verrà sovrascritto).
*
* Pre-condizioni:
* - 'calendario' deve essere una coda inizializzata.
* - 'nome_file' deve essere un puntatore valido a una stringa non nulla.
*
* Side-effect:
* - Apre il file in modalità scrittura.
* - Estrae temporaneamente gli iscritti dalle pile per scriverli su file.
* - Ripristina le pile originali degli iscritti al termine della scrittura.
*/
void salva_lezioni(coda calendario, const char *nome_file);

/* Funzione: data_passata
*
* Verifica se una data nel formato "dd/mm/yyyy" è precedente alla data odierna
*
* Parametri:
* data_str: stringa contenente la data da analizzare
*
* Pre-condizione:
* - 'data_str' deve essere una stringa valida nel formato "dd/mm/yyyy"
*
* Post-condizione:
* - Ritorna 1 se la data è nel passato rispetto a oggi, 0 altrimenti
*/
int data_passata(const char *data_str, const char *orario);

/* Funzione: pulisci_lezioni_passate
*
* Rimuove dalla coda tutte le lezioni con data già passata, salvandole su un file storico.
*
* Parametri:
* - calendario: coda contenente le lezioni da analizzare.
* - nome_file: nome del file su cui salvare le lezioni eliminate.
*
* Pre-condizioni:
* - 'calendario' deve essere una coda inizializzata e non vuota.
* - 'nome_file' deve essere un puntatore valido a una stringa non nulla.
*
* Side-effect:
* - Apre il file in modalità append ("a").
* - Modifica la struttura della coda rimuovendo nodi.
* - Scrive su file le lezioni passate e i relativi iscritti.
* - Libera la memoria dei nodi eliminati.
*/
void pulisci_lezioni_passate(coda calendario, const char *nome_file);

/* Funzione: report_mensile
*
* Genera e stampa un report ordinato delle lezioni svolte in un mese specifico,
* elencando solo quelle con almeno un partecipante, ordinate per numero di partecipanti decrescente.
*
* Pre-condizione:
* - Il file "storico.txt" deve esistere e rispettare il formato previsto.
*
* Side-effect:
* - Legge da file, acquisisce input da tastiera, stampa a schermo.
*/
void report_mensile(const char* filename);

/* Funzione: caso_test_1
*
* Verifica la corretta registrazione di una prenotazione e l’aggiornamento della disponibilità
*
* Parametri:
* calendario: la coda contenente le lezioni su cui effettuare il test
*
* Pre-condizione:
* - 'calendario' deve essere inizializzato e contenere almeno una lezione
*
* Side-effect:
* - Inserisce un partecipante fittizio nella prima lezione della coda
*/
void caso_test_1(coda calendario);

/* Funzione: caso_test_2
*
* Verifica la gestione degli abbonamenti e la prenotazione da parte di un abbonato
*
* Parametri:
* calendario: la coda contenente le lezioni su cui effettuare il test
*
* Pre-condizione:
* - 'calendario' deve essere inizializzato e contenere almeno una lezione
*
* Side-effect:
* - Modifica il file `abbonati.txt`, inserisce un nuovo abbonato e aggiorna le lezioni
*/
void caso_test_2(coda calendario);

/* Funzione: caso_test_3
*
* Verifica la generazione del report mensile con lezioni passate
*
* Parametri:
* calendario: la coda contenente le lezioni su cui effettuare il test
*
* Pre-condizione:
* - 'calendario' deve essere inizializzato
*
* Side-effect:
* - Scrive nel file `storico.txt`, modifica la coda e interagisce con l’utente tramite I/O
*/
void caso_test_3(coda calendario);

#endif
