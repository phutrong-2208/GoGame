#ifndef RENDER_ZONE_HPP
#define RENDER_ZONE_HPP

#include <SFML/Graphics.hpp>
#include <Board.hpp>


class RenderZone{
    private:
    public:
        unsigned int ZONE_SIZE = 800;
        unsigned int CONTROL_SIZE = 400;
        double ASPECT_RATIO = 1.0L * (ZONE_SIZE + CONTROL_SIZE) / ZONE_SIZE;
        double SHIFT_CONST = 50;
        unsigned CONTROL_SHIFT = 25;
        unsigned int WINDOW_SIZE = sf :: VideoMode :: getDesktopMode().height / 2;
        void drawBoard(sf :: RenderWindow &window);
        void drawPiece(sf :: RenderWindow &window, GoBoard &goBoard, int i, int j);
        void drawAllPieces(sf :: RenderWindow &window, GoBoard &goBoard);
        void drawMain(sf :: RenderWindow &window, GoBoard &goBoard);
        void initSize(sf :: RenderWindow &window);
        void normalizeSize(sf :: RenderWindow &window);
        void drawControlPanel(sf :: RenderWindow &window);
};
#endif