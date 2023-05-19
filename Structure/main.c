#include "board.h"
#include "move.h"
#include <stdio.h>
#include <stdlib.h>

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
    swap(board[3],board[4]);
    swap(board[4],board[4+8]);
    swap(board[0],board[7*8]);
    swap(board[8],board[7+7*8]);

    printboard(board);
    printf("%i\n",checkMate(board,board[3]->color));
    

    
    freeBoard(board);
    
}