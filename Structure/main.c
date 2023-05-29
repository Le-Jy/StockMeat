#include "board.h"
#include "move.h"
#include "../Game/game.h"
#include <stdio.h>
#include <stdlib.h>

void main()
{
    struct piece** board = malloc(64*sizeof(struct piece));
    initBoard(board,WHITE);
    printf("\n");
    printboard(board);
    printf("\n");
    // printf("%i\n",checkMate(board,board[3]->color,5,1));
    

    
    freeBoard(board);
    
}