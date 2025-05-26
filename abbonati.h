#ifndef ABBONATI_H
#define ABBONATI_H

#define MAX_CARATTERI 50 // Dimensione massima per i campi stringa

// Struttura dell'abbonato
typedef struct abbonato 
{
    char *chiave; // Stringa univoca per identificare l'abbonato
    char nomeutente[MAX_CARATTERI]; // Nome utente
    char password[MAX_CARATTERI]; // Password
    int lezioni_rimanenti; // Numero di lezioni rimanenti
    struct abbonato *prossimo; // Puntatore al prossimo abbonato
} abbonato;

#endif
