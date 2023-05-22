#include "board.h"
#include "move.h"
#include <stdio.h>
#include <stdlib.h>

void main()
{
    struct piece** board = malloc(64*sizeof(struct piece));
    initBoard(board,WHITE);
    
    swap(board[5+8],board[5+3*8]);
    // swap(board[3+7*8],board[5+8]);
    // swap(board[5+7*8],board[2+4*8]);


    printboard(board);
    printf("x : %i, y : %i",board[5+3*8]->x,board[5+3*8]->y);
    // printf("%i\n",checkMate(board,board[3]->color,5,1));
    

    
    freeBoard(board);
    
}