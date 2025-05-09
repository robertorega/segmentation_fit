#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contattaci.h"
#include "queue.h"

int main() {
	int scelta=0; // Variabile che memorizza la scelta dell'utente
	queue calendario = newQueue(); // Crea una nuova coda per il calendario delle lezioni

	// Messaggio di benvenuto all'utente
    	printf("Segmentation Fit\n");
    	printf("Benvenuti nella palestra numero uno per gli informatici\n\n");

	// Ciclo infinito per il menu principale
	while (1) {
		// Stampa le opzioni del menu
    		printf("Selezionare un’opzione:\n");
    		printf("1 - Area abbonati\n");
    		printf("2 - lezioni\n");
   		printf("3 - lezioni più frequentate\n");
   		printf("4 - disdici\n");
		printf("5 - contattaci\n");
    		printf("6 - esci\n");

		printf("La tua scelta: "); // Chiede all'utente di inserire la propria scelta
    		scanf("%d", &scelta); // Legge l'input dell'utente

    		switch(scelta) {
        		case 1:
            		printf("Funzione ancora da implementare.\n");
            		break;
        		case 2:
            		printf("Funzione ancora da implementare.\n");
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
            		return 0;  // esce dal programma
        		default:
            		printf("Valore non valido\n\n"); // Messaggio di errore
            		break;
    		}
	}
	return 0;
}
