#include "button.hpp"
#include <iostream>
#include <cassert>

void Button :: drawButton(sf :: RenderWindow &window, sf :: Vector2f position, sf :: Vector2f siz, std :: string Text, sf :: Color color){
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
        std :: cout << "The font doesn't exits!";
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