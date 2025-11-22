#include "EasyMode.hpp"

unsigned seed = std :: chrono :: steady_clock :: now().time_since_epoch().count();

std :: mt19937_64 rng(seed);

int Rand(int l, int h){
    assert(l <= h);
    return std :: uniform_int_distribution<int>(l, h)(rng);
}

//========================================================
//EASY MODE --- BRUTE_FORCE, RANDOM
//========================================================
void EasyMode :: Easy_Mode(GoBoard& goBoard){
    int numPossible = goBoard.validMove.size();

    std :: pair<int, int> Random_Move = goBoard.validMove[Rand(0, numPossible - 1)];
    goBoard.playMove(Random_Move.first, Random_Move.second, goBoard.turn, 1);
}