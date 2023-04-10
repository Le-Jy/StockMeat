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
    
    struct piece** listOfPieces = malloc(32*sizeof(struct piece));
    struct piece **board = malloc(64*sizeof(struct piece));
    initBoard(board,WHITE,listOfPieces);
    for(int i=1;i<7;i++)
    {
        if(i!=4)
        {
            board[i]->role = EMPTY;
            board[i]->color = NONE;
            board[i]->value = 0;
        }    
    }
    for(int i=57;i<63;i++)
    {
        if(i!=60)
        {
            board[i]->role = EMPTY;
            board[i]->color = NONE;
            board[i]->value = 0;
        }    
    }
    shortCastle(board,board[4],listOfPieces);
    printboard(board);
    freeBoard(board);
    free(listOfPieces);
        
}