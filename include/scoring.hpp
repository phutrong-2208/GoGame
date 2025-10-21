
#ifndef SCORING_HPP
#define SCORING_HPP
#include "board.hpp"

#include <tuple>

class Score{
    public:
        int whiteTerr, blackTerr; // saving the player's territory
        int whiteCaptured, blackCaptured; //saving the number stone each player captured
        Score(){
            whiteCaptured = blackCaptured = 0;
            whiteTerr = blackTerr = 0;
        }

        Piece winner(void);
};

#endif SCORING_HPP