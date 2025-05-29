#ifndef UTILE_CODA_H
#define UTILE_CODA_H

#include "abbonati.h"
#include "coda.h"
#include "lezione.h"

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

/* Funzione: giorno_lezione
*
* Verifica se il giorno della settimana corrente è previsto per una lezione.
*
* Parametri:
* giorno_settimana: intero rappresentante il giorno della settimana (0 = Domenica, 6 = Sabato)
* giorno: stringa (allocata dall'esterno) dove verrà salvato il nome del giorno (es. "Lunedi")
* orario: stringa (allocata dall'esterno) dove verrà salvata la fascia oraria della lezione (es. "10-12")
* ora_inizio: puntatore a intero dove viene salvata l'ora di inizio della lezione
*
* Pre-condizione:
* - Le stringhe 'giorno' e 'orario' devono essere allocate con dimensione sufficiente (almeno 10 caratteri).
* - 'ora_inizio' deve essere un puntatore valido.
*
* Post-condizione:
* - Se il giorno è valido per una lezione, restituisce 1 e riempie le stringhe giorno e orario, 
*   e imposta 'ora_inizio', altrimenti restituisce 0.
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

/* Funzione: data_passata
*
* Verifica se una data nel formato "gg/mm/aaaa" con orario associato è precedente alla data e ora attuali.
*
* Parametri:
* - data_str: stringa con la data da verificare (formato "gg/mm/aaaa")
* - orario: stringa che indica l'orario della lezione ("10-12" o "16-18")
*
* Pre-condizione:
* - 'data_str' deve essere valida e ben formattata
* - 'orario' deve essere uno dei valori riconosciuti
*
* Post-condizione:
* - Ritorna 1 se la data/orario indicati sono passati rispetto all'ora corrente, 0 altrimenti
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
* Genera un report mensile delle lezioni passate con almeno un partecipante,
* ordinate per numero di partecipanti decrescente.
*
* Parametri:
* - nome_file: nome del file storico da cui leggere i dati
*
* Pre-condizione:
* - Il file storico deve esistere e rispettare il formato previsto.
*
* Side-effect:
* - Legge da file, acquisisce input da tastiera, stampa a video.
*/
void report_mensile(const char* nome_file);

/* Funzione: caso_test_3
*
* Verifica la generazione del report mensile con lezioni passate
*
* Parametri:
* - calendario: la coda contenente le lezioni su cui effettuare il test, deve essere inizializzata
*
* Pre-condizione:
* - 'calendario' deve essere inizializzato
* - il file "ct3_storico.txt" viene letto e aggiornato durante il test
*
* Side-effect:
* - Scrive e aggiorna il file "ct3_storico.txt" con le lezioni passate
* - Modifica la coda 'calendario' aggiungendo la lezione creata
* - Interagisce con l’utente tramite I/O per mostrare il report
*/
void caso_test_3(coda calendario);

#endif
