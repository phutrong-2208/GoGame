#include <iostream>
#include <assert.h>
#include <cmath>
#include <vector>

#include "SFML/Graphics.hpp"
#include "mathFunctions.hpp"
#include "Board.hpp"
#include "button.hpp"
#include "mouseInput.hpp"
#include "renderZone.hpp"

GoBoard goBoard;
std :: vector<Button> buttons({
    Button(
        {2 * RenderZone :: SHIFT_CONST + RenderZone :: ZONE_SIZE, RenderZone :: SHIFT_CONST}, 
        {100, 100}, "undo", sf :: Color(210, 170, 120), 2
    )
});

int main(){
    sf :: RenderWindow window(sf :: VideoMode({1200, 800}), "GoGame");

    RenderZone :: initSize(window);
    
    goBoard.newGame();
    
    while(window.isOpen()){
        sf :: Event event; 

        while(window.pollEvent(event)){  //get the value and pop it from the queue
            if(event.type == sf :: Event :: Closed){
                window.close();
            }
            if(event.type == sf :: Event :: Resized){ // normalize window size
                RenderZone :: normalizeSize(window);
            }
            if(event.type == sf :: Event :: MouseButtonPressed){
                auto [snatchX, snatchY] = MouseInput :: checkBoard(window);
                if(goBoard.newStep(snatchX, snatchY, goBoard.turn)) continue;
                for (Button &x: buttons) {
                    if (x.detectHover(window)) {
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
        for (Button &x: buttons) {
            if (x.detectHover(window)) {
                x.doActionHover();
            } else {
                x.doActionStall();
            }
        }
        window.clear();
        RenderZone :: drawMain(window, goBoard);
        for (Button &x : buttons) {
            x.drawButton(window);
        }
        window.display();
    }
    
}