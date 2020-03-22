#include "header/parser.h"
#include "header/utils.h"
#include "header/CPCTOKEN.h"

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


void execute(CPCTOKEN tokens, int lineNbr) {
    char* keyword = strLower(tokens.content[0]);

    if(strcmp(keyword, "txt/") == 0) {
        printCPC(tokens);
        return;
    }

    else if(strcmp(keyword, "rem/") == 0) {
        return;
    }

    else {
        printf("\n\n[-] Erreur de syntaxe sur la ligne %d: Mot clé %s inconnu !\n%s\n\n", lineNbr, keyword, showTokens(tokens, 0, 0));
        exit(1);
        return;
    }

}

void parse(CPCLINE lines) {
    for(int i=0; i<lines.length; i++) {
        CPCTOKEN tokens = tokenize(lines.content[i]);
        execute(tokens, i+1);
    }
}
