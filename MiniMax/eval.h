#pragma once
#include "../Strcture/board.h"

float whitePawnEval(int x, int y);

float whiteBishopEval(int x, int y);

float whiteKnightEval(int x, int y);

float whiteRookEval(int x, int y);

float whiteQueenEval(int x, int y);

float whiteKingEval(int x, int y);

float getEval(struct piece** board, int color);