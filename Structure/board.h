#pragma once
#include "piece.h"
#include <stdlib.h>

void initBoard(struct piece **board, enum Color colorPlayer, struct piece** listOfPieces);

void freeBoard(struct piece** board);