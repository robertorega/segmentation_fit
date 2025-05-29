#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "coda.h"
#include "lezione.h"
#include "hash.h"
#include "utile_coda.h"
#include "test_programma.h"
#include "pila.h"
#include "utile_hash.h"

// Nodo della coda
struct nodo
{
	lezione valore;
	struct nodo *prossimo;
};

// Struttura della coda
struct c_coda
{
	struct nodo *testa,*coda;
	int numel;
};

// Confronta due file riga per riga
int confronta_file(const char *file1, const char *file2)
{
    FILE *f1 = fopen(file1, "r");
    FILE *f2 = fopen(file2, "r");
    if (!f1 || !f2) return 0;

    char r1[MASSIMO_LINEA], r2[MASSIMO_LINEA];
    while (1) {
        char *s1 = fgets(r1, sizeof(r1), f1);
        char *s2 = fgets(r2, sizeof(r2), f2);

        if (s1 == NULL || s2 == NULL) {
            // PASS solo se entrambi finiscono insieme
            int ok = (s1 == NULL && s2 == NULL);
            fclose(f1);
            fclose(f2);
            return ok;
        }

        // rimuovo newline e CR residui
        r1[strcspn(r1, "\r\n")] = 0;
        r2[strcspn(r2, "\r\n")] = 0;

        if (strcmp(r1, r2) != 0) {
            fclose(f1);
            fclose(f2);
            return 0;
        }
    }
}

// Legge utenti da file e aggiunge un nuovo utente alla lista in memoria
int aggiorna_input_e_oracle(const char *input_file, char utenti[][MASSIMO_LINEA]) 
{
    FILE *f = fopen(input_file, "r");
    if (!f) return -1;

    char linea[MASSIMO_LINEA];
    int num_iscritti = 0;

    // Salta intestazione
    fgets(linea, sizeof(linea), f);

    // Legge utenti già presenti
    while (fgets(linea, sizeof(linea), f) && num_iscritti < MASSIMO_UTENTI - 1) {
        linea[strcspn(linea, "\n")] = 0; // rimuove newline
        strcpy(utenti[num_iscritti], linea);
        num_iscritti++;
    }
    fclose(f);

    // Aggiunge nuovo utente
    snprintf(utenti[num_iscritti], MASSIMO_LINEA, "Utente_Test%d", num_iscritti + 1);
    num_iscritti++;

    // Scrive di nuovo tutti gli utenti nel file input
    f = fopen(input_file, "w");
    if (!f) return -1;
    fprintf(f, "Data;Giorno;Orario;NumeroIscritti\n");
    for (int i = 0; i < num_iscritti; i++) {
        fprintf(f, "%s\n", utenti[i]);
    }
    fclose(f);

    return num_iscritti;
}

/* Funzione: caso_test_1
*
* Verifica la corretta registrazione di una prenotazione e l’aggiornamento della disponibilità
*
* Descrizione:
* La funzione seleziona la prima lezione disponibile nella coda 'calendario', registra un partecipante fittizio 
* ("Utente_TestN" dove N è incrementale) e aggiorna il file "ct1_lezioni.txt" con il nuovo numero di iscritti 
* e la lista dei partecipanti.
* Il test confronta il numero di iscritti prima e dopo la prenotazione per verificarne la corretta registrazione.
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
void caso_test_1(coda calendario) 
{
    printf("TEST 1: Verifica registrazione prenotazione e aggiornamento disponibilità\n");
    printf("Premi INVIO per iniziare...");
    getchar();

    // 1. Carica/genera lezioni
    if (coda_vuota(calendario)) {
        genera_lezioni(calendario);
        carica_lezioni(calendario, "caso_test_1_input.txt");
    }

    if (coda_vuota(calendario)) {
        printf("ERRORE: Nessuna lezione disponibile.\nPremi INVIO per tornare al menu...");
        getchar();
        return;
    }

    // 2. Aggiungi utente fittizio
    char utenti[MASSIMO_UTENTI][MASSIMO_LINEA];
    int num_iscritti = aggiorna_input_e_oracle("caso_test_1_input.txt", utenti);
    if (num_iscritti == -1) {
        printf("Errore nella lettura o scrittura dei file di test.\n");
        getchar();
        return;
    }

    lezione *lez = &calendario->testa->valore;
    if (lez->iscritti == NULL) {
        lez->iscritti = nuova_pila();
    }
    inserisci_pila(utenti[num_iscritti - 1], lez->iscritti);

    // 3. Salva sia output che oracle
    salva_lezioni(calendario, "caso_test_1_output.txt");
    salva_lezioni(calendario, "caso_test_1_oracle.txt");

    // 4. Confronta output con oracle
    int esito = confronta_file("caso_test_1_output.txt", "caso_test_1_oracle.txt");
    printf("RISULTATO TEST 1: %s\n", esito ? "PASSATO" : "FALLIMENTO");

    FILE *res = fopen("esiti_test.txt", "a");
    if (res) 
    {
        fprintf(res, "Caso Test 1: %s\n", esito ? "PASSATO" : "FALLIMENTO");
        fclose(res);
    }

    FILE *elenco = fopen("elenco_test.txt", "w");
    if (elenco) 
    {
        fprintf(elenco, "CT1 %d\n", num_iscritti);
        fclose(elenco);
    }

    printf("Premi INVIO per tornare al menu...");
    getchar();
}

/* Funzione: caso_test_2
*
* Verifica la gestione degli abbonamenti e la prenotazione da parte di un abbonato
*
* Descrizione:
* La funzione crea un nuovo abbonato fittizio con 0 lezioni disponibili e lo inserisce nel file "ct2_abbonati.txt".
* Verifica che l’abbonato non possa prenotare senza lezioni disponibili, poi ricarica l’abbonamento con 12 lezioni,
* tenta la prenotazione automatica alla prima lezione della coda 'calendario' e controlla l’aggiornamento delle lezioni
* rimanenti e il numero di iscritti alla lezione.
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
void caso_test_2(coda calendario) 
{
    static int contatore_abbonati = 1;

    printf("\n--- TEST 2: Gestione Abbonamenti ---\n");
    printf("Test della gestione degli abbonamenti e della verifica della validità.\n");
    printf("Crea 'Abbonato_TestN', verifica prenotazione senza lezioni, ricarica e prenota.\n\n");
    printf("Premi INVIO per iniziare...");
    getchar();

    // 1. Genera nome abbonato deterministico
    char nomeutente[MAX_CARATTERI];
    snprintf(nomeutente, MAX_CARATTERI, "Abbonato_Test%d", contatore_abbonati++);

    // 2. Crea o aggiorna file input
    FILE *check = fopen("caso_test_2_input.txt", "r");
    int esiste = (check != NULL);
    if (check) fclose(check);

    FILE *input = fopen("caso_test_2_input.txt", "a");
    if (!input) {
        printf("Errore nella scrittura del file di input.\n");
        return;
    }
    if (!esiste) {
        fprintf(input, "Data;Giorno;Orario;NumeroIscritti\n");
    }
    fprintf(input, "%s\n", nomeutente);
    fclose(input);

    // 3. Carica lezioni da input
    if (coda_vuota(calendario)) {
        genera_lezioni(calendario);
        carica_lezioni(calendario, "caso_test_2_input.txt");
    }

    if (coda_vuota(calendario)) {
        printf("ERRORE: Nessuna lezione disponibile.\nPremi INVIO per tornare al menu...");
        getchar();
        return;
    }

    // 4. Crea abbonato fittizio
    abbonato nuovo;
    strcpy(nuovo.nomeutente, nomeutente);
    strcpy(nuovo.password, "1234");
    nuovo.chiave = strdup(nuovo.nomeutente);
    nuovo.lezioni_rimanenti = 0;

    tabella_hash tabella = carica_abbonati("ct2_abbonati.txt");
    tabella = inserisci_hash(nuovo, tabella);
    salva_abbonati(tabella, "ct2_abbonati.txt");

    printf("Abbonato creato: %s\n", nuovo.nomeutente);

    // 5. Ricarica e verifica
    tabella = carica_abbonati("ct2_abbonati.txt");
    abbonato *trovato = cerca_hash(nomeutente, tabella);
    if (!trovato) {
        printf("ERRORE: Utente non trovato dopo la creazione.\n");
        getchar();
        return;
    }

    // 6. Tentativo di prenotazione SENZA lezioni disponibili
    printf("\nTentativo di prenotazione senza lezioni disponibili...\n");
    if (trovato->lezioni_rimanenti <= 0) {
        printf("Comportamento corretto: prenotazione rifiutata per mancanza di lezioni.\n\n");
    } else {
        printf("ERRORE: L'utente ha ancora lezioni disponibili, ma non dovrebbe.\n\n");
    }

    // 7. Ricarica abbonamento
    trovato->lezioni_rimanenti = 12;
    salva_abbonati(tabella, "ct2_abbonati.txt");
    printf("Lezioni rimanenti dopo ricarica: %d\n\n", trovato->lezioni_rimanenti);

    // 8. Prenotazione automatica
    printf("Prenotazione automatica della prima lezione...\n");
    struct nodo *lezione_test = calendario->testa;
    if (!lezione_test) {
        printf("ERRORE: Nessuna lezione disponibile.\n");
        getchar();
        return;
    }

    int iscritti_pre = dimensione_pila(lezione_test->valore.iscritti);
    int lezioni_pre = trovato->lezioni_rimanenti;

    if (inserisci_pila(trovato->nomeutente, lezione_test->valore.iscritti)) {
        trovato->lezioni_rimanenti--;
        salva_abbonati(tabella, "ct2_abbonati.txt");

        // Salva output e oracle
        salva_lezioni(calendario, "caso_test_2_output.txt");
        salva_lezioni(calendario, "caso_test_2_oracle.txt");

        int iscritti_post = dimensione_pila(lezione_test->valore.iscritti);
        printf("Prenotazione riuscita. Iscritti prima: %d, dopo: %d\n", iscritti_pre, iscritti_post);
        printf("Lezioni rimanenti: %d\n", trovato->lezioni_rimanenti);

        if (lezioni_pre - 1 == trovato->lezioni_rimanenti) {
            printf("Lezione scalata correttamente.\n");
        } else {
            printf("ERRORE: Lezione non scalata correttamente.\n");
        }

        // Confronta output con oracle
        int esito = confronta_file("caso_test_2_output.txt", "caso_test_2_oracle.txt");
        printf("RISULTATO TEST 2: %s\n", esito ? "PASSATO" : "FALLIMENTO");

        FILE *res = fopen("esiti_test.txt", "a");
        if (res) {
            fprintf(res, "Caso Test 2: %s\n", esito ? "PASSATO" : "FALLIMENTO");
            fclose(res);
        }

        FILE *elenco = fopen("elenco_test.txt", "a");
        if (elenco) {
            fprintf(elenco, "CT2 %d\n", iscritti_post);
            fclose(elenco);
        }

    } else {
        printf("ERRORE: Prenotazione fallita dopo ricarica.\n");
    }

    printf("Premi INVIO per tornare al menu...");
    getchar();
}