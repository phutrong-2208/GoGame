#ifndef OPERATION_HPP
#define OPERATION_HPP

#include <vector>
#include "Board.hpp"
#include "MetaControls.hpp"

class Operation{
    public:
        std :: vector<GoBoard> history;
        std :: vector<GoBoard> snap;

        void Rollback(GoBoard &goBoard, int t);
        void NewGame(GoBoard& goBoard);
        void Resign(GoBoard& goBoard);
        void Pass(GoBoard& goBoard);
        void SetSize(GoBoard& goBoard, int siz);
};


#endif