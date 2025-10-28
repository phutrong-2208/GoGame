#include <iostream>
#include <vector>

#include "SFML/Graphics.hpp"
#include "mouseInput.hpp"
#include "Board.hpp"
#include "button.hpp"
#include "renderZone.hpp"
#include "boardOperation.hpp"

GoBoard goBoard;
RenderZone render;
MouseInput mouse;
Operation op;
Button setup;

std :: vector<Button> button_list;

int main(){
    sf :: RenderWindow window(sf :: VideoMode({1200, 800}), "GoGame");
    render.initSize(window);
    goBoard.newGame();
    
    setup.setupButtonOperation(render, button_list);

    op.history.emplace_back(goBoard);

    while(window.isOpen()){
        sf :: Event event; 
        auto [snatchX, snatchY] = mouse.checkBoard(window, render, goBoard);
        while(window.pollEvent(event)){  //get the value and pop it from the queue
            if(event.type == sf :: Event :: Closed){
                window.close();
            }
            if(event.type == sf :: Event :: Resized){ // normalize window size
                render.normalizeSize(window);
            }
            if(event.type == sf :: Event :: MouseButtonPressed){
                if(goBoard.newStep(snatchX, snatchY, goBoard.turn)){
                    op.history.emplace_back(goBoard);
                    op.snap.clear();
                    continue;
                }
                for (Button &button : button_list) {
                    button.doActionClick(window, mouse, render, goBoard, op);
                }
                if(goBoard.ended()){
                    goBoard.newGame();
                    break;
                }
            }
        }
        for (Button &button : button_list) {
            button.doActionHover(window, mouse, render);
        }
        window.clear();
        render.drawMain(window, goBoard);
        if (snatchX != 999) render.drawPiece(window, goBoard, snatchX, snatchY, goBoard.turn);
        for (Button &button : button_list) {
            button.drawButton(window);
        }
        window.display();
    }
    
}