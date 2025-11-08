#ifndef META_CONTROLS_HPP
#define META_CONTROLS_HPP

#include <vector>

class MetaControls{ // contains anything related to the game but not part of the game
    private:
    public:
        bool playWithBot = 0, startAsWhite = 0;
        bool musicActive = 0, soundActive = 0, audioVolume = 0;
        int themeChoice = 0;
        int difficulty = 0;
};

extern MetaControls metaControls;
#endif