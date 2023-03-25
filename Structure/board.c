#include "board.h"

void initBoard(struct piece **board, enum Color colorPlayer, struct piece** listOfPiece)
{
    if(colorPlayer==1)
    {
        int cpt = 0;
        for (size_t i = 0; i < 2; i++)
        {
            for (size_t j = 0; j < 8; j++)
            {
                struct piece *new = malloc(sizeof(struct piece));
                newpiece(new,j,i,WHITE,cpt);
                new->realPlayerColor = colorPlayer;
                board[i*8+j] = new;
                listOfPiece[cpt] = new;
                cpt++;
            }
            
        }
        for (size_t i = 2; i < 6; i++)
        {
            for (size_t j = 0; j < 8; j++)
            {
                struct piece *new = malloc(sizeof(struct piece));
                newpiece(new,j,i,NONE,0);
                board[i*8+j] = new;
            }
            
        }
        for (size_t i = 6; i < 8; i++)
        {
            for (size_t j = 0; j < 8; j++)
            {
                struct piece *new = malloc(sizeof(struct piece));
                newpiece(new,j,i,BLACK,cpt);
                new->realPlayerColor = colorPlayer;
                board[i*8+j] = new;
                listOfPiece[cpt] = new;
                cpt++;
            }
        }
        
    }
    else
    {
        int cpt = 0;
        for (size_t i = 0; i < 2; i++)
        {
            for (size_t j = 0; j < 8; j++)
            {
                struct piece *new = malloc(sizeof(struct piece));
                newpiece(new,j,i,BLACK,cpt);
                new->realPlayerColor = colorPlayer;
                board[i*8+j] = new;
                listOfPiece[cpt] = new;
                cpt++;
            }
            
        }
        for (size_t i = 2; i < 6; i++)
        {
            for (size_t j = 0; j < 8; j++)
            {
                struct piece *new = malloc(sizeof(struct piece));
                newpiece(new,j,i,NONE,0);
                board[i*8+j] = new;
            }
            
        }
        for (size_t i = 6; i < 8; i++)
        {
            for (size_t j = 0; j < 8; j++)
            {
                struct piece *new = malloc(sizeof(struct piece));
                newpiece(new,j,i,WHITE,cpt);
                new->realPlayerColor = colorPlayer;
                board[i*8+j] = new;
                listOfPiece[cpt] = new;
                cpt++;
            }
        }
    }
        

}
