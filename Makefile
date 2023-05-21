# Makefile

CC = gcc
CFLAGS = `pkg-config --cflags gtk+-3.0` -Wall -O3
LDLIBS = `pkg-config --libs gtk+-3.0`

SRC = main.c Game/game.c Structure/board.c Structure/piece.c Structure/move.c
OBJ = ${SRC:.c=.o}
EXE = ${SRC:.c=}

all: main

main: main.o ${OBJ}

.PHONY: clean

clean:
	${RM} ${OBJ} main.o
	${RM} ${EXE}

# END
