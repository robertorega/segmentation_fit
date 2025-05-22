#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "coda.h"
#include "funzioni_generiche.h"
#include "hash.h"
#include "lezione.h"
#include "pila.h"

/* Funzione: abbonamenti
*
* Gestisce l'area abbonamenti dell'applicazione
*
* Parametri:
* calendario - struttura contenente il calendario delle lezioni disponibili
*
* Pre-condizione:
* calendario è una struttura coda valida e inizializzata correttamente
*
* Post-condizione:
* Viene gestito l'accesso all'area abbonati: login, registrazione o ricarica abbonamento
*
* Side-effect:
* - Output a schermo
* - Possibili modifiche al file "abbonati.txt" e "lezioni.txt"
*/
void abbonamenti(coda calendario);

/* Funzione: contattaci
*
* Stampa a schermo le informazioni di contatto e attende che l'utente prema INVIO per continuare
* Side-effect:
* Output a schermo
*/
void contattaci();

int main()
{
	char scelta[10];
	coda calendario = nuova_coda();
	carica_lezioni(calendario, "lezioni.txt");
	genera_lezioni(calendario);

	//Ciclo infinito per il menu principale
	while (1) 
	{
		pulisci_schermo(); //Pulisce lo schermo della console.

		//Messaggio di benvenuto all'utente
		printf("Segmentation Fit\n");
		printf("Benvenuti nella palestra numero uno per gli informatici\n");
		//Stampa le opzioni del menu
		printf("\nSelezionare un’opzione:\n");
    		printf("1 - Area abbonati\n");
    		printf("2 - Lezioni\n");
   		printf("3 - Disdici\n");
   		printf("4 - Report mensili\n");
		printf("5 - Contattaci\n");
    		printf("6 - Esci\n");

		printf("La tua scelta: ");
		fgets(scelta, sizeof(scelta), stdin);
		scelta[strcspn(scelta, "\n")] = 0;  // Rimuove newline

    		switch(atoi(scelta)) 
		{
        		case 1:
            		abbonamenti(calendario);
            		break;
        		case 2:
			pulisci_lezioni_passate(calendario, "storico.txt");
            		prenota_lezione(calendario);
			salva_lezioni(calendario, "lezioni.txt");
            		break;
        		case 3:
            		disdici_iscrizione(calendario, "lezioni.txt");
            		break;
 			case 4:
            		report_mensile();
			break;
    			case 5:
           		contattaci();
          		break;
        		case 6:
            		printf("Arrivederci!\n");
            		return 0;  //Esce dal programma
        		default:
            		printf("Valore non valido\n\n");
					printf("Possiamo fare altro per te? Premi INVIO\n");
                    getchar(); 
            		break;
    		}
	}
	return 0;
}

/* Funzione: abbonamenti
*
*
* Gestisce l'interazione dell'utente con l'area dedicata agli abbonamenti.
*
* Descrizione:
* Offre tre opzioni principali: accesso all'area riservata per utenti registrati,
* registrazione di un nuovo abbonamento, oppure ritorno al menu principale.
*
* Se l'utente è già registrato, può effettuare il login inserendo le proprie credenziali,
* controllare le lezioni rimanenti, prenotare una lezione o ricaricare l’abbonamento con nuovi pacchetti.
*
* Se l'utente non è registrato, può creare un nuovo account scegliendo nome utente e password.
*
* Parametri:
* calendario - struttura dati contenente le lezioni, utilizzata per prenotazioni e gestione
*
* Pre-condizione:
* calendario è inizializzato correttamente e i file di supporto ("abbonati.txt", "lezioni.txt") sono presenti o creati
*
* Post-condizione:
* Le operazioni selezionate dall'utente vengono eseguite e i dati aggiornati vengono salvati su file.
* Se viene creato un nuovo abbonamento, l'utente viene salvato nella tabella hash.
*
* Side-effect:
* - Lettura e scrittura su file ("abbonati.txt", "lezioni.txt")
* - Allocazione dinamica di memoria per nuovi utenti
*/
void abbonamenti(coda calendario)
{
	char scelta[10];
	tabella_hash tabella_abbonati = carica_abbonati("abbonati.txt");

	while (1) {
	pulisci_schermo();
	printf("Scegli il piano di allenamento adatto a te!\n\n");
        printf("Seleziona un'opzione:\n");
        printf("1 - Sei già abbonato? Entra nella tua area riservata\n");
        printf("2 - Vuoi creare un nuovo abbonamento?\n");
        printf("3 - Torna al menu principale\n\n");
        printf("La tua scelta: ");
        fgets(scelta, sizeof(scelta), stdin);

        switch (atoi(scelta)) {
            case 1: {
                char nomeutente[MAX_CARATTERI];
                char password[MAX_CARATTERI];
                printf("Inserisci il nome utente: ");
                scanf("%s", nomeutente);
                getchar();
                abbonato *utente = cerca_hash(nomeutente, tabella_abbonati);

                if (!utente) {
                    printf("Utente non trovato.\nPremi INVIO per continuare...");
                    getchar();
                    break;
                }

                printf("Inserisci la password: ");
                scanf("%s", password);
                getchar();

                if (strcmp(utente->password, password) != 0) {
                    printf("Password errata.\nPremi INVIO per continuare...");
                    getchar();
                    break;
                }

                printf("\nBenvenuto %s, hai %d lezioni rimanenti.\n", utente->nomeutente, utente->lezioni_rimanenti);

                int dentro_area = 1;
                while (dentro_area) {
                    char scelta_operazione[10];
                    printf("\n1 - Prenota una lezione\n");
                    printf("2 - Ricarica abbonamento\n");
                    printf("3 - Torna al menu abbonamenti\n");
                    printf("Scelta: ");
                    fgets(scelta_operazione, sizeof(scelta_operazione), stdin);

                    switch (atoi(scelta_operazione)) {
                        case 1:
                            pulisci_lezioni_passate(calendario, "storico.txt");
                            prenota_lezione_abbonato(calendario, utente);
                            salva_abbonati(tabella_abbonati, "abbonati.txt");
                            salva_lezioni(calendario, "lezioni.txt");
                            break;

                        case 2: {
                            int scelta_abbonamento = 0;
                            while (1) {
                                printf("\nScegli il piano di allenamento:\n");
                                printf("1 - 12 lezioni - 60€\n");
                                printf("2 - 24 lezioni - 100€\n");
                                printf("3 - 36 lezioni - 150€\n");
                                printf("4 - Annulla\n");
                                printf("La tua scelta: ");
                                scanf("%d", &scelta_abbonamento);
                                getchar();

                                if (scelta_abbonamento >= 1 && scelta_abbonamento <= 3) {
                                    int lezioni = scelta_abbonamento * 12;
                                    utente->lezioni_rimanenti += lezioni;
                                    printf("Abbonamento aggiornato! Ora hai %d lezioni.\n", utente->lezioni_rimanenti);
                                    salva_abbonati(tabella_abbonati, "abbonati.txt");
                                    break;
                                } else if (scelta_abbonamento == 4) {
                                    break;
                                } else {
                                    printf("Valore non valido, riprova.\n");
                                }
                            }
                            break;
                        }

                        case 3:
                            dentro_area = 0;
                            break;

                        default:
                            printf("Scelta non valida.\n");
                    }
                }
                break;
            }

            case 2: {
                char nomeutente[MAX_CARATTERI];
                char password[MAX_CARATTERI];

                printf("Inserisci nome utente: ");
                scanf("%s", nomeutente);
                getchar();

                abbonato *utente = cerca_hash(nomeutente, tabella_abbonati);

                if (utente) {
                    printf("Utente già esistente. Accedi dall'area riservata per ricaricare l'abbonamento.\nPremi INVIO per continuare...");
                    getchar();
                    break;
                }

                printf("Inserisci una password: ");
                scanf("%s", password);
                getchar();

                abbonato nuovo;
                strncpy(nuovo.nomeutente, nomeutente, MAX_CARATTERI);
                strncpy(nuovo.password, password, MAX_CARATTERI);
                nuovo.chiave = strdup(nomeutente);
                nuovo.lezioni_rimanenti = 0;

                tabella_abbonati = inserisci_hash(nuovo, tabella_abbonati);
                salva_abbonati(tabella_abbonati, "abbonati.txt");

                printf("Account creato con successo! Ora accedi dall'area riservata per attivare un abbonamento.\nPremi INVIO per continuare...");
                getchar();
                break;
            }

            case 3:
                printf("Tornando al menu principale...\n");
                return;

            default:
                printf("Valore non valido, riprova.\n");
                break;
        }
    }
}

/* Funzione: contattaci
*
* Stampa a schermo le informazioni di contatto e attende che l'utente prema INVIO per continuare
*
* Descrizione:
* La funzione mostra un messaggio contenente l'indirizzo e i numeri di telefono per contattare il personale
* Vengono anche visualizzati gli orari di apertura del centro
* Alla fine la funzione attende che l'utente prema INVIO prima di proseguire
*
* Side-effect:
* Output a schermo
*/
void contattaci()
 {
	printf("\nHai bisogno di ulteriori info?\n");
	printf("Ci trovi in Via degli Atleti, n51\n");
	printf("Altrimenti chiamaci ai seguenti numeri:\n");
	printf("Roberto Rega - 0512121583\n");
	printf("Andrea Zottoli - 0512122412\n");
	printf("I nostri orari: LUN-VEN 07:00 - 22:00, SAB 08:30 - 17:00, DOM CHIUSI\n\n");

	printf("Possiamo fare altro per te? Premi INVIO\n");
    getchar();
}
