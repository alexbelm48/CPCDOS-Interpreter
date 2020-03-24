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

#include <ci/cpc/parser.h>
#include <ci/cpc/CPCLINE.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    buffer = (char*)malloc((file_size  + 1 ) * sizeof(char));

    if(buffer == NULL) {
        printf("Memory error");
        fclose(fptr);
        exit(1);
    }

    fread(buffer, sizeof(char), file_size, fptr);
    fclose(fptr);
    buffer[file_size] = '\0';

    line_nbr = count_line(buffer);
    lines = (char**)malloc(sizeof(char*) * line_nbr);

    if(lines == NULL) {
        printf("Memory error\n");
        fclose(fptr);
        free(buffer);
        exit(1);
    }

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

    free(file_lines.content);
}
