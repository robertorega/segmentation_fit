#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "coda.h"
#include "lezione.h"
#include "hash.h"

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

/* Funzione: carica_lezioni
*
* Carica le lezioni salvate da un file e le inserisce nella coda calendario
*
* Descrizione:
* La funzione apre il file indicato in modalità lettura e scrittura
* Per ogni lezione trovata nel file legge la data il giorno l'orario e il numero di iscritti
* Crea una nuova pila per gli iscritti e li inserisce uno alla volta leggendo righe successive
* Alla fine inserisce la lezione completa nella coda calendario
* Se il file non esiste viene creato automaticamente
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
void carica_lezioni(coda calendario, const char *nome_file)
{
	FILE *fp = fopen(nome_file, "a+");  // apre in lettura/scrittura e crea se non esiste
	if (fp == NULL)
	{
		perror("Errore apertura file");
        	return;
	}

	rewind(fp); // torna all'inizio del file

	char linea[256];
	while (fgets(linea, sizeof(linea), fp))
	{
		lezione l;
		int numero_iscritti;

        	if (sscanf(linea, "%[^;];%[^;];%[^;];%d", l.data, l.giorno, l.orario, &numero_iscritti) == 4)
		{
        		l.iscritti = nuova_pila();

        		for (int i = 0; i < numero_iscritti; i++)
			{
                		if (fgets(linea, sizeof(linea), fp))
				{
                			linea[strcspn(linea, "\n")] = 0;
                			inserisci_pila(linea, l.iscritti);
        			}
            		}

        		inserisci_lezione(l, calendario);
        	}
	}

    	fclose(fp);
}

/* Funzione: nuova_coda
*
* Crea e inizializza una nuova coda vuota
*
* Descrizione:
* La funzione alloca dinamicamente memoria per una struttura di tipo c_coda
* Inizializza il numero di elementi a zero e i puntatori testa e coda a NULL
* Restituisce un puntatore alla nuova coda vuota creata
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
* Descrizione:
* La funzione controlla se il puntatore alla coda è NULL
* In tal caso restituisce -1 per segnalare un errore
* Altrimenti restituisce 1 se la coda è vuota o 0 se contiene elementi
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
* Descrizione:
* La funzione alloca dinamicamente un nuovo nodo contenente la lezione da inserire
* Se la coda è vuota imposta il nuovo nodo come testa della coda
* Altrimenti lo collega in fondo alla coda esistente
* In entrambi i casi aggiorna il puntatore alla coda e incrementa il numero di elementi
* Restituisce 1 in caso di successo 0 se l'allocazione fallisce -1 se la coda è NULL
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
* Descrizione:
* La funzione controlla se la coda è NULL o vuota e in tal caso restituisce ELEMENTO_NULLO
* Altrimenti salva la lezione del primo nodo, aggiorna il puntatore alla testa
* Dealloca il nodo rimosso e aggiorna il numero di elementi nella coda
* Se la coda diventa vuota aggiorna anche il puntatore alla coda
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
* Descrizione:
* La funzione controlla se il valore del giorno della settimana corrisponde a uno dei giorni in cui sono previste lezioni
* Se il giorno è valido copia il nome del giorno e la fascia oraria corrispondente nelle stringhe passate come parametri
* Restituisce 1 se il giorno è valido altrimenti restituisce 0
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
* Genera e aggiunge alla coda calendario le lezioni previste nei prossimi 30 giorni, evitando duplicati
*
* Descrizione:
* La funzione analizza i prossimi 30 giorni a partire dalla data odierna
* Per ogni giorno controlla se è previsto lo svolgimento di una lezione
* Se il giorno è valido e la lezione con quella data e orario non è già presente nella coda
* allora crea una nuova lezione vuota e la inserisce nel calendario
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
void genera_lezioni(coda calendario) //NUOVA 16/05 (CON FILE)
{
	time_t t = time(NULL);
	struct tm oggi = *localtime(&t);

	for (int i = 0; i < 30; i++)
	{
        	struct tm temp = oggi;
        	temp.tm_mday += i;
        	mktime(&temp);

        	char data[11];
        	char giorno[20];
        	char orario[20];

        	if (giorno_lezione(temp.tm_wday, giorno, orario))
		{
            		strftime(data, sizeof(data), "%d/%m/%Y", &temp);

            		// Controlla se esiste già una lezione in questa data e orario
            		struct nodo *corrente = calendario->testa;
            		int trovata = 0;
            		while (corrente != NULL)
			{
                		if (strcmp(corrente->valore.data, data) == 0 && strcmp(corrente->valore.orario, orario) == 0)
				{
                    			trovata = 1;
                    			break;
                		}
                		corrente = corrente->prossimo;
            		}

            		if (!trovata)
			{
                		lezione l;
                		l.iscritti = nuova_pila();
                		strcpy(l.data, data);
                		strcpy(l.giorno, giorno);
                		strcpy(l.orario, orario);
                		inserisci_lezione(l, calendario);
            		}
        	}
    	}
}

/* Funzione: stampa_lezioni
*
* Stampa l’elenco delle lezioni presenti nella coda, con data, giorno, orario e disponibilità
*
* Descrizione:
* La funzione scorre la coda delle lezioni e per ogni lezione mostra le informazioni principali
* Viene indicato se ci sono posti disponibili o se la lezione è al completo
* Ogni lezione è numerata per facilitare eventuali selezioni da parte dell'utente
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

	printf("\nLezioni di fitness disponibili:\n");

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
* Descrizione:
* La funzione mostra all'utente l'elenco delle lezioni disponibili e consente di selezionare una lezione
* Tramite input, l'utente sceglie la lezione desiderata e inserisce il proprio nome per prenotarsi
* Se ci sono posti disponibili, il nome viene inserito nella pila degli iscritti della lezione scelta
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
		printf("Possiamo fare altro per te? Premi INVIO...");
        getchar();
    	return;
	}

	printf("--- Prenota una Lezione di Fitness ---\n");
	stampa_lezioni(calendario);
	printf("Costo ingresso singolo: 15€");

	char risposta;
	printf("\n\nDesideri prenotare una lezione? (s/n): ");
	scanf(" %c", &risposta);
	getchar();  // consuma il newline

	if (risposta != 's' && risposta != 'S')
	{
        printf("Prenotazione annullata.\n");
		printf("Possiamo fare altro per te? Premi INVIO...");
        getchar();
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
		printf("Premi INVIO\n");
        getchar();
    	return;
	}

	if (dimensione_pila(corrente->valore.iscritti) >= MASSIMO_PILA)
	{
    	printf("Mi dispiace, la lezione è al completo!\n");
		printf("Possiamo fare altro per te? Premi INVIO\n");
        getchar();
    	return;
	}

	partecipante nome;
	printf("Inserisci il tuo nome per prenotarti: ");
	fgets(nome, sizeof(nome), stdin);
	nome[strcspn(nome, "\n")] = 0; // rimuove newline

	if (inserisci_pila(nome, corrente->valore.iscritti))
	{
        printf("Prenotazione completata per %s\nTi è stato addebitato il costo di 15€\n", nome);
		printf("Possiamo fare altro per te? Premi INVIO...");
    	getchar(); 
    }
	
    else
	{
      printf("Errore nella prenotazione.\n");
	  printf("Possiamo fare altro per te? Premi INVIO...");
    getchar();
	}
}

/* Funzione: prenota_lezione_abbonato
*
* Prenota una lezione per un utente abbonato
*
* Descrizione:
* La funzione permette a un utente abbonato di prenotare una lezione tra quelle disponibili
* Dopo aver verificato la disponibilità delle lezioni e delle lezioni rimanenti dell’abbonato,
* viene richiesto all’utente di selezionare una lezione. Se non è già iscritto e ci sono posti liberi,
* l’utente viene aggiunto alla pila degli iscritti della lezione e le sue lezioni rimanenti vengono decrementate
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
void prenota_lezione_abbonato(coda calendario, abbonato *utente_loggato)
{
	if (coda_vuota(calendario)) {
    	printf("Non ci sono lezioni disponibili.\n");
		printf("Possiamo fare altro per te? Premi INVIO...");
        getchar();
    	return;
	}

	stampa_lezioni(calendario);

	char risposta;
	printf("\nDesideri prenotare una lezione, %s? (s/n): ", utente_loggato->nomeutente);
	scanf(" %c", &risposta);
	getchar();  // consuma newline

	if (risposta != 's' && risposta != 'S') {
    		printf("Prenotazione annullata.\n");
		printf("Possiamo fare altro per te? Premi INVIO...");
        	getchar();
    		return;
	}

	if (utente_loggato->lezioni_rimanenti <= 0) {
    	printf("Non hai lezioni rimanenti. Rinnova l'abbonamento o acquista più lezioni.\n");
		printf("Possiamo fare altro per te? Premi INVIO...");
        getchar();
    	return;
	}

	char scelta[10];
	printf("Inserisci il numero della lezione a cui vuoi iscriverti: ");
	fgets(scelta, sizeof(scelta), stdin);
    scelta[strcspn(scelta, "\n")] = 0;

	struct nodo *corrente = calendario->testa;
	int indice = 1;
	while (corrente != NULL && indice < atoi(scelta)) {
    	corrente = corrente->prossimo;
    	indice++;
	}

	if (corrente == NULL) {
    	printf("Scelta non valida.\n");
		printf("Possiamo fare altro per te? Premi INVIO...");
        getchar();
    	return;
	}

	if (dimensione_pila(corrente->valore.iscritti) >= MASSIMO_PILA) {
    	printf("Mi dispiace, la lezione è al completo!\n");
		printf("Possiamo fare altro per te? Premi INVIO...");
        getchar();
    	return;
	}

	// Controllo se l'utente è già iscritto
	pila temp = nuova_pila();
	partecipante p;
	int duplicato = 0;
	while (!pila_vuota(corrente->valore.iscritti)) {
 	   estrai_pila(corrente->valore.iscritti, p);
 	   if (strcmp(p, utente_loggato->nomeutente) == 0) {
	        duplicato = 1;
	    }
	    inserisci_pila(p, temp);
	}
	while (!pila_vuota(temp)) {
	    estrai_pila(temp, p);
	    inserisci_pila(p, corrente->valore.iscritti);
	}
	free(temp);

	if (duplicato) {
	    printf("Sei già iscritto a questa lezione.\n");
	    printf("Premi INVIO\n");
 	   getchar();
	    return;
	}
	
	// Aggiunge il nome utente nella pila iscritti
	if (inserisci_pila(utente_loggato->nomeutente, corrente->valore.iscritti)) {
    	utente_loggato->lezioni_rimanenti--;
    	printf("Prenotazione completata per %s.\n", utente_loggato->nomeutente);
    	printf("Lezioni rimanenti: %d\n", utente_loggato->lezioni_rimanenti);
		printf("Possiamo fare altro per te? Premi INVIO...");
        getchar();
	} else {
    	printf("Errore nella prenotazione.\n");
		printf("Possiamo fare altro per te? Premi INVIO...");
        getchar();
	}
}

/*
* Funzione: disdici_iscrizione
*
* Permette a un utente di disdire la propria iscrizione da una lezione selezionata 
*
* Descrizione:
* - Viene stampato l'elenco delle lezioni disponibili, ottenuto dalla coda calendario
* - L'utente seleziona una lezione inserendo il numero corrispondente (indice dinamico)
* - Viene chiesto il nome del partecipante da disiscrivere
* - Il nome, se presente nella pila degli iscritti della lezione selezionata, viene rimosso
* - Il nome viene rimosso anche dal file che memorizza le iscrizioni
*
* Parametri:
* - calendario: coda di lezioni (lista dinamica) contenente le informazioni delle lezioni e gli iscritti
* - lezioni: nome del file contenente tutte le iscrizioni
* 
* Pre-condizione:
* - Il calendario deve contenere almeno una lezione valida
* - Il file 'lezioni' deve essere accessibile in lettura e scrittura
*
* Side-effect:
* - modifica la pila iscritti della lezione selezionata
* - aggiorna il file delle iscrizioni eliminando il partecipante disdetto
* - libera la memoria della pila di supporto usata per la rimozione
*/
void disdici_iscrizione(coda calendario, const char* lezioni)
{
	printf("--- Disdici una prenotazione ---\n");
    	if (coda_vuota(calendario))
	{
    		printf("Non ci sono lezioni di fitness disponibili.\n");
			printf("Possiamo fare altro per te? Premi INVIO...");
            getchar();
    		return;
	}

	stampa_lezioni(calendario);

	char risposta;
	printf("\nDesideri disdire l'iscrizione ad una lezione? (s/n): ");
	scanf(" %c", &risposta);
	getchar();  // consuma il newline

	if (risposta != 's' && risposta != 'S')
	{
        printf("Nessuna lezione disdetta.\n");
		printf("Possiamo fare altro per te? Premi INVIO...");
        getchar();
		return;
    }

	char scelta[10];
	printf("Inserisci il numero della lezione a cui vuoi disdire la tua iscrizione: "); //CONTROLLO VALORE!!!
	fgets(scelta, sizeof(scelta), stdin);

// Conta dinamicamente il numero di lezioni nella coda calendario
int max_lezioni = 0;
struct nodo* temp = calendario->testa;
while (temp != NULL) 
{
    max_lezioni++;
    temp = temp->prossimo;
}

int num_scelta = atoi(scelta);
if (num_scelta < 1 || num_scelta > max_lezioni)
{
    printf("Scelta non valida.\n");
	printf("Possiamo fare altro per te? Premi INVIO...");
    getchar();
    return;
}

    struct nodo* corrente = calendario->testa;
    int indice = 0;
while (corrente != NULL && indice < num_scelta - 1) 
{
    corrente = corrente->prossimo;
    indice++;
}

if (corrente == NULL)
{
    printf("Errore: lezione non trovata.\n");
	printf("Possiamo fare altro per te? Premi INVIO...");
    getchar();
    return;
}

lezione* selezionata = &corrente->valore; 

    char nome[50];
    printf("Inserisci il tuo nome per disdire l'iscrizione: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = 0;  // rimuove newline

    int trovato = 0;
    pila supporto = nuova_pila();
    if (supporto == NULL)
    {
        printf("Errore nell'allocazione della pila di supporto.\n");
		printf("Possiamo fare altro per te? Premi INVIO...");
        getchar();
        return;
    }

    partecipante p;

    while (!pila_vuota(selezionata->iscritti))
    {
        strcpy(p, testa(selezionata->iscritti));
        estrai_pila(selezionata->iscritti, p);

        if (strcmp(p, nome) == 0 && !trovato)
        {
            trovato = 1;
            // Non reinserisco nella pila di supporto => rimuovo l'iscritto
        }
        else
        {
            inserisci_pila(p, supporto);
        }
    }

    while (!pila_vuota(supporto))
    {
        strcpy(p, testa(supporto));
        estrai_pila(supporto, p);
        inserisci_pila(p, selezionata->iscritti);
    }
    free(supporto);

    if (!trovato)
    {
        printf("Partecipante non trovato.\n");
		printf("Possiamo fare altro per te? Premi INVIO...");
        getchar();
        remove("temp.txt");
        return;
    }

FILE* file = fopen(lezioni, "r");
if (!file)
{
    printf("Errore nell'apertura del file.\n");
	printf("Premi INVIO\n");
    getchar();
    return;
}

FILE* temp_file = fopen("temp_file.txt", "w");
if (!temp_file)
{
    fclose(file);
    printf("Errore nella creazione del file temporaneo.\n");
	printf("Possiamo fare altro per te? Premi INVIO...");
    getchar();
    return;
}

char riga[256];
int in_lezione_target = 0;

while (fgets(riga, sizeof(riga), file))
{
    // Rimuove newline
    riga[strcspn(riga, "\n")] = 0;

    // Se contiene la data, è intestazione di una nuova lezione
    if (strstr(riga, "/") && strstr(riga, ";"))
    {
        if (strstr(riga, selezionata->data))
            in_lezione_target = 1;
        else
            in_lezione_target = 0;

        fputs(riga, temp_file);
        fputc('\n', temp_file);
        continue;
    }

    // Se è partecipante nella lezione giusta e corrisponde al nome da eliminare, salta la riga
    if (in_lezione_target && strcmp(riga, nome) == 0)
        continue;

    // Altrimenti scrive normalmente
    fputs(riga, temp_file);
    fputc('\n', temp_file);
}

    fclose(file);
    fclose(temp_file);
    remove(lezioni);
    rename("temp_file.txt", lezioni);

    printf("Iscrizione disdetta con successo.\nPremi INVIO per continuare...");
    getchar();
}

/* Funzione: salva_lezioni
*
* Salva tutte le lezioni presenti nella coda calendario su file, includendo anche gli iscritti
*
* Descrizione:
* La funzione salva tutte le lezioni contenute nella coda calendario in un file
* Ogni lezione viene scritta con data giorno orario e numero iscritti
* Gli iscritti vengono temporaneamente estratti dalla pila e scritti su file
* Dopo la scrittura la pila originale degli iscritti viene ripristinata
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
void salva_lezioni(coda calendario, const char *nome_file)
{
	FILE *fp = fopen(nome_file, "w");
    	if (fp == NULL)
	{
        	perror("Errore apertura file");
			printf("Premi INVIO\n");
            getchar();
        	return;
    	}

    	struct nodo *corrente = calendario->testa;

    	while (corrente != NULL)
	{
        	fprintf(fp, "%s;%s;%s;%d\n", 
            	corrente->valore.data,
            	corrente->valore.giorno,
            	corrente->valore.orario,
            	dimensione_pila(corrente->valore.iscritti));

        	// Salva tutti gli iscritti
        	pila iscritti_tmp = nuova_pila();
        	partecipante p;

        	while (!pila_vuota(corrente->valore.iscritti))
		{
            		if (estrai_pila(corrente->valore.iscritti, p))
			{
                		fprintf(fp, "%s\n", p);
                		inserisci_pila(p, iscritti_tmp); // ricostruisce pila
            		}
        	}

        	// Ripristina pila originale
        	while (!pila_vuota(iscritti_tmp))
		{
            		if (estrai_pila(iscritti_tmp, p))
			{
                		inserisci_pila(p, corrente->valore.iscritti);
            		}
        	}

        	corrente = corrente->prossimo;
    	}

    	fclose(fp);
}

/* Funzione: data_passata
*
* Verifica se una data nel formato "dd/mm/yyyy" è precedente alla data odierna
*
* Descrizione:
* La funzione verifica se la data passata come stringa è precedente alla data odierna
* La data deve essere nel formato dd/mm/yyyy
* Se la data è nel passato restituisce 1 altrimenti restituisce 0
* Utilizza le strutture tm per confrontare le date in formato time_t
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
int data_passata(const char *data_str)
{
	struct tm data = {0};

    	int giorno, mese, anno;
    	if (sscanf(data_str, "%d/%d/%d", &giorno, &mese, &anno) != 3)
        	return 0;  // Formato invalido, per sicurezza la consideriamo non passata

    	data.tm_mday = giorno;
    	data.tm_mon = mese - 1;  // mesi da 0 a 11
    	data.tm_year = anno - 1900;

    	time_t tempo_data = mktime(&data);

    	time_t oggi = time(NULL);
    	struct tm oggi_tm = *localtime(&oggi);
    	oggi_tm.tm_hour = 0; oggi_tm.tm_min = 0; oggi_tm.tm_sec = 0;
    	time_t tempo_oggi = mktime(&oggi_tm);

    	return difftime(tempo_data, tempo_oggi) < 0;
}

/* Funzione: pulisci_lezioni_passate
*
* Rimuove dalla coda tutte le lezioni con data già passata, salvandole su un file storico
*
* Descrizione:
* La funzione scorre la coda delle lezioni e rimuove tutte quelle con data passata
* Ogni lezione eliminata viene salvata su un file storico insieme ai relativi iscritti
* Le lezioni vengono confrontate con la data odierna usando la funzione data_passata
* La struttura della coda viene modificata eliminando i nodi corrispondenti alle lezioni passate
* La memoria dei nodi eliminati viene liberata e le informazioni vengono scritte in append su file
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
void pulisci_lezioni_passate(coda calendario, const char *nome_file)
{
	if (calendario == NULL || coda_vuota(calendario)) return;

	FILE *fp = fopen(nome_file, "a");
	if (fp == NULL)
	{
        	printf("Errore apertura file storico");
			printf("Premi INVIO\n");
            getchar();
        	return;
    	}

    	struct nodo *corrente = calendario->testa;
    	struct nodo *precedente = NULL;

	while (corrente != NULL)
	{
        	struct nodo *prossimo = corrente->prossimo;

		if (data_passata(corrente->valore.data))
		{
        		// Scrivi su file storico
            		fprintf(fp, "%s;%s;%s;%d\n",
                	corrente->valore.data,
                	corrente->valore.giorno,
                	corrente->valore.orario,
                	dimensione_pila(corrente->valore.iscritti));

            		// Salva anche tutti gli iscritti
            		pila iscritti_tmp = nuova_pila();
            		partecipante p;
            		while (!pila_vuota(corrente->valore.iscritti))
			{
                		if (estrai_pila(corrente->valore.iscritti, p))
				{
                    			fprintf(fp, "%s\n", p);
                    			inserisci_pila(p, iscritti_tmp);
                		}
            		}
            		while (!pila_vuota(iscritti_tmp))
			{
                		if (estrai_pila(iscritti_tmp, p))
                    			inserisci_pila(p, corrente->valore.iscritti);
            		}

			// Rimuovi il nodo dalla coda
            		if (precedente == NULL)
                		calendario->testa = prossimo;
			else
                		precedente->prossimo = prossimo;

            		if (corrente == calendario->coda) {
                		calendario->coda = precedente;
            		}

        		free(corrente);
            		calendario->numel--;
		}
		else 
            		precedente = corrente;

        	corrente = prossimo;
	}

	fclose(fp);
}

/* Funzione: report_mensile
*
* Genera e stampa un report ordinato delle lezioni svolte in un mese specifico,
* elencando solo quelle con almeno un partecipante, ordinate per numero di partecipanti in ordine decrescente
*
* Descrizione:
* La funzione chiede all’utente di selezionare un mese tra quelli presenti nel file storico
* Per ogni lezione nel file che corrisponde al mese e anno scelti e ha almeno un partecipante
* memorizza data, giorno, orario e numero di partecipanti in array temporanei
* Ordina poi le lezioni trovate in ordine decrescente in base al numero di partecipanti
* Infine stampa il report mensile ordinato delle lezioni a schermo
*
* (utilizzando bubble sort), quindi stampa il report ordinato a video.
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
void report_mensile()
{
	while(1)
	{
		printf("--- Report Mensile ---\n");
	printf("Visualizza le lezioni di fitness passate, ordinate per numero di partecipanti.\n");
    FILE *file_storico = fopen("storico.txt", "r");
    if (!file_storico)
    {
        printf("Errore nel report.\n");
		printf("Premi INVIO\n");
        getchar();
        return;
    }

    // Primo passaggio: estrai mesi e anni unici dal file
int mesi[120], anni[120], count = 0;
char riga[256];

while (fgets(riga, sizeof(riga), file_storico))
{
    int giorno, mese, anno, num;
    char data[11], giorno_s[15], orario[10];

    if (sscanf(riga, "%10[^;];%14[^;];%9[^;];%d", data, giorno_s, orario, &num) == 4)
    {
        if (sscanf(data, "%d/%d/%d", &giorno, &mese, &anno) == 3)
        {
            int già_presente = 0;
            for (int i = 0; i < count; i++)
            {
                if (mesi[i] == mese && anni[i] == anno)
                {
                    già_presente = 1;
                    break;
                }
            }
            if (!già_presente)
            {
                mesi[count] = mese;
                anni[count] = anno;
                count++;
            }
        }

        // Salta righe partecipanti
        for (int i = 0; i < num; i++)
            fgets(riga, sizeof(riga), file_storico);
    }
}

if (count == 0)
{
    fclose(file_storico);
    printf("Nessun dato disponibile nel file storico.\nPremi INVIO\n");
    getchar();
    return;
}

// Mostra elenco numerato mesi/anni disponibili
printf("\nSeleziona il mese da analizzare:\n");
for (int i = 0; i < count; i++)
    printf("%d) %02d/%d\n", i + 1, mesi[i], anni[i]);

	printf("0) Torna al menu principale\n");

char scelta[10];
int scelta_numero = 0;
printf("Inserisci il numero della tua scelta: ");
fgets(scelta, sizeof(scelta), stdin);
scelta_numero = atoi(scelta);

if (scelta_numero == 0)
    {
        fclose(file_storico);
        return;
    }

if (scelta_numero < 0 || scelta_numero > count)
{
    printf("Scelta non valida.\nPremi INVIO\n");
    getchar();
    fclose(file_storico);
    return;
}

int mese_da_cercare = mesi[scelta_numero - 1];
int anno_da_cercare = anni[scelta_numero - 1];

rewind(file_storico);

    // Array per memorizzare le lezioni trovate
    char elenco_date[100][11];
    char elenco_giorni[100][15];
    char elenco_orari[100][10];
    int elenco_partecipanti[100];
    int totale_lezioni = 0;

    // Lettura del file riga per riga
    while (fgets(riga, sizeof(riga), file_storico)) 
	{
        char data_lettura[11];
        char giorno_lettura[15];
        char orario_lettura[10];
        int numero_partecipanti;
		int g, m, a;

        // Lettura dei dati principali dalla riga
        if (sscanf(riga, "%10[^;];%14[^;];%9[^;];%d", data_lettura, giorno_lettura, orario_lettura, &numero_partecipanti) == 4)
		{
			sscanf(data_lettura, "%d/%d/%d", &g, &m, &a);
        if (m == mese_da_cercare && a == anno_da_cercare && numero_partecipanti > 0)
     {
        strcpy(elenco_date[totale_lezioni], data_lettura);
        strcpy(elenco_giorni[totale_lezioni], giorno_lettura);
         strcpy(elenco_orari[totale_lezioni], orario_lettura);
         elenco_partecipanti[totale_lezioni] = numero_partecipanti;
         totale_lezioni++;
     }

            for (int i = 0; i < numero_partecipanti; i++)
                fgets(riga, sizeof(riga), file_storico);
        }
    }

    fclose(file_storico);

    if (totale_lezioni == 0) 
	{
        printf("Nessuna lezione trovata per il mese %d/%d.\n", mese_da_cercare, anno_da_cercare);
		printf("Possiamo fare altro per te? Premi INVIO\n");
        getchar();
        return;
    }

    // Bubble sort
	for (int i = 0; i < totale_lezioni - 1; i++)
{
    for (int j = i + 1; j < totale_lezioni; j++)
    {
        if (elenco_partecipanti[j] > elenco_partecipanti[i])
        {
            int tmp = elenco_partecipanti[i];
            elenco_partecipanti[i] = elenco_partecipanti[j];
            elenco_partecipanti[j] = tmp;

            char tmp_data[11], tmp_giorno[15], tmp_orario[10];
            strcpy(tmp_data, elenco_date[i]);
            strcpy(tmp_giorno, elenco_giorni[i]);
            strcpy(tmp_orario, elenco_orari[i]);

            strcpy(elenco_date[i], elenco_date[j]);
            strcpy(elenco_giorni[i], elenco_giorni[j]);
            strcpy(elenco_orari[i], elenco_orari[j]);

            strcpy(elenco_date[j], tmp_data);
            strcpy(elenco_giorni[j], tmp_giorno);
            strcpy(elenco_orari[j], tmp_orario);
        }
    }
}


    // Stampa finale del report mensile ordinato
    printf("\n--- Report Mensile %02d/%d ---\n", mese_da_cercare, anno_da_cercare);
    for (int i = 0; i < totale_lezioni; i++) 
	{
        printf("%d) Data: %s | Giorno: %s | Orario: %s | Partecipanti: %d\n",
               i + 1,
               elenco_date[i],
               elenco_giorni[i],
               elenco_orari[i],
               elenco_partecipanti[i]);
    }
	printf("Possiamo fare altro per te? Premi INVIO\n");
    getchar(); 
	}
}

void caso_test_1(coda calendario) 
{
    printf("\n--- TEST 1: Registrazione Prenotazione e Disponibilità ---\n");
	printf("Permette di verificare la corretta registrazione delle prenotazioni e dell'aggiornamento delle disponibilita'.\n");
	printf("Viene creato 'Utente_Test' che viene iscritto alla prima lezione disponibile aggiornando la disponibilita'.\n\n");
    printf("Premi INVIO per iniziare");
    getchar(); 

    // 1. Verifica che ci siano lezioni
    if (coda_vuota(calendario))
    {
        printf("ERRORE: Nessuna lezione disponibile.\n");
        printf("Possiamo fare altro per te? Premi INVIO...");
        getchar(); 
        return;
    }

    // 2. Seleziona la prima lezione
    struct nodo *lezione_test = calendario->testa;
    int iscritti_iniziali = dimensione_pila(lezione_test->valore.iscritti);

    // 3. Inserisce un partecipante
    partecipante nome;
    strcpy(nome, "Utente_Test");
    int esito = inserisci_pila(nome, lezione_test->valore.iscritti);

    // 4. Verifica aggiornamento
    int iscritti_finali = dimensione_pila(lezione_test->valore.iscritti);
    if (esito && iscritti_finali == iscritti_iniziali + 1) 
    {
        printf("SUCCESSO: Prenotazione registrata correttamente.\n");
        printf("Iscritti prima: %d, dopo: %d\n", iscritti_iniziali, iscritti_finali);
    } 
    else 
    {
        printf("ERRORE: Prenotazione fallita o numero iscritti non aggiornato.\n");
        printf("Attesi: %d, Trovati: %d\n", iscritti_iniziali + 1, iscritti_finali);
    }

    printf("Premi INVIO per tornare al menu principale...");
    getchar(); 
}

void caso_test_2(coda calendario) 
{
    printf("\n--- TEST 2: Gestione Abbonamenti ---\n");
    printf("Test della gestione degli abbonamenti e della verifica della validita'.\n");
	printf("Crea 'Abbonato_Test' diverso ogni volta, cerca di prenotare senza lezioni fallendo, ricarica l'abbonamento e l'utente viene iscritto.\n\n");
    printf("Premi INVIO per iniziare...");
    getchar();

    // 1. Genera nome utente univoco
    FILE *fc = fopen("counter.txt", "r+");
    int counter = 1;
    if (fc) 
	{
        fscanf(fc, "%d", &counter);
        rewind(fc);
    } 
	else 
	{
        fc = fopen("counter.txt", "w+");
    }
    fprintf(fc, "%d", counter + 1);
    fclose(fc);

    char nomeutente[MAX_CARATTERI];
    snprintf(nomeutente, MAX_CARATTERI, "Abbonato_Test%d", counter);

    // 2. Crea nuovo abbonato
    abbonato nuovo;
    strcpy(nuovo.nomeutente, nomeutente);
    strcpy(nuovo.password, "1234");
    nuovo.chiave = strdup(nuovo.nomeutente);
    nuovo.lezioni_rimanenti = 0;

    tabella_hash tabella = carica_abbonati("abbonati.txt");
    tabella = inserisci_hash(nuovo, tabella);
    salva_abbonati(tabella, "abbonati.txt");

    printf("Abbonato creato: %s\n", nuovo.nomeutente);

    // 3. Ricarica tabella e cerca utente
    tabella = carica_abbonati("abbonati.txt");
    abbonato *trovato = cerca_hash(nomeutente, tabella);

    if (!trovato) 
	{
        printf("ERRORE: Utente non trovato dopo la creazione.\n");
        return;
    }

    // 4. Tentativo automatico di prenotazione SENZA lezioni disponibili
    printf("\nTentativo automatico di prenotazione senza lezioni disponibili...\n");
    if (trovato->lezioni_rimanenti <= 0) 
	{
        printf("Comportamento corretto: prenotazione rifiutata per mancanza di lezioni.\n\n");
    } 
	else 
	{
        printf("ERRORE: L'utente ha ancora lezioni disponibili, ma non dovrebbe.\n\n");
    }

    // 5. Ricarica abbonamento
    trovato->lezioni_rimanenti += 12;
    salva_abbonati(tabella, "abbonati.txt");
    printf("Lezioni rimanenti dopo ricarica: %d\n\n", trovato->lezioni_rimanenti);

    // 6. Prenotazione automatica della prima lezione
    printf("\nPrenotazione automatica della prima lezione...\n");
    struct nodo *lezione_test = calendario->testa;
    if (!lezione_test) 
	{
        printf("ERRORE: Nessuna lezione disponibile.\n");
        return;
    }

    int iscritti_pre = dimensione_pila(lezione_test->valore.iscritti);
    int lezioni_pre = trovato->lezioni_rimanenti;

    if (inserisci_pila(trovato->nomeutente, lezione_test->valore.iscritti)) 
	{
        trovato->lezioni_rimanenti--;
        salva_abbonati(tabella, "abbonati.txt");
        salva_lezioni(calendario, "lezioni.txt");

        int iscritti_post = dimensione_pila(lezione_test->valore.iscritti);
        printf("Prenotazione riuscita. Iscritti prima: %d, dopo: %d\n", iscritti_pre, iscritti_post);
        printf("Lezioni rimanenti: %d\n", trovato->lezioni_rimanenti);

        if (lezioni_pre - 1 == trovato->lezioni_rimanenti) 
		{
            printf("Lezione scalata correttamente.\n");
        } 
		else 
		{
            printf("ERRORE: Lezione non scalata correttamente.\n");
        }
    } 
	else 
	{
        printf("ERRORE: Prenotazione fallita dopo ricarica.\n");
    }

    printf("Premi INVIO per tornare al menu principale...");
    getchar();
}