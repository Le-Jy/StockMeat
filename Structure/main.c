#include "board.h"
#include "move.h"
#include <stdio.h>
#include <stdlib.h>

void main()
{
    int p = 2;
    struct piece **board = malloc(64*sizeof(struct piece));
    initBoard(board,WHITE);
    
    board[1+1*8]->role = EMPTY;
    board[1+1*8]->color = NONE;
    board[3+1*8]->role = EMPTY;
    board[3+1*8]->color = NONE;
    int c = 1;
    for(int j = 0;j<64;j++,c++)
    {
        printf(" %i ",board[j]->role);
        if(c%8==0)
        {
            printf("\n");
        }
    }
    getMoves(board,board[p],WHITE);
    while(board[p]->possibleMoves->data >= 0)
    {
        printf("%i\n",board[p]->possibleMoves->data);        
        board[p]->possibleMoves = board[p]->possibleMoves->next;
    }
        
}