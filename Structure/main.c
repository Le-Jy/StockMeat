#include "board.h"
#include "move.h"
#include <stdio.h>
#include <stdlib.h>

void printboard(struct piece** board)
{
    int c = 1;
    for(int j = 0;j<64;j++,c++)
    {
        printf(" %i ",board[j]->role);
        if(c%8==0)
        {
            printf("\n");
        }
    }
    printf("\n");
    printf("\n");
}

void main()
{
    struct piece** board = malloc(64*sizeof(struct piece));
    initBoard(board,WHITE);
    swap(board[0],board[7*8]);
    promotion(board[0],QUEEN);
    printf("%i\n",board[0]->color);
    printboard(board);
    
    freeBoard(board);
    


        
}