#include "button.hpp"

#include <iostream>
#include <cassert>


void Button :: drawButton(sf :: RenderWindow &window){
    //set the position , color and the size of the boxes
    box.setPosition(position);
    box.setSize(siz);
    box.setFillColor(color);
    
    //set the color of outline and the thinkness
    box.setOutlineThickness(2);
    box.setOutlineColor(sf :: Color :: Black);
    box.setOrigin(siz.x / 2, siz.y / 2);
    //set words font of the texts on each button
    sf :: Font font;

    if(!font.loadFromFile("font\\arial.ttf")){
        std :: cout << "The font doesn't exist!";
        assert(false);
    }
    sf :: Text label(Text, font, 36);
    label.setColor(sf :: Color :: Black);

    sf :: FloatRect textBounds = label.getGlobalBounds();
    sf :: FloatRect boxBounds = box.getGlobalBounds();
    //centering the text in the box
    label.setOrigin(textBounds.left + textBounds.width / 2.0, textBounds.top + textBounds.height / 2.0);
    label.setPosition(position.x, position.y);

    float width_ratio = (boxBounds.width * 0.6f) / textBounds.width;
    float height_ratio = (boxBounds.height * 0.2f) / textBounds.height;

    label.setScale(width_ratio, height_ratio); // resize the text bounds for fitting with the box

    window.draw(box);
    window.draw(label);
}

bool Button :: detectHover(sf :: RenderWindow &window, MouseInput& mouse, RenderZone& render) {
    auto [mouseX, mouseY] = mouse.getPosition(window, render);
    if (mouseX < position.x - siz.x * 0.5f) return 0;
    if (mouseX > position.x + siz.x * 0.5f) return 0;
    if (mouseY < position.y - siz.y * 0.5f) return 0;
    if (mouseY > position.y + siz.y * 0.5f) return 0;
    return 1;
}

void Button :: doActionStall(void) {
    // hard coded behaviour
    // 20 = size change speed
    // 100 = target size
    // 21 = 20 + 1
    // siz.x = (siz.x * 20 + 90) / 21.0L;
    // siz.y = (siz.y * 20 + 110) / 21.0L;
    color = sf :: Color(222, 184, 135);
}

void Button :: doActionHover(void) {
    // hard coded behaviour
    // 20 = size change speed
    // 120 = target size
    // 21 = 20 + 1
    // siz.x = (siz.x * 20 + 100) / 21.0L;
    // siz.y = (siz.y * 20 + 120) / 21.0L;
    color = sf :: Color(153, 101, 60);
}

void Button :: doActionClick(void) {
    switch (type){
        case 0: 
            // calls startGame;
            break; 
        case 1:
            // calls endGame;
            break;
        case 2:
            // calls undoMove;
            break;
        case 3:
            // calls redoMove;
            break;
        case 4:
            // calls passMove;
            break;
        case 5: 
            // calls resign;
            break;
    }
}