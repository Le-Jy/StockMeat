#include "eval.h"
#include "../Structure/board.h"

float whitePawnEval(int x, int y){
    float grid[64]={0,0,0,0,0,0,0,0,5,5,5,5,5,5,5,5,1,1,2,3,3,2,1,1,0.5,0.5,1,2.5,2.5,1,0.5,0.5,0,0,0,2,2,0,0,0,0.5,-0.5,-1,0,0,-1,-0.5,0.5,0.5,1,1,-2,-2,1,1,0.5,0,0,0,0,0,0,0,0};
    return grid[8*y+x];
}

float whiteBishopEval(int x, int y){
    float grid[64]={-2,-1,-1,-1,-1,-1,-1,-2,-1,0,0,0,0,0,0,-1,-1,0,0.5,1,1,0.5,0,-1,-1,0.5,0.5,1,1,0.5,0.5,-1,-1,0,1,1,1,1,0,-1,-1,1,1,1,1,1,1,-1,-1,0.5,0,0,0,0,0.5,-1,-2,-1,-1,-1,-1,-1,-1,-2};
    return grid[8*y+x];
}

float whiteKnightEval(int x, int y){
    float grid[64]={-5,-4,-3,-3,-3,-3,-4,-5,-4,-2,0,0,0,0,-2,-4,-3,0,1,1.5,1.5,1,0,-3,-3,0.5,1.5,2,2,1.5,0.5,-3,-3,0,1.5,2,2,1.5,0,-3,-3,0.5,1,1.5,1.5,1,0.5,-3,-4,-2,0,0.5,0.5,0,-2,-4,-5,-4,-3,-3,-3,-3,-4,-5};
    return grid[8*y+x];
}

float whiteRookEval(int x, int y){
    float grid[64]={0,0,0,0,0,0,0,0,0.5,1,1,1,1,1,1,0.5,-0.5,-0.5,-0.5,-0.5,-0.5,-0.5,-0.5,-0.5,-0.5,-0.5,-0.5,-0.5,-0.5,-0.5,-0.5,-0.5,-0.5,-0.5,-0.5,-0.5,-0.5,-0.5,-0.5,-0.5,-0.5,-0.5,-0.5,-0.5,-0.5,-0.5,-0.5,-0.5,-0.5,-0.5,-0.5,-0.5,-0.5,-0.5,-0.5,-0.5,0,0,0,0.5,0.5,0,0,0};
    return grid[8*y+x];
}

float whiteQueenEval(int x, int y){
    float grid[64]={-2,-1,-1,-0.5,-0.5,-1,-1,-2,-1,0,0,0,0,0,0,-1,-1,0,0.5,0.5,0.5,0.5,0,-1,-0.5,0,0.5,0.5,0.5,0.5,0,-0.5,0,0,0.5,0.5,0.5,0.5,0,-0.5,-1,0.5,0.5,0.5,0.5,0.5,0,-1,-1,0,0.5,0,0,0,0,-1,-2,-1,-1,-0.5,-0.5,-1,-1,-2};
    return grid[8*y+x];
}

float whiteKingEval(int x, int y){
    float grid[64]={-3,-4,-4,-5,-5,-4,-4,-3,-3,-4,-4,-5,-5,-4,-4,-3,-3,-4,-4,-5,-5,-4,-4,-3,-3,-4,-4,-5,-5,-4,-4,-3,-2,-3,-3,-4,-4,-3,-3,-2,-1,-2,-2,-2,-2,-2,-2,-1,2,2,0,0,0,0,2,2,2,3,1,0,0,1,3,2};
    return grid[8*y+x];
}

float getEval(struct piece** board, int color){
    float eval=0;
    int materialblack=0;
    int materialwhite=0;
    int whitebishops=0;
    int blackbishops=0;
    int whitepawns [8] = {0,0,0,0,0,0,0,0};
    int blackpawns [8] = {0,0,0,0,0,0,0,0};
    int whiterooks [8] = {0,0,0,0,0,0,0,0};
    int blackrooks [8] = {0,0,0,0,0,0,0,0};
    for (int i=0;i<64;i++){
        if (board[i]->role!=0){
            if (board[i]->color==WHITE){
                materialwhite=materialwhite+board[i]->value;
                if (board[i]->role==PAWN){
                    materialwhite=materialwhite+whitePawnEval(board[i]->x,board[i]->y)/10;
                    whitepawns[board[i]->y]++;
                }
                if (board[i]->role==BISHOP){
                    whitebishops++;
                    materialwhite=materialwhite+whiteBishopEval(board[i]->x,board[i]->y)/10;
                }
                if (board[i]->role==KNIGHT){
                    materialwhite=materialwhite+whiteKnightEval(board[i]->x,board[i]->y)/10;
                }
                if (board[i]->role==ROOK){
                    materialwhite=materialwhite+whiteRookEval(board[i]->x,board[i]->y)/10;
                    whiterooks[board[i]->x]++;
                }
                if (board[i]->role==QUEEN){
                    materialwhite=materialwhite+whiteQueenEval(board[i]->x,board[i]->y)/10;
                }
                if (board[i]->role==KING){
                    materialwhite=materialwhite+whiteKingEval(board[i]->x,board[i]->y)/10;
                }
            }
            else{
                materialblack=materialblack+board[i]->value;
                int xvalue=board[i]->x;
                int yvalue=board[i]->y;
                yvalue = (7-yvalue);
                if (board[i]->role==PAWN){
                    materialblack=materialblack+whitePawnEval(xvalue,yvalue)/10;
                    blackpawns[yvalue]++;
                }
                if (board[i]->role==BISHOP){
                    blackbishops++;
                    materialblack=materialblack+whiteBishopEval(xvalue,yvalue)/10;
                }
                if (board[i]->role==KNIGHT){
                    materialblack=materialblack+whiteKnightEval(xvalue,yvalue)/10;
                }
                if (board[i]->role==ROOK){
                    materialblack=materialblack+whiteRookEval(xvalue,yvalue)/10;
                    blackrooks[xvalue]++;
                }
                if (board[i]->role==QUEEN){
                    materialblack=materialblack+whiteQueenEval(xvalue,yvalue)/10;
                }
                if (board[i]->role==KING){
                    materialblack=materialblack+whiteKingEval(xvalue,yvalue)/10;
                }
            }
        }
    }
    eval=materialwhite-materialblack;
    if (whitebishops==2 && whitebishops>blackbishops){
        eval=eval+0.3;
    }
    if (blackbishops==2 && blackbishops>whitebishops){
        eval=eval-0.3;
    }
    for (int i=0;i<8;i++){
        if (whitepawns[i]>1){
            eval=eval-0.1*(i-1);
        }
        if (blackpawns[i]>1){
            eval=eval+0.1*(i-1);
        }
        if (whitepawns[i]==0 && blackpawns[i]==0){
            if (whiterooks[i]>0 && !(blackrooks[i]>0)){
                eval=eval+0.15;
            }
            if (blackrooks[i]>0 &&  !(whiterooks[i]>0)){
                eval=eval-0.15;
            }
        }
    }
    return eval;
}