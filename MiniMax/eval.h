#pragma once
#include "../Strcture/board.h"

int whitePawnEval(int x, int y);

int whiteBishopEval(int x, int y);

int whiteKnightEval(int x, int y);

int whiteRookEval(int x, int y);

int whiteQueenEval(int x, int y);

int whiteKingEval(int x, int y);

int getEval(struct piece** board, int color);