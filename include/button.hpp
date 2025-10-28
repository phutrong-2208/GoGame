#ifndef BUTTON_HPP
#define BUTTON_HPP
#include <SFML/Graphics.hpp>

#include "mouseInput.hpp"
#include "renderZone.hpp"
#include "boardOperation.hpp"

#include <iostream>
#include <cassert>


class Button{
    private:
    public:
        sf :: RectangleShape box;
        sf :: Vector2f position;
        sf :: Vector2f siz;
        std :: string Text;
        sf :: Color color;
        int type;
        Button(){}
        Button(sf :: Vector2f _position, sf :: Vector2f _siz, std :: string _Text, sf :: Color _color, int _type){
            position = _position;
            siz = _siz;
            Text = _Text;
            color = _color;
            type = _type;
        }
        void drawButton(sf :: RenderWindow &window);
        void setupButtonOpertation(RenderZone &render, std::vector<Button> &button_list);
        bool detectHover(sf ::RenderWindow &window, MouseInput &mouse, RenderZone &render);
        void doActionStall(void);
        void doActionHover(void);
        void doActionClick(GoBoard &goBoard, Operation& op);
};

#endif