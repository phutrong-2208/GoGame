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

enum state {BOARD, GAME_MENU, SETTING_MENU, MODE_MENU, SCORE, CONF_DIALOG};

/*
    This UI manager will manage 6 different cpp file for:
    Board UI
    Game option UI
    Setting menu UI
    Mode menu UI
    Config dialog 
    Score Reveal UI 
*/

class Manager{
    public: 
        state State;
        Manager(){
            State = GAME_MENU;
        }
        
        void boardManager(sf :: RenderWindow &window, GoBoard& goBoard, std :: vector<Button> &button_list, sf :: Event event);
        void drawBoard(sf :: RenderWindow&window, GoBoard& goBoard, std :: vector<Button> &button_list);
        void drawMenu(sf :: RenderWindow &window, std :: vector<Button> &button_list, std :: string FontLink);
        void doActionHover(Button &button, sf :: RenderWindow &window);
        void doActionClick(GoBoard &goBoard, Button &button, sf :: RenderWindow &window); 
        void MenuManager(sf :: RenderWindow &window, std :: vector<Button> &button_list, GoBoard& goBoard, sf :: Event event);
        void drawScore(sf :: RenderWindow &window, std :: vector<Button>&button_list, std :: string FontLink);
}; 

extern Manager ui;
#endif