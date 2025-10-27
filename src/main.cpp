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

std :: vector<Button> button_list;
void setupButtonOpertation(void){
    float height = (render.ZONE_SIZE - 2 * render.SHIFT_CONST - 6 * render.CONTROL_SHIFT) / 5.0f;
    float width = render.ZONE_SIZE * (render.ASPECT_RATIO - 1) - render.SHIFT_CONST - 2 * render.CONTROL_SHIFT; 

    button_list.emplace_back(
        Button({render.ZONE_SIZE + render.CONTROL_SHIFT + width / 2.0f, render.SHIFT_CONST + render.CONTROL_SHIFT + height / 2.0f}, 
        {width, height}, "Clock", sf :: Color(222, 184, 135), 2)
    );
    button_list.emplace_back(
        Button({render.ZONE_SIZE + render.CONTROL_SHIFT + width / 2.0f, render.SHIFT_CONST + 2 * render.CONTROL_SHIFT + height / 2.0f + height}, 
        {width, height}, "Undo/Redo", sf :: Color(222, 184, 135), 2)
    );
    button_list.emplace_back(
        Button({render.ZONE_SIZE + render.CONTROL_SHIFT + width / 2.0f, render.SHIFT_CONST + 3 * render.CONTROL_SHIFT + height / 2.0f + 2 * height}, 
        {width, height}, "Resign", sf :: Color(222, 184, 135), 2)
    );
    button_list.emplace_back(
        Button({render.ZONE_SIZE + render.CONTROL_SHIFT + width / 2.0f, render.SHIFT_CONST + 4 * render.CONTROL_SHIFT + height / 2.0f + 3 * height}, 
        {width, height}, "New Game", sf :: Color(222, 184, 135), 2)
    );
    button_list.emplace_back(
        Button({render.ZONE_SIZE + render.CONTROL_SHIFT + width / 2.0f, render.SHIFT_CONST + 5 * render.CONTROL_SHIFT + height / 2.0f + 4 * height}, 
        {width, height}, "Pass Turn", sf :: Color(222, 184, 135), 2)
    );
}
int main(){
    sf :: RenderWindow window(sf :: VideoMode({1200, 800}), "GoGame");
    render.initSize(window);
    goBoard.newGame();
    
    setupButtonOpertation();
    
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