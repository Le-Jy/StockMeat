#include "board.h"
#include "move.h"
#include <stdio.h>
#include <stdlib.h>

void printboard(struct piece** board)
{
     printf("------------------------\n");
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

void main()
{
    struct piece** board = malloc(64*sizeof(struct piece));
    initBoard(board,WHITE);
    swap(board[3],board[4]);
    for(int i = 0;i<16;i++)
    {
        if(i!=3 && i!=4)
        {
            board[i]->color = NONE;
            board[i]->role = EMPTY;
        }
    }
    swap(board[3+8],board[7*8]);
    swap(board[8],board[7+7*8]);

    printboard(board);
    printf("%i\n",mathCheck(board,board[3]->color));
    

    
    freeBoard(board);
    
}