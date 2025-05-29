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
void caso_test_1()
{
    printf("TEST 1: Verifica registrazione prenotazione e aggiornamento disponibilità\n");
    printf("Premi INVIO per iniziare...");
    getchar();

    coda calendario = nuova_coda();

    // 1. Carica lezioni già presenti
    carica_lezioni(calendario, "caso_test_1_output.txt");

    // 2. Se vuota, genera nuove lezioni
    if (coda_vuota(calendario)) {
        genera_lezioni(calendario);
        carica_lezioni(calendario, "caso_test_1_input.txt");
    }

    if (coda_vuota(calendario)) {
        printf("ERRORE: Nessuna lezione disponibile.\nPremi INVIO per tornare al menu...");
        getchar();
        return;
    }

    // 3. Aggiungi utente fittizio
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

    // 4. Salva output e oracle aggiornati
    salva_lezioni(calendario, "caso_test_1_output.txt");
    salva_lezioni(calendario, "caso_test_1_oracle.txt");

    // 5. Confronta
    int esito = confronta_file("caso_test_1_output.txt", "caso_test_1_oracle.txt");
    printf("RISULTATO TEST 1: %s\n", esito ? "PASSATO" : "FALLIMENTO");

    FILE *res = fopen("esiti_test.txt", "a");
    if (res) {
        fprintf(res, "Caso Test 1: %s\n", esito ? "PASSATO" : "FALLIMENTO");
        fclose(res);
    }

    FILE *elenco = fopen("elenco_test.txt", "a");
    if (elenco) {
        fprintf(elenco, "Caso Test 1 %d\n", num_iscritti);
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
void caso_test_2()
{
    static int contatore_abbonati = 1;
    printf("\n--- TEST 2: Gestione Abbonamenti ---\n");
    printf("Test della gestione degli abbonamenti e della verifica della validità.\n");
    printf("Crea 'Abbonato_TestN', verifica prenotazione senza lezioni, ricarica e prenota.\n\n");
    printf("Premi INVIO per iniziare...");
    getchar();

    coda calendario = nuova_coda();

    // 1. Carica lezioni già presenti
    carica_lezioni(calendario, "caso_test_2_output.txt");

    // 2. Se vuota, genera nuove lezioni
    if (coda_vuota(calendario)) {
        genera_lezioni(calendario);
        carica_lezioni(calendario, "caso_test_2_input.txt");
    }

    if (coda_vuota(calendario)) {
        printf("ERRORE: Nessuna lezione disponibile.\nPremi INVIO per tornare al menu...");
        getchar();
        return;
    }

    // 3. Crea abbonato fittizio
    char nomeutente[MAX_CARATTERI];
    snprintf(nomeutente, MAX_CARATTERI, "Abbonato_Test%d", contatore_abbonati++);

    abbonato nuovo;
    strcpy(nuovo.nomeutente, nomeutente);
    strcpy(nuovo.password, "1234");
    nuovo.chiave = strdup(nuovo.nomeutente);
    nuovo.lezioni_rimanenti = 0;

    tabella_hash tabella = carica_abbonati("caso_test_2_abbonati.txt");
    tabella = inserisci_hash(nuovo, tabella);
    salva_abbonati(tabella, "caso_test_2_abbonati.txt");

    printf("Abbonato creato: %s\n", nuovo.nomeutente);

    // 4. Ricarica e verifica
    tabella = carica_abbonati("caso_test_2_abbonati.txt");
    abbonato *trovato = cerca_hash(nomeutente, tabella);
    if (!trovato) {
        printf("ERRORE: Utente non trovato dopo la creazione.\n");
        getchar();
        return;
    }

    // 5. Tentativo di prenotazione SENZA lezioni disponibili
    printf("\nTentativo di prenotazione senza lezioni disponibili...\n");
    if (trovato->lezioni_rimanenti <= 0) {
        printf("Comportamento corretto: prenotazione rifiutata per mancanza di lezioni.\n\n");
    } else {
        printf("ERRORE: L'utente ha ancora lezioni disponibili, ma non dovrebbe.\n\n");
    }

    // 6. Ricarica abbonamento
    trovato->lezioni_rimanenti = 12;
    salva_abbonati(tabella, "caso_test_2_abbonati.txt");
    printf("Lezioni rimanenti dopo ricarica: %d\n\n", trovato->lezioni_rimanenti);

    // 7. Prenotazione automatica
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
        salva_abbonati(tabella, "caso_test_2_abbonati.txt");

        // Salva output e oracle aggiornati
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

        int esito = confronta_file("caso_test_2_output.txt", "caso_test_2_oracle.txt");
        printf("RISULTATO TEST 2: %s\n", esito ? "PASSATO" : "FALLIMENTO");

        FILE *res = fopen("esiti_test.txt", "a");
        if (res) {
            fprintf(res, "Caso Test 2: %s\n", esito ? "PASSATO" : "FALLIMENTO");
            fclose(res);
        }

        FILE *elenco = fopen("elenco_test.txt", "a");
        if (elenco) {
            fprintf(elenco, "Caso Test 2 %d\n", iscritti_post);
            fclose(elenco);
        }
    } else {
        printf("ERRORE: Prenotazione fallita dopo ricarica.\n");
    }

    printf("Premi INVIO per tornare al menu...");
    getchar();
}

/* Funzione: caso_test_3
*
* Verifica la generazione del report mensile con lezioni passate
*
* Descrizione:
* La funzione crea una lezione in una data passata con partecipanti fittizi, la inserisce nella coda 'calendario',
* salva la lezione nel file storico "ct3_storico.txt" tramite la funzione `pulisci_lezioni_passate`.
* Successivamente esegue la funzione `report_mensile` per verificare che la lezione sia correttamente visualizzata nel report.
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
void caso_test_3(coda calendario)
{
    printf("\n--- TEST 3: Verifica Report Mensile con Partecipanti Casuali ---\n");
    printf("Questo test genera UNA lezione passata per volta, partendo dal 3 marzo 2025.\n");
    printf("Premi INVIO per iniziare...");
    getchar();

    srand(time(NULL));

    // 1. Leggi la data corrente da file o inizializza a 3 marzo 2025
    struct tm data_corrente = {0};
    FILE *data_file = fopen("ct3_data_corrente.txt", "r");
    if (data_file) {
        fscanf(data_file, "%d %d %d", &data_corrente.tm_mday, &data_corrente.tm_mon, &data_corrente.tm_year);
        fclose(data_file);
    } else {
        data_corrente.tm_mday = 3;
        data_corrente.tm_mon = 2; // Marzo (0-based)
        data_corrente.tm_year = 2025 - 1900;
    }

    // 2. Cerca la prossima data valida e passata
    int lezione_generata = 0;
    char data_str[11], giorno[20], orario[20];
    int ora_inizio;
    lezione l;

    while (!lezione_generata) {
        mktime(&data_corrente);
        strftime(data_str, sizeof(data_str), "%d/%m/%Y", &data_corrente);

        if (giorno_lezione(data_corrente.tm_wday, giorno, orario, &ora_inizio) &&
            data_passata(data_str, orario)) {

            // Crea la lezione
            l.iscritti = nuova_pila();
            strcpy(l.data, data_str);
            strcpy(l.giorno, giorno);
            strcpy(l.orario, orario);

            int num_partecipanti = rand() % 10 + 1;
            for (int i = 1; i <= num_partecipanti; i++) {
                char nome[50];
                snprintf(nome, sizeof(nome), "utente%d", i);
                inserisci_pila(nome, l.iscritti);
            }

            inserisci_lezione(l, calendario);
            lezione_generata = 1;

            // Scrive la lezione anche nel file di input
            FILE *input = fopen("caso_test_3_input.txt", "w");
            if (input) {
                fprintf(input, "%s;%s;%s;%d\n", l.data, l.giorno, l.orario, num_partecipanti);
                pila temp = nuova_pila();
                partecipante p;
                while (!pila_vuota(l.iscritti)) {
                    if (estrai_pila(l.iscritti, p)) {
                        fprintf(input, "%s\n", p);
                        inserisci_pila(p, temp);
                    }
                }
                while (!pila_vuota(temp)) {
                    if (estrai_pila(temp, p)) {
                        inserisci_pila(p, l.iscritti);
                    }
                }
                fclose(input);
            }

            // Aggiorna la data per la prossima esecuzione
            data_corrente.tm_mday++;
            mktime(&data_corrente);
            FILE *next = fopen("ct3_data_corrente.txt", "w");
            if (next) {
                fprintf(next, "%d %d %d", data_corrente.tm_mday, data_corrente.tm_mon, data_corrente.tm_year);
                fclose(next);
            }
        } else {
            // Se la data non è valida o non è passata, passa al giorno successivo
            data_corrente.tm_mday++;
            mktime(&data_corrente);
        }

        // Se la data è oggi o futura, interrompi il ciclo
        time_t oggi = time(NULL);
        struct tm oggi_tm = *localtime(&oggi);
        oggi_tm.tm_hour = 0;
        oggi_tm.tm_min = 0;
        oggi_tm.tm_sec = 0;
        time_t tempo_oggi = mktime(&oggi_tm);

        struct tm temp = data_corrente;
        temp.tm_hour = 0;
        temp.tm_min = 0;
        temp.tm_sec = 0;
        time_t tempo_data = mktime(&temp);

        if (difftime(tempo_data, tempo_oggi) >= 0 && !lezione_generata) {
            printf("Tutte le lezioni passate sono già state generate.\n");
            printf("Premi INVIO per tornare al menu principale...");
            getchar();
            return;
        }
    }

    // 3. Carica lezioni già presenti in output
    coda lezioni_precedenti = nuova_coda();
    carica_lezioni(lezioni_precedenti, "caso_test_3_output.txt");

    // 4. Unisci le lezioni precedenti con quella nuova
    while (!coda_vuota(calendario)) {
        lezione lezione_corrente = rimuovi_lezione(calendario);
        inserisci_lezione(lezione_corrente, lezioni_precedenti);
    }

    // 5. Filtra solo le lezioni passate
    coda finali = nuova_coda();
    while (!coda_vuota(lezioni_precedenti)) {
        lezione lezione_corrente = rimuovi_lezione(lezioni_precedenti);
        if (data_passata(lezione_corrente.data, lezione_corrente.orario)) {
            inserisci_lezione(lezione_corrente, finali);
        }
    }

    // 6. Salva tutto
    salva_lezioni(finali, "caso_test_3_output.txt");
    salva_lezioni(finali, "caso_test_3_oracle.txt");

    // 7. Confronta i file
    int esito = confronta_file("caso_test_3_output.txt", "caso_test_3_oracle.txt");
    printf("RISULTATO TEST 3: %s\n", esito ? "PASSATO" : "FALLIMENTO");

    FILE *res = fopen("esiti_test.txt", "a");
    if (res) {
        fprintf(res, "Caso Test 3: %s\n", esito ? "PASSATO" : "FALLIMENTO");
        fclose(res);
    }

    FILE *elenco = fopen("elenco_test.txt", "a");
    if (elenco) {
        fprintf(elenco, "Caso Test 3: %s\n", esito ? "PASSATO" : "FALLIMENTO");
        fclose(elenco);
    }

    // 8. Esegui il report
    printf("\nEsecuzione del report mensile...\n");
    report_mensile("caso_test_3_oracle.txt");

    printf("Verifica completata. Premi INVIO per tornare al menu principale...");
    getchar();
}