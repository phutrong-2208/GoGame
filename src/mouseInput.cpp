#include <mouseInput.hpp>
#include <cmath>

double Euclidean(double x1, double y1, double x2, double y2){ //Euclidean distance between two points
    x1 -= x2; y1 -= y2;
    return sqrtl(x1 * x1 + y1 * y1);
}
sf :: Vector2f MouseInput :: getPosition(sf :: RenderWindow &window, RenderZone &render) {
    auto [mouseX, mouseY] = sf :: Mouse :: getPosition(window);

    mouseX = mouseX * 800.0L / render.WINDOW_SIZE;
    mouseY = mouseY * 800.0L / render.WINDOW_SIZE;

    return sf :: Vector2f(mouseX, mouseY);
}
std :: pair<int, int> MouseInput ::  checkBoard(sf :: RenderWindow &window, RenderZone &render, GoBoard &goBoard){
    auto [mouseX, mouseY] = sf :: Mouse :: getPosition(window);

    mouseX = mouseX * 800.0L / render.WINDOW_SIZE;
    mouseY = mouseY * 800.0L / render.WINDOW_SIZE;

    int snatchX = -1, snatchY = -1;
    double snatchD = 99999;
    double spacing = (1.0 * (render.ZONE_SIZE - 2 * render.SHIFT_CONST) / (goBoard.siz - 1));
    for (int i = 0; i < goBoard.siz; ++i){
        for (int j = 0; j < goBoard.siz; ++j){
            int vertexX = render.SHIFT_CONST + i * spacing;
            int vertexY = render.SHIFT_CONST + j * spacing;
            if (snatchX == -1 || Euclidean(vertexX, vertexY, mouseX, mouseY) < snatchD){
                snatchD = Euclidean(vertexX, vertexY, mouseX, mouseY);
                snatchX = i; snatchY = j;
            }
        }
    }
    if (snatchD > 30) return std :: pair<int, int>(999, 999); // mouse too far away to place piece
    return std :: pair<int, int>(snatchX, snatchY);
}