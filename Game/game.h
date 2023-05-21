#pragma once
#include "../Structure/board.h"
#include "../Structure/move.h"

void initParty(struct piece** board, int color);

void printColorTurn(unsigned long turn);

int* choosePiece();

int* chooseDest();

int isValidPiece(int* coord, struct piece** board, int turn);