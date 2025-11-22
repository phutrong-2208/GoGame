#ifndef BOT_LOGIC_HPP
#define BOT_LOGIC_HPP

#include <cassert>

#include "Board.hpp"
#include "metaControls.hpp"
#include "BotLogic.hpp"
#include "scoring.hpp"

#include "EasyMode.hpp"
#include "MediumMode.hpp"
#include "HardMode.hpp"

class GoBot{    
    public: 
        Piece botTurn;
        bool botisThinking;

        GoBot(){
            botTurn = (metaControls.goFirst == 1 ? White : Black);
            botisThinking = false;
        }
        void botMove(GoBoard& goBoard);
};

extern GoBot botMode;

#endif 

