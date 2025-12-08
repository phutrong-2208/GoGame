#ifndef FILE_OPERATION_HPP
#define FILE_OPERATION_HPP

#include "Board.hpp"
#include <iostream>
#include <fstream>
#include "modelEngine.hpp"

class FileOperation{
    public: 
        int boardType, playWithBot, difficulty;
    public:
        void importBoard(GoBoard& goBoard);
        void exportBoard(GoBoard& goBoard);
};

#endif