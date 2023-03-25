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
    // for(size_t i = 0;i<32;i++)
    // {
    //     printf("%i\n",listOfPieces[i]->color);
    // }
    // int p = 1+7*8;
    int x = 9;
    
    // printboard(board);
    // getMoves(board, board[p], WHITE);
    // int z = move(board, board[p],0,5,listOfPieces);
    // printf("\n%i\n",z);
    // printboard(board);
    //  getMoves(board, board[x], WHITE);
    // z = move(board, board[x],1,3,listOfPieces);
    // printf("\n%i\n",z);
    // printboard(board);
    // p = 5*8;
    // getMoves(board, board[p], WHITE);
    // z = move(board, board[p],1,3,listOfPieces);
    // printf("\n%i\n",z);
    // printboard(board);
    // for(size_t i = 0;i<32;i++)
    // {
    //     printf("%i\n",listOfPieces[i]->role);
    // }
    board[3+8]->role = EMPTY;
    board[3+8]->color = NONE;
    board[3+8]->value = 0;
    printf("%i\n",board[3+8]->role);
    board[3+8*6]->role = EMPTY;
    board[3+8*6]->color = NONE;
    board[3+8*6]->value = 0;
    printboard(board);
    getMoves(board, board[x], WHITE);
    int z = move(board, board[x],1,3,listOfPieces);
    // printf("\n%i\n",z)
    printboard(board);    
        
}