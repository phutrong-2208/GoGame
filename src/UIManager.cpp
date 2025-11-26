#include "UIManager.hpp"
#include "metaControls.hpp"


SoundEffect soundButton;
void Manager :: doActionHover(Button &button, sf :: RenderWindow &window) {
    auto [mouseX, mouseY] = mouse.getPosition(window);
    float tmpSpace = 1.0f * button.siz.x / button.cnt;
    for (int i = 0; i < button.cnt; ++i) {
        button.color[i] = metaControls.Color3;
        button.hover[i] = 0;
        if (button.position.x + tmpSpace * i >= mouseX) continue;
        if (button.position.x + tmpSpace * (i + 1) <= mouseX) continue;
        if (button.position.y >= mouseY || mouseY >= button.position.y + button.siz.y) continue;
        button.color[i] *= sf :: Color(200, 200, 200);
        button.hover[i] = 1;
    }
}

void Manager :: doActionClick(GoBoard &goBoard, Button &button, sf :: RenderWindow &window) {
    auto [mouseX, mouseY] = mouse.getPosition(window);
    float tmpSpace = 1.0f * button.siz.x / button.cnt;
    for (int i = 0; i < button.cnt; ++i) {
        if (button.position.x + tmpSpace * i >= mouseX) continue;
        if (button.position.x + tmpSpace * (i + 1) <= mouseX) continue;
        if (button.position.y >= mouseY || mouseY >= button.position.y + button.siz.y) continue;
        soundButton.click.play();
        
        switch (button.type){
            case 1: // Undo / Redo
                op.Rollback(goBoard, button.attr[i]);
                break;
            case 2:
                op.Resign(goBoard);
                break;
            case 3:
                op.Pass(goBoard);
                break;
            case 4:
                op.NewGame(goBoard);
                break;
            case 5:
                State = GAME_MENU;
                break;
            case 6:
                State = BOARD;
                break;
            case 7: 
                State = MODE_MENU;
                break;
            case 8:
                State = SETTING_MENU;
                break;
            case 9:
                window.close();
                break;
            case 10:
                (button.currentSelection += 1) %= button.Text.size();
                goBoard.setSize(button.attr[button.currentSelection]);
                break;
            case 11:
                (button.currentSelection += 1) %= button.Text.size();
                metaControls.playWithBot = button.attr[button.currentSelection];
                break;
            case 12:
                (button.currentSelection += 1) %= button.Text.size();
                metaControls.difficulty = button.attr[button.currentSelection];
                break;
            case 13:
                (button.currentSelection += 1) %= button.Text.size();
                metaControls.goFirst = button.attr[button.currentSelection];
                break;
            case 14:
                (button.currentSelection += 1) %= button.Text.size();
                metaControls.musicActive = button.attr[button.currentSelection];
                break;
            case 15:
                (button.currentSelection += 1) %= button.Text.size();
                metaControls.soundActive = button.attr[button.currentSelection];
                break;
            case 16:
                {
                    int &tVolume = metaControls.audioVolume;
                    tVolume += button.attr[i];
                    if (tVolume > 100) tVolume = 100;
                    if (tVolume < 0) tVolume = 0;
                }
                button.updateDisplayVolume();
                break;
            case 17:    
                (button.currentSelection += 1) %= button.Text.size();
                metaControls.themeChoice = button.attr[button.currentSelection];
                break;
            case 18:
                op.File(goBoard, button.attr[i]);
                break;
            case 19: 
                if(button.attr[i] == 1) State = GAME_MENU;
                else State = BOARD;
                goBoard.newGame();
                break;
            case 20:
                break;
        }
    }
}
std :: string ImageLink = "assets\\Button.png";
//================================================================================================================================
//For board 
void Manager :: drawBoard(sf :: RenderWindow&window, GoBoard& goBoard, std :: vector<Button> &button_list){
    auto [snatchX, snatchY] = mouse.checkBoard(window, goBoard);
    render.drawMain(window, goBoard);
    logbox.drawLogBox(window);
    logbox.drawText(window);
    if (snatchX != 999) render.drawPiece(window, goBoard, snatchX, snatchY, goBoard.turn);
    std :: string font = "font\\Bungee_Regular.ttf";
    std :: string ImageLink =  "";
    for (Button &button : button_list) {
        button.drawButton(window, font, ImageLink);
    }
}
void Manager :: boardManager(sf :: RenderWindow &window, GoBoard& goBoard, std :: vector<Button> &button_list, sf :: Event event){
    if(botMode.botisThinking) return; // to prevent pre-moving
    auto [snatchX, snatchY] = mouse.checkBoard(window, goBoard);
    if(metaControls.playWithBot){
        Piece botColor = (metaControls.goFirst == 0 ? White : Black);
        if(goBoard.turn == botColor){
            botMode.botisThinking = true;            
            botMode.botMove(goBoard);
            op.history.emplace_back(goBoard);
            op.snap.clear();
            botMode.botisThinking = false;
            return; 
        }
    }
    if(event.type == sf :: Event :: MouseButtonPressed){
        if(goBoard.playMove(snatchX, snatchY, goBoard.turn, 1)){
            op.history.emplace_back(goBoard);
            op.snap.clear();
            return;
        }
        
        for (Button &button : button_list) {
            doActionClick(goBoard, button, window);
        }
    }
    if(event.type == sf :: Event :: MouseWheelScrolled){
        auto [snatchX, snatchY] = mouse.getPosition(window);
        if(logbox.inBound(snatchX, snatchY)){
            int delta = event.mouseWheelScroll.delta;
            if(delta > 0){
                logbox.scrollUp();
            }
            else{
                logbox.scrollDown();
            }
        }
    }
}

//================================================================================================================================

void Manager :: initBackgrounds(){
    presetBackgrounds.resize(4);
    for (int i = 0; i < 4; i++) {
        auto &bg = presetBackgrounds[i];
        if (!bg.loadFromFile(("assets\\MenuGameBackground" + std :: to_string(i) + ".png").c_str())){
            std :: cerr << "Cannot find MenuGameBackground" << i << ".png!\n";
            return;
        }
        bg.setSmooth(true);
    }

    // MenuGameBackground0.png: 
    // https://www.flickr.com/photos/vintage_illustration/51916036912
    // https://commons.wikimedia.org/wiki/File:%E6%98%8E-%E6%96%87%E5%BE%B5%E6%98%8E_%E6%8B%99%E6%94%BF%E5%9C%92%E5%9C%96%E8%A9%A9_%E5%86%8A-Garden_of_the_Inept_Administrator_MET_DP235625.jpg

    // MenuGameBackground1.png:
    // https://pxhere.com/en/photo/912000
    // https://commons.wikimedia.org/wiki/File:Artist%27s_impression_of_Saturn%27s_rings.jpg

    // MenuGameBackground2.png:
    // https://www.goodfon.com/fantasy/wallpaper-castle-towers-snow-river-boats-trees-winter-lanterns-sky-clo.html

    // MenuGameBackground3.png:
    // https://www.goodfon.com/painting/wallpaper-the-three-wishes-dominik-mayer-by-dominik-mayer-30-min-speed.html
}

void Manager :: drawMenu(sf :: RenderWindow &window, std :: vector<Button> &button_list, std :: string FontLink){
    sf :: Texture &background = presetBackgrounds[metaControls.themeChoice];
    sf :: Sprite bg(background);
    float render_height = metaControls.ZONE_SIZE;
    float render_width = metaControls.ZONE_SIZE * metaControls.ASPECT_RATIO; 
    bg.setScale(render_width / background.getSize().x, render_height / background.getSize().y);
    window.draw(bg);

    for (Button& button : button_list){
        button.drawButton(window, FontLink, button.ImageLink);
    }    
}

void Manager :: MenuManager(sf :: RenderWindow &window, std :: vector<Button> &button_list, GoBoard& goBoard, sf :: Event event){
    if(event.type == sf :: Event :: MouseButtonPressed){
        for (Button &button : button_list) {
            doActionClick(goBoard, button, window);
        }
    }
}
//================================================================================================================================
void Manager :: drawScore(sf :: RenderWindow &window, std :: vector<Button> &button_list, std :: string FontLink){
    for (Button& button : button_list){
        button.drawButton(window, FontLink, button.ImageLink);
    } 
}