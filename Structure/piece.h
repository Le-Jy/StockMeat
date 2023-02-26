#pragma once
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
};

void newpiece (struct piece *newpiece,int x,int y,enum Color color);