#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "coda.h"
#include "contattaci.h"
#include "funzioni_generiche.h"
#include "hash.h"
#include "lezione.h"
#include "pila.h"

void abbonamenti(coda calendario);

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
