#include "board.h"
#include "move.h"
#include <stdio.h>
#include <stdlib.h>

void main()
{
    int p = 4+7*8;
    struct piece **board = malloc(64*sizeof(struct piece));
    initBoard(board,WHITE);
    board[-4+7*8]->color = NONE;
    board[-4+7*8]->role = EMPTY;
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
    printf("Possible moves of %i:\n", board[p]->role);
    while(board[p]->possibleMoves->data >= 0)
    {
        printf("%i\n",board[p]->possibleMoves->data);        
        board[p]->possibleMoves = board[p]->possibleMoves->next;
    }
        
}