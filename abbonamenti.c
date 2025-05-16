#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "abbonamenti.h"
#include "funzioni_generiche.h"
#include "lezione.h"
#include "hash.h"

void abbonamenti(coda calendario)
{
	int scelta = 0;
	tabella_hash tabella_abbonati = nuova_hash(10);

	while (1) {
        pulisci_schermo();

        printf("Scegli il piano di allenamento adatto a te!\n\n");
        printf("Selezionare un’opzione:\n");
        printf("1 - Sei già abbonato? Entra nella tua area riservata\n");
        printf("2 - Vuoi creare un nuovo abbonamento?\n");
        printf("3 - Torna al menu principale\n\n");

        printf("La tua scelta: ");
        scanf("%d", &scelta);
        getchar(); // pulisce newline

        switch (scelta)
	{
        	case 1:
		{
                	char nomeutente[MAX_CARATTERI];
                	char password[MAX_CARATTERI];

                	printf("Inserisci il nome utente per entrare nella tua area riservata: ");
                	scanf("%s", nomeutente);

                	abbonato *abbonato_trovato = cerca_hash(nomeutente, tabella_abbonati);

                	if (abbonato_trovato == NULL) {
                    		printf("Utente non trovato.\n");
                	} else {
                    		printf("Inserisci la tua password: ");
                    		scanf("%s", password);

                    		if (strcmp(abbonato_trovato->password, password) == 0)
				{
                        		printf("Benvenuto %s, hai %d lezioni rimanenti.\n",
                               		abbonato_trovato->nomeutente,
                               		abbonato_trovato->lezioni_rimanenti);

                        		int scelta_operazione = 0;
                        		int dentro_area = 1;
                        		while (dentro_area)
					{
                            			printf("\n1 - Prenota una lezione\n");
                            			printf("2 - Torna al menu abbonamenti\n");
                            			printf("Scelta: ");
                            			scanf("%d", &scelta_operazione);
                            			getchar();

                            			switch (scelta_operazione) {
                                			case 1:
                                    			prenota_lezione_abbonato(calendario, abbonato_trovato);
                                    			break;
                                			case 2:
                                    			dentro_area = 0;
                                    			break;
                                			default:
                                    			printf("Scelta non valida.\n");
                            			}
                        		}
                    		} else {
                        		printf("Password errata.\n");
                    		}
                	}
                	break;
            	}

            	case 2:
		{
                	int scelta_abbonamento = 0;
                	while (1)
			{
                    		printf("Scegli il piano di allenamento:\n");
                    		printf("1 - Abbonamento da 12 lezioni - 60€\n");
                    		printf("2 - Abbonamento da 24 lezioni - 100€\n");
                    		printf("3 - Abbonamento da 36 lezioni - 150€\n");
                    		printf("4 - Torna al menu principale\n");

                    		printf("La tua scelta: ");
                    		scanf("%d", &scelta_abbonamento);
                    		getchar();

                    		if (scelta_abbonamento >= 1 && scelta_abbonamento <= 3)
				{
                        		abbonato nuovo_abbonato;
                        		printf("Inserisci nome utente: ");
                        		scanf("%s", nuovo_abbonato.nomeutente);
                        		printf("Inserisci password: ");
                        		scanf("%s", nuovo_abbonato.password);

                        		switch (scelta_abbonamento)
					{
                            			case 1: nuovo_abbonato.lezioni_rimanenti = 12; break;
                            			case 2: nuovo_abbonato.lezioni_rimanenti = 24; break;
                            			case 3: nuovo_abbonato.lezioni_rimanenti = 36; break;
                        		}

                        		nuovo_abbonato.chiave = strdup(nuovo_abbonato.nomeutente);
                        		tabella_abbonati = inserisci_hash(nuovo_abbonato, tabella_abbonati);
                        		printf("Abbonamento creato con successo!\n\n");
                    		} else if (scelta_abbonamento == 4) {
                        		break;
                    		} else {
                        		printf("Valore non valido, riprova.\n\n");
                    		}
                	}
                	break;
            	}

            	case 3:
                	printf("Tornando al menu principale...\n\n");
                	return;

            	default:
                	printf("Valore non valido, riprova.\n\n");
                	break;
        }
    }
}
