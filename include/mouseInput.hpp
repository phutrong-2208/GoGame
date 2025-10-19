#include <SFML/Graphics.hpp>
#include <iostream>
#include "mathFunctions.hpp"
#include "renderZone.hpp"
#include <assert.h>
#include <cmath>
#include <vector>

namespace MouseInput{
    std :: pair<int, int> checkBoard(sf :: RenderWindow &window){
        auto [mouseX, mouseY] = sf :: Mouse :: getPosition(window);

        mouseX = mouseX * 800.0L / RenderZone :: WINDOW_SIZE;
        mouseY = mouseY * 800.0L / RenderZone :: WINDOW_SIZE;

        int snatchX = -1, snatchY = -1;
        double snatchD = 99999;
        double spacing = (1.0 * (RenderZone :: ZONE_SIZE - 2 * RenderZone :: SHIFT_CONST) / (BOARD_SIZE - 1));
        for (int i = 0; i < BOARD_SIZE; ++i){
            for (int j = 0; j < BOARD_SIZE; ++j){
                int vertexX = RenderZone :: SHIFT_CONST + i * spacing;
                int vertexY = RenderZone :: SHIFT_CONST + j * spacing;
                if (snatchX == -1 || mathFunctions :: Euclidean(vertexX, vertexY, mouseX, mouseY) < snatchD){
                    snatchD = mathFunctions :: Euclidean(vertexX, vertexY, mouseX, mouseY);
                    snatchX = i; snatchY = j;
                }
            }
        }
        if (snatchD > 30) return std :: pair<int, int>(999, 999); // mouse too far away to place piece
        return std :: pair<int, int>(snatchX, snatchY);
    }
}