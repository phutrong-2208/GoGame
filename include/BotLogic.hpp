#ifndef BOT_LOGIC_HPP
#define BOT_LOGIC_HPP

#include <cassert>
#include "thread"
#include "atomic"
#include "mutex"

#include "Board.hpp"
#include "metaControls.hpp"
#include "scoring.hpp"
#include "EasyMode.hpp"
#include "Medium_HardMode.hpp"


class GoBot{    
    public: 
        std :: atomic<bool> botisThinking;
        std :: atomic<bool> inGame;
        std :: mutex botMutex;
        GoBot(){
            botisThinking = false;
            inGame = true;
        };
        void botMove(GoBoard& goBoard);
        void botMoveAsync(GoBoard& goBoard); // preventing UI got freeze when AI is moving
};

extern GoBot botMode;

#endif 

