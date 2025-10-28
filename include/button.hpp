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
        int type, cnt = 1;
        std :: vector<std :: string> Text;
        std :: vector<sf :: Color> color;
        std :: vector<int> attr;
        Button(){}
        Button(sf :: Vector2f _position, sf :: Vector2f _siz, int _type, int _cnt, 
            std :: vector<std :: string> _Text, std :: vector<sf :: Color> _color, std :: vector<int> _attr){
            position = _position;
            siz = _siz;
            type = _type;
            cnt = _cnt;
            Text.swap(_Text);
            color.swap(_color);
            attr.swap(_attr);
            assert(Text.size() == cnt);
            assert(color.size() == cnt);
            assert(attr.size() == cnt);
        }
        void drawButton(sf :: RenderWindow &window);
        void setupButtonOperation(RenderZone &render, std :: vector<Button> &button_list);
        void doActionHover(sf :: RenderWindow &window, MouseInput &mouse, RenderZone &render);
        void doActionClick(sf :: RenderWindow &window, MouseInput &mouse, RenderZone &render, GoBoard &goBoard, Operation& op);
};

#endif