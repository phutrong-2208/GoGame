#include "UIManager.hpp"
#include "metaControls.hpp"

void Manager :: doActionHover(Button &button, sf :: RenderWindow &window) {
    auto [mouseX, mouseY] = mouse.getPosition(window);
    float tmpSpace = 1.0f * button.siz.x / button.cnt;
    for (int i = 0; i < button.cnt; ++i) {
        if (!metaControls.playWithBot && (button.type == 12 || button.type == 13)) { // adhoc fix
            button.color[i] = metaControls.Color4 + metaControls.Color4 + sf :: Color(50, 50, 50); continue;
        }
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
        if (!metaControls.playWithBot && (button.type == 12 || button.type == 13)) continue; // adhoc fix
        if (button.position.x + tmpSpace * i >= mouseX) continue;
        if (button.position.x + tmpSpace * (i + 1) <= mouseX) continue;
        if (button.position.y >= mouseY || mouseY >= button.position.y + button.siz.y) continue;
        Audio.click.play();
        
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
            case 7:{
                State = MODE_MENU;
                botMode.inGame = false;
                break;
            }
            case 8:
                State = SETTING_MENU;
                break;
            case 9:
                window.close();
                break;
            case 10: {
                (button.currentSelection += 1) %= button.Text.size();
                goBoard.setSize(button.attr[button.currentSelection]);
                (metaControls.boardType += 1) %= 3;
                katago[metaControls.boardType].sendCommand("boardsize " + std :: to_string(button.attr[button.currentSelection]));
                break;
            }
            case 11:
                (button.currentSelection += 1) %= button.Text.size();
                metaControls.playWithBot = button.attr[button.currentSelection];
                break;
            case 12:
            if (!metaControls.playWithBot) continue;
                (button.currentSelection += 1) %= button.Text.size();
                metaControls.difficulty = button.attr[button.currentSelection];
                if(metaControls.difficulty > 0){
                    std :: string maxTime = (metaControls.difficulty == 1 ? "1" : "3");
                    katago[metaControls.boardType].sendCommand("kata-set-param maxTime " + maxTime);
                    katago[metaControls.boardType].readCommand();
                }
                break;
            case 13: 
                if (!metaControls.playWithBot) continue;
                (button.currentSelection += 1) %= button.Text.size();
                metaControls.goFirst = button.attr[button.currentSelection];
                break;
            case 14:
                (button.currentSelection += 1) %= button.Text.size();
                metaControls.musicActive = button.attr[button.currentSelection];
                Audio.Background.setVolume(metaControls.audioVolume * metaControls.musicActive * 0.5);
                Audio.Background.play();
                break;
            case 15:
                (button.currentSelection += 1) %= button.Text.size();
                metaControls.soundActive = button.attr[button.currentSelection];
                Audio.click.setVolume(metaControls.audioVolume * metaControls.soundActive);
                Audio.piece.setVolume(metaControls.audioVolume * metaControls.soundActive);
                break;
            case 16:
                {
                    int &tVolume = metaControls.audioVolume;
                    tVolume += button.attr[i];
                    if (tVolume > 100) tVolume = 100;
                    if (tVolume < 0) tVolume = 0;
                    Audio.click.setVolume(tVolume * metaControls.soundActive);
                    Audio.piece.setVolume(tVolume * metaControls.soundActive);
                    Audio.Background.setVolume(tVolume * metaControls.musicActive * 0.5);
                }
                button.updateDisplayVolume();
                break;
            case 17:    
                (button.currentSelection += 1) %= button.Text.size();
                {
                    int &i = metaControls.themeChoice;
                    i = button.attr[button.currentSelection];
                    metaControls.Color1 = metaControls.presetColor1[i];
                    metaControls.Color2 = metaControls.presetColor2[i];
                    metaControls.Color3 = metaControls.presetColor3[i];
                    metaControls.Color4 = metaControls.presetColor4[i];
                    Audio.Background.stop();
                    Audio.Background.openFromFile("assets\\background" + std :: to_string(i) + ".wav");
                    Audio.Background.play();
                    render.initColor();
                }
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
    auto [snatchX, snatchY] = mouse.checkBoard(window, goBoard);

    if(metaControls.playWithBot){ 
        Piece botColor = (metaControls.goFirst == 0 ? White : Black);
        if(!botMode.botisThinking and goBoard.turn == botColor){         
            botMode.botMoveAsync(goBoard);
        }
    }
    if(event.type == sf :: Event :: MouseButtonPressed){
        std :: string color = (goBoard.turn == Black ? "black" : "white");

        if(botMode.botMutex.try_lock()){ // check if there's exist a thread is running 
            if(goBoard.playMove(snatchX, snatchY, goBoard.turn, 1)){
                if(metaControls.difficulty > 0){ //update for katago model
                    katago[metaControls.boardType].sendCommand("play " + color + " " + metaControls.encode(snatchX, snatchY));
                    katago[metaControls.boardType].readCommand();
                }
                op.history.emplace_back(goBoard);
                op.snap.clear();
            }
            botMode.botMutex.unlock();
        }
        
        for (Button &button : button_list) {
            if(botMode.botisThinking) continue;
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
    presetBackgrounds.resize(5);
    for (int i = 0; i < 5; i++) {
        auto &bg = presetBackgrounds[i];
        if (!bg.loadFromFile(("assets\\MenuGameBackground" + std :: to_string(i) + ".png"))){
            std :: cerr << "Cannot find MenuGameBackground" << i << ".png!\n";
            return;
        }
        bg.setSmooth(true);
    }
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