#include "UIManager.hpp"
#include "metaControls.hpp"
SoundEffect sounds;
void Manager :: doActionHover(Button &button, sf :: RenderWindow &window) {
    auto [mouseX, mouseY] = mouse.getPosition(window);
    float tmpSpace = 1.0f * button.siz.x / button.cnt;
    for (int i = 0; i < button.cnt; ++i) {
        button.color[i] = metaControls.Button_Color;
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
        sounds.click.play();
        
        switch (button.type){
            case 1: // Undo / Redo
                op.Rollback(goBoard, button.attr[i]);
                break;
            case 2:
                op.Resign(goBoard);
                std :: cout << goBoard.endGame << '\n';
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
                metaControls.startAsWhite = button.attr[button.currentSelection];
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
                (button.currentSelection += 1) %= button.Text.size();
                metaControls.audioVolume += button.attr[button.currentSelection];
                break;
            case 17:    
                (button.currentSelection += 1) %= button.Text.size();
                metaControls.themeChoice = button.attr[button.currentSelection];
            case 18:
                op.File(goBoard, button.attr[i]);
                break;
            case 19: 
                if(button.attr[i] == 1) State = GAME_MENU;
                else State = BOARD;
                goBoard.newGame();
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
    if (snatchX != 999) render.drawPiece(window, goBoard, snatchX, snatchY, goBoard.turn);
    std :: string font = "font\\Bungee_Regular.ttf";
    std :: string ImageLink =  "";
    for (Button &button : button_list) {
        button.drawButton(window, font, ImageLink);
    }
}
void Manager :: boardManager(sf :: RenderWindow &window, GoBoard& goBoard, std :: vector<Button> &button_list, sf :: Event event){
    auto [snatchX, snatchY] = mouse.checkBoard(window, goBoard);
    if(event.type == sf :: Event :: MouseButtonPressed){
        if(goBoard.newStep(snatchX, snatchY, goBoard.turn)){
            sounds.piece.play();
            op.history.emplace_back(goBoard);
            op.snap.clear();
            return;
        }
        for (Button &button : button_list) {
            doActionClick(goBoard, button, window);
        }
    }
}

//================================================================================================================================
void Manager :: drawMenu(sf :: RenderWindow &window, std :: vector<Button> &button_list, std :: string FontLink){
    sf :: Texture background;
    if(!background.loadFromFile("assets\\MenuGameBackground.png")){
        std :: cout << "Cannot file Menu_background image!\n";
        return;
    }
    background.setSmooth(true);

    sf :: Sprite bg(background);
    
    float render_height = render.ZONE_SIZE;
    float render_width = render.ZONE_SIZE * render.ASPECT_RATIO; 
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
