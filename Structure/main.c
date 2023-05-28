#include "board.h"
#include "move.h"
#include "../Game/game.h"
#include <stdio.h>
#include <stdlib.h>

void main()
{
    struct piece** board = malloc(64*sizeof(struct piece));
    initBoard(board,WHITE);
    printboard(board);
    swap(board[4],board[16]);
    swap(board[5+7*8],board[4+6*8]);
    swap(board[3+7*8],board[4+7*8]);
    swap(board[5+0*8],board[7+3*8]);
    printboard(board);
    printf("%i\n",isCheckinG(board,4,6));
    // printf("%i\n",checkMate(board,board[3]->color,5,1));
    

    
    freeBoard(board);
    
}