#include "roundedRectangle.hpp"

void roundedRectangle(sf :: RenderWindow &window, sf :: Vector2<double> A, sf :: Vector2<double> B, sf :: Color col, double radius) {
    sf :: ConvexShape shape(20);
    assert(A.x <= B.x);
    assert(A.y <= B.y);
    radius = std :: min(radius, std :: min(B.x - A.x, B.y - A.y) * 0.5);
    for (int i = 0; i <= 3; i++) {
        sf :: Vector2<double> CPoint((i <= 1? A.x + radius: B.x - radius), (i == 0 || i == 3? A.y + radius: B.y - radius));
        double CAngle = pi * -0.5L - i * pi * 0.5L;
        for (int j = 0; j <= 4; ++j) {
            shape.setPoint(i * 5 + j, {CPoint.x + radius * std :: cos(CAngle), CPoint.y + radius * std :: sin(CAngle)});
            CAngle -= pi * 0.125L;
        }
    }
    shape.setFillColor(col);
    window.draw(shape);
}

void customPanelRender(sf :: RenderWindow &window, sf :: Vector2<double> A, sf :: Vector2<double> B, sf :: Color col){
    roundedRectangle(window, A + sf :: Vector2<double>{5, 5}, B + sf :: Vector2<double>{5, 5}, {0, 0, 0, 20});
    roundedRectangle(window, A, B, col);
}

void customPanelRender(sf :: RenderWindow &window, sf :: RectangleShape shape){
    customPanelRender(window, sf :: Vector2<double>(shape.getPosition()), sf :: Vector2<double>(shape.getPosition() + shape.getSize()), shape.getFillColor());
}