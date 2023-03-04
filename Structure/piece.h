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
    EMPTY = -1,
    PAWN = 1,
    BISHOP = 2,
    KNIGHT = 3,
    ROOK = 4,
    QUEEN = 5,
    KING = 6
};
enum Color{
    BLACK = 1,
    WHITE = 0,
    NONE = -2

};

struct piece {
    int x;
    int y;
    enum Role role;
    enum Color color;
    int value;
    struct list *possibleMoves;
};

void newpiece (struct piece *newpiece,int x,int y,enum Color color);