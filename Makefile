CC  = gcc
SRC = src/*.c
OBJ = cpc

all:
	$(CC) $(SRC) -o $(OBJ)

install: all
	cp ./cpc /usr/bin
