#ifndef CPCTOKEN_H
#define CPCTOKEN_H

typedef struct CPCTOKEN {
    char** content;
    int length;
    int charCount;
} CPCTOKEN;

CPCTOKEN tokenize(char* line);
char* showTokens(CPCTOKEN tokens, int start, int stop);
void destroy_CPCTOKEN(CPCTOKEN* tokens);

#endif
