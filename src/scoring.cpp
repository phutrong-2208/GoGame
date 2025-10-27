#include "Scoring.hpp"


Piece Score :: winner(void){
    int whiteTotal = whiteTerr + whiteCaptured;
    int blackTotal = blackTerr + blackCaptured;

    if(whiteTotal == blackTotal) return Empty;
    if(whiteTotal > blackTotal) return White;
    return Black;
}

