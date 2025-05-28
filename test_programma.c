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
    while (fgets(r1, sizeof(r1), f1) && fgets(r2, sizeof(r2), f2)) 
    {
        if (strcmp(r1, r2) != 0) {

            fclose(f1); fclose(f2);
            return 0;
        }
    }

    int fine1 = feof(f1), fine2 = feof(f2);
    fclose(f1); fclose(f2);
    return fine1 && fine2;
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
        strcpy(utenti[num_iscritti], linea);
        num_iscritti++;
    }
    fclose(f);

    // Aggiunge nuovo utente
    snprintf(utenti[num_iscritti], MASSIMO_LINEA, "Utente_Test%d", num_iscritti + 1);
    num_iscritti++;

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
void caso_test_1(coda calendario) {
    printf("TEST 1: Verifica registrazione prenotazione e aggiornamento disponibilità\n");
    printf("Premi INVIO per iniziare...");
    getchar();

    // 1. Se la coda è vuota, crea una lezione fittizia
    if (coda_vuota(calendario)) {
        lezione nuova;
        strcpy(nuova.data, "28/05/2025");
        strcpy(nuova.giorno, "Mercoledi");
        strcpy(nuova.orario, "16-18");
        nuova.iscritti = nuova_pila();
        inserisci_coda(calendario, nuova);
    }

    // 2. Recupera la prima lezione
    lezione *lez = &calendario->testa->valore;

    if (lez->iscritti == NULL) {
        lez->iscritti = nuova_pila();
    }

    // 3. Aggiunge utente fittizio
    int numero_attuali = dimensione_pila(lez->iscritti);
    partecipante nuovo_utente;
    snprintf(nuovo_utente, MASSIMO_LINEA, "Utente_Test%d", numero_attuali + 1);
    inserisci_pila(nuovo_utente, lez->iscritti);

    // 4. Salva su file "caso_test_1_output.txt"
    FILE *out = fopen("caso_test_1_output.txt", "w");
    if (out) {
        fprintf(out, "Data;Giorno;Orario;Iscritti\n");
        fprintf(out, "%s;%s;%s;%d\n", lez->data, lez->giorno, lez->orario, dimensione_pila(lez->iscritti));

        // Stampa anche i partecipanti
        pila temporanea = nuova_pila();
        partecipante tmp;

        while (estrai_pila(lez->iscritti, tmp)) {
            fprintf(out, "%s", tmp);
            if (tmp[strlen(tmp)-1] != '\n') fprintf(out, "\n"); // assicurati che ogni riga finisca a capo
            inserisci_pila(tmp, temporanea);
        }

        // Ripristina la pila originale
        while (estrai_pila(temporanea, tmp)) {
            inserisci_pila(tmp, lez->iscritti);
        }

        fclose(out);
    } else {
        printf("Errore apertura file output.\nPremi INVIO per tornare al menu...");
        getchar();
        return;
    }

    // 5. Crea oracle se non esiste
    FILE *oracle = fopen("caso_test_1_oracle.txt", "r");
    if (!oracle) {
        FILE *src = fopen("caso_test_1_output.txt", "r");
        FILE *dst = fopen("caso_test_1_oracle.txt", "w");
        if (src && dst) {
            char ch;
            while ((ch = fgetc(src)) != EOF) {
                fputc(ch, dst);
            }
            printf("Creato file oracle.\n");
        }
        if (src) fclose(src);
        if (dst) fclose(dst);
    } else {
        fclose(oracle);
    }

    // 6. Confronta file output e oracle
    FILE *f1 = fopen("caso_test_1_output.txt", "r");
    FILE *f2 = fopen("caso_test_1_oracle.txt", "r");
    int esito = 1;
    if (f1 && f2) {
        char r1[MASSIMO_LINEA], r2[MASSIMO_LINEA];
        while (fgets(r1, MASSIMO_LINEA, f1) && fgets(r2, MASSIMO_LINEA, f2)) {
            if (strcmp(r1, r2) != 0) {
                esito = 0;
                break;
            }
        }
        if (!(feof(f1) && feof(f2))) esito = 0;
        fclose(f1);
        fclose(f2);
    } else {
        esito = 0;
    }

    printf("RISULTATO TEST 1: %s\n", esito ? "PASS" : "FAIL");

    FILE *res = fopen("esiti_test.txt", "a");
    if (res) {
        fprintf(res, "Caso Test 1: %s\n", esito ? "PASSATO" : "FALLIMENTO");
        fclose(res);
    }

    FILE *elenco = fopen("elenco_test.txt", "w");
    if (elenco) {
        fprintf(elenco, "CT1 %d\n", dimensione_pila(lez->iscritti));
        fclose(elenco);
    }

    printf("Premi INVIO per tornare al menu...");
    getchar();
}