#pragma once
#include "piece.h"
#include <stdlib.h>

void initBoard(struct piece **board, enum Color colorPlayer);

void freeBoard(struct piece** board);