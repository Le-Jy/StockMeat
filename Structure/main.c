#include "board.h"
#include <stdio.h>
#include <stdlib.h>

void main()
{
    struct piece **board = malloc(64*sizeof(struct piece));
    initBoard(board,WHITE);
    int c = 1;
    for(int j = 0;j<64;j++,c++)
    {
        printf(" %i ",board[j]->role);
        if(c%8==0)
        {
            printf("\n");
        }
    }    
}