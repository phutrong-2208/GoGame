#include "EasyMode.hpp"

//========================================================
//EASY MODE --- BRUTE_FORCE, RANDOM
//========================================================
unsigned seed = std :: chrono :: steady_clock :: now().time_since_epoch().count();
std :: mt19937 rngEasy(seed);
int easyRand(int l, int h){
    return std :: uniform_int_distribution<int>(l, h)(rngEasy);
}

void EasyMode :: Easy_Mode(GoBoard& goBoard){
    int numPossible = goBoard.validMove.size();

    std :: pair<int, int> Random_Move = goBoard.validMove[easyRand(0, numPossible - 1)];
    if(Random_Move.first != -1 || Random_Move.second != -1)
        goBoard.playMove(Random_Move.first, Random_Move.second, goBoard.turn, 1);
    else
        goBoard.pass++;
}