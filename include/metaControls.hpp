#ifndef META_CONTROLS_HPP
#define META_CONTROLS_HPP

#include <vector>

class MetaControls{ // contains anything related to the game but not part of the game
    private:
    public:
        bool playWithBot = 0, startAsWhite = 0;
        bool musicActive = 0, soundActive = 0;
        int audioVolume = 0, audioChoice = 0;
        int boardChoice = 0;
        int stoneChoice = 0;
        int difficulty = 0;
};

#endif