#include "lezione.h"

typedef struct c_queue *queue;

queue newQueue(void);
int emptyQueue(queue calendario);
int inserisci(lezione val, queue calendario);
lezione rimuovi(queue calendario);