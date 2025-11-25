#ifndef FILE_OPERATION_HPP
#define FILE_OPERATION_HPP

#include "Board.hpp"
#include <iostream>
#include <fstream>

class FileOperation{
    public:
        void importBoard(GoBoard& goBoard);
        void exportBoard(GoBoard& goBoard);
};

#endif