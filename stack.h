#ifndef STACK_H
#define STACK_H

#include "partecipante.h"
#define MAXSTACK 20 //numero massimo partecipanti

typedef struct c_stack *stack;

stack newStack(void);
int emptyStack(stack iscritti);
int pop(stack iscritti);
int push(partecipante val, stack iscritti);
char* top(stack iscritti);
int stackSize(stack iscritti);

#endif
