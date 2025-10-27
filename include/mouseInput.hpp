#ifndef MOUSE_INPUT_HPP
#define MOUSE_INPUT_HPP
#include "renderZone.hpp"

class MouseInput{
    private:
    public:
        std :: pair<int, int> checkBoard(sf :: RenderWindow &window, RenderZone& render);  
        sf :: Vector2f getPosition(sf :: RenderWindow &window, RenderZone &render);
};

#endif MOUSE_INPUT_HPP