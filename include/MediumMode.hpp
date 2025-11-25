#ifndef MEDIUM_MODE_HPP
#define MEDIUM_MODE_HPP

#include "Board.hpp"
#include "LogBoxManager.hpp"

const int oo = 1e9; // infinity for alpha and beta pruning  

class MediumMode{
    public:
        void Medium_Mode(GoBoard& goBoard);
    private:
        int evaluateScore(GoBoard& currentBoard);
        int scoreGain(GoBoard goBoard, std :: pair<int, int> &move);        
        void optimizeMove(GoBoard& goBoard, std :: vector<std :: pair<int, int>> &move);
        int minimax(GoBoard currentBoard, int treeDepth, int alpha = -oo, int beta = oo, bool maxi = 1);
};

extern MediumMode medium;
#endif