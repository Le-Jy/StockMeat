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
        printf(" %i ",board[j]->role);
        if(c%8==0)
        {
            printf("\n");
        }
    }
    printf("%i\n", board[0+6*8]->role);
    getMoves(board,board[0+6*8],WHITE);
    while(board[0+6*8]->possibleMoves->next)
    {
        
        board[0+6*8]->possibleMoves = board[0+6*8]->possibleMoves->next;
        printf("%i\n",board[0+6*8]->possibleMoves->data);
    }
        
}