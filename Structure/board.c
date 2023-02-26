#include "board.h"
#include "piece.h"
#include <stdlib.h>

void initBoard(struct piece **board, enum Color colorPlayer)
{
    if(colorPlayer)
    {
        for (size_t i = 0; i < 2; i++)
        {
            for (size_t j = 0; j < 8; j++)
            {
                struct piece *new = malloc(sizeof(struct piece));
                newpiece(new,j,i,WHITE);
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
                board[i*8+j] = new;
            }
        }
    }
        

}
