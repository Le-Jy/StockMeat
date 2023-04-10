#pragma once
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

struct list
{
  struct list *next;
  int data;
};

void list_init(struct list *list);

int list_is_empty(struct list *list);

enum Role {
    EMPTY = 0,
    PAWN = 1,
    BISHOP = 2,
    KNIGHT = 3,
    ROOK = 4,
    QUEEN = 5,
    KING = 6
};
enum Color{
    BLACK = 1,
    WHITE = -1,
    NONE = 0

};

struct piece {
    int x;
    int y;
    enum Role role;
    enum Color color;
    int value;
    struct list *possibleMoves;
    int realPlayerColor;
    int index;
    int hasMoved;
};

void newpiece (struct piece *newpiece,int x,int y,enum Color color,int index);

void freeMoves(struct piece* piece);

void freePiece(struct piece* piece);