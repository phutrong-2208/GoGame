#include "ScoreRevealManager.hpp"

void drawText(sf :: RenderWindow& window, std :: string Font_link, std :: string Text, sf :: Vector2f pos){
    sf :: Font newFont;
    newFont.loadFromFile(Font_link);
    
    sf :: Text label(Text, newFont, 30);
    
    label.setColor(metaControls.Color4);
    sf :: FloatRect textBounds = label.getGlobalBounds();
    // do not use textBounds.height
    float realHeight = (sf :: Text){"o", newFont, 30}.getGlobalBounds().height;
    
    label.setCharacterSize(30);
    //centering the text in the box
    label.setOrigin(textBounds.left + textBounds.width / 2.0, textBounds.top + realHeight / 2.0);
    label.setPosition(pos);
    window.draw(label);
}

void ScoreReveal :: setupScoreButton(std :: vector<Button> &button_list){
    int width = metaControls.ZONE_SIZE * metaControls.ASPECT_RATIO;
    int height = metaControls.ZONE_SIZE;
    button_list.push_back(Button({width / 2.0f - 500 / 2.0f, height / 2.0f + 150}, {500, 50}, 
        19, 2, 
        {"Return Menu", "New Game"}, {sf :: Color(161, 118, 84), sf :: Color(161, 118, 84), sf :: Color(161, 118, 84)}, 
        {1, 2}, ""
    ));
}   

void ScoreReveal :: drawScoreReveal(sf :: RenderWindow &window, GoBoard& goBoard){
    sf :: Texture ScoringBoard;
    if(!ScoringBoard.loadFromFile("assets\\ScoreReveal.png")){
        std :: cerr << "Can't find the Scoring Board image!\n";
        assert(false);
    }
    ScoringBoard.setSmooth(true);
    
    sf :: Sprite board(ScoringBoard);
    board.setOrigin(ScoringBoard.getSize().x / 2.0f, ScoringBoard.getSize().y / 2.0f);
    board.setPosition(metaControls.ZONE_SIZE * metaControls.ASPECT_RATIO / 2.0f, metaControls.ZONE_SIZE / 2.0f - 50);
    
    window.draw(board);
    std :: string winner, reason;
    auto[whiteScore, blackScore] = goBoard.getScore();
    if(goBoard.endGame == 1){
        if(whiteScore > blackScore) {
            winner = "White Won";
        }
        else{
            winner = "Black Won";
        }
        reason = "";
    }
    if(goBoard.endGame == 2){
        winner = goBoard.turn == White ? "Black Won" : "White Won";
        reason = " by Resignation";
    }
    int width = metaControls.ZONE_SIZE * metaControls.ASPECT_RATIO;
    int height = metaControls.ZONE_SIZE;
    std :: string FontLink = "font\\Bungee_Regular.ttf";
    drawText(window, FontLink, "White: " + std :: to_string(whiteScore), {width / 2.0f, height / 2.0f + 50});
    drawText(window, FontLink, "Black: " + std :: to_string(blackScore), {width / 2.0f, height / 2.0f + 100});
    drawText(window, FontLink, winner + reason, {width / 2.0f, height / 2.0f});
}
