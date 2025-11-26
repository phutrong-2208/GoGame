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
    const std :: vector<sf :: Color> presetColor1 = {{237, 212, 145}, {236, 203, 126}, {236, 203, 126}, {236, 203, 126}};    // Background colour (very light)
    const std :: vector<sf :: Color> presetColor2 = {{236, 203, 126}, {236, 203, 126}, {236, 203, 126}, {236, 203, 126}};    // Panel colour (light)
    const std :: vector<sf :: Color> presetColor3 = {{219, 168, 78},  {236, 203, 126}, {236, 203, 126}, {236, 203, 126}};    // Object colour (bright)
    const std :: vector<sf :: Color> presetColor4 = {{36, 28, 13},    {236, 203, 126}, {236, 203, 126}, {236, 203, 126}};    // Outline colour (dark)

    // Variables
    bool playWithBot;
    bool musicActive, soundActive;
    int audioVolume;
    int themeChoice;
    int difficulty;
    int goFirst; // 0 if you, 1 if bot
    sf :: Color Color1 = presetColor1[0];
    sf :: Color Color2 = presetColor2[0];
    sf :: Color Color3 = presetColor3[0];
    sf :: Color Color4 = presetColor4[0];

    MetaControls(){
        playWithBot = 0;
        musicActive = 0, soundActive = 0, audioVolume = 100;
        themeChoice = 0;
        difficulty = 0;
        goFirst = 0; // 0 if you, 1 if bot
    }
};

extern MetaControls metaControls;
#endif