#ifndef SCORING_HPP
#define SCORING_HPP
#include "Board.hpp"

#include <tuple>

class Score{
    public:
        int whiteTerr, blackTerr; // saving the player's territory
        int aliveWhiteStones, aliveBlackStones; //saving the number stone each player captured
        Score(){
            aliveWhiteStones = aliveBlackStones = 0;
            whiteTerr = blackTerr = 0;
        }
};

extern Score score;

#endif