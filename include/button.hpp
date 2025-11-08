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
        std :: string ImageLink;
        Button(){}
        Button(sf :: Vector2f _position, sf :: Vector2f _siz, int _type, int _cnt, 
            std :: vector<std :: string> _Text, std :: vector<sf :: Color> _color, std :: vector<int> _attr, std :: string _ImageLink = ""){
            position = _position;
            siz = _siz;
            type = _type;
            cnt = _cnt;
            Text.swap(_Text);
            color.swap(_color);
            attr.swap(_attr);
            ImageLink = _ImageLink;
            assert((int)Text.size() == cnt);
            assert((int)color.size() == cnt);
            assert((int)attr.size() == cnt);
        }
        void drawButton(sf :: RenderWindow &window, std :: string FontLink, std :: string ImageLink = "");
        void setupButtonOperation(std :: vector<Button> &button_list);
};

#endif