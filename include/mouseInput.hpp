#ifndef MOUSE_INPUT_HPP
#define MOUSE_INPUT_HPP
#include "renderZone.hpp"
#include "metaControls.hpp"

class MouseInput{
    private:
    public:
        std :: pair<int, int> checkBoard(sf :: RenderWindow &window, GoBoard &goBoard);  
        sf :: Vector2f getPosition(sf :: RenderWindow &window);
};

extern MouseInput mouse;
#endif