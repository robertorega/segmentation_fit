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

/* Funzione: abbonamenti
*
* Gestisce l'area abbonamenti dell'applicazione
*
* Parametri:
* calendario: struttura contenente il calendario delle lezioni disponibili
*
* Pre-condizione:
* - 'calendario' è una struttura coda valida e inizializzata correttamente
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
void contattaci(void);

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
    	coda calendario = nuova_coda(); // Inizializza la coda delle lezioni 
	carica_lezioni(calendario, "lezioni.txt"); // Carica le lezioni salvate da file
	pulisci_lezioni_passate(calendario, "storico.txt"); // Rimuove le lezioni passate e le archivia nello storico
	genera_lezioni(calendario); // Genera nuove lezioni per i prossimi 30 giorni

	while (1) 
	{
		pulisci_schermo(); // Pulisce lo schermo

		printf("--- Segmentation Fit ---\n");
		printf("Benvenuto nella palestra numero uno per gli informatici\n");

		printf("\nSelezionare un’opzione:\n");
    		printf("1 - Area abbonati\n");
    		printf("2 - Ingresso Singolo\n");
    		printf("3 - Disdici\n");
    		printf("4 - Report mensili\n");
    		printf("5 - Contattaci\n");
    		printf("6 - Esci\n\n");
		printf("La tua scelta: ");
		fgets(scelta, sizeof(scelta), stdin);
		scelta[strcspn(scelta, "\n")] = 0;

    		switch(atoi(scelta)) 
		{
        		case 1:
				// Accesso all'area abbonati
            			abbonamenti(calendario);
            			break;
        		case 2:
				// Prenotazione per ingresso singolo
				pulisci_schermo();
				pulisci_lezioni_passate(calendario, "storico.txt");
				genera_lezioni(calendario); 
				prenota_lezione(calendario);
				salva_lezioni(calendario, "lezioni.txt");
            			break;
        		case 3:
				// Disdetta di una prenotazione
				pulisci_schermo();
            			disdici_iscrizione(calendario, "lezioni.txt");
            			break;
 			case 4:
				// Visualizzazione report mensile
				pulisci_schermo();
            			report_mensile("storico.txt");
				break;
    			case 5:
				// Informazioni di contatto
           			contattaci();
          			break;
        		case 6:
				// Uscita dal programma
            			printf("Arrivederci!\n");
            			return 0;
        		default:
				// Gestione input non valido
            			printf("Scelta non valida.\n");
				printf("Premi INVIO per riprovare...");
            			getchar(); 
            			break;
    		}	
	}
	return 0;
}


/* Funzione: abbonamenti
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
* calendario: struttura contenente il calendario delle lezioni disponibili
*
* Pre-condizione:
* - 'calendario' è una struttura coda valida e inizializzata correttamente
*
* Side-effect:
* - Output a schermo
* - Possibili modifiche al file "abbonati.txt" e "lezioni.txt"
*/
void abbonamenti(coda calendario)
{
    char scelta[10];
    tabella_hash tabella_abbonati = carica_abbonati("abbonati.txt"); // Carica la tabella hash degli abbonati dal file

    while (1)
    {
	pulisci_schermo();
	printf("--- Area Abbonati ---");
        printf("\nScegli il piano di allenamento adatto a te!\n\n");
        printf("Seleziona un'opzione:\n");
        printf("1 - Sei gia' abbonato? Entra nella tua area riservata\n");
        printf("2 - Vuoi creare un nuovo abbonamento?\n");
        printf("3 - Torna al menu principale\n\n");
        printf("La tua scelta: ");
        fgets(scelta, sizeof(scelta), stdin);
        scelta[strcspn(scelta, "\n")] = 0;

        switch (atoi(scelta))
	{
        	case 1:
		{
			// Accesso area riservata per abbonati esistenti
			char nomeutente[MAX_CARATTERI];
            		char password[MAX_CARATTERI];

			// Autenticazione utente
            		printf("Inserisci il nome utente: ");
            		scanf("%s", nomeutente);
           		getchar();
            		abbonato *utente = cerca_hash(nomeutente, tabella_abbonati);
            		if (!utente)
			{
                		printf("Utente non trovato.\nPremi INVIO per continuare...");
                		getchar();
                		break;
            		}
            		printf("Inserisci la password: ");
            		scanf("%s", password);
            		getchar();
            		if (strcmp(utente->password, password) != 0)
			{
                		printf("Password errata.\nPremi INVIO per continuare...");
                		getchar();
                		break;
            		}

			// Accesso riuscito
            		printf("\nBenvenuto %s, hai %d lezioni rimanenti.\n", utente->nomeutente, utente->lezioni_rimanenti);
            		int dentro_area = 1;
            		while (dentro_area)
			{
                		char scelta_operazione[10];
                		printf("\n1 - Prenota una lezione\n");
                		printf("2 - Ricarica abbonamento\n");
                		printf("3 - Torna al menu abbonamenti\n\n");
                		printf("La tua scelta: ");
                		fgets(scelta_operazione, sizeof(scelta_operazione), stdin);
                		scelta[strcspn(scelta, "\n")] = 0;
                		switch (atoi(scelta_operazione))
                 		{
                			case 1:
						// Prenotazione lezione per abbonato
                    				pulisci_lezioni_passate(calendario, "storico.txt");
                    				prenota_lezione_abbonato(calendario, utente);
                    				salva_abbonati(tabella_abbonati, "abbonati.txt");
                    				salva_lezioni(calendario, "lezioni.txt");
                    				break;
                			case 2:
					{
						// Ricarica abbonamento
                    				char scelta_abbonamento[10];
                    				while (1)
						{
                        				printf("\nScegli il piano di allenamento:\n");
                        				printf("1 - 12 lezioni: 60€\n");
                        				printf("2 - 24 lezioni: 100€\n");
                        				printf("3 - 36 lezioni: 150€\n");
                        				printf("4 - Annulla\n\n");
                        				printf("La tua scelta: ");
                        				fgets(scelta_abbonamento, sizeof(scelta_abbonamento), stdin);
                        				scelta[strcspn(scelta, "\n")] = 0;

                        				if (atoi(scelta_abbonamento) >= 1 && atoi(scelta_abbonamento) <= 3) 
                        				{
                            					int lezioni = atoi(scelta_abbonamento) * 12;
                            					utente->lezioni_rimanenti += lezioni;
                            					printf("Abbonamento aggiornato! Ora hai %d lezioni rimanenti.\n", utente->lezioni_rimanenti);
                            					salva_abbonati(tabella_abbonati, "abbonati.txt");
                            					break;
                        				} 
                        				else if (atoi(scelta_abbonamento) == 4) 
                        				{
                            					break;
                        				} else 
                        				{
                            					printf("Scelta non valida.\n");
                            					printf("Premi INVIO per riprovare...");
                            					getchar(); 
                        				}
                    				}
                    				break;
                			}
                			case 3:
						// Uscita dall'area riservata
                    				dentro_area = 0;
                    				break;
                			default:
                    				printf("Scelta non valida.\n");
                    				printf("Premi INVIO per riprovare...");
                    				getchar(); 
                		}
            		}
            		break;
        	}
        	case 2:
		{
			// Creazione nuovo abbonamento
            		char nomeutente[MAX_CARATTERI];
            		char password[MAX_CARATTERI];

			// Inserimento nome utente con validazione
            		do
			{
            			printf("Inserisci nome utente: ");
            			fgets(nomeutente, sizeof(nomeutente), stdin);
            			nomeutente[strcspn(nomeutente, "\n")] = 0; // Rimuove newline

            			if (strchr(nomeutente, ' ') != NULL)
				{
            				printf("Il nome utente non può contenere spazi. Riprova.\n");
            			} else if (strlen(nomeutente) == 0)
				{
            				printf("Il nome utente non può essere vuoto. Riprova.\n");
            			} else
            			{
            				break;
            			}
            		}while (1);

			// Verifica se l'utente esiste già
            		abbonato *utente = cerca_hash(nomeutente, tabella_abbonati);
            		if (utente)
			{
                		printf("Utente gia' esistente. Accedi dall'area riservata per ricaricare l'abbonamento.\nPremi INVIO per continuare...");
                		getchar();
                		break;
            		}

			// Inserimento password con validazione
            		do
			{
            			printf("Inserisci password: ");
            			fgets(password, sizeof(password), stdin);
            			password[strcspn(password, "\n")] = 0;

            			if (strchr(password, ' ') != NULL)
				{
            				printf("La password non può contenere spazi. Riprova.\n");
            			} else if (strlen(password) == 0)
				{
            				printf("La password non può essere vuota. Riprova.\n");
            			} else
				{
             				break;
            			}
            		} while (1);

			// Creazione nuovo abbonato
            		abbonato nuovo;
            		strncpy(nuovo.nomeutente, nomeutente, MAX_CARATTERI);
            		strncpy(nuovo.password, password, MAX_CARATTERI);
            		nuovo.chiave = strdup(nomeutente);
            		nuovo.lezioni_rimanenti = 0;

			// Inserimento nella tabella hash e salvataggio
            		tabella_abbonati = inserisci_hash(nuovo, tabella_abbonati);
            		salva_abbonati(tabella_abbonati, "abbonati.txt");
            		printf("Account creato con successo! Ora accedi dall'area riservata per attivare un abbonamento.\nPremi INVIO per continuare...");
            		getchar();
            		break;
        	}
        	case 3:
            		// Ritorna al menu principale
            		return;
        	default:
            		printf("Scelta non valida.\n");
            		printf("Premi INVIO per riprovare...");
            		getchar();
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
void contattaci(void)
 {
	pulisci_schermo();
	printf("--- Contattaci ---");
	printf("\nHai bisogno di ulteriori info?\n\n");
	printf("Ci trovi in Via degli Atleti, n51\n");
	printf("Altrimenti chiamaci ai seguenti numeri:\n");
	printf("Roberto Rega - 0512121583\n");
	printf("Andrea Zottoli - 0512122412\n");
	printf("I nostri orari: LUN-VEN 07:00 - 22:00, SAB 08:30 - 17:00, DOM CHIUSI\n\n");

	printf("Premi INVIO per tornare al menu principale...");
	getchar();
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
