cmake_minimum_required(VERSION 3.14)
project(CPCDOS-Interpreter C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "--std=c99 --pedantic -Wall -Wextra -Wmissing-prototypes -g")

add_executable(cpc ./src/main.c
        ./src/CPCTOKEN.c ./src/header/CPCTOKEN.h
        ./src/CPCVAR.c ./src/header/CPCVAR.h
        ./src/parser.c ./src/header/parser.h
        ./src/str.c ./src/header/str.h)