#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "partecipante.h"
#include "pila.h"
#include "coda.h"
#include "lezione.h"

struct c_pila
 {

	partecipante vet[MASSIMO_PILA];
	int testa;

};

/* Funzione: nuova_pila
*
* Crea e inizializza una nuova pila vuota
* Post-condizione:
* Restituisce un puntatore a una pila vuota chiamata iscritti
*
* Side-effect:
* Alloca memoria dinamica per la pila
*/
pila nuova_pila(void)
 {
	pila iscritti;
	iscritti = malloc(sizeof(struct c_pila));

	if (iscritti == NULL)
	return NULL;

	iscritti->testa = 0;
	return iscritti;
}

/* Funzione: pila_vuota
*
* controlla se la pila iscritti è vuota
* Parametri:
* iscritti: pila da controllare
*
* Pre-condizione:
* iscritti è una pila inizializzata
*
* Post-condizione:
* Il valore restituito è 1 se e solo se la pila è vuota (iscritti->testa == 0), altrimenti 0.
*/
int pila_vuota(pila iscritti) 
{
	return iscritti->testa == 0;
}

/* Funzione: inserisci_pila
*
* Inserisce un partecipante in cima alla pila iscritti, se la pila non è piena
* Parametri:
* persona: il partecipante da inserire
* iscritti: la pila in cui inserire i partecipanti 
*
* Pre-condizione:
* iscritti è una pila inizializzata 
*
* Post-condizione:
* Restituisce 1 se persona viene copia in cima altrimenti restituisce 0
*
* Side-effect:
* Modifica la pila iscritti incrementando testa e scrivendo in persona[testa].
*/
int inserisci_pila(partecipante val, pila iscritti) 
{
	if (iscritti->testa == MASSIMO_PILA)
    return 0;

	strcpy(iscritti->vet[iscritti->testa], val);
	(iscritti->testa)++;
	return 1;
}

/* Funzione: estrai_pila
*
* Rimuove l’elemento in cima alla pila iscritti, se la pila non è vuota
* Parametri:
* iscritti: la pila in cui rimuovere i partecipanti 
*
* Pre-condizione:
* iscritti è una pila inizializzata 
*
* Post-condizione:
* se iscritti->testa == 0 allora result 0 altrimenti result 1
*
* Side-effect:
* iscritti = <a2, …, an>
*/
int estrai_pila(pila iscritti) 
{
	if (iscritti->testa == 0)
    return 0;

	(iscritti->testa)--;
	return 1;
}

/* Funzione: testa
*
* Restituisce l’elemento in cima alla pila iscritti senza rimuoverlo
* Parametri:
* iscritti: pila da cui leggere l’elemento in cima
*
* Pre-condizione:
* iscritti deve essere una pila inizializzata e non nulla
*
* Post-condizione:
* se top>0  ritorna un puntatore al partecipante in cima alla pila altrimenti NESSUN_PARTECIPANTE
*/
char* testa(pila iscritti)
 {
	if (iscritti->testa > 0)
    return iscritti->vet[iscritti->testa - 1];

	else
    return NESSUN_PARTECIPANTE;
}

/* Funzione: dimensione_pila
*
* Restituisce il numero di elementi attualmente presenti nella pila iscritti
* Parametri:
* iscritti:  pila da analizzare
*
* Pre-condizione:
* iscritti = <a1, a2, ..., an> n>0
*
* Post-condizione:
* Restituisce il numero di partecipanti, se la pila è vuota restituisce return -1
*/
int dimensione_pila(pila iscritti)
 {
	if (iscritti == NULL)
    return -1;  

	return iscritti->testa; 
}

/*
 * Funzione: disdici_iscrizione
 *
 * Rimuove un partecipante dalla pila degli iscritti, se presente.
 *
 * Parametri:
 * - iscritti: pila principale degli iscritti
 * - nome: stringa contenente il nome dell'utente da rimuovere
 *
 * Pre-condizione:
 * - iscritti è una pila inizializzata
 * - nome deve essere presente nella pila
 * 
 * Post-condizione:
 * - 1 se il partecipante è stato trovato e rimosso
 * - 0 se il partecipante non è presente nella pila
 *
 * Side-effect:
 * - modifica la pila iscritti
 * - libera la memoria della pila di supporto
 */
int disdici_iscrizione(lezione* calendario, int numero_lezioni, const char* lezioni)
{
    	if (coda_vuota(calendario) || numero_lezioni <= 0)
	{
    		printf("Non ci sono lezioni disponibili.\n");
    		return -1;
	}

	stampa_lezioni(calendario);

	char risposta;
	printf("\nDesideri disdire l'iscrizione ad una lezione? (s/n): ");
	scanf(" %c", &risposta);
	getchar();  // consuma il newline

	if (risposta != 's' && risposta != 'S')
	{
        printf("Nessuna lezione disdetta.\n");
		return -1;
    }

	char scelta[10];
	printf("Inserisci il numero della lezione a cui vuoi disdire la tua iscrizione: "); //CONTROLLO VALORE!!!
	fgets(scelta, sizeof(scelta), stdin);

	int num_scelta = atoi(scelta);
    if (num_scelta < 1 || num_scelta > numero_lezioni)
    {
        printf("Scelta non valida.\n");
        return -1;
    }

    lezione* selezionata = &calendario[num_scelta - 1];

    char nome[50];
    printf("Inserisci il tuo nome per disdire l'iscrizione: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = 0;  // rimuove newline

    int trovato = 0;
    pila supporto = nuova_pila();
    if (supporto == NULL)
    {
        printf("Errore nell'allocazione della pila di supporto.\n");
        return -1;
    }

    partecipante p;

    while (!pila_vuota(selezionata->iscritti))
    {
        strcpy(p, testa(selezionata->iscritti));
        estrai_pila(selezionata->iscritti);

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
        estrai_pila(supporto);
        inserisci_pila(p, selezionata->iscritti);
    }
    free(supporto);

    if (!trovato)
    {
        printf("Partecipante non trovato.\n");
        return 0;
    }

FILE* file = fopen(lezioni, "r");
if (!file)
{
    printf("Errore nell'apertura del file.\n");
    return -1;
}

FILE* temp = fopen("temp.txt", "w");
if (!temp)
{
    fclose(file);
    printf("Errore nella creazione del file temporaneo.\n");
    return -1;
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

        fputs(riga, temp);
        fputc('\n', temp);
        continue;
    }

    // Se è partecipante nella lezione giusta e corrisponde al nome da eliminare, salta la riga
    if (in_lezione_target && strcmp(riga, nome) == 0)
        continue;

    // Altrimenti scrivi normalmente
    fputs(riga, temp);
    fputc('\n', temp);
}

    fclose(file);
    fclose(temp);
    remove(lezioni);
    rename("temp.txt", lezioni);

    printf("Iscrizione disdetta con successo.\nPremi INVIO per continuare...");
    getchar();
	getchar();

    return 1;
}
