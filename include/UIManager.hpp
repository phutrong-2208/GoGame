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

enum Display {GAME_MENU, BOARD, SETTING_MENU, MODE_MENU};
class Manager{
    public: 
        Display State;
        Manager(){
            State = GAME_MENU;
        }

        void boardManager(Manager& ui, sf :: RenderWindow &window, std :: vector<Button> &button_list, RenderZone&render, MouseInput& mouse, GoBoard& goBoard, Operation& op, sf :: Event event);
        void drawBoard(sf :: RenderWindow&window, GoBoard& goBoard, RenderZone& render, MouseInput& mouse, std :: vector<Button> button_list);
        void drawMenu(sf :: RenderWindow &window, GoBoard& goBoard, RenderZone&render, std :: vector<Button> &button_list, std :: string FontLink);
        void doActionHover(Button &button, sf :: RenderWindow &window, MouseInput& mouse, RenderZone& render);
        void doActionClick(Manager &ui, Button &button, sf :: RenderWindow &window, MouseInput& mouse, RenderZone& render, GoBoard &goBoard, Operation& op); 
        void setupMenuButton(RenderZone &render, std :: vector<Button> &button_list);
        void setupModeButton(RenderZone &render, std :: vector<Button> &button_list);
        void setupSettingButton(RenderZone &render, std :: vector<Button> &button_list);
        void MenuManager(Manager &ui, sf :: RenderWindow &window, std :: vector<Button> button_list, RenderZone&render, MouseInput& mouse, GoBoard& goBoard, Operation& op, sf :: Event event);
}; 


#endif