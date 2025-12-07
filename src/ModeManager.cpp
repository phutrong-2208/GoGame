#include "ModeManager.hpp"


std :: string ModeImage = "assets\\Button.png";
void Mode :: setupModeButton(std :: vector<Button> &button_list){
    int distance_between_button = 25;
    float width = metaControls.ZONE_SIZE * metaControls.ASPECT_RATIO / 3.0f;
    float height = (2.0f * metaControls.ZONE_SIZE / 3.0f - 2.0f * metaControls.CONTROL_SHIFT) / 5.0f - distance_between_button;

    float tmp_posX = width, tmp_posY = 1.0f * metaControls.ZONE_SIZE / 3.0f;
    //draw the middle button
    button_list.emplace_back(Button(
        {tmp_posX, tmp_posY}, {width, height}, 
        10, 1, 
        {"9x9", "13x13", "19x19"}, {sf :: Color(222, 184, 135), sf :: Color(222, 184, 135), sf :: Color(222, 184, 135)}, {9, 13, 19}
        , ModeImage)
    );
    tmp_posY += distance_between_button + height;
    button_list.emplace_back(Button(
        {tmp_posX, tmp_posY}, {width, height}, 
        11, 1, 
        {"Play Human", "Play Bot"}, {sf :: Color(222, 184, 135), sf :: Color(222, 184, 135)}, {0, 1}, ModeImage)
    );

    tmp_posY += distance_between_button + height;
    button_list.emplace_back(Button(
        {tmp_posX, tmp_posY}, {width, height}, 
        12, 1, 
        {"Easy", "Medium", "Hard"}, {sf :: Color(222, 184, 135), sf :: Color(222, 184, 135), sf :: Color(222, 184, 135)}, {0, 1, 2}, ModeImage)
    );

    tmp_posY += distance_between_button + height;
    button_list.emplace_back(Button(
        {tmp_posX, tmp_posY}, {width, height}, 
        13, 1, 
        {"Player First", "Bot First"}, {sf :: Color(222, 184, 135), sf :: Color(222, 184, 135)}, {0, 1}, ModeImage)
    );

    tmp_posY += distance_between_button + height;
    button_list.emplace_back(Button(
        {tmp_posX, tmp_posY}, {width, height}, 
        5, 1, 
        {"Save & Quit"}, {sf :: Color(222, 184, 135)}, {0}, ModeImage)
    );
}