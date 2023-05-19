#pragma once
#include "board.h"



void getMoves(struct piece** board, struct piece* piece, int playercolor);

void getPawnMoves(struct piece** board, struct piece* piece, int playercolor);

void getBishopMoves(struct piece** board, struct piece* piece);

void getKnightMoves(struct piece** board, struct piece* piece);

void getRookMoves(struct piece** board, struct piece* piece);

void getQueenMoves(struct piece** board, struct piece* piece);

void getKingMoves(struct piece** board, struct piece* piece);

int move(struct piece** board, struct piece* piece, int x , int y);

int isCheck(struct piece** board, int color, int indexIgnored, int indexIgnored2);

int canShortCastle(struct piece** board,struct piece* piece);

int canLongCastle(struct piece** board, struct piece* piece);

void shortCastle(struct piece** board, struct piece* piece);

void longCastle(struct piece** board, struct piece* piece);

void promotion(struct piece* piece, int role);

int canPromote(struct piece* piece);

void swap(struct piece *A, struct piece *B);

int checkMate(struct piece** board,int KingColor);

int cannotProtectKing(struct piece** board,int dangerousmoves[8], int KingColor, int cpt);