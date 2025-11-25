#ifndef HARD_MODE_HPP
#define HARD_MODE_HPP

#include "Board.hpp"
#include "metaControls.hpp"
#include "LogBoxManager.hpp"

#include "random"
#include "memory"
#include "chrono"
#include "cassert"

class HardMode{
    public: 
        void Hard_Mode(GoBoard& goBoard);  
};

extern HardMode hard;

#endif
