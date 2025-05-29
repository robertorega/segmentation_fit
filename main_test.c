#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "coda.h"
#include "hash.h"
#include "lezione.h"
#include "pila.h"
#include "utile_coda.h"
#include "utile_hash.h"
#include "test_programma.h"

/* Funzione: pulisci_schermo
*
* Pulisce il contenuto visualizzato nel terminale, rendendo lo schermo vuoto
*
* Pre-condizione:
* Nessuna
*
* Post-condizione:
* Il terminale viene pulito (effetto visivo simile a "schermo vuoto")
*
* Side-effect:
* Chiama un comando di sistema (dipendente dal sistema operativo):
* - Su Windows: esegue "cls"
* - Su Unix/Linux/macOS: esegue "clear"
*/
void pulisci_schermo(void);

int main()
{
    char scelta[10];
    coda calendario = nuova_coda();
    carica_lezioni(calendario, "lezioni.txt");
    pulisci_lezioni_passate(calendario, "storico.txt");
    genera_lezioni(calendario);

    int test_scelta = 0;
    do
    {
        pulisci_schermo();
        printf("--- Segmentation Fit: Casi di Test ---\n");
        printf("Esecuzione dei casi di test per la verifica delle funzionalità principali\n\n");
        printf("1 - Caso Test 1\n");
        printf("2 - Caso Test 2\n");
        printf("3 - Caso Test 3\n");
        printf("4 - Esci\n\n");
        printf("La tua scelta: ");
        fgets(scelta, sizeof(scelta), stdin);
        scelta[strcspn(scelta, "\n")] = 0;
        test_scelta = atoi(scelta);

        switch (test_scelta)
        {
            case 1:
                caso_test_1(calendario);
                break;
            case 2:
                caso_test_2(calendario);
                break;
            case 3:
                caso_test_3(calendario);
                break;
            case 4:
                printf("Uscita dai casi di test.\n");
                break;
            default:
                printf("Scelta non valida.\n");
                printf("Premi INVIO per riprovare...");
                getchar();
                break;
        }
    } while (test_scelta != 4);

    return 0;
}

/* Funzione: pulisci_schermo
*
* Pulisce il contenuto visualizzato nel terminale, rendendo lo schermo vuoto
*
* Descrizione:
* La funzione pulisce lo schermo del terminale eseguendo il comando appropriato
* in base al sistema operativo in uso. Su Windows esegue il comando "cls",
* mentre su sistemi Unix/Linux/macOS esegue "clear". Questo permette di ottenere
* un terminale visivamente vuoto, migliorando la leggibilità dell'interfaccia utente.
*
* Side-effect:
* Chiama un comando di sistema (dipendente dal sistema operativo):
* - Su Windows: esegue "cls"
* - Su Unix/Linux/macOS: esegue "clear"
*/
void pulisci_schermo(void)
{
	#ifdef _WIN32
    		system("cls");
	#else
    		system("clear");
	#endif
}
