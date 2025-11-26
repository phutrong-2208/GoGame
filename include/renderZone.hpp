#ifndef RENDER_ZONE_HPP
#define RENDER_ZONE_HPP

#include <SFML/Graphics.hpp>
#include <Board.hpp>
#include "metaControls.hpp"
#include "roundedRectangle.hpp"
#include "LogBoxManager.hpp"

class RenderZone{
    private:
    public:
        unsigned int WINDOW_SIZE = sf :: VideoMode :: getDesktopMode().height / 2;
        void drawBoard(sf :: RenderWindow &window, GoBoard &goBoard);
        void drawPiece(sf :: RenderWindow &window, GoBoard &goBoard, int i, int j, int ghost);
        void drawAllPieces(sf :: RenderWindow &window, GoBoard &goBoard);
        void drawMain(sf :: RenderWindow &window, GoBoard &goBoard);
        void initSize(sf :: RenderWindow &window);
        void normalizeSize(sf :: RenderWindow &window);
        void drawControlPanel(sf :: RenderWindow &window);
};

extern RenderZone render;
#endif