#ifdef __unix__
#define CLEAR "clear"
#elif defined(_WIN32) || defined(WIN32)
#define CLEAR "cls"
#endif

#include "header/parser.h"
#include "header/str.h"
#include "header/CPCTOKEN.h"
#include "header/CPCVAR.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printCPC(CPCTOKEN tokens) {
    char* last_token = tokens.content[tokens.length-1];

    if(strcmp(strLower(last_token), "/#r") == 0) {
        printf("%s", showTokens(tokens, 1, -1));
    } else {
        printf("%s\n", showTokens(tokens, 1, 0));
    }
}

void execute(CPCTOKEN tokens, CPCVAR* var) {
    char* keyword = strLower(tokens.content[0]);
    char* completeLine = showTokens(tokens, 0, 0);

    if(strcmp(keyword, "txt/") == 0) {
        CPCTOKEN new_tokens = place_var(var, tokens);
        printCPC(new_tokens);
    }

    else if(strcmp(keyword, "cls/") == 0) {
        printf("\n");
        system(CLEAR);
    }

    else if(strcmp(keyword, "fix/") == 0) {
        char* declaration = showTokens(tokens, 1, 0);
        char* varname = malloc(sizeof(char) * strlen(declaration));

        char* content;

        strcpy(varname, declaration);
        varname = removeUselessSpace(strtok(varname, "="));

        if(strcmp(declaration, varname) == 0 && tokens.length == 2) {
            printf("\n[-] Erreur de syntaxe sur la ligne:\n%s\nAucune valeur est donnée à la variable !\n\n", completeLine);
            exit(1);
        }

        if(spaceIn(varname)) {
            printf("\n[-] Erreur de syntaxe sur la ligne:\n%s\nUn nom de variable ne peux pas avoir d'espace !\n\n", completeLine);
            exit(1);
        }

        content = strtok(declaration, "=");
        content = removeUselessSpace(strtok(NULL, "="));
        declare_var(var, varname, content);
    }

    else if(strcmp(keyword, "rem/") == 0 || strcmp(keyword, "//") == 0) {
        return;
    }

    else {
        printf("\n[-] Erreur de syntaxe: Mot clé %s inconnu !\n%s\n\n", keyword, completeLine);
        exit(1);
    }
}

void parse(CPCLINE lines) {
    CPCVAR var;

    init_CPCVAR(&var);

    for(int i=0; i<lines.length; i++) {
        CPCTOKEN tokens = tokenize(lines.content[i]);
        execute(tokens, &var);
    }

    destroy(&var);
}
