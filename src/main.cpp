#include <iostream>
#include <vector>

#include "SFML/Graphics.hpp"
#include "mouseInput.hpp"
#include "Board.hpp"
#include "button.hpp"
#include "renderZone.hpp"
#include "boardOperation.hpp"
#include "UIManager.hpp"

GoBoard goBoard;
RenderZone render;
MouseInput mouse;
Operation op;
Button setup;

Manager ui;
std :: vector<Button> board_button_list; // save board button
std :: vector<Button> menu_button_list; // save menu button

int main(){
    sf :: RenderWindow window(sf :: VideoMode({1200, 800}), "GoGame");
    render.initSize(window);
    setup.setupButtonOperation(render, board_button_list);
    ui.setupMenuButton(render, menu_button_list);
    op.history.emplace_back(goBoard);

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
                ui.boardManager(ui, window, board_button_list, render, mouse, goBoard, op, event);
                if(goBoard.ended()){
                    goBoard.newGame();
                    op.history.clear();
                    op.snap.clear();
                    op.history.emplace_back(goBoard);
                    break;
                }
            }
            else if(ui.State == GAME_MENU){
                ui.MenuManager(ui, window, menu_button_list, render, mouse, goBoard, op, event);
                if(ui.State != GAME_MENU) break;
            }
        }
        window.clear();
        if(ui.State == BOARD){
            ui.drawBoard(window, goBoard, render, mouse, board_button_list);
            for (Button &button : board_button_list) {
                ui.doActionHover(button, window, mouse, render);
            }
        }
        else if(ui.State == GAME_MENU){
            ui.drawMenu(window, goBoard, render, menu_button_list);
            for (Button &button : menu_button_list) {
                ui.doActionHover(button, window, mouse, render);
            }
        }
        else if(ui.State == SETTING_MENU){

        }
        else if(ui.State == MODE_MENU){

        }
        window.display();
    }
    
}