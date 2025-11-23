#include "BotLogic.hpp"


//========================================================
//HARD MODE --- CHATGPT
//========================================================


void GoBot :: botMove(GoBoard& goBoard){
    if     (metaControls.difficulty == 0) easy.Easy_Mode(goBoard);
    else if(metaControls.difficulty == 1) medium.Medium_Mode(goBoard);
    else if(metaControls.difficulty == 2) hard.Hard_Mode(goBoard);
}