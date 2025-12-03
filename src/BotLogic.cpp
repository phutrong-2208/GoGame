#include "BotLogic.hpp"


void GoBot :: botMove(GoBoard& goBoard){
    if (metaControls.difficulty == 0) easy.Move(goBoard);
    else medium_and_hard.Move(goBoard);
}
void GoBot :: botMoveAsync(GoBoard& goBoard){
    botisThinking = true;
    inGame = true;  
    std :: thread([this, &goBoard](){
        std :: lock_guard<std :: mutex> lock(botMutex); //lock the board ensure that there's only one thread is processing this board
        //prevent Race Conditions
        while(inGame){
            this -> botMove(goBoard);
            op.history.emplace_back(goBoard);
            op.snap.clear();
            botisThinking = false;
            break;
        }
    }).detach(); // creating a new thread run independent to the main thread
}

