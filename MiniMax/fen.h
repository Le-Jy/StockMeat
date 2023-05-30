#pragma once
#include <stdlib.h>
#include <time.h>
#include "../Structure/board.h"

char* getFEN(struct piece** board, int colorPlayer);

float* database(char *FEN);