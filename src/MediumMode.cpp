#include "MediumMode.hpp"

//========================================================
//MEDIUM MODE --- MINIMAX, HEURISTIC, ALPHA-BETA PRUNING
//========================================================

int MediumMode :: evaluateScore(GoBoard& currentBoard){
    auto[whiteScore, blackScore] = currentBoard.getScore();
    Piece botColor = (metaControls.goFirst == 0 ? White : Black);
    
    int totalScore = whiteScore - blackScore;
    if(botColor == Black){
        return -totalScore;
    }
    else{
        return totalScore;
    }
}
Piece botColor = (metaControls.goFirst == 0 ? White : Black);
Piece playerColor = (botColor == White ? Black : White);
int MediumMode :: scoreGain(GoBoard goBoard, std :: pair<int, int> &move){
    std :: pair<int, int> nowScore = goBoard.getScore();
    if(move.first == -1 and move.second == -1){ //pass the turn
        return 0;
    }
    int before = (botColor == White ? nowScore.first - nowScore.second : nowScore.second - nowScore.first);
    goBoard.playMove(move.first, move.second, botColor, 0);
    
    nowScore = goBoard.getScore();
    int after = (botColor == White ? nowScore.first - nowScore.second : nowScore.second - nowScore.first);

    return after - before;
}
void MediumMode :: optimizeMove(GoBoard& goBoard, std :: vector<std :: pair<int, int>> &move){
    sort(move.begin(), move.end(), [&](std :: pair<int, int>&a, std :: pair<int, int>& b){
        return scoreGain(goBoard, a) > scoreGain(goBoard, b);
    });
}

int MediumMode :: minimax(GoBoard currentBoard, int treeDepth, int alpha, int beta, bool maxi){
    if(treeDepth == 0 || currentBoard.ended())
        return evaluateScore(currentBoard);

    optimizeMove(currentBoard, currentBoard.validMove);

    if(maxi){
        int best = -oo;
        for (std :: pair<int, int>&move : currentBoard.validMove){
            GoBoard newBoard = currentBoard;
            if(move.first == -1 and move.second == -1){ // AI gonna pass the turn
                newBoard.pass++;
                newBoard.turn = (newBoard.turn == Black ? White : Black);
            }
            else
                newBoard.playMove(move.first, move.second, botColor, 0);
            
            int value = minimax(newBoard, treeDepth - 1, alpha, beta, 0);
            alpha = std :: max(alpha, value);
            best = std :: max(best, value);
            if(beta <= alpha) break;
        }
        return best;
    }
    else{
        int best = oo;
        for (std :: pair<int, int>&move :currentBoard.validMove){
            GoBoard newBoard = currentBoard;
            if(move.first == -1 and move.second == -1){// AI gonna pass the turn
                newBoard.pass++;
                newBoard.turn = (newBoard.turn == Black ? White : Black);
            }
            else    
                newBoard.playMove(move.first, move.second, botColor, 0);

            int value = minimax(newBoard, treeDepth - 1, alpha, beta, 1);
            beta = std :: min(beta, value);
            best = std :: min(best, value);
            if(beta <= alpha) break;
        }
        return best;
    }
    return -oo;
}



void MediumMode :: Medium_Mode(GoBoard& goBoard){
    std :: pair<int, int> bestMove = {-1, -1};
    int bestPoint = -oo;
    std :: vector<std :: pair<int, int>> validMove = goBoard.validMove;

    int treeDepth = (goBoard.boardSize < 13 ? 2 : 1);
    optimizeMove(goBoard, validMove);

    for (std :: pair<int, int> move : validMove){
        GoBoard currentBoard = goBoard;
        currentBoard.playMove(move.first, move.second, botColor, 0);

        int point = minimax(currentBoard, treeDepth - 1, -oo, oo, 0);
        if(point > bestPoint){
            bestPoint = point;
            bestMove = move;
        }
    }
    if(bestMove != std :: make_pair(-1, -1))
        goBoard.playMove(bestMove.first, bestMove.second, botColor, 1);
    else{
        goBoard.pass++;
        goBoard.turn = (goBoard.turn == Black ? White : Black);
    }
}   