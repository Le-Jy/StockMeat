#include "fen.h"

char getFEN(struct piece** board, enum ColorPlayer){
    char FEN="";
    int blank=0;
    int pieceHere=0;
    int castleRes1;
    int castleRes2;
    int castleRes3;
    int castleRes4;
    for (size_t i=0;i<8;i++){
        if (i>0){
            strcat(FEN,'/');
        }
        for (size_t j=0;j<8;j++){
            piecehere=0;
            for elm in piece{
                if (elm->x==i && elm->y==j){
                    piecehere=1;
                    if (blank>0){
                        strcat(FEN,blank);
                        blank=0;
                    }
                    if (elm->role==PAWN){
                        if (elm->color==BLACK){
                            strcat(FEN,'p');
                        }
                        else{
                            strcat(FEN,'P');
                        }
                    }
                    if (elm->role==KNIGHT){
                        if (elm->color==BLACK){
                            strcat(FEN,'n');
                        }
                        else{
                            strcat(FEN,'N');
                        }
                    }
                    if (elm->role==BISHOP){
                        if (elm->color==BLACK){
                            strcat(FEN,'b');
                        }
                        else{
                            strcat(FEN,'B');
                        }
                    }
                    if (elm->role==ROOK){
                        if (elm->color==BLACK){
                            strcat(FEN,'r');
                        }
                        else{
                            strcat(FEN,'R');
                        }
                    }
                    if (elm->role==QUEEN){
                        if (elm->color==BLACK){
                            strcat(FEN,'q');
                        }
                        else{
                            strcat(FEN,'Q');
                        }
                    }
                    if (elm->role==KING){
                        if (elm->color==BLACK){
                            strcat(FEN,'k');
                            castleRes3=canShortCastle((struct piece** board,struct piece* elm));
                            castleRes4=canLongCastle((struct piece** board,struct piece* elm));
                        }
                        else{
                            strcat(FEN,'K');
                            castleRes1=canShortCastle((struct piece** board,struct piece* elm));
                            castleRes2=canLongCastle((struct piece** board,struct piece* elm));
                        }
                    }
                }
            }
            if (piecehere==0){
                blank++;
            }
        }
    }
    FEN.append(' ');
    if (ColorPlayer==WHITE){
        strcat(FEN,'w');
    }
    else{
        strcat(FEN,'b');
    }
    strcat(FEN,' ');
    check=1;
    if (castleRes1==1){
        strcat(FEN,'K');
        check=0;
    }
    if (castleRes2==1){
        strcat(FEN,'Q');
        check=0;
    }
    if (castleRes3==1){
        strcat(FEN,'k');
        check=0;
    }
    if (castleRes4==1){
        strcat(FEN,'q');
        check=0;
    }
    if (check==1){
        strcat(FEN,'-');
    }
    strcat(FEN,' ');
    strcat(FEN,'-');
    strcat(FEN,' ');
    strcat(FEN,'0');
    strcat(FEN,' ');
    strcat(FEN,'1');
    return FEN;
}

int database(char FEN){
    int randnum=0;
    if (FEN="rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"){
        srand(time(NULL));
        randnum = rand() % 2 + 1;
        if (randum==1){
            return 36, 4, 6;
        }
        else{
            return 35, 3, 6;
        }
    }

    if (FEN="rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq - 0 1"){
        srand(time(NULL));
        randnum = rand() % 2 + 1;
        if (randum==1){
            return 28, 4, 1;
        }
        else{
            return 26, 2, 1;
        }
    }

    if (FEN="rnbqkbnr/pppp1ppp/8/4p3/4P3/8/PPPP1PPP/RNBQKBNR w KQkq - 0 1"){
        srand(time(NULL));
        randnum = rand() % 2 + 1;
        if (randum==1){
            return 45, 6, 7;
        }
        else{
            return 42, 1, 7;
        }
    }

    if (FEN="rnbqkbnr/pppp1ppp/8/4p3/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq - 0 1"){
        srand(time(NULL));
        randnum = rand() % 2 + 1;
        if (randum==1){
            return 18, 1, 0;
        }
        else{
            return 19, 3, 1;
        }
    }

    if (FEN="r1bqkbnr/pppp1ppp/2n5/4p3/4P3/5N2/PPPP1PPP/RNBQKB1R w KQkq - 0 1"){
        return 34, 5, 7;
    }

    if (FEN="r1bqkbnr/pppp1ppp/2n5/4p3/2B1P3/5N2/PPPP1PPP/RNBQK2R b KQkq - 0 1"){
        srand(time(NULL));
        randnum = rand() % 2 + 1;
        if (randum==1){
            return 21, 6, 0;
        }
        else{
            return 19, 3, 1;
        }
    }

    if (FEN="r1bqkb1r/pppp1ppp/2n2n2/4p3/2B1P3/5N2/PPPP1PPP/RNBQK2R w KQkq - 0 1"){
        srand(time(NULL));
        randnum = rand() % 2 + 1;
        if (randum==1){
            return 42, 1, 7;
        }
        else{
            return 43, 3, 6;
        }
    }

    if (FEN="r1bqkb1r/pppp1ppp/2n2n2/4p3/2B1P3/2N2N2/PPPP1PPP/R1BQK2R b KQkq - 0 1"){
        srand(time(NULL));
        randnum = rand() % 2 + 1;
        if (randum==1){
            return 26, 5, 0;
        }
        else{
            return 36, 5, 2;
        }
    }

    if (FEN="r1bqkb1r/pppp1ppp/2n5/4p3/2B1n3/2N2N2/PPPP1PPP/R1BQK2R w KQkq - 0 1"){
        return 36, 2, 5;
    }

    if (FEN="r1bqkb1r/pppp1ppp/2n5/4p3/2B1N3/5N2/PPPP1PPP/R1BQK2R b KQkq - 0 1"){
        return 27, 3, 1;
    }

    if (FEN="r1bqk2r/pppp1ppp/2n2n2/2b1p3/2B1P3/2N2N2/PPPP1PPP/R1BQK2R w KQkq - 0 1"){
        srand(time(NULL));
        randnum = rand() % 2 + 1;
        if (randum==1){
            return 43, 3, 6;
        }
        else{
            return 63, 4, 7;
        }
    }

    if (FEN="r1bqkb1r/pppp1ppp/2n2n2/4p3/2B1P3/3P1N2/PPP2PPP/RNBQK2R b KQkq - 0 1"){
        srand(time(NULL));
        randnum = rand() % 2 + 1;
        if (randum==1){
            return 26, 5, 0;
        }
        else{
            return 23, 7, 1;
        }
    }

    if (FEN="r1bqk2r/pppp1ppp/2n2n2/2b1p3/2B1P3/3P1N2/PPP2PPP/RNBQK2R w KQkq - 0 1"){
        srand(time(NULL));
        randnum = rand() % 2 + 1;
        if (randum==1){
            return 42, 2, 6;
        }
        else{
            return 23, 7, 1;
        }
    }

    if (FEN="r1bqkb1r/pppp1pp1/2n2n1p/4p3/2B1P3/3P1N2/PPP2PPP/RNBQK2R w KQkq - 0 1"){
        srand(time(NULL));
        randnum = rand() % 2 + 1;
        if (randum==1){
            return 42, 2, 6;
        }
        else{
            return 51, 1, 7;
        }
    }

    if (FEN="r1bqkbnr/ppp2ppp/2np4/4p3/2B1P3/5N2/PPPP1PPP/RNBQK2R w KQkq - 0 1"){
        srand(time(NULL));
        randnum = rand() % 2 + 1;
        if (randum==1){
            return 42, 2, 6;
        }
        else{
            return 35, 3, 6;
        }
    }

    if (FEN="r1bqkbnr/ppp2ppp/2np4/4p3/2B1P3/2P2N2/PP1P1PPP/RNBQK2R b KQkq - 0 1"){
        srand(time(NULL));
        randnum = rand() % 2 + 1;
        if (randum==1){
            return 12, 5, 0;
        }
        else{
            return 23, 7, 1;
        }
    }

    if (FEN="r1bqkbnr/ppp2pp1/2np3p/4p3/2B1P3/2P2N2/PP1P1PPP/RNBQK2R w KQkq - 0 1"){
        srand(time(NULL));
        randnum = rand() % 2 + 1;
        if (randum==1){
            return 35, 3, 6;
        }
        else{
            return 23, 7, 1;
        }
    }

    if (FEN="r1bqk1nr/ppp1bppp/2np4/4p3/2B1P3/2P2N2/PP1P1PPP/RNBQK2R w KQkq - 0 1"){
        srand(time(NULL));
        randnum = rand() % 2 + 1;
        if (randum==1){
            return 41, 3, 7;
        }
        else{
            return 23, 7, 1;
        }
    }

    if (FEN="r1bqkbnr/ppp2ppp/2np4/4p3/2BPP3/5N2/PPP2PPP/RNBQK2R b KQkq - 0 1"){
        srand(time(NULL));
        randnum = rand() % 2 + 1;
        if (randum==1){
            return 35, 4, 3;
        }
        else{
            return 21, 6, 0;
        }
    }

    if (FEN="r1bqkb1r/ppp2ppp/2np1n2/4p3/2BPP3/5N2/PPP2PPP/RNBQK2R w KQkq - 0 1"){
        return 27, 4, 3;
    }

    if (FEN="r1bqkbnr/ppp2ppp/2np4/8/2BpP3/5N2/PPP2PPP/RNBQK2R w KQkq - 0 1"){
        return 35, 5, 5;
    }

    if (FEN="r1bqkbnr/pppp1ppp/2n5/4p3/4P3/2N2N2/PPPP1PPP/R1BQKB1R b KQkq - 0 1"){
        return 21, 6, 0;
    }

    if (FEN="r1bqkb1r/pppp1ppp/2n2n2/4p3/4P3/2N2N2/PPPP1PPP/R1BQKB1R w KQkq - 0 1"){
        return 34, 5, 7;
    }

    if (FEN="rnbqkbnr/ppp2ppp/3p4/4p3/4P3/5N2/PPPP1PPP/RNBQKB1R w KQkq - 0 1"){
        srand(time(NULL));
        randnum = rand() % 2 + 1;
        if (randum==1){
            return 42, 1, 7;
        }
        else{
            return 47, 7, 6;
        }
    }

    if (FEN="rnbqkbnr/ppp2ppp/3p4/4p3/4P3/5N1P/PPPP1PP1/RNBQKB1R b KQkq - 0 1"){
        srand(time(NULL));
        randnum = rand() % 2 + 1;
        if (randum==1){
            return 21, 6, 0;
        }
        else{
            return 26, 2, 1;
        }
    }

    if (FEN="rnbqkbnr/pp3ppp/3p4/2p1p3/4P3/5N1P/PPPP1PP1/RNBQKB1R w KQkq - 0 1"){
        return 34, 5, 7;
    }

    if (FEN="rnbqkbnr/pp3ppp/3p4/2p1p3/2B1P3/5N1P/PPPP1PP1/RNBQK2R b KQkq - 0 1"){
        return 21, 6, 0;
    }

    if (FEN="rnbqkb1r/pp3ppp/3p1n2/2p1p3/2B1P3/5N1P/PPPP1PP1/RNBQK2R w KQkq - 0 1"){
        srand(time(NULL));
        randnum = rand() % 2 + 1;
        if (randum==1){
            return 42, 1, 7;
        }
        else{
            return 30, 5, 5;
        }
    }

    if (FEN="rnbqkb1r/ppp2ppp/3p1n2/4p3/4P3/5N1P/PPPP1PP1/RNBQKB1R w KQkq - 0 1"){
        return 35, 3, 6;
    }

    if (FEN="rnbqkb1r/ppp2ppp/3p1n2/4p3/3PP3/5N1P/PPP2PP1/RNBQKB1R b KQkq - 0 1"){
        srand(time(NULL));
        randnum = rand() % 2 + 1;
        if (randum==1){
            return 35, 4, 3;
        }
        else{
            return 12, 5, 0; 
        }
    }

    if (FEN="rnbqkb1r/ppp2ppp/3p1n2/8/3pP3/5N1P/PPP2PP1/RNBQKB1R w KQkq - 0 1"){
        return 35, 3, 7;
    }

    if (FEN="rnbqk2r/ppp1bppp/3p1n2/4p3/3PP3/5N1P/PPP2PP1/RNBQKB1R w KQkq - 0 1"){
        srand(time(NULL));
        randnum = rand() % 2 + 1;
        if (randum==1){
            return 42, 1, 7;
        }
        else{
            return 44, 2, 7;
        }
    }

    if (FEN="rnbqkbnr/ppp2ppp/3p4/4p3/4P3/2N2N2/PPPP1PPP/R1BQKB1R b KQkq - 0 1"){
        return 21, 6, 0;
    }

    if (FEN="rnbqkb1r/ppp2ppp/3p1n2/4p3/4P3/2N2N2/PPPP1PPP/R1BQKB1R w KQkq - 0 1"){ 
        return 32, 0, 6;
    }

    if (FEN="rnbqkb1r/ppp2ppp/3p1n2/4p3/P3P3/2N2N2/1PPP1PPP/R1BQKB1R b KQkq - 0 1"){
        srand(time(NULL));
        randnum = rand() % 2 + 1;
        if (randum==1){
            return 23, 7, 1;
        }
        else{
            return 26, 2, 1;
        }
    }

    if (FEN="rnbqkb1r/ppp2pp1/3p1n1p/4p3/P3P3/2N2N2/1PPP1PPP/R1BQKB1R w KQkq - 0 1"){
        srand(time(NULL));
        randnum = rand() % 2 + 1;
        if (randum==1){
            return 47, 7, 6;
        }
        else{
            return 34, 5, 7;
        }
    }

    if (FEN="rnbqkb1r/pp3ppp/3p1n2/2p1p3/P3P3/2N2N2/1PPP1PPP/R1BQKB1R w KQkq - 0 1"){
        return 34, 5, 7;
    }

    if (FEN="rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR w KQkq - 0 1"){
        return 45, 6, 7;
    }

    if (FEN="rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq - 0 1"){
        srand(time(NULL));
        randnum = rand() % 2 + 1;
        if (randum==1){
            return 20, 4, 1;
        }
        else{
            return 18, 1, 0;
        }
    }

    if (FEN="rnbqkbnr/pp1p1ppp/4p3/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R w KQkq - 0 1"){
        return 35, 3, 6;
    }

    if (FEN="rnbqkbnr/pp1p1ppp/4p3/2p5/3PP3/5N2/PPP2PPP/RNBQKB1R b KQkq - 0 1"){
        return 35, 2, 3;
    }

    if (FEN="rnbqkbnr/pp1p1ppp/4p3/8/3pP3/5N2/PPP2PPP/RNBQKB1R w KQkq - 0 1"){
        return 35, 3, 7;
    }

    if (FEN="rnbqkbnr/pp1p1ppp/4p3/8/3QP3/5N2/PPP2PPP/RNB1KB1R b KQkq - 0 1"){
        srand(time(NULL));
        randnum = rand() % 2 + 1;
        if (randum==1){
            return 21, 6, 0;
        }
        else{
            return 18, 1, 0;
        }
    }

    if (FEN="rnbqkb1r/pp1p1ppp/4pn2/8/3QP3/5N2/PPP2PPP/RNB1KB1R w KQkq - 0 1"){
        srand(time(NULL));
        randnum = rand() % 2 + 1;
        if (randum==1){
            return 42, 1, 7;
        }
        else{
            return 43, 3, 4;
        }
    }

    if (FEN="r1bqkbnr/pp1p1ppp/2n1p3/8/3QP3/5N2/PPP2PPP/RNB1KB1R w KQkq - 0 1"){
        srand(time(NULL));
        randnum = rand() % 2 + 1;
        if (randum==1){
            return 44, 3, 4;
        }
        else{
            return 43, 3, 4;
        }
    }

    if (FEN="r1bqkbnr/pp1ppppp/2n5/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R w KQkq - 0 1"){
        srand(time(NULL));
        randnum = rand() % 2 + 1;
        if (randum==1){
            return 25, 5, 7;
        }
        else{
            return 42, 1, 7;
        }
    }

    if (FEN="r1bqkbnr/pp1ppppp/2n5/1Bp5/4P3/5N2/PPPP1PPP/RNBQK2R b KQkq - 0 1"){
        srand(time(NULL));
        randnum = rand() % 2 + 1;
        if (randum==1){
            return 19, 3, 1;
        }
        else{
            return 20, 4, 1;
        }
    }

    if (FEN="r1bqkbnr/pp2pppp/2np4/1Bp5/4P3/5N2/PPPP1PPP/RNBQK2R w KQkq - 0 1"){
        srand(time(NULL));
        randnum = rand() % 2 + 1;
        if (randum==1){
            return 42, 1, 7;
        }
        else{
            return 23, 7, 1;
        }
    }

    if (FEN="r1bqkbnr/pp1p1ppp/2n1p3/1Bp5/4P3/5N2/PPPP1PPP/RNBQK2R w KQkq - 0 1"){
        srand(time(NULL));
        randnum = rand() % 2 + 1;
        if (randum==1){
            return 42, 1, 7;
        }
        else{
            return 23, 7, 1;
        }
    }

    if (FEN="r1bqkbnr/pp2pppp/2np4/1Bp5/4P3/2N2N2/PPPP1PPP/R1BQK2R b KQkq - 0 1"){
        return 20, 4, 1;
    }

    if (FEN="r1bqkbnr/pp2pppp/2np4/1Bp5/4P3/5N2/PPPP1PPP/RNBQ1RK1 b kq - 0 1"){
        return 20, 4, 1;
    }

    if (FEN="r1bqkbnr/pp3ppp/2npp3/1Bp5/4P3/5N2/PPPP1PPP/RNBQ1RK1 w kq - 0 1"){
        return 42, 1, 7;
    }

    if (FEN="r1bqkbnr/pp3ppp/2npp3/1Bp5/4P3/2N2N2/PPPP1PPP/R1BQK2R w kq - 0 1"){
        return 23, 7, 1;
    }

    if (FEN="r1bqkbnr/pp1p1ppp/2n1p3/1Bp5/4P3/5N2/PPPP1PPP/RNBQK2R w kq - 0 1"){
        srand(time(NULL));
        randnum = rand() % 2 + 1;
        if (randum==1){
            return 42, 1, 7;
        }
        else{
            return 23, 7, 1;
        }
    }

    if (FEN="r1bqkbnr/pp1p1ppp/2n1p3/1Bp5/4P3/5N2/PPPP1PPP/RNBQ1RK1 b kq - 0 1"){
        return 19, 3, 1;
    }

    if (FEN="r1bqkbnr/pp1p1ppp/2n1p3/1Bp5/4P3/2N2N2/PPPP1PPP/R1BQK2R b kq - 0 1"){
        return 19, 3, 1;
    }

    if (FEN="r1bqkbnr/pp1ppppp/2n5/2p5/4P3/2N2N2/PPPP1PPP/R1BQKB1R b kq - 0 1"){
        srand(time(NULL));
        randnum = rand() % 2 + 1;
        if (randum==1){
            return 19, 3, 1;
        }
        else{
            return 20, 4, 1;
        }
    }

    if (FEN="r1bqkbnr/pp2pppp/2np4/2p5/4P3/2N2N2/PPPP1PPP/R1BQKB1R w kq - 0 1"){
        return 25, 5, 7;
    }

    if (FEN="r1bqkbnr/pp1p1ppp/2n1p3/2p5/4P3/2N2N2/PPPP1PPP/R1BQKB1R w kq - 0 1"){
        srand(time(NULL));
        randnum = rand() % 2 + 1;
        if (randum==1){
            return 25, 5, 7;
        }
        else{
            return 35, 3, 6;
        }
    }

    if (FEN="r1bqkbnr/pp1p1ppp/2n1p3/2p5/3PP3/2N2N2/PPP2PPP/R1BQKB1R b kq - 0 1"){
        return 35, 2, 3;
    }

    if (FEN="r1bqkbnr/pp1p1ppp/2n1p3/8/3pP3/2N2N2/PPP2PPP/R1BQKB1R w kq - 0 1"){
        return 35, 5, 5;
    }

    if (FEN="rnbqkbnr/pppppppp/8/8/3P4/8/PPP1PPPP/RNBQKBNR b KQkq - 0 1"){
        srand(time(NULL));
        randnum = rand() % 2 + 1;
        if (randum==1){
            return 27, 3, 1;
        }
        else{
            return 21, 6, 0;
        }
    }

    if (FEN="rnbqkbnr/ppp1pppp/8/3p4/3P4/8/PPP1PPPP/RNBQKBNR w KQkq - 0 1"){
        return 34, 2, 6;
    }

    if (FEN="rnbqkb1r/pppppppp/5n2/8/3P4/8/PPP1PPPP/RNBQKBNR w KQkq - 0 1"){
        return 34, 2, 6;
    }

    if (FEN="rnbqkb1r/pppppppp/5n2/8/2PP4/8/PP2PPPP/RNBQKBNR b KQkq - 0 1"){
        return 27, 3, 1;
    }

    if (FEN="rnbqkbnr/ppp1pppp/8/3p4/2PP4/8/PP2PPPP/RNBQKBNR b KQkq - 0 1"){
        return 21, 6, 0;
    }

    if (FEN="rnbqkb1r/ppp1pppp/5n2/3p4/2PP4/8/PP2PPPP/RNBQKBNR w KQkq - 0 1"){
        srand(time(NULL));
        randnum = rand() % 2 + 1;
        if (randum==1){
            return 45, 6, 7;
        }
        else{
            return 27, 2, 4;
        }
    }

    if (FEN="rnbqkb1r/ppp1pppp/5n2/3P4/3P4/8/PP2PPPP/RNBQKBNR b KQkq - 0 1"){
        return 27, 3, 0;
    }

    if (FEN="rnb1kb1r/ppp1pppp/5n2/3q4/3P4/8/PP2PPPP/RNBQKBNR w KQkq - 0 1"){
        srand(time(NULL));
        randnum = rand() % 2 + 1;
        if (randum==1){
            return 42, 1, 7;
        }
        else{
            return 45, 6, 7;
        }
    }

    if (FEN="rnb1kb1r/ppp1pppp/5n2/3q4/3P4/2N5/PP2PPPP/R1BQKBNR b KQkq - 0 1"){
        return 24, 3, 3;
    }

    if (FEN="rnb1kb1r/ppp1pppp/5n2/3q4/3P4/5N2/PP2PPPP/RNBQKB1R b KQkq - 0 1"){
        srand(time(NULL));
        randnum = rand() % 2 + 1;
        if (randum==1){
            return 20, 4, 1;
        }
        else{
            return 18, 1, 0;
        }
    }

    if (FEN="r1b1kb1r/ppp1pppp/2n2n2/3q4/3P4/5N2/PP2PPPP/RNBQKB1R w KQkq - 0 1"){
        return 42, 1, 7;
    }

    if (FEN="rnb1kb1r/ppp2ppp/4pn2/3q4/3P4/5N2/PP2PPPP/RNBQKB1R w KQkq - 0 1"){
        return 42, 1, 7;
    }

    if (FEN="rnbqkb1r/ppp1pppp/5n2/3p4/2PP4/5N2/PP2PPPP/RNBQKB1R b KQkq - 0 1"){
        srand(time(NULL));
        randnum = rand() % 2 + 1;
        if (randum==1){
            return 34, 3, 3;
        }
        else{
            return 18, 2, 1;
        }
    }

    if (FEN="rnbqkb1r/ppp1pppp/5n2/8/2pP4/5N2/PP2PPPP/RNBQKB1R w KQkq - 0 1"){
        return 44, 4, 6;
    }

    if (FEN="rnbqkb1r/ppp1pppp/5n2/8/2pP4/4PN2/PP3PPP/RNBQKB1R b KQkq - 0 1"){    
        srand(time(NULL));
        randnum = rand() % 2 + 1;
        if (randum==1){
            return 20, 4, 1;
        }
        else{
            return 16, 0, 1;
        }
    }

    if (FEN="rnbqkb1r/ppp2ppp/4pn2/8/2pP4/4PN2/PP3PPP/RNBQKB1R w KQkq - 0 1"){
        return 34, 5, 7;
    }

    if (FEN="rnbqkb1r/1pp1pppp/p4n2/8/2pP4/4PN2/PP3PPP/RNBQKB1R w KQkq - 0 1"){
        return 34, 5, 7;
    }

    if (FEN="rnbqkb1r/pp2pppp/2p2n2/3p4/2PP4/5N2/PP2PPPP/RNBQKB1R w KQkq - 0 1"){
        srand(time(NULL));
        randnum = rand() % 2 + 1;
        if (randum==1){
            return 27, 2, 4;
        }
        else{
            return 42, 1, 7;
        }
    }

    if (FEN="rnbqkb1r/pp2pppp/2p2n2/3p4/2PP4/2N2N2/PP2PPPP/R1BQKB1R b KQkq - 0 1"){
        srand(time(NULL));
        randnum = rand() % 2 + 1;
        if (randum==1){
            return 34, 3, 3;
        }
        else{
            return 20, 4, 2;
        }
    }

    if (FEN="rnbqkb1r/pp2pppp/2p2n2/8/2pP4/2N2N2/PP2PPPP/R1BQKB1R w KQkq - 0 1"){
        return 36, 4, 6;
    }

    if (FEN="rnbqkb1r/pp3ppp/2p1pn2/3p4/2PP4/2N2N2/PP2PPPP/R1BQKB1R w KQkq - 0 1"){
        srand(time(NULL));
        randnum = rand() % 2 + 1;
        if (randum==1){
            return 44, 4, 6;
        }
        else{
            return 27, 2, 4;
        }
    }

    if (FEN="rnbqkb1r/pp2pppp/2p2n2/3P4/3P4/5N2/PP2PPPP/RNBQKB1R b KQkq - 0 1"){
        return 27, 2, 2;
    }

    if (FEN="rnbqkb1r/pp3ppp/2p1pn2/3p4/2PP4/2N2N2/PP2PPPP/R1BQKB1R w KQkq - 0 1"){
        srand(time(NULL));
        randnum = rand() % 2 + 1;
        if (randum==1){
            return 42, 1, 7;
        }
        else{
            return 37, 2, 7;
        }
    }

    else{
        return NULL, NULL, NULL;
    }
}