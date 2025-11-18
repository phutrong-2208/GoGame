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
#include "ScoreRevealManager.hpp"

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
ScoreReveal ScoreUI;
std :: vector<Button> button_list[5];   // save board button

int main(){
    sf :: RenderWindow window(sf :: VideoMode({1200, 800}), "GoGame");
    render.initSize(window);
    setup.setupButtonOperation(button_list[0]);
    MenuUI.setupMenuButton(button_list[1]);
    SettingUI.setupSettingButton(button_list[2]);
    ModeUI.setupModeButton(button_list[3]);
    ScoreUI.setupScoreButton(button_list[4]);

    goBoard.newGame(); 
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
                goBoard.ended();
                if(goBoard.endGame){
                    ui.State = SCORE;
                }
                continue;
            }
            ui.MenuManager(window, button_list[ui.State], goBoard, event);
        }

        window.clear();
        if(ui.State == BOARD) ui.drawBoard(window, goBoard, button_list[BOARD]);
        else if(ui.State == SCORE){
            ui.drawBoard(window, goBoard, button_list[BOARD]);
            ScoreUI.drawScoreReveal(window, goBoard);
            ui.drawScore(window, button_list[SCORE], "font\\Bungee_Regular.ttf");
        }
        else ui.drawMenu(window, button_list[ui.State], "font\\Bungee_Regular.ttf");

        for (Button &button : button_list[ui.State]) {
            ui.doActionHover(button, window);
        }
        window.display();
    }
    
}