#ifndef CPCVAR_H
#define CPCVAR_H

#include "CPCTOKEN.h"

typedef struct {
    char** keys;
    char** values;
    int length;
} CPCVAR;

void declare_var(CPCVAR* var, char* key, char* value);
char* get_var(CPCVAR* var, char* key);
CPCTOKEN place_var(CPCVAR* var, CPCTOKEN token);
void init_CPCVAR(CPCVAR* var);
void destroy(CPCVAR* var);

#endif
