#include <iostream>
#include <assert.h>
#include <cmath>
#include <vector>

#include "SFML/Graphics.hpp"
#include "mathFunctions.hpp"
#include "mouseInput.hpp"
#include "Board.hpp"
#include "renderZone.hpp"

GoBoard goBoard;

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
                goBoard.newStep(snatchX, snatchY, Piece(goBoard.turn == Black ? Black : White));
                if(goBoard.ended()){
                    goBoard.newGame();
                    break;
                }
            }
        }
        window.clear();
        RenderZone :: drawMain(window, goBoard);
        window.display();
    }
    
}