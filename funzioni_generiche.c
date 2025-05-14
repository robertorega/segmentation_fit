#include <stdio.h>
#include <stdlib.h>

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
void pulisci_schermo()
{
	#ifdef _WIN32
    		system("cls");
	#else
    		system("clear");
	#endif
}
