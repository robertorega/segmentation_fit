#include <stdio.h>
#include <stdlib.h>
#include "lezione.h"
#include "queue.h"
#define NULLITEM (lezione){.max_partecipanti = -1}

struct node{
lezione value;
struct node *next;
};

struct c_queue {
struct node *head,*tail;
int numel;
};

queue newQueue(void)
{
	struct c_queue *calendario;
	calendario = malloc(sizeof(struct c_queue));
    if (calendario == NULL)
        return NULL;

    calendario->numel = 0;
	calendario->head = NULL;
	calendario->tail = NULL;
	return calendario;
}

int emptyQueue(queue calendario)
{
    if (calendario == NULL)
        return -1;
	return calendario->numel == 0;
}

int inserisci(lezione val, queue calendario)
{ 
	if (calendario == NULL)
        return -1;

	struct node *nuovo;
    nuovo = malloc(sizeof(struct node));
	if (nuovo == NULL)
        return 0;

	nuovo->value = val;
	nuovo->next = NULL;

	if (calendario->head == NULL)
    		calendario->head = nuovo;
	else
    		calendario->tail->next = nuovo;

	calendario->tail = nuovo;
	(calendario->numel)++;
	return 1;
}

lezione rimuovi(queue calendario){ 
	if (calendario == NULL)
        return NULLITEM;
	if (calendario->numel == 0)
        return NULLITEM; 

	lezione result = calendario->head->value;
	struct node *temp = calendario->head; 
	calendario->head = calendario->head->next; 
	free(temp); 

	if (calendario->head == NULL)
  	  	calendario->tail = NULL;

	(calendario->numel)--;
	return result;
}