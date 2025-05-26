#ifndef CODA_H
#define CODA_H

#include "abbonati.h"
#include "lezione.h"
#define ELEMENTO_NULLO ((lezione){ NULL, "", "", "" }) // Lezione nulla/vuota

typedef struct c_coda *coda;

/* Funzione: carica_lezioni
*
* Carica le lezioni salvate da un file e le inserisce nella coda calendario
*
* Parametri:
* calendario: la coda dove verranno inserite le lezioni lette dal file
* partecipanti: nome del file da cui leggere le lezioni e gli iscritti
*
* Pre-condizione:
* calendario deve essere una coda inizializzata
* partecipanti deve essere un puntatore valido a una stringa non nulla
*
* Post-condizione:
* Inserisce nella coda tutte le lezioni lette correttamente dal file, con i rispettivi iscritti
*
* Side-effect:
* Legge da file e alloca dinamicamente memoria per le pile di iscritti e per i nodi della coda
*/
void carica_lezioni(coda calendario, const char *nome_file);

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
* Genera e aggiunge alla coda calendario le lezioni previste nei prossimi 30 giorni, evitando duplicati
*
* Parametri:
* calendario: la coda dove inserire le nuove lezioni generate
*
* Pre-condizione:
* calendario deve essere una coda inizializzata contenente eventualmente lezioni già caricate da file
*
* Post-condizione:
* Inserisce nella coda le lezioni valide (Lun, Mer, Ven, Sab) che non sono già presenti per data e orario
*
* Side-effect:
* Analizza le prossime 30 date a partire da oggi, verifica i giorni di lezione, controlla duplicati
* e alloca dinamicamente nuove lezioni da inserire nella coda
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

/* Funzione: prenota_lezione_abbonato
*
* Prenota una lezione per un utente abbonato
*
* Parametri:
* calendario: coda contenente le lezioni
* utente_loggato: abbonato che effettua la prenotazione
*
* Pre-condizione:
* calendario inizializzato e non vuoto
* utente_loggato valido
*
* Post-condizione:
* Se la prenotazione va a buon fine:
* - l’utente viene aggiunto alla pila degli iscritti
* - decrementa le lezioni rimanenti dell’abbonato
*
* Side-effect:
* Modifica pila iscritti e lezioni_rimanenti, interazione I/O
*/
void prenota_lezione_abbonato(coda calendario, abbonato *utente_loggato);

/* Funzione: disdici_iscrizione
*
* Permette a un utente di disdire la prenotazione a una lezione
*
* Parametri:
* calendario: la coda contenente le lezioni
* lezioni: nome del file da aggiornare dopo la disdetta
*
* Pre-condizione:
* calendario deve essere una coda inizializzata e contenere lezioni
* lezioni deve essere il percorso valido al file contenente i dati delle lezioni
*
* Post-condizione:
* Se la disdetta va a buon fine, l’utente viene rimosso dalla pila degli iscritti della lezione selezionata
* e il file delle lezioni aggiornato
*
* Side-effect:
* Interazione I/O con l’utente, modifica la pila degli iscritti, aggiorna file e lezioni_rimanenti se abbonato
*/
void disdici_iscrizione(coda calendario, const char* lezioni);

/* Funzione: salva_lezioni
*
* Salva tutte le lezioni presenti nella coda calendario su file, includendo anche gli iscritti
*
* Parametri:
* calendario: la coda contenente le lezioni da salvare
* partecipanti: nome del file su cui salvare i dati (verrà sovrascritto)
*
* Pre-condizione:
* calendario deve essere una coda inizializzata
* partecipanti deve essere un puntatore valido a una stringa non nulla
*
* Post-condizione:
* Scrive sul file tutte le lezioni contenute nella coda e i rispettivi partecipanti
*
* Side-effect:
* Apre il file in modalità scrittura ("w"), estrae temporaneamente gli iscritti dalle pile,
* li salva su file, e poi ripristina la pila originale
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
* data_str deve essere una stringa valida nel formato "dd/mm/yyyy"
*
* Post-condizione:
* Ritorna 1 se la data è nel passato rispetto a oggi, 0 altrimenti
*
* Side-effect:
* Nessuno
*/
int data_passata(const char *data_str);

/* Funzione: pulisci_lezioni_passate
*
* Rimuove dalla coda tutte le lezioni con data già passata, salvandole su un file storico
*
* Parametri:
* calendario: la coda contenente le lezioni da analizzare
* storico_file: nome del file su cui salvare le lezioni eliminate
*
* Pre-condizione:
* calendario deve essere una coda inizializzata contenente lezioni
* storico_file deve essere un puntatore valido a una stringa non nulla
*
* Post-condizione:
* Le lezioni con data passata vengono rimosse dalla coda e salvate nel file storico
*
* Side-effect:
* Apre il file in modalità append ("a"), modifica la struttura della coda,
* scrive su file e libera la memoria dei nodi eliminati
*/
void pulisci_lezioni_passate(coda calendario, const char *nome_file);

/* Funzione: report_mensile
*
* Genera e stampa un report ordinato delle lezioni svolte in un mese specifico,
* elencando solo quelle con almeno un partecipante, ordinate per numero di partecipanti in ordine decrescente
*
* Parametri:
* Nessun parametro di input
*
* Pre-condizione:
* Il file "storico.txt" deve essere presente nella directory del programma e formattato correttamente
*
* Post-condizione:
* Se esistono lezioni nel mese/anno specificati con almeno un partecipante, viene stampato un elenco ordinato
* Se non ci sono lezioni corrispondenti, viene stampato un messaggio informativo
*
* Side-effect:
* Lettura da file, acquisizione input da tastiera, stampa a schermo
* Nessuna modifica ai dati persistenti o alla memoria dinamica
*/
void report_mensile(void);

/* Funzione: caso_test_1
*
* Verifica la corretta registrazione di una prenotazione e l’aggiornamento della disponibilità
*
* Parametri:
* calendario: la coda contenente le lezioni su cui effettuare il test
*
* Pre-condizione:
* calendario deve essere inizializzato e contenere almeno una lezione
*
* Side-effect:
* Inserisce un partecipante fittizio nella prima lezione della coda
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
* calendario deve essere inizializzato e contenere almeno una lezione
*
* Side-effect:
* Modifica il file `abbonati.txt`, inserisce un nuovo abbonato e aggiorna le lezioni
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
* calendario deve essere inizializzato
*
* Side-effect:
* Scrive nel file `storico.txt`, modifica la coda e interagisce con l’utente tramite I/O
*/
void caso_test_3(coda calendario);

#endif
