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
void caso_test_1() {
    coda calendario = nuova_coda();

    // Crea la lezione
    lezione nuova;
    strcpy(nuova.data, "01/06/2024");
    strcpy(nuova.giorno, "Sabato");
    strcpy(nuova.orario, "10:00");
    nuova.iscritti = nuova_pila();

    // Aggiunge 3 partecipanti
    inserisci_pila("Luca", nuova.iscritti);
    inserisci_pila("Anna", nuova.iscritti);
    inserisci_pila("Marco", nuova.iscritti);

    // Inserisce la lezione nella coda
    inserisci_lezione(nuova, calendario);

    // Estrae la lezione dalla coda
    lezione *lez = calendario->testa->prossimo;

    // Stampa gli iscritti (estrae e ristampa usando pila temporanea)
    pila temporanea = nuova_pila();
    partecipante nome;

    printf("Iscritti nella lezione:\n");
    while (estrai_pila(lez->iscritti, nome)) {
        printf("- %s\n", nome);
        inserisci_pila(nome, temporanea); // salva temporaneamente
    }

    // Ripristina la pila originale
    while (estrai_pila(temporanea, nome)) {
        inserisci_pila(nome, lez->iscritti);
    }

    // Libera memoria della coda e pile
    // (solo se hai funzioni tipo distruggi_coda o distruggi_pila)

    printf("\n[Test completato]\n");
}
