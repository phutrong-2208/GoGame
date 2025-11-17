#include <iostream>
#include <vector>


//including header file
#include "SFML/Graphics.hpp"
#include "mouseInput.hpp"
#include "Board.hpp"
#include "button.hpp"
#include "renderZone.hpp"
#include "boardOperation.hpp"
#include "UIManager.hpp"
#include "soundEffect.hpp"
#include "ModeManager.hpp"
#include "SettingManager.hpp"
#include "MenuManager.hpp"


Operation op; 
MetaControls metaControls;
MouseInput mouse;
SoundEffect sound;
Button setup;
GoBoard goBoard;
RenderZone render;


//UIs Manager 
Manager ui;
Mode ModeUI;
Setting SettingUI;
Menu MenuUI;

std :: vector<Button> button_list[4];   // save board button

int main(){
    sf :: RenderWindow window(sf :: VideoMode({1200, 800}), "GoGame");
    render.initSize(window);
    setup.setupButtonOperation(button_list[0]);
    MenuUI.setupMenuButton(button_list[1]);
    SettingUI.setupSettingButton(button_list[2]);
    ModeUI.setupModeButton(button_list[3]);
    op.history.emplace_back(goBoard);

    sound.Background.setLoop(true);
    sound.Background.play();
    
    
    while(window.isOpen()){
        sf :: Event event; 
        while(window.pollEvent(event)){  //get the value and pop it from the queue
            if(event.type == sf :: Event :: Closed){
                window.close();
                continue;
            }
            if(event.type == sf :: Event :: Resized){ // normalize window size
                render.normalizeSize(window);
                continue;
            }
            if(ui.State == BOARD){
                ui.boardManager(window, goBoard, button_list[0], event);
                if(goBoard.ended()){
                    goBoard.newGame();
                    op.history.clear();
                    op.snap.clear();
                    op.history.emplace_back(goBoard);
                    break;
                }
                continue;
            }
            op.reset(); op.history.emplace_back(goBoard);
            goBoard.newGame();
            ui.MenuManager(window, button_list[ui.State], goBoard, event);
        }

        window.clear();
        if(ui.State == 0) ui.drawBoard(window, goBoard, button_list[ui.State]);
        else ui.drawMenu(window, button_list[ui.State], "font\\Bungee_Regular.ttf");

        for (Button &button : button_list[ui.State]) {
            ui.doActionHover(button, window);
        }
        window.display();
    }
    
}