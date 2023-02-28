#pragma once
#include "board.h"


void getMoves(struct piece** board, struct piece* piece, int playercolor);

int move(struct piece** board, int x, int y, struct piece* piece);

void getPawnMoves(struct piece** board, struct piece* piece, int playercolor);