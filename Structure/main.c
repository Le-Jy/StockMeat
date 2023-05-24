#include "board.h"
#include "move.h"
#include <stdio.h>
#include <stdlib.h>

void main()
{
    struct piece** board = malloc(64*sizeof(struct piece));
    initBoard(board,WHITE);
    
    swap(board[5+8],board[5+3*8]);
    swap(board[4+8],board[4+2*8]);
    swap(board[3+7*8],board[6+8*2]);
    // swap(board[5+7*8],board[2+4*8]);
    getMoves(board,board[4]);
    sortMoves(board,board[4]);
    for(struct list* p = board[4]->possibleMoves;p!=NULL;p = p->next)
    {
        printf("PM : %i\n",p->data);
    }


    printboard(board);
    // printf("%i\n",checkMate(board,board[3]->color,5,1));
    

    
    freeBoard(board);
    
}