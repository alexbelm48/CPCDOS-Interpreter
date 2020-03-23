CC  = gcc
SRC = src/*.c
OBJ = cpc
DEBUG = -g

all:
	$(CC) $(DEBUG) $(SRC) -o $(OBJ)

install: all
	cp ./cpc /usr/bin
