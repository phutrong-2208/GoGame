#include <SFML/Graphics.hpp>
#include <iostream>
#include <Board.h>
#include <assert.h>
#include <cmath>
#include <vector>

const int WINDOW_SIZE = 800;
const int SHIFT_CONST = 50;
unsigned int LENGTH = WINDOW_SIZE + 2 * SHIFT_CONST;
void drawBoard(sf :: RenderWindow &window){
    window.clear(sf :: Color(222, 184, 35));
    sf :: RectangleShape background({LENGTH, LENGTH});
    background.setFillColor(sf :: Color(222, 184, 135));

    window.draw(background);
    sf :: Vertex line[2];
    //it requires two vertexes to draw a line
    line[0].color = sf :: Color :: Black;
    line[1].color = sf :: Color :: Black;

    //Drawing the horizontal line
    for (int i = 0; i < BOARD_SIZE; ++i){
        line[0].position = sf :: Vector2f(SHIFT_CONST, SHIFT_CONST + i * (1.0 * WINDOW_SIZE / (BOARD_SIZE - 1)));
        line[1].position = sf :: Vector2f(WINDOW_SIZE + SHIFT_CONST, SHIFT_CONST + i * (1.0 * WINDOW_SIZE / (BOARD_SIZE - 1)));
        window.draw(line, 2, sf :: Lines);
    }

    //Drawing the vertical line  
    for (int i = 0; i < BOARD_SIZE; ++i){
        line[0].position = sf :: Vector2f(SHIFT_CONST + i * (1.0 * WINDOW_SIZE / (BOARD_SIZE - 1)), SHIFT_CONST);
        line[1].position = sf :: Vector2f(SHIFT_CONST + i * (1.0 * WINDOW_SIZE / (BOARD_SIZE - 1)), WINDOW_SIZE + SHIFT_CONST);
        window.draw(line, 2, sf :: Lines);
    }

    //Drawing hoshi point
    std :: vector<sf :: Vector2f> hoshiPosition;
    
    double CeilSize = (1.0 * WINDOW_SIZE / (BOARD_SIZE - 1));

    if(BOARD_SIZE == 9){
        std :: vector<std :: pair<int, int>> point = {
            {2, 2}, {2, 6}, {6, 2}, {6, 6}, {4, 4}
        };

        for (std :: pair<int, int> x : point){
            hoshiPosition.emplace_back(sf :: Vector2f(CeilSize * x.first, CeilSize * x.second));
        }
    }
    if(BOARD_SIZE == 13){
        std :: vector<std :: pair<int, int>> point = {
            {3, 3}, {3, 9}, {9, 3}, {9, 9}, {6, 6} 
        };
        
        for (std :: pair<int, int> x : point){
            hoshiPosition.emplace_back(sf :: Vector2f(CeilSize * x.first, CeilSize * x.second));
        }
    }
    if(BOARD_SIZE == 19){
        std :: vector<std :: pair<int, int>> point = {
            {3, 3}, {3, 9}, {3, 15}, {9, 3}, {9, 9}, {9, 15}, {15, 3}, {15, 9}, {15, 15}  
        };

        for (std :: pair<int, int> x : point){
            hoshiPosition.emplace_back(sf :: Vector2f(CeilSize * x.first, CeilSize * x.second));
        }
    }


    sf :: CircleShape hoshi(5.0f);
    hoshi.setFillColor(sf :: Color :: Black);
    for (sf :: Vector2f x : hoshiPosition){
        hoshi.setPosition(SHIFT_CONST + x.x - hoshi.getRadius(), SHIFT_CONST + x.y - hoshi.getRadius());
        window.draw(hoshi);
    }
}   
int main(){
    sf :: RenderWindow window(sf::VideoMode({LENGTH, LENGTH}), "GoGame");

    while(window.isOpen()){
        sf :: Event event; 

        while(window.pollEvent(event)){  //get the value and pop it from the queue
            if(event.type == sf :: Event :: Closed){
                window.close();
            }
        }
        drawBoard(window);
        window.display();
    }
}