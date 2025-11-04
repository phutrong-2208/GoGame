#ifndef UI_MANAGER
#define UI_MANAGER

#include <vector>
#include <iostream>

#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"

#include "button.hpp"
#include "boardOperation.hpp"
#include "Board.hpp"
#include "mouseInput.hpp"
#include "renderZone.hpp"
#include "metaControls.hpp"
#include "soundEffect.hpp"

enum Display {GAME_MENU, BOARD, SETTING_MENU, MODE_MENU, CONF_DIALOG, SCORE};

class Manager{
    public: 
        Display State;
        Manager(){
            State = GAME_MENU;
        }

        void boardManager(sf :: RenderWindow &window, GoBoard& goBoard, std :: vector<Button> &button_list, sf :: Event event);
        void drawBoard(sf :: RenderWindow&window, GoBoard& goBoard, std :: vector<Button> button_list);
        void drawMenu(sf :: RenderWindow &window, std :: vector<Button> &button_list, std :: string FontLink);
        void doActionHover(Button &button, sf :: RenderWindow &window);
        void doActionClick(GoBoard &goBoard, Button &button, sf :: RenderWindow &window); 
        void setupMenuButton(std :: vector<Button> &button_list);
        void setupModeButton(std :: vector<Button> &button_list);
        void setupSettingButton(std :: vector<Button> &button_list);
        void MenuManager(sf :: RenderWindow &window, std :: vector<Button> button_list, GoBoard& goBoard, sf :: Event event);
        void drawConfigDialog(sf :: RenderWindow &window, std :: vector<Button> button_list);
        void drawScoreDisplayed(sf :: RenderWindow& window);
}; 


static Manager ui;
#endif