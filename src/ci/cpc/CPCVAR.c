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

#include <ci/cpc/CPCVAR.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void init_CPCVAR(CPCVAR* var) {
    var->length = 0;
    var->keys = malloc(sizeof(char*) * 2048);

    if(var->keys == NULL) {
        printf("Memory Error\n");
        exit(1);
    }

    var->values = malloc(sizeof(char*) * 2048);

    if(var->values == NULL) {
        printf("Memory Error\n");
        free(var->keys);
        exit(1);
    }
}

void declare_var(CPCVAR* var, char* key, char* value) {
    var->keys[var->length] = key;
    var->values[var->length] = value;
    var->length++;
}

char* get_var(CPCVAR* var, char* key) {
    for(int i=0; i < var->length; i++) {
        if(strcmp(var->keys[i], key) == 0) {
            return var->values[i];
        }
    }

    return ".#NOVAR#.";
}

CPCTOKEN place_var(CPCVAR* var, CPCTOKEN token) {
    CPCTOKEN new_token;
    char** tokens = malloc(sizeof(char*) * token.length);
    int length = 0;
    char* tmp;

    for(int i=0; i < token.length; i++) {
        char* tok = token.content[i];

        if(tok[0] == '%') {
            tmp = malloc(sizeof(char) * strlen(token.content[i]));
            strncpy(tmp, token.content[i]+1, strlen(token.content[i]) -2);
            tmp = get_var(var, tmp);
        } else {
            tmp = malloc(sizeof(char) * strlen(token.content[i]));
            strcpy(tmp, token.content[i]);
        }

        tokens[length++] = tmp;
    }

    new_token.length = length;
    new_token.content = tokens;

    return new_token;

}

void destroy(CPCVAR* var) {
    free(var->values);
    free(var->keys);
}
