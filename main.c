#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contattaci.h"
#include "queue.h"

void contattaci();

int main(){
	char scelta[10];

    	printf("Segmentation Fit\n");
    	printf("Benvenuti nella palestra numero uno per gli informatici\n\n");

while (1) {

    		printf("Selezionare un’opzione:\n");
    		printf("1 - abbonati\n");
    		printf("2 - lezioni\n");
   	 	printf("3 - lezioni più frequentate\n");
   	 	printf("4 - login abbonati\n");
  	  	printf("5 - i nostri iscritti\n");
   	 	printf("6 - disdici\n");
 	   	printf("7 - contattaci\n");
    	printf("8 - esci\n");

		printf("La tua scelta: ");
    		scanf("%s", scelta);

    	switch(atoi(scelta)) 
		{
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
      			      	printf("Funzione ancora da implementare.\n");
     			       	break;
    		    	case 6:
      			      	printf("Funzione ancora da implementare.\n");
     			       	break;
    		    	case 7:
           			 	contattaci();
          			  	break;
        	case 8:
            	printf("Arrivederci!\n");
            	return 0;  // esce dal programma
        	default:
            	printf("Valore non valido\n\n");
            	break;
    		}
}
return 0;
}