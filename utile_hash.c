#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "utile_hash.c"

// Struttura della tabella hash
struct c_hash 
{
  int dimensione;
  abbonato **tabella;
};

