#pragma once
#include "../Structure/board.h"


int playMove(struct piece** board, enum ColorPlayer, int turn);

int miniMax(struct piece** board, int depth, float pruninga, float pruningb, int whiteturn);