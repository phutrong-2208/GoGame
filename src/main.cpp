#include <SFML/Graphics.hpp>
#include <iostream>
#include <Board.h>

int main(){
    sf :: RenderWindow window(sf::VideoMode({800, 600}), "Go Game");
    
    sf :: Texture texture;
    
    if(!texture.loadFromFile("Texture/9x9_Board.png")){
        return EXIT_FAILURE;
    }   
    sf :: Sprite sprite(texture);

    while(window.isOpen()){
        sf :: Event event; 

        while(window.pollEvent(event)){  //get the value and pop it from the queue
            if(event.type == sf :: Event :: Closed){
                window.close();
            }
        }
        window.clear();
        window.draw(sprite);
        // window.draw(sprite);
        sprite.setScale({2, 2});
        sprite.setPosition({10, 10});
        window.display();
    }
}