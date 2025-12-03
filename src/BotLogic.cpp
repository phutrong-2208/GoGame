#include "BotLogic.hpp"

void GoBot :: botMove(GoBoard& goBoard){
    if     (metaControls.difficulty == 0) easy.Move(goBoard);
    else    medium_and_hard.Move(goBoard);
}
