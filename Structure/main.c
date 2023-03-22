#include "board.h"
#include "move.h"
#include <stdio.h>
#include <stdlib.h>

void main()
{
    struct piece** listOfPieces = malloc(32*sizeof(struct piece));
    int p = 6*8;
    struct piece **board = malloc(64*sizeof(struct piece));
    initBoard(board,WHITE,listOfPieces);
    int c = 1;
    for(int j = 0;j<64;j++,c++)
    {
        printf(" %i ",board[j]->color);
        if(c%8==0)
        {
            printf("\n");
        }
    }
    printf("\n");
    printf("\n");
    getMoves(board, board[p], WHITE);
    int z = move(board, board[p],0,7,listOfPieces);
    printf("%i\n",z);
    printf("\n");
    c = 1;
    for(int j = 0;j<64;j++,c++)
    {
        printf(" %i ",board[j]->role);
        if(c%8==0)
        {
            printf("\n");
        }
    }
    
        
}