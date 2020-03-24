/*
 * CC+ interpreter written in C
 * Copyright (C) 2020 0v3rl0w & contributors
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <ci/cpc/CPCTOKEN.h>
#include <ci/cpc/str.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char* showTokens(CPCTOKEN tokens, int start, int stop) {
    char* return_value = calloc(tokens.charCount, sizeof(char));

    if(return_value == NULL) {
        printf("Memory Error\n");
        exit(1);
    }

    char* format = strFormat(tokens.content[start]);
    strcpy(return_value, format);

    free(format);

    if(stop < 0) {
        stop += tokens.length;
    }

    for(int i=start+1; i<tokens.length; i++) {
        strcat(return_value, " ");
        if(i == stop)
            break;

        format = strFormat(tokens.content[i]);
        strcat(return_value, format);

        free(format);
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

    if(tokens == NULL) {
        printf("Memory Error\n");
        exit(1);
    }

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

void destroy_CPCTOKEN(CPCTOKEN* token) {
    free(token->content);
}
