#pragma once
#include "../Structure/board.h"


float* playMove(struct piece** board, enum ColorPlayer, int turn);

float* miniMax(struct piece** board, int depth, float pruninga, float pruningb, int whiteturn);