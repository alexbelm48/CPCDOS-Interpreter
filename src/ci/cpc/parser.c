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

#ifdef __unix__
#define CLEAR "clear"
#elif defined(_WIN32) || defined(WIN32)
#define CLEAR "cls"
#endif

#include <ci/cpc/parser.h>
#include <ci/cpc/str.h>
#include <ci/cpc/CPCTOKEN.h>
#include <ci/cpc/CPCVAR.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printCPC(CPCTOKEN tokens) {
    char* last_token = tokens.content[tokens.length-1];
    char* lower = strLower(last_token);
    char* token;

    if(strcmp(lower, "/#r") == 0) {
        token = showTokens(tokens, 1, -1);
        printf("%s", token);
    } else {
        token = showTokens(tokens, 1, 0);
        printf("%s\n", token);
    }

    free(token);
    free(lower);
}

void execute(CPCTOKEN tokens, CPCVAR* var) {
    char* keyword = strLower(tokens.content[0]);
    char* completeLine = showTokens(tokens, 0, 0);

    if(strcmp(keyword, "txt/") == 0) {
        CPCTOKEN new_tokens = place_var(var, tokens);
        printCPC(new_tokens);

        destroy_CPCTOKEN(&new_tokens);
    }

    else if(strcmp(keyword, "cls/") == 0) {
        printf("\n");
        system(CLEAR);
    }

    else if(strcmp(keyword, "fix/") == 0) {
        char* declaration = showTokens(tokens, 1, 0);
        char* varnameMalloc = malloc(sizeof(char) * strlen(declaration));

        strcpy(varnameMalloc, declaration);
        char* varname = removeUselessSpace(strtok(varnameMalloc, "="));

        if(strcmp(declaration, varname) == 0 && tokens.length == 2) {
            printf("\n[-] Erreur de syntaxe sur la ligne:\n%s\nAucune valeur est donnée à la variable !\n\n", completeLine);
            free(keyword);
            free(completeLine);
            free(varname);
            free(declaration);
            exit(1);
        }

        if(spaceIn(varname)) {
            printf("\n[-] Erreur de syntaxe sur la ligne:\n%s\nUn nom de variable ne peux pas avoir d'espace !\n\n", completeLine);
            free(keyword);
            free(varname);
            free(completeLine);
            free(declaration);
            exit(1);
        }

        strtok(declaration, "=");
        char* tok = strtok(NULL, "=");
        char* content = removeUselessSpace(tok);

        declare_var(var, varname, content);
    }

    else if(strcmp(keyword, "rem/") == 0 || strcmp(keyword, "//") == 0) {
        free(completeLine);
        free(keyword);
        return;
    }

    else {
        printf("\n[-] Erreur de syntaxe: Mot clé %s inconnu !\n%s\n\n", keyword, completeLine);
        free(completeLine);
        free(keyword);
        exit(1);

    }

    free(completeLine);
    free(keyword);

}

void parse(CPCLINE lines) {
    CPCVAR var;

    init_CPCVAR(&var);

    for(int i=0; i<lines.length; i++) {
        CPCTOKEN tokens = tokenize(lines.content[i]);
        execute(tokens, &var);

        free(tokens.content);
    }

    destroy(&var);
}
