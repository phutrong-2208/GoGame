#include "button.hpp"
#include "mouseInput.hpp"
#include <iostream>
#include <cassert>

Button :: Button(sf :: Vector2f _position, sf :: Vector2f _siz, std :: string _Text, sf :: Color _color, int _type){
    position = _position;
    siz = _siz;
    Text = _Text;
    color = _color;
    type = _type;
}

void Button :: drawButton(sf :: RenderWindow &window){
    sf :: RectangleShape box;
    
    //set the position , color and the size of the boxes
    box.setPosition(position);
    box.setSize(siz);
    box.setFillColor(color);
    
    //set the color of outline and the thinkness
    box.setOutlineThickness(2);
    box.setOutlineColor(sf :: Color :: Black);
    
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
    label.setPosition(position.x + box.getSize().x / 2.0, position.y + box.getSize().y / 2.0);

    float width_ratio = (boxBounds.width * 0.6f) / textBounds.width;
    float height_ratio = (boxBounds.height * 0.2f) / textBounds.height;

    label.setScale(width_ratio, height_ratio); // resize the text bounds for fitting with the box

    window.draw(box);
    window.draw(label);
}

bool Button :: detectHover(sf :: RenderWindow &window) {
    auto [mouseX, mouseY] = RenderZone :: getPosition(window);
    if (mouseX < position.x) return 0;
    if (mouseX > position.x + siz.x) return 0;
    if (mouseY < position.y) return 0;
    if (mouseY > position.y + siz.y) return 0;
    return 1;
}

void Button :: doActionStall() {
    // hard coded behaviour
    // 20 = size change speed
    // 100 = target size
    // 21 = 20 + 1
    siz.x = (siz.x * 20 + 100) / 21.0L;
    siz.y = (siz.y * 20 + 100) / 21.0L;
}

void Button :: doActionHover() {
    // hard coded behaviour
    // 20 = size change speed
    // 120 = target size
    // 21 = 20 + 1
    siz.x = (siz.x * 20 + 120) / 21.0L;
    siz.y = (siz.y * 20 + 120) / 21.0L;
}

void Button :: doActionClick() {
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