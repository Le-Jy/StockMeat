#pragma once
#include "board.h"


void getMoves(struct piece** board, struct piece* piece, int playercolor);

int move(struct piece** board, int x, int y, struct piece* piece);

void getPawnMoves(struct piece** board, struct piece* piece, int playercolor);

void getBishopMoves(struct piece** board, struct piece* piece);

void getKnightMoves(struct piece** board, struct piece* piece);

void getRookMoves(struct piece** board, struct piece* piece, int playercolor);

void getQueenMoves(struct piece** board, struct piece* piece, int playercolor);

void getKingMoves(struct piece** board, struct piece* piece, int playercolor);