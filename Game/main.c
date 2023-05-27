#include "game.h"

void main()
{
    
    struct piece** board = malloc(64*sizeof(struct piece));
    int checkMatevalue = 0;
    int check = 0;
    unsigned long turn = 0;
    int* coord = NULL;
    initParty(board, WHITE);
    int x,y,xx,yy;

    while(checkMatevalue == 0)
    {
        printboard(board);
        printColorTurn(turn);
        int hasmoved = 0;
        while(hasmoved == 0)
        {
            coord = choosePiece();
            while(isValidPiece(coord, board, turn) == 0)
            {
                printf("Please, select your color !\n");
                coord = choosePiece();
            }
            x = coord[0];
            y = coord[1];
            int* coord2 = chooseDest();
            xx = coord2[0];
            yy = coord2[1];
            if(move(board,board[x + y*8],xx,yy))
                hasmoved = 1;
            else if(board[x+8*y]->role == KING && board[xx+yy*8]->role == ROOK)
            {
                if(yy>y && canShortCastle(board,board[x+8*y]))
                {
                    shortCastle(board,board[x+8*y]);
                    hasmoved = 1;
                }
                if(yy<y && canLongCastle(board,board[x+8*y]))
                {
                    longCastle(board,board[x+8*y]);
                    hasmoved = 1;
                }
                else
                {
                    printf("You can't castle\n");
                }

            }
            else
            {
                printf("Invalid move, please retry\n");
                free(coord);
                free(coord2);
            }
        }
        if(canPromote(board[xx+yy*y]))
        {
            printf("Please promote your pawn\n");
            printf("Bishop : 2\nKnight : 3\nRook : 4\nQueen : 5\n");
            int pr;
            int err = scanf("%d",&pr);
            while(err>1 && pr <2 && pr>5)
            {
                printf("Please promote your pawn\n");
                printf("Bishop : 2\nKnight : 3\nRook : 4\nQueen : 5\n");
                err = scanf("%d",&pr);
            }
        }
        if(isCheckinG(board,xx,yy))
        {
            if(checkMate(board,board[xx+yy*8]->color,xx,yy))
                checkMatevalue = board[xx+yy*8]->color;
        }
        turn++;
    }
    printboard(board);
    freeBoard(board);
    return;
}