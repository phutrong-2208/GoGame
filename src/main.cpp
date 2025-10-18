#include <SFML/Graphics.hpp>
#include <iostream>
#include <Board.h>

int main(){
    sf :: RenderWindow window(sf::VideoMode({800, 600}), "Go Game");
    
    sf :: Texture board;
    
    if(!board.loadFromFile("Texture/9x9_Board.png")){
        return EXIT_FAILURE;
    }   
    sf :: Sprite boardImage(board);

    while(window.isOpen()){
        sf :: Event event; 

        while(window.pollEvent(event)){  //get the value and pop it from the queue
            if(event.type == sf :: Event :: Closed){
                window.close();
            }
        }
        window.clear();
        window.draw(boardImage);
        boardImage.setScale({4, 4});
        boardImage.setPosition({10, 10});
        
        window.display();
    }
}