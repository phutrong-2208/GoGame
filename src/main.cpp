#include <iostream>
#include <vector>

#include "SFML/Graphics.hpp"
#include "mouseInput.hpp"
#include "Board.hpp"
#include "button.hpp"
#include "renderZone.hpp"
#include "boardOperation.hpp"
#include "UIManager.hpp"
#include "soundEffect.hpp"

SoundEffect sound;
Button setup;
GoBoard goBoard;

std :: vector<Button> button_list[4];   // save board button

int main(){
    sf :: RenderWindow window(sf :: VideoMode({1200, 800}), "GoGame");
    render.initSize(window);
    setup.setupButtonOperation(button_list[0]);
    ui.setupMenuButton(button_list[1]);
    ui.setupModeButton(button_list[2]);
    ui.setupSettingButton(button_list[3]);
    op.history.emplace_back(goBoard);

    sound.Background.setLoop(true);
    sound.Background.play();
    

    while(window.isOpen()){
        sf :: Event event; 
        while(window.pollEvent(event)){  //get the value and pop it from the queue
            if(event.type == sf :: Event :: Closed){
                window.close();
            }
            if(event.type == sf :: Event :: Resized){ // normalize window size
                render.normalizeSize(window);
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
            }
            else if(ui.State == GAME_MENU){
                ui.MenuManager(window, button_list[1], goBoard, event);
                op.reset(); op.history.emplace_back(goBoard);
                if(ui.State != GAME_MENU) break;
            }
            else if(ui.State == SETTING_MENU){
                ui.MenuManager(window, button_list[2], goBoard, event);
                op.reset(); op.history.emplace_back(goBoard);
                if(ui.State != SETTING_MENU) break;
            }
            else if(ui.State == MODE_MENU){
                ui.MenuManager(window, button_list[3], goBoard, event);
                op.reset(); op.history.emplace_back(goBoard);
                if(ui.State != MODE_MENU) break;
            }
        }
        window.clear();
        if(ui.State == BOARD){
            ui.drawBoard(window, goBoard, button_list[0]);
            for (Button &button : button_list[0]) {
                ui.doActionHover(button, window);
            }
        }
        else if(ui.State == GAME_MENU){
            ui.drawMenu(window, button_list[1], "font\\Bungee_Regular.ttf");
            for (Button &button : button_list[1]) {
                ui.doActionHover(button, window);
            }
        }
        else if(ui.State == SETTING_MENU){
            ui.drawMenu(window, button_list[2], "font\\arial.ttf");
            for (Button &button : button_list[2]) {
                ui.doActionHover(button, window);
            }
        }
        else if(ui.State == MODE_MENU){
            ui.drawMenu(window, button_list[3], "font\\arial.ttf");
            for (Button &button : button_list[3]) {
                ui.doActionHover(button, window);
            }
        }
        window.display();
    }
    
}