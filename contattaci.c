#include <stdio.h>
#include "contattaci.h"

/* Funzione: contattaci
*
* Stampa a schermo le informazioni di contatto e attende che l'utente prema INVIO per continuare
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
    getchar(); // Consuma il carattere di newline rimasto nel buffer
	getchar(); // Libera il buffer per l'input successivo
}
