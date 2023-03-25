#pragma once
#include "board.h"



void getMoves(struct piece** board, struct piece* piece, int playercolor);

void getPawnMoves(struct piece** board, struct piece* piece, int playercolor);

void getBishopMoves(struct piece** board, struct piece* piece);

void getKnightMoves(struct piece** board, struct piece* piece);

void getRookMoves(struct piece** board, struct piece* piece);

void getQueenMoves(struct piece** board, struct piece* piece);

void getKingMoves(struct piece** board, struct piece* piece);

int move(struct piece** board, struct piece* piece, int x , int y, struct piece** listOfPieces);

int isCheck(struct piece** board, struct piece** listOfPieces, int color);

void freePiece(struct piece* piece);