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
    private:
        int index;
        sf :: Font font;
        sf :: Text terminal;
        std :: vector<std :: pair<sf :: Text, sf :: Text>> notification;
        float posX, posY, width, height;
    
    public:
        const int MAX_LINES = 8;
        const double coeff_shift = 10.0f;
        const double fudge = 0.8f;
        const double terminal_size = 40.0f;


    void updatePosition(void){
        posX = metaControls.ZONE_SIZE + metaControls.CONTROL_SHIFT;
        posY = metaControls.SHIFT_CONST + metaControls.CONTROL_SHIFT + 
               6.0f * (metaControls.CONTROL_SHIFT + 
               1.0f * (metaControls.ZONE_SIZE - 2 * metaControls.SHIFT_CONST - 10 * metaControls.CONTROL_SHIFT) / 10);
        width = metaControls.ZONE_SIZE * (metaControls.ASPECT_RATIO - 1) - metaControls.SHIFT_CONST - 2 * metaControls.CONTROL_SHIFT; 
        height = metaControls.ZONE_SIZE - metaControls.CONTROL_SHIFT - metaControls.SHIFT_CONST - posY;
    }

    public: 
        LogBox(){
            index = 0;
            updatePosition();
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