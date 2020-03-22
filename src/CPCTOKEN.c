#include "header/CPCTOKEN.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* showTokens(CPCTOKEN tokens, int start, int stop) {
    char* return_value = calloc(tokens.charCount, sizeof(char));
    strcpy(return_value, tokens.content[start]);

    if(stop < 0) {
        stop += tokens.length;
    }

    for(int i=start+1; i<tokens.length; i++) {
        strcat(return_value, " ");
        if(i == stop)
            break;

        strcat(return_value, tokens.content[i]);
    }

    return return_value;
}

int nbrSpace(char* str) {
    int nbrSpace = 0;
    for(int i=0; str[i] != '\0'; i++) {
        if(str[i] == ' ')
            nbrSpace++;
    }

    return nbrSpace;
}

CPCTOKEN tokenize(char* line) {
    char* token;
    CPCTOKEN return_value;
    int length = 0;
    char** tokens = malloc(sizeof(char*) * (nbrSpace(line) + 1));
    token = strtok(line, " ");

    while(token != NULL) {
        tokens[length++] = token;
        return_value.charCount += strlen(token) + 1;
        token = strtok(NULL, " ");
    }

    return_value.length = length;
    return_value.content = tokens;

    return return_value;
}
