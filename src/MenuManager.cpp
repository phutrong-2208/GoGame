#include "MenuManager.hpp"

void Menu :: setupMenuButton(std :: vector<Button> &button_list){
    int distance_between_button = 25;
    float width = metaControls.ZONE_SIZE * metaControls.ASPECT_RATIO / 3.0f;
    float height = (2.0f * metaControls.ZONE_SIZE / 3.0f - 2.0f * metaControls.CONTROL_SHIFT) / 4.0f - distance_between_button;

    float tmp_posX = width, tmp_posY = 1.0f * metaControls.ZONE_SIZE / 3.0f;
    button_list.emplace_back(Button(
        {tmp_posX, tmp_posY}, {width, height}, 
        6, 1, 
        {"Play"}, {sf :: Color(222, 184, 135)}, {0}, "assets\\Button.png")
    );
    tmp_posY += distance_between_button + height;
    button_list.emplace_back(Button(
        {tmp_posX, tmp_posY}, {width, height},  
        7, 1, 
        {"Modes"}, {sf :: Color(222, 184, 135)}, {0}, "assets\\Button.png")
    );

    tmp_posY += distance_between_button + height;
    button_list.emplace_back(Button(
        {tmp_posX, tmp_posY}, {width, height}, 
        8, 1, 
        {"Settings"}, {sf :: Color(222, 184, 135)}, {0}, "assets\\Button.png")
    );

    tmp_posY += distance_between_button + height;
    button_list.emplace_back(Button(
        {tmp_posX, tmp_posY}, {width, height}, 
        9, 1, 
        {"Exit"}, {sf :: Color(222, 184, 135)}, {0}, "assets\\Button.png")
    );
}