#ifndef TRACERY_HELPERS_H
#define TRACERY_HELPERS_H
#include "list.h"

typedef struct 
{
    char *key;
    List *expansions;
    
} Rule;



Rule* make_rule(char* key);

void free_rule(Rule* rule);

List* read_grammar(char* filename);

char* expand(char* rule, List* grammar);

void print_grammar(List* grammar);

#endif
