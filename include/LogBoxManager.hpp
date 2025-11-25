#ifndef LOG_BOX_MANAGER
#define LOG_BOX_MANAGER

#include "SFML/Graphics.hpp"
#include "metaControls.hpp"
#include "roundedRectangle.hpp"
#include "button.hpp"

#include "cassert"
#include "iostream"

#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>



class LogBox{
    int index;
    sf :: Font font;
    sf :: Text terminal;
    std :: vector<std :: pair<sf :: Text, sf :: Text>> notification;
    public: 
        LogBox(){
            index = 0;
            notification.clear();
            if(!font.loadFromFile("font\\Play_Regular.ttf")){
                std :: cout << "Can not find the Play Regular font file!\n";
                assert(false);
            }
        }
        void drawLogBox(sf :: RenderWindow& window);
        void insertText(std :: string notif);
        void drawText(sf :: RenderWindow &window);
        void scrollUp(void);
        void scrollDown(void);
        void reset(void);
        bool inBound(int x, int y);
        void drawConfigDialog(sf :: RenderWindow& window);
}; 

extern LogBox logbox;
#endif