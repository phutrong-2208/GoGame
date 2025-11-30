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
    const std :: vector<sf :: Color> presetColor1 = {{173, 146, 102}, {82, 138, 160},  {193, 101, 220}, {178, 64, 54},   {106, 151, 63}};     // Background colour (damp)
    const std :: vector<sf :: Color> presetColor2 = {{229, 194, 117}, {152, 203, 246}, {220, 175, 227}, {234, 156, 146}, {183, 216, 160}};    // Panel colour (soft)
    const std :: vector<sf :: Color> presetColor3 = {{240, 213, 144}, {198, 226, 250}, {233, 202, 236}, {241, 188, 181}, {205, 228, 190}};    // Object colour (light)
    const std :: vector<sf :: Color> presetColor4 = {{42, 34, 19},    {22, 40, 61},    {69, 41, 73},    {102, 62, 56},   {38, 57, 26}};       // Outline colour (dark)

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