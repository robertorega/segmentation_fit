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

// Legge input, aggiunge un utente, aggiorna input e oracle
int aggiorna_input_e_oracle(const char *input_file, const char *oracle_file, char utenti[][MASSIMO_LINEA ]) 
{
    FILE *f = fopen(input_file, "r");
    if (!f) return -1;

    char intestazione[MASSIMO_LINEA];
    fgets(intestazione, sizeof(intestazione), f);

    int num_iscritti;
    sscanf(intestazione, "%*[^;];%*[^;];%*[^;];%d", &num_iscritti);

    for (int i = 0; i < num_iscritti; i++) {
        fgets(utenti[i], MASSIMO_LINEA, f);
    }
    fclose(f);

    // Aggiungi nuovo utente
    snprintf(utenti[num_iscritti], MASSIMO_LINEA, "Utente_Test%d\n", num_iscritti + 1);
    num_iscritti++;

    // Riscrivi input e oracle aggiornati
    char nuova_intestazione[MASSIMO_LINEA];
    sscanf(intestazione, "%[^;];%*[^;];%*[^;];", nuova_intestazione);
    char giorno[20], orario[20];
    sscanf(intestazione, "%*[^;];%[^;];%[^;];", giorno, orario);
    FILE *out1 = fopen(input_file, "w");
    FILE *out2 = fopen(oracle_file, "w");
    if (!out1 || !out2) return -1;

    fprintf(out1, "%s;%s;%s;%d\n", nuova_intestazione, giorno, orario, num_iscritti);
    fprintf(out2, "%s;%s;%s;%d\n", nuova_intestazione, giorno, orario, num_iscritti);
    for (int i = 0; i < num_iscritti; i++) {
        fputs(utenti[i], out1);
        fputs(utenti[i], out2);
    }
    fclose(out1);
    fclose(out2);
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

    if (coda_vuota(calendario)) 
    {
        genera_lezioni(calendario);
        carica_lezioni(calendario, "caso_test_1_input.txt");
    }

    if (coda_vuota(calendario)) 
    {
        printf("ERRORE: Nessuna lezione disponibile.\nPremi INVIO per tornare al menu...");
        getchar();
        return;
    }

    char utenti[MASSIMO_UTENTI][MASSIMO_LINEA];
    int num_iscritti = aggiorna_input_e_oracle("caso_test_1_input.txt", "caso_test_1_oracle.txt", utenti);
    if (num_iscritti == -1) 
    {
        printf("Errore nella lettura o scrittura dei file di test.\n");
        printf("Possiamo fare altro per te? Premi INVIO...");
        getchar();
        return;
    }

    // Aggiungi l'utente alla pila della prima lezione
    lezione *lez = &calendario->testa->valore;
    lez->iscritti = nuova_pila();   
    inserisci_pila(utenti[num_iscritti - 1], lez->iscritti); // ultimo utente aggiunto

    // Salva lo stato reale
    salva_lezioni(calendario, "caso_test_1_output.txt");

    // Confronta output con oracle
    int esito = confronta_file("caso_test_1_output.txt", "caso_test_1_oracle.txt");

    // Stampa risultato
    printf("RISULTATO TEST 1: %s\n", esito ? "PASS" : "FAIL");
    
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
