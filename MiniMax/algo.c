#include "algo.h"



int playMove(struct piece** board, enum Color ColorPlayer, int turn){
    char FEN=(getFEN(board, ColorPlayer));
    int res=0;
    int res2=0;
    int res3=0;
    int val=0;
    int color=0;
    if (ColorPlayer==WHITE){
        color=1;
    }
    if (turn<5){
        res,res2,res3=database(FEN);
        if (res!=NULL){
            return res, res2, res3;
        }
        else{
            val, res, res2, res3 = miniMax(board, 3, -infinity, +infinity, color);
        }
    }
    else{
        val, res, res2, res3 = miniMax(board, 3, -infinity, +infinity, color);
    }
    return res, res2, res3;
}


int miniMax(struct piece** board, int depth, float pruninga, float pruningb, int whiteturn){
    if (depth==0){
        return getEval(board, whiteturn);
    }
    struct piece*** listOfBoards = malloc(64*sizeof(struct piece));
    int datalist[300];
    int datalistb[128];
    int cpt=0;
    int destcoord=0;
    int startcoordx=0;
    int startcoordy=0;
    
    if (whiteturn){
        int maxEval=-infinity;
        for (int i=0;i<64;i++){
            if (board[i]->role!=0){
                getMoves(board,board[i]);
                sortMoves(board,board[i]);
                for (struct list* moves = board[i]->possibleMoves;moves!=NULL,moves=moves->next){
                    struct piece** newBoard = malloc(64*sizeof(struct piece));
                    int j = 0;
                    for(struct piece p = board[j], j<64,j++)
                    {
                        newBoard[j] = malloc(sizeof(struct piece));
                        newBoard[j]->role = p->role;
                        newBoard[j]->x = p->x;
                        newBoard[j]->y = p->y;
                        newBoard[j]->color = p->color;
                        newBoard[j]->value = p->value;
                        newBoard[j]->realPlayerColor = p->realPlayerColor;
                        newBoard[j]->hasMoved = p->hasMoved;
                    }
                    int dest_x = moves->data%8;
                    int dest_y = moves->data/8;
                    move(struct piece** newBoard, struct piece* newBoard[i], int dest_x, int dest_y);
                    datalist[cpt]=moves->data;
                    datalistb[2*cpt]=board[i]->x;
                    datalistb[2*cpt+1]=board[i]->y;
                    cpt++;
                    realloc(listOfBoards,cpt*64*sizeof(struct piece));
                }
            }
        }
        for (int k=0;k<cpt;k++){
            position=listOfBoards[k];
            eval, destcoord, startcoordx, startcoordy=minimax(position,depth-1, pruninga, pruningb, 0);
            if (eval>maxEval){
                maxEval=eval;
                destcoord=datalist[k];
                startcoordx=datalistb[k];
                startcoordy=datalistb[k+1];
            }
            maxEval=max(maxEval,eval);
            pruninga=max(pruninga,eval);
            if (pruningb<=pruninga){
                break;
            }
        }
        return maxEval, destcoord, startcoordx, startcoordy;
    }
    else{
        int minEval=+infinity;
        for (int i=0;i<64;i++){
            if (board[i]->role!=0){
                getMoves(board,board[i]);
                sortMoves(board,board[i]);
                for (struct list* moves = board[i]->possibleMoves;moves!=NULL,moves=moves->next){
                    struct piece** newBoard = malloc(64*sizeof(struct piece));
                    int j = 0;
                    for(struct piece p = board[j], j<64,j++)
                    {
                        newBoard[j] = malloc(sizeof(struct piece));
                        newBoard[j]->role = p->role;
                        newBoard[j]->x = p->x;
                        newBoard[j]->y = p->y;
                        newBoard[j]->color = p->color;
                        newBoard[j]->value = p->value;
                        newBoard[j]->realPlayerColor = p->realPlayerColor;
                        newBoard[j]->hasMoved = p->hasMoved;
                    }
                    int dest_x = moves->data%8
                    int dest_y = moves->data/8
                    move(struct piece** newBoard, struct piece* newBoard[i], int dest_x, int dest_y);
                    datalist[cpt]=moves->data;
                    datalistb[2*cpt]=board[i]->x;
                    datalistb[2*cpt+1]=board[i]->y;
                    cpt++;
                    realloc(listOfBoards,cpt*64*sizeof(struct piece));
                }
            }
        }
        for (int k=0;k<cpt;k++){
            position=listOfBoards[k];
            eval, destcoord, startcoordx, startcoordy=minimax(position,depth-1,pruninga, pruningb, 1);
            if (eval<minEval){
                maxEval=eval;
                destcoord=datalist[k];
                startcoordx=datalistb[k];
                startcoordy=datalistb[k+1];
            }
            minEval=min(minEval,eval);
            pruningb=min(pruningb,eval);
            if (pruningb<=pruninga){
                break;
            }
        }
        return minEval, destcoord, startcoordx, startcoordy;
    }
}