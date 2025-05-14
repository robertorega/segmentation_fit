#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contattaci.h"
#include "coda.h"

int main()
{
	char scelta[10];
	coda calendario = nuova_coda();
	genera_lezioni(calendario);
	
	//Messaggio di benvenuto all'utente
	printf("Segmentation Fit\n");
	printf("Benvenuti nella palestra numero uno per gli informatici\n");

	//Ciclo infinito per il menu principale
	while (1) 
	{
		clearScreen(); //Pulisce lo schermo della console.
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
            		printf("Funzione ancora da implementare.\n");
            		break;
        		case 2:
            		prenota_lezione(calendario); 
            		break;
        		case 3:
            		printf("Funzione ancora da implementare.\n");
            		break;
 			case 4:
            		printf("Funzione ancora da implementare.\n");
			break;
    			case 5:
           		contattaci();
          		break;
        		case 6:
            		printf("Arrivederci!\n");
            		return 0;  //Esce dal programma
        		default:
            		printf("Valore non valido\n\n");
            		break;
    		}
	}
	return 0;
}
