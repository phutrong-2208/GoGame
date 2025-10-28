#ifndef MOUSE_INPUT_HPP
#define MOUSE_INPUT_HPP
#include "renderZone.hpp"

class MouseInput{
    private:
    public:
        std :: pair<int, int> checkBoard(sf :: RenderWindow &window, RenderZone& render, GoBoard &goBoard);  
        sf :: Vector2f getPosition(sf :: RenderWindow &window, RenderZone &render);
};

#endif