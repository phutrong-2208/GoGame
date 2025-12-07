#ifndef MEDIUM_HARD_MODE_HPP
#define MEDIUM_HARD_MODE_HPP

#include "Board.hpp"
#include "metaControls.hpp"
#include "LogBoxManager.hpp"
#include "Medium_HardMode.hpp"
#include "modelEngine.hpp"


class HardMode{
    public: 
        void Move(GoBoard& goBoard); 
};

extern HardMode medium_and_hard;

#endif
