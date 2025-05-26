#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"  

// Struttura della tabella hash
struct c_hash 
{
	int dimensione;
	abbonato **tabella;
};

/* Funzione: nuova_hash
*
* Crea e inizializza una nuova tabella hash
*
* Descrizione: 
* Viene allocata dinamicamente una struttura hash e una tabella di puntatori a abbonato 
* della dimensione specificata in input. Ogni slot della tabella viene inizializzato a NULL 
* tramite calloc, garantendo che tutti i puntatori siano azzerati.
*
* Parametri:
* dimensione: numero di slot nella tabella hash
*
* Pre-condizione:
* dimensione>0
*
* Post-condizione:
* Restituisce una tabella hash con i puntatori inizializzati a 0
*
* Side-effect:
* Alloca memoria dinamica per la nuova tabella hash
*/
tabella_hash nuova_hash(int dimensione) 
{
	// Alloca la struttura principale
	tabella_hash h = malloc(sizeof(struct c_hash));
	if (h == NULL) 
    		return NULL;

	h->dimensione = dimensione;
	h->tabella = calloc(dimensione, sizeof(abbonato *));
	if (h->tabella == NULL) 
    	{
    		free(h);
    		return NULL;
	}

	return h;
}

/* Funzione: calcola_indice
*
* Calcola l'indice nella tabella hash associato alla stringa chiave
*
* Descrizione:
* La funzione calcola un valore intero a partire da una stringa utilizzando 
* una funzione di hash semplice basata su moltiplicazioni successive con 31 
* Il risultato viene poi ridotto modulo dimensione per garantire che l’indice rientri 
* nell’intervallo valido degli slot della tabella hash
*
* Parametri:
* chiave: la stringa di cui si vuole calcolare l'indice 
* dimensione: numero di slot nella tabella hash
*
* Pre-condizione:
* chiave è una stringa non nulla che termina con \0 e dimensione>0
*
* Post-condizione:
* 0<=indice<dimensione (l'indice denota quale slot della tabella andare a leggere o scrivere)
*/
int calcola_indice(char *chiave, int dimensione)
{
	unsigned int hash = 0;

	// Calcola il valore hash moltiplicativo
	while (*chiave)
    	{
    		hash = hash * 31 + *chiave++;
	}

	// Applica il modulo per ottenere l'indice
	return hash % dimensione;
}

/* Funzione: inserisci_hash
*
* Inserisce un nuovo elemento (nuovo) nella tabella hash h
*
* Descrizione:
* La funzione calcola l’indice della chiave del nuovo abbonato all’interno della tabella hash, 
* utilizzando la funzione calcola_indice. Scorre poi la lista collegata in quella posizione per 
* verificare se la chiave è già presente: se sì, la funzione termina senza modificare la tabella. 
* In caso contrario, alloca un nuovo nodo abbonato, duplica la chiave con strdup, copia 
* nome utente e password (assicurandosi che siano null-terminate), e lo inserisce in testa 
* alla lista nella posizione calcolata
*
* Parametri:
* nuovo: elemento da inserire (contiene: chiave, nomeutente, password)
* h: tabella hash in cui inserire l'oggetto
*
* Pre-condizione:
* nuovo.chiave è una stringa non vuota, h deve essere una tabella hash valida
*
* Post-condizione:
* se nuovo.chiave non è presente nella tabella, viene inserito un nuovo nodo                                
* Altrimenti la tabella rimane invariata
*
* Side-effect:
* Viene allocata memoria dinamicamente per un nuovo nodo e duplicata la chiave
*/
tabella_hash inserisci_hash(abbonato nuovo, tabella_hash h) 
{
	// Calcola la posizione nella tabella
	int indice = calcola_indice(nuovo.chiave, h->dimensione);
	abbonato *corrente = h->tabella[indice];

	// Verifica se la chiave esiste già
	while (corrente != NULL)
	{
    		if (strcmp(corrente->chiave, nuovo.chiave) == 0)
        	{
        		return h;  // Chiave già presente
    		}

    		corrente = corrente->prossimo;
	}

	// Alloca il nuovo nodo
	abbonato *nodo = malloc(sizeof(abbonato));
	if (nodo == NULL) 
    		return h;

	// Copia i dati dell'abbonato
	nodo->chiave = strdup(nuovo.chiave);
	strncpy(nodo->nomeutente, nuovo.nomeutente, MAX_CARATTERI - 1);
	nodo->nomeutente[MAX_CARATTERI - 1] = '\0';
	strncpy(nodo->password, nuovo.password, MAX_CARATTERI - 1);
	nodo->password[MAX_CARATTERI - 1] = '\0';

	// Inserisce in testa
	nodo->lezioni_rimanenti = nuovo.lezioni_rimanenti;
	nodo->prossimo = h->tabella[indice];
	h->tabella[indice] = nodo;

	return h;
}

/* Funzione: cerca_hash
* Cerca nella tabella hash h un elemento con chiave uguale a chiave e lo restituisce se trovato
* 
* Descrizione:
* La funzione calcola l'indice associato alla chiave usando la funzione calcola_indice
* Poi scorre la lista collegata presente in quella posizione della tabella hash
* Se trova un nodo con chiave uguale a quella cercata lo restituisce
* In caso contrario restituisce NULL
*
* Parametri:
* chiave: elemento da cercare nella tabella 
* h: tabella hash in cui si cerca l'elemento
*
* Pre-condizione:
* chiave è una stringa non vuota e h è una tabella hash valida
*
* Post-condizione:
* restituisce l'elemento se presente nella tabella, altrimenti NULL
*/
abbonato* cerca_hash(char *chiave, tabella_hash h) 
{
	// Calcola la posizione nella tabella
	int indice = calcola_indice(chiave, h->dimensione);
	abbonato *corrente = h->tabella[indice];

	// Scorre la lista cercando la chiave
	while (corrente != NULL) 
    	{
    		if (strcmp(corrente->chiave, chiave) == 0) 
        	return corrente;

    		corrente = corrente->prossimo;
	}
	return NULL;
}

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
* Post-condizione:
* Se il file è accessibile in scrittura, i dati degli abbonati sono salvati correttamente
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
