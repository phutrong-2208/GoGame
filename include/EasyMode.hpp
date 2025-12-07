#ifndef EASY_MODE_HPP
#define EASY_MODE_HPP

#include <chrono>
#include <cassert>
#include <random>

#include "LogBoxManager.hpp"
#include "Board.hpp"

class EasyMode{
    public:
        void Move(GoBoard& goBoard);
};

extern EasyMode easy;
#endif