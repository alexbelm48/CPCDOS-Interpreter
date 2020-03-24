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

#ifndef CPCTOKEN_H
#define CPCTOKEN_H

typedef struct CPCTOKEN {
    char** content;
    int length;
    int charCount;
} CPCTOKEN;

CPCTOKEN tokenize(char* line);
char* showTokens(CPCTOKEN tokens, int start, int stop);
void destroy_CPCTOKEN(CPCTOKEN* tokens);

#endif
