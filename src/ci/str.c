#include <ci/str.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char* strLower(char* str) {
    char* return_value = calloc(strlen(str), sizeof(char*));

    if(return_value == NULL) {
        printf("Memory Error\n");
        exit(1);
    }

    for(int i=0; i < strlen(str); i++) {
        if(str[i] > 64 && str[i] < 91) {
           return_value[i] = str[i] + 32;
        } else{
            return_value[i] = str[i];
        }
    }

    return return_value;
}

char* strFormat(char* str) {
    char* return_value = calloc(strlen(str), sizeof(char*));

    if(return_value == NULL) {
        printf("Memory Error\n");
        exit(1);
    }

    int index = 0;
    for(int i=0; i < strlen(str); i++) {
        if(str[i] == '\\') {
            return_value[index++] += str[++i];
        }

        else {
            return_value[index++] += str[i];
        }
    }

    return return_value;
}

char* removeUselessSpace(char* str) {
    char* return_value = calloc(strlen(str), sizeof(char));

    if(return_value == NULL) {
        printf("Memory Error\n");
        exit(1);
    }

    if(str[strlen(str) - 1 ] == ' ') {
        strncpy(return_value, str, strlen(str) - 1);
    }

    else if(str[0] == ' ') {
        strncpy(return_value, str+1, strlen(str));
    }

    else {
        return_value = str;
    }

    return return_value;
}

int spaceIn(char* str) {
    int return_value = 0;

    for(int i=0; i < strlen(str) && !return_value; i++) {
        if(str[i] == ' ')
            return_value = 1;
    }

    return return_value;
}
