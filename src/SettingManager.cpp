#include "SettingManager.hpp"

std :: string SettingImage = "assets\\Button.png";
void Setting :: setupSettingButton(std :: vector<Button> &button_list){
    int distance_between_button = 25;
    float height = (2.0f * metaControls.ZONE_SIZE / 3.0f) / 5.0f - distance_between_button;
    float width = metaControls.ZONE_SIZE * metaControls.ASPECT_RATIO / 3.0f;
    
    float tmp_posX = width, tmp_posY = 1.0f * metaControls.ZONE_SIZE / 3.0f;
    button_list.emplace_back(Button(
        {tmp_posX, tmp_posY}, {width, height}, 
        14, 1, 
        {"Music: On", "Music: Off"}, {sf :: Color(222, 184, 135), sf :: Color(222, 184, 135)}, {1, 0}, SettingImage)
    );
    tmp_posY += distance_between_button + height;
    button_list.emplace_back(Button(
        {tmp_posX, tmp_posY}, {width, height}, 
        15, 1, 
        {"Sounds: On", "Sounds: Off"}, {sf :: Color(222, 184, 135), sf :: Color(222, 184, 135)}, {1, 0}, SettingImage)
    );

    tmp_posY += distance_between_button + height;
    button_list.emplace_back(Button(
        {tmp_posX, tmp_posY}, {width, height}, 
        16, 1, 
        {"Volume down", "placeholder", "Volume up"}, {sf :: Color(222, 184, 135), sf :: Color(222, 184, 135), sf :: Color(222, 184, 135)}, {-5, 0, 5}
    , SettingImage)
    );

    tmp_posY += distance_between_button + height;
    button_list.emplace_back(Button(
        {tmp_posX, tmp_posY}, {width, height}, 
        17, 1, 
        {"Classic", "Futuristic", "Magical"}, {sf :: Color(222, 184, 135), sf :: Color(222, 184, 135), sf :: Color(222, 184, 135)}, {0, 1, 2}
    , SettingImage)
    );

    tmp_posY += distance_between_button + height;
    button_list.emplace_back(Button(
        {tmp_posX, tmp_posY}, {width, height}, 
        5, 1, 
        {"Save and return"}, {sf :: Color(222, 184, 135)}, {0}
    , SettingImage)
    );
}