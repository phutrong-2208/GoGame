#ifndef OPERATION_HPP
#define OPERATION_HPP
#include <vector>

#include "LogBoxManager.hpp"
#include "Board.hpp"
#include "MetaControls.hpp"

class Operation{
    public:
        std :: vector<GoBoard> history;
        std :: vector<GoBoard> snap;

        void reset(void);
        void Rollback(GoBoard &goBoard, int t);
        void NewGame(GoBoard& goBoard);
        void Resign(GoBoard& goBoard);
        void Pass(GoBoard& goBoard);
        void SetSize(GoBoard& goBoard, int siz);
        void File(GoBoard& goBoard, int attr);

    private:
        void FileImport(GoBoard& goBoard);
        void FileExport(GoBoard& goBoard);
};

extern Operation op;
#endif