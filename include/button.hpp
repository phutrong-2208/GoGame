#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>
#include "renderZone.hpp"
#include "mouseInput.hpp"

class Button{
    private:
    public:
        void drawButton(sf :: RenderWindow &window, sf :: Vector2f position, sf :: Vector2f siz, std :: string Text, sf :: Color);
};

#endif BUTTON_HPP