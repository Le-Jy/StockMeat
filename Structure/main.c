#include "board.h"
#include "move.h"
#include <stdio.h>
#include <stdlib.h>

void main()
{
    struct piece **board = malloc(64*sizeof(struct piece));
    initBoard(board,WHITE);
    int c = 1;
    for(int j = 0;j<64;j++,c++)
    {
        printf(" %i ",board[j]->color);
        if(c%8==0)
        {
            printf("\n");
        }
    }
    getMoves(board,board[7+1*8],WHITE);
    while(board[7+1*8]->possibleMoves->data >= 0)
    {
        printf("%i\n",board[7+1*8]->possibleMoves->data);        
        board[7+1*8]->possibleMoves = board[7+1*8]->possibleMoves->next;
    }
        
}