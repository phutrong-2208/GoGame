#include "ScoreRevealManager.hpp"

std :: string ScoreReveal_Link = "";

void ScoreReveal :: setupScoreButton(std :: vector<Button> button_list){
    
}   
void drawScoreReveal(sf :: RenderWindow &window){
    sf :: Texture endState_background;
    sf :: Sprite bg(endState_background);
    bg.setColor(metaControls.Background_Color);

    
    window.draw(bg);
}