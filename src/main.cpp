#include <iostream>
#include <vector>

#include "SFML/Graphics.hpp"
#include "mouseInput.hpp"
#include "Board.hpp"
#include "button.hpp"
#include "renderZone.hpp"

GoBoard goBoard;
RenderZone render;
MouseInput mouse;

int main(){
    sf :: RenderWindow window(sf :: VideoMode({1200, 800}), "GoGame");

    render.initSize(window);
    
    goBoard.newGame();
    
    std :: vector<Button> button_list;

    while(window.isOpen()){
        sf :: Event event; 
        while(window.pollEvent(event)){  //get the value and pop it from the queue
            if(event.type == sf :: Event :: Closed){
                window.close();
            }
            if(event.type == sf :: Event :: Resized){ // normalize window size
                render.normalizeSize(window);
            }
            if(event.type == sf :: Event :: MouseButtonPressed){
                auto [snatchX, snatchY] = mouse.checkBoard(window, render);
                if(goBoard.newStep(snatchX, snatchY, goBoard.turn)) continue;
                for (Button &x: button_list) {
                    if (x.detectHover(window, mouse, render)) {
                        x.doActionClick();
                        break;
                    }
                }
                if(goBoard.ended()){
                    goBoard.newGame();
                    break;
                }
            }
        }
        for (Button &x: button_list) {
            if (x.detectHover(window, mouse, render)) {
                x.doActionHover();
            } else {
                x.doActionStall();
            }
        }
        window.clear();
        render.drawMain(window, goBoard);
        for (Button &x : button_list) {
            x.drawButton(window);
        }
        window.display();
    }
    
}