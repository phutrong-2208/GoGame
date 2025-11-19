#ifndef BOT_LOGIC_HPP
#define BOT_LOGIC_HPP

#include <chrono>
#include <random>
#include <cassert>

#include "Board.hpp"
#include "metaControls.hpp"
#include "BotLogic.hpp"

class GoBot{    
    public: 
        Piece botTurn;
        int Difficulty;
        bool botisThinking;

        GoBot(){
            botTurn = (metaControls.goFirst == 1 ? White : Black);
            botisThinking = false;
        }
        void Easy_Mode(GoBoard& goBoard);
        void Medium_Mode(GoBoard& goBoard);
        void Hard_Mode(GoBoard& goBoard);
        void botMove(GoBoard& goBoard);
};

extern GoBot botMode;

#endif 

