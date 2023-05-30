#pragma once
#include <stdlib.h>
#include <time.h>
#include "../Structure/board.h";

char getFEN(struct piece** board, enum ColorPlayer);

float* database(char FEN);