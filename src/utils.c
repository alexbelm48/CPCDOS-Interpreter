#include <stdlib.h>
#include <string.h>

#include "header/utils.h"

char* strLower(char* str) {
    char* return_value = calloc(strlen(str), sizeof(char*));

    for(int i=0; str[i] != '\0'; i++) {
        if(str[i] > 64 && str[i] < 91) {
           return_value[i] = str[i] + 32;
        } else{
            return_value[i] = str[i];
        }
    }

    return return_value;
}
