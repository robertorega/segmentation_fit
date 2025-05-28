#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "utile_hash.h"

// Struttura della tabella hash
struct c_hash 
{
  int dimensione;
  abbonato **tabella;
};

/* Funzione: carica_abbonati
*
* Carica da file i dati degli abbonati e li inserisce in una nuova tabella hash
*
* Descrizione:
* Apre il file specificato in modalità lettura e, per ogni riga correttamente formattata,
* crea un nuovo oggetto abbonato con i dati letti (nome utente, password, lezioni rimanenti).
* Ogni abbonato viene poi inserito nella tabella hash appena creata.
* Se il file non esiste, viene creata una nuova tabella hash vuota con dimensione predefinita.
*
* Parametri:
* nome_file: nome del file da cui leggere i dati
*
* Pre-condizione:
* nome_file è un puntatore a stringa non nullo
*
* Post-condizione:
* Restituisce una tabella hash inizializzata contenente tutti gli abbonati letti dal file.
* Se il file non esiste, la tabella restituita è vuota.
*
* Side-effect:
* Lettura da file e allocazione dinamica di memoria per ciascun abbonato caricato
*/
tabella_hash carica_abbonati(const char *nome_file)
{
	// Prova ad aprire il file
	FILE *file = fopen(nome_file, "r");
    	if (!file)
	{
        	printf("File abbonati non trovato. Verra' creato un nuovo file.\n");
        	return nuova_hash(10);
    	}

	// Crea una nuova tabella hash
    	tabella_hash h = nuova_hash(10);
    	char riga[200];

	// Legge il file riga per riga
	while (fgets(riga, sizeof(riga), file))
	{
        	char *nomeutente = strtok(riga, ";");
        	char *password = strtok(NULL, ";");
       		char *lezioni_str = strtok(NULL, "\n");

		// Crea un nuovo abbonato
        	if (nomeutente && password && lezioni_str)
		{
            		abbonato nuovo;
            		strncpy(nuovo.nomeutente, nomeutente, MAX_CARATTERI);
            		strncpy(nuovo.password, password, MAX_CARATTERI);
            		nuovo.lezioni_rimanenti = atoi(lezioni_str);
            		nuovo.chiave = strdup(nuovo.nomeutente);
            		h = inserisci_hash(nuovo, h); // Inserisce nella tabella
        	}
    	}

    	fclose(file);
    	return h;
}

/* Funzione: salva_abbonati
*
* Salva su file i dati degli abbonati presenti nella tabella hash
*
* Descrizione:
* Apre il file specificato in modalità scrittura e, per ogni elemento presente nella tabella hash,
* scrive una riga contenente nome utente, password e numero di lezioni rimanenti separati da punto e virgola.
* Ogni riga rappresenta un abbonato.
*
* Parametri:
* h: tabella hash contenente gli abbonati da salvare
* nome_file: nome del file su cui salvare i dati
*
* Pre-condizione:
* h è una tabella hash valida e nome_file è un puntatore a stringa non nullo
*
* Side-effect:
* Scrittura su file. Se il file non può essere aperto, viene stampato un messaggio di errore
*/
void salva_abbonati(tabella_hash h, const char *nome_file)
{
	// Apre il file in scrittura
	FILE *file = fopen(nome_file, "w");
    	if (!file)
	{
        	printf("Errore nell'apertura del file per il salvataggio.\n");
        	return;
    	}

	// Scorre tutti gli slot della tabella
    	for (int i = 0; i < h->dimensione; i++)
	{
        	abbonato *corrente = h->tabella[i];
		// Scrive gli abbonati
        	while (corrente != NULL)
		{
            		fprintf(file, "%s;%s;%d\n", corrente->nomeutente, corrente->password, corrente->lezioni_rimanenti);
            		corrente = corrente->prossimo;
        	}
    	}

	fclose(file);
}
