#include "board.h"

void initBoard(struct piece **board, enum Color colorPlayer)
{
    if(colorPlayer==BLACK)
    {
        
        for (size_t i = 0; i < 2; i++)
        {
            for (size_t j = 0; j < 8; j++)
            {
                struct piece *new = malloc(sizeof(struct piece));
                newpiece(new,j,i,WHITE);
                new->realPlayerColor = colorPlayer;
                board[i*8+j] = new;
            }
            
        }
        for (size_t i = 2; i < 6; i++)
        {
            for (size_t j = 0; j < 8; j++)
            {
                struct piece *new = malloc(sizeof(struct piece));
                newpiece(new,j,i,NONE);
                board[i*8+j] = new;
            }
            
        }
        for (size_t i = 6; i < 8; i++)
        {
            for (size_t j = 0; j < 8; j++)
            {
                struct piece *new = malloc(sizeof(struct piece));
                newpiece(new,j,i,BLACK);
                new->realPlayerColor = colorPlayer;
                board[i*8+j] = new;
            }
        }
        
    }
    else
    {
        for (size_t i = 0; i < 2; i++)
        {
            for (size_t j = 0; j < 8; j++)
            {
                struct piece *new = malloc(sizeof(struct piece));
                newpiece(new,j,i,BLACK);
                new->realPlayerColor = colorPlayer;
                board[i*8+j] = new;
            }
            
        }
        for (size_t i = 2; i < 6; i++)
        {
            for (size_t j = 0; j < 8; j++)
            {
                struct piece *new = malloc(sizeof(struct piece));
                newpiece(new,j,i,NONE);
                board[i*8+j] = new;
            }
            
        }
        for (size_t i = 6; i < 8; i++)
        {
            for (size_t j = 0; j < 8; j++)
            {
                struct piece *new = malloc(sizeof(struct piece));
                newpiece(new,j,i,WHITE);
                new->realPlayerColor = colorPlayer;
                board[i*8+j] = new;
            }
        }
    }
        

}

void printboard(struct piece** board)
{
    int c2 = 0;
    int c = 1;
    for(int j = -1;j<8;j++)
    {
        if(j>=0)
            printf(" %i ",j);
        else
            printf("    ");
    }
    printf("\n");
    for(int j = -1;j<8;j++)
    {
        if(j>=0)
            printf("───");
        else
            printf("    ");
    }
    printf("\n");
    printf(" %i︱",c2);
    for(int j = 0;j<64;j++,c++)
    {
        if(c%8 == 1 && c!=1)
            printf(" %i︱",c2);
        printf(" %i ",board[j]->role);
        if(c%8==0)
        {
            printf("\n");

            c2++;
        }
    }
}

void freeBoard(struct piece** board)
{
    for(int i = 0; i<64;i++)
    {
        freePiece(board[i]);
    }
    free(board);
}
