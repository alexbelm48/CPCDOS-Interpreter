#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "header/parser.h"
#include "header/CPCLINE.h"

int count_line(char* buffer) {
    int line_nbr = 0;
    for(size_t i = 0; i < strlen(buffer); i++) {
        if(buffer[i] == '\n')
            line_nbr++;
    }

    return line_nbr;
}

CPCLINE read_lines(char* filename)
{
    FILE* fptr;
    char* buffer;
    char* tmp;
    char** lines;
    long file_size;
    int line_nbr;
    int index = 0;
    CPCLINE return_value;

    if((fptr = fopen(filename, "r")) == NULL) {
        fprintf(stderr, "%s: No such file\n", filename);
        fclose(fptr);
        exit(1);
    }

    fseek(fptr, 0, SEEK_END);
    file_size = ftell(fptr);
    fseek(fptr, 0, SEEK_SET);

    buffer = (char*)malloc(file_size * sizeof(char));

    if(buffer == NULL) {
        fprintf(stderr, "Memory error");
        fclose(fptr);
        exit(1);
    }

    fread(buffer, sizeof(char), file_size, fptr);
    fclose(fptr);

    line_nbr = count_line(buffer);
    lines = (char**)malloc(sizeof(char*) * line_nbr);

    tmp = strtok(buffer, "\n");

    while(tmp != NULL) {
        lines[index++] = tmp;
        tmp = strtok(NULL, "\n");
    }

    return_value.content = lines;
    return_value.length = index;

    return return_value;
}


int main(int argc, char* argv[])
{
    if(argc == 1 || argc > 2) {
        fprintf(stderr, "Usage: %s FILE.cpc\n", argv[0]);
        return 1;
    }

    CPCLINE file_lines = read_lines(argv[1]);
    parse(file_lines);
}
