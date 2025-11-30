#ifndef HARD_MODE_HPP
#define HARD_MODE_HPP

#include "Board.hpp"
#include "metaControls.hpp"
#include "LogBoxManager.hpp"
#include "HardMode.hpp"
#include "modelEngine.hpp"


class HardMode{
    public: 
        void Hard_Mode(GoBoard& goBoard); 
};

extern HardMode hard;

#endif
