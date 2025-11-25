#ifndef META_CONTROLS_HPP
#define META_CONTROLS_HPP

#include <vector>
#include "SFML/Graphics.hpp"

class MetaControls{ // contains anything related to the game but not part of the game
    private:
    public:
    // Constants
    const unsigned int ZONE_SIZE = 800;
    const unsigned int CONTROL_SIZE = 400;
    const double ASPECT_RATIO = 1.0L * (ZONE_SIZE + CONTROL_SIZE) / ZONE_SIZE;
    const double SHIFT_CONST = 50;
    const unsigned CONTROL_SHIFT = 15;

    // Variables
    bool playWithBot;
    bool musicActive, soundActive, audioVolume;
    int themeChoice;
    int difficulty;
    int goFirst; // 0 if you, 1 if bot
    
    MetaControls(){
        playWithBot = 0;
        musicActive = 0, soundActive = 0, audioVolume = 0;
        themeChoice = 0;
        difficulty = 0;
        goFirst = 0; // 0 if you, 1 if bot
    }
    sf :: Color Background_Color = sf :: Color(236, 203, 126);
    sf :: Color Button_Color = sf :: Color(184, 159, 98);
    sf :: Color logboxColor = sf :: Color(210, 170, 90);
};

extern MetaControls metaControls;
#endif