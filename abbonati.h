#ifndef ABBONATI_H
#define ABBONATI_H

#define MAX_CARATTERI 16

typedef struct abbonato {
    char *chiave;
    char nomeutente[MAX_CARATTERI];
    char password[MAX_CARATTERI];
    int lezioni_rimanenti;
    struct abbonato *prossimo;
} abbonato;

#endif
