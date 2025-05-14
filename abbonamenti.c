#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "abbonamenti.h"
#include "funzioni_generiche.h"


void abbonamenti()
{
	char scelta[10];
	tabella_hash tabella_abbonati = nuova_hash(10);  // Crea una tabella hash con 10 slot

	while (1)
  	{  // Continuo a mostrare il menu fino a quando l'utente non seleziona "Torna al menu principale"
		pulisci_schermo(); // Pulisce lo schermo della console
    
		// Mostra il menu delle 2 opzioni iniziali
    		printf("Scegli il piano di allenamento adatto a te!\n\n");
    		printf("Selezionare un’opzione:\n");
		printf("1 - Sei già abbonato? Entra nella tua area riservata\n");
		printf("2 - Vuoi creare un nuovo abbonamento?\n");
    		printf("3 - Torna al menu principale\n\n");

    		printf("La tua scelta: ");
    		fgets(scelta, sizeof(scelta), stdin);
		    scelta[strcspn(scelta, "\n")] = 0;  // Rimuove newline

    		switch (atoi(scelta))
    		{
      			case 1:
			{
            			// L'utente è già abbonato, dobbiamo cercarlo
            			char nomeutente[MAX_CARATTERI];
            			char password[MAX_CARATTERI];

            			printf("Inserisci il nome utente per entrare nella tua area riservata: ");
            			scanf("%s", nomeutente);

            			// Cerca l'utente
            			abbonato *abbonato_trovato = cerca_hash(nomeutente, tabella_abbonati);

            			// Verifica se l'utente esiste
            			if (abbonato_trovato == NULL)
                			printf("Utente non trovato.\n");
				else
				{
                			// L'utente è stato trovato, ora chiedi la password
                			printf("Inserisci la tua password: ");
                			scanf("%s", password);

                			// Verifica la password
                			if (strcmp(abbonato_trovato->password, password) == 0)
					{
                    				printf("Benvenuto %s, hai %d lezioni rimanenti.\n", abbonato_trovato->nomeutente, abbonato_trovato->lezioni_rimanenti);
                    				printf("Puoi prenotare una lezione, che tipo di operazione vuoi fare?\n");
                    				// Implementa qui altre funzionalità come la prenotazione
                			} else
						printf("Password errata. Accesso negato.\n");
            			}
            			break;
        		}
        		case 2:
			{
            			// Sottomenu per la creazione di un nuovo abbonamento
            			int scelta_abbonamento = 0;
            			while (1)
				{  // Mostra il menu per scegliere il tipo di abbonamento
                			printf("Scegli il piano di allenamento:\n");
                			printf("1 - Abbonamento da 12 lezioni - 60€\n");
                			printf("2 - Abbonamento da 24 lezioni - 100€\n");
                			printf("3 - Abbonamento da 36 lezioni - 150€\n");
                			printf("4 - Torna al menu principale\n");

                			printf("La tua scelta: ");
                			scanf("%d", &scelta_abbonamento);

                			switch (scelta_abbonamento)
					{
                    				case 1:
						{
                        				// Abbonamento da 12 lezioni
                        				abbonato nuovo_abbonato;
                        				printf("Inserisci nome utente: ");
                        				scanf("%s", nuovo_abbonato.nomeutente);
                        				printf("Inserisci password: ");
                        				scanf("%s", nuovo_abbonato.password);
                        				nuovo_abbonato.lezioni_rimanenti = 12; // Lezioni iniziali

                        				// Creazione della chiave per l'abbonato
                        				nuovo_abbonato.chiave = strdup(nuovo_abbonato.nomeutente);  // Chiave può essere il nome utente

                        				// Inserimento nell'hash
                        				tabella_abbonati = inserisci_hash(nuovo_abbonato, tabella_abbonati);
                        				printf("Abbonamento da 12 lezioni creato con successo!\n\n");
                        				break;
                    				}
                    				case 2:
						{
                        				// Abbonamento da 24 lezioni
                        				abbonato nuovo_abbonato;
                        				printf("Inserisci nome utente: ");
                        				scanf("%s", nuovo_abbonato.nomeutente);
                        				printf("Inserisci password: ");
                        				scanf("%s", nuovo_abbonato.password);
                        				nuovo_abbonato.lezioni_rimanenti = 24; // Lezioni iniziali
		
                        				// Creazione della chiave per l'abbonato
                        				nuovo_abbonato.chiave = strdup(nuovo_abbonato.nomeutente);  // Chiave può essere il nome utente

                        				// Inserimento nell'hash
                        				tabella_abbonati = inserisci_hash(nuovo_abbonato, tabella_abbonati);
                        				printf("Abbonamento da 24 lezioni creato con successo!\n\n");
                        				break;
                    				}
                    				case 3:
						{
                        				// Abbonamento da 36 lezioni
                        				abbonato nuovo_abbonato;
                        				printf("Inserisci nome utente: ");
                        				scanf("%s", nuovo_abbonato.nomeutente);
                        				printf("Inserisci password: ");
                        				scanf("%s", nuovo_abbonato.password);
                        				nuovo_abbonato.lezioni_rimanenti = 36; // Lezioni iniziali

                        				// Creazione della chiave per l'abbonato
                        				nuovo_abbonato.chiave = strdup(nuovo_abbonato.nomeutente);  // Chiave può essere il nome utente

                        				// Inserimento nell'hash
                        				tabella_abbonati = inserisci_hash(nuovo_abbonato, tabella_abbonati);
                        				printf("Abbonamento da 36 lezioni creato con successo!\n\n");
                        				break;
                    				}
                    				case 4:
						{
                        				// Torna al menu principale
                        				printf("Tornando al menu principale...\n\n");
                        				return;  // Esce dalla funzione abbonamenti()
                    				}
                    				default:
                        				printf("Valore non valido, riprova.\n\n");
                        				break;
                			}
            			}
            			break;
        		}
        		case 3:
			{
            			printf("Tornando al menu principale...\n\n");
            			return;  // Esce dalla funzione abbonamenti()
        		}
        		default:
            			printf("Valore non valido, riprova.\n\n");
            			break;
    		}
	}
}
