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

#define BOARD               0
#define GAME_MENU           1
#define SETTING_MENU        2
#define MODE_MENU           3
#define CONF_DIALOG         4
#define SCORE               5

class Manager{
    public: 
        int State;
        Manager(){
            State = GAME_MENU;
        }
        
        void boardManager(sf :: RenderWindow &window, GoBoard& goBoard, std :: vector<Button> &button_list, sf :: Event event);
        void drawBoard(sf :: RenderWindow&window, GoBoard& goBoard, std :: vector<Button> &button_list);
        void drawMenu(sf :: RenderWindow &window, std :: vector<Button> &button_list, std :: string FontLink);
        void doActionHover(Button &button, sf :: RenderWindow &window);
        void doActionClick(GoBoard &goBoard, Button &button, sf :: RenderWindow &window); 
        void MenuManager(sf :: RenderWindow &window, std :: vector<Button> &button_list, GoBoard& goBoard, sf :: Event event);
}; 

extern Manager ui;
#endif