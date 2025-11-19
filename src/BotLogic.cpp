#include "BotLogic.hpp"

unsigned seed = std :: chrono :: steady_clock :: now().time_since_epoch().count();

std :: mt19937_64 rng(seed);

int Rand(int l, int h){
    assert(l <= h);
    return std :: uniform_int_distribution<int>(l, h)(rng);
}


void GoBot :: Easy_Mode(GoBoard& goBoard){
    int numPossible = goBoard.validMove.size();

    std :: pair<int, int> Random_Move = goBoard.validMove[Rand(0, numPossible - 1)];
    goBoard.playMove(Random_Move.first, Random_Move.second, goBoard.turn);
}

void GoBot :: Medium_Mode(GoBoard& goBoard){

}

void GoBot :: Hard_Mode(GoBoard& goBoard){

}

void GoBot :: botMove(GoBoard& goBoard){
    if     (Difficulty == 0) Easy_Mode(goBoard);
    else if(Difficulty == 1) Medium_Mode(goBoard);
    else if(Difficulty == 2) Hard_Mode(goBoard);
}