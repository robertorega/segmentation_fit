#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "partecipante.h"
#include "stack.h"

struct c_stack {
	partecipante vet[MAXSTACK];
	int top;
};

stack newStack(void)
{
	stack iscritti;
	iscritti = malloc(sizeof(struct c_stack));
	if (iscritti == NULL) return NULL;
	iscritti->top = 0;
	return iscritti;
}

int emptyStack(stack iscritti)
{
	return iscritti->top == 0;
}

int push(partecipante val, stack iscritti)
{
	if (iscritti->top == MAXSTACK)
    	return 0;
	strcpy(iscritti->vet[iscritti->top], val);
	(iscritti->top)++;
	return 1;
}

int pop(stack iscritti)
{
	if (iscritti->top == 0)
    	return 0;
	(iscritti->top)--;
	return 1;
}

char* top(stack iscritti)
{
	if (iscritti->top > 0)
    	return iscritti->vet[iscritti->top - 1];
	else
    	return NULLPARTECIPANTE;
}

int stackSize(stack iscritti)
{
	if (iscritti == NULL)
    		return -1;  
	return iscritti->top; // numero partecipanti
}
