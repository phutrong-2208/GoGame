#ifndef BUTTON_HPP
#define BUTTON_HPP
#include <SFML/Graphics.hpp>

class Button{
    private:
    public:
        sf :: Vector2f position;
        sf :: Vector2f siz;
        std :: string Text;
        sf :: Color color;
        int type;
        Button(sf :: Vector2f _position, sf :: Vector2f _siz, std :: string _Text, sf :: Color _color, int _type);
        void drawButton(sf :: RenderWindow &window);
        bool detectHover(sf :: RenderWindow &window);
        void doActionStall();
        void doActionHover();
        void doActionClick();
};

#endif BUTTON_HPP
