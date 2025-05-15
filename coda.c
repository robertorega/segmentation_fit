#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "lezione.h"
#include "coda.h"
#define ELEMENTO_NULLO ((lezione){ NULL, "", "", "" })

struct nodo
{
    lezione valore;
    struct nodo *prossimo;
};

struct c_coda
{
	struct nodo *testa,*coda;
	int numel;
};

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
coda nuova_coda(void)
{
	struct c_coda *calendario;
	calendario = malloc(sizeof(struct c_coda));
	if (calendario == NULL)
		return NULL;
	
	calendario->numel = 0;
	calendario->testa = NULL;
	calendario->coda = NULL;
	return calendario;
}

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
int coda_vuota(coda calendario)
{
	if (calendario == NULL)
		return -1;
	return calendario->numel == 0;
}

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
int inserisci_lezione(lezione val, coda calendario)
{ 
	if (calendario == NULL)
		return -1;

	struct nodo *nuovo;
	nuovo = malloc(sizeof(struct nodo));
	if (nuovo == NULL)
		return 0;

	nuovo->valore = val;
	nuovo->prossimo = NULL;

	if (calendario->testa == NULL)
    		calendario->testa = nuovo;
	else
    		calendario->coda->prossimo = nuovo;

	calendario->coda = nuovo;
	(calendario->numel)++;
	return 1;
}

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
lezione rimuovi_lezione(coda calendario)
{
	if (calendario == NULL)
		return ELEMENTO_NULLO;
	if (calendario->numel == 0)
        	return ELEMENTO_NULLO; 

	lezione risultato = calendario->testa->valore;
	struct nodo *temp = calendario->testa; 
	calendario->testa = calendario->testa->prossimo; 
	free(temp); 

	if (calendario->testa == NULL)
		calendario->coda = NULL;

	(calendario->numel)--;
	return risultato;
}

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
int giorno_lezione(int giorno_settimana, char *giorno, char *orario)
{
	switch (giorno_settimana)
	{
    		case 1: // Lunedì
        	strcpy(giorno, "Lunedi");
        	strcpy(orario, "10-12");
        	return 1;
    		case 3: // Mercoledì
        	strcpy(giorno, "Mercoledi");
        	strcpy(orario, "16-18");
        	return 1;
    		case 5: // Venerdì
        	strcpy(giorno, "Venerdi");
        	strcpy(orario, "16-18");
        	return 1;
    		case 6: // Sabato
        	strcpy(giorno, "Sabato");
        	strcpy(orario, "10-12");
        	return 1;
    		default:
        	return 0;
	}
}

/* Funzione: genera_lezioni
*
* Popola la coda calendario con tutte le lezioni previste nei prossimi 30 giorni
*
* Parametri:
* calendario: la coda dove inserire le lezioni generate
*
* Pre-condizione:
* calendario deve essere una coda inizializzata
*
* Post-condizione:
* Aggiunge in calendario tutte le lezioni che cadono nei giorni validi (Lun, Mer, Ven, Sab)
*
* Side-effect:
* Inserisce dinamicamente nuove lezioni nella coda
*/
void genera_lezioni(coda calendario)
{
	time_t t = time(NULL);
	struct tm oggi = *localtime(&t);

	for (int i = 0; i < 30; i++) {
    		struct tm temp = oggi;
    		temp.tm_mday += i;
    		mktime(&temp); // normalizza la data

    		char giorno[20];
    		char orario[20];
   	 
    		if (giorno_lezione(temp.tm_wday, giorno, orario))
		{
        		lezione l;
        		l.iscritti = nuova_pila();
        		strftime(l.data, sizeof(l.data), "%d/%m/%Y", &temp);
        		strcpy(l.giorno, giorno);
        		strcpy(l.orario, orario);
        		inserisci_lezione(l, calendario);
        	}
    }
}

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
void stampa_lezioni(coda calendario)
{
	struct nodo *corrente = calendario->testa;
	int indice = 1;

	printf("\nLezioni disponibili:\n");

	while (corrente != NULL)
	{
    		int num_iscritti = dimensione_pila(corrente->valore.iscritti);
    		printf("%d) Data: %s - Giorno: %s - Orario: %s - ",
		indice, corrente->valore.data, corrente->valore.giorno, corrente->valore.orario);

    		if (num_iscritti >= MASSIMO_PILA)
        		printf("Posti esauriti\n");
    		else
        		printf("Posti disponibili: %d/%d\n", MASSIMO_PILA - num_iscritti, MASSIMO_PILA);

    		corrente = corrente->prossimo;
    		indice++;
	}
}

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
void prenota_lezione(coda calendario)
{
	if (coda_vuota(calendario))
	{
    		printf("Non ci sono lezioni disponibili.\n");
    		return;
	}

	stampa_lezioni(calendario);
	printf("Costo ingresso singolo: 15€");

	char risposta;
	printf("\nDesideri prenotare una lezione? (s/n): ");
	scanf(" %c", &risposta);
	getchar();  // consuma il newline

	if (risposta != 's' && risposta != 'S')
	{
        printf("Prenotazione annullata.\n");
		return;
    }

	char scelta[10];
	printf("Inserisci il numero della lezione a cui vuoi iscriverti: "); //CONTROLLO VALORE!!!
	fgets(scelta, sizeof(scelta), stdin);

	// Naviga alla lezione scelta
	struct nodo *corrente = calendario->testa;
	int indice = 1;
	while (corrente != NULL && indice < atoi(scelta))
	{
    		corrente = corrente->prossimo;
    		indice++;
	}

	if (corrente == NULL)
	{
    		printf("Scelta non valida.\n");
    		return;
	}

	if (dimensione_pila(corrente->valore.iscritti) >= MASSIMO_PILA)
	{
    		printf("Mi dispiace, la lezione è al completo!\n");
    		return;
	}

	partecipante nome;
	printf("Inserisci il tuo nome per prenotarti: ");
	fgets(nome, sizeof(nome), stdin);
	nome[strcspn(nome, "\n")] = 0; // rimuove newline

	if (inserisci_pila(nome, corrente->valore.iscritti))
    printf("Prenotazione completata per %s\nTi è stato addebitato il costo di 15€\n", nome);

	else
    printf("Errore nella prenotazione.\n");
}
