#include "UIManager.hpp"
void Manager :: doActionHover(Button &button, sf :: RenderWindow &window, MouseInput& mouse, RenderZone& render) {
    auto [mouseX, mouseY] = mouse.getPosition(window, render);
    float tmpSpace = 1.0f * button.siz.x / button.cnt;
    for (int i = 0; i < button.cnt; ++i) {
        button.color[i] = sf :: Color(222, 184, 135);
        if (button.position.x + tmpSpace * i >= mouseX) continue;
        if (button.position.x + tmpSpace * (i + 1) <= mouseX) continue;
        if (button.position.y >= mouseY || mouseY >= button.position.y + button.siz.y) continue;
        button.color[i] = sf :: Color(153, 101, 60);
    }
}

void Manager :: doActionClick(Manager &ui, Button &button, sf :: RenderWindow &window, MouseInput& mouse, RenderZone& render, GoBoard &goBoard, Operation& op) {
    auto [mouseX, mouseY] = mouse.getPosition(window, render);
    float tmpSpace = 1.0f * button.siz.x / button.cnt;
    for (int i = 0; i < button.cnt; ++i) {
        if (button.position.x + tmpSpace * i >= mouseX) continue;
        if (button.position.x + tmpSpace * (i + 1) <= mouseX) continue;
        if (button.position.y >= mouseY || mouseY >= button.position.y + button.siz.y) continue;
        
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
                ui.State = GAME_MENU;
                break;
            case 6:
                ui.State = BOARD;
                break;
            case 7: 
                ui.State = MODE_MENU;
                break;
            case 8:
                ui.State = SETTING_MENU;
                break;
            case 9:
                window.close();
                break;
            case 10:
                goBoard.setSize(button.attr[i]);
                break;
            case 11:
                metaControls.playWithBot = button.attr[i];
                break;
            case 12:
                metaControls.difficulty = button.attr[i];
                break;
            case 13:
                metaControls.startAsWhite = button.attr[i];
                break;
            case 14:
                metaControls.musicActive = button.attr[i];
                break;
            case 15:
                metaControls.soundActive = button.attr[i];
                break;
            case 16:
                metaControls.audioVolume += button.attr[i];
                break;
            case 17:
                metaControls.themeChoice = button.attr[i];
                break;
        }
    }
}

//================================================================================================================================
//For board 
void Manager :: drawBoard(sf :: RenderWindow&window, GoBoard& goBoard, RenderZone& render, MouseInput& mouse, std :: vector<Button> button_list){
    auto [snatchX, snatchY] = mouse.checkBoard(window, render, goBoard);
    render.drawMain(window, goBoard);
    if (snatchX != 999) render.drawPiece(window, goBoard, snatchX, snatchY, goBoard.turn);
    for (Button &button : button_list) {
        button.drawButton(window);
    }
}
void Manager :: boardManager(Manager &ui, sf :: RenderWindow &window, std :: vector<Button> &button_list, RenderZone&render, MouseInput& mouse, GoBoard& goBoard, Operation& op, sf :: Event event){
    auto [snatchX, snatchY] = mouse.checkBoard(window, render, goBoard);
    if(event.type == sf :: Event :: MouseButtonPressed){
        if(goBoard.newStep(snatchX, snatchY, goBoard.turn)){
            op.history.emplace_back(goBoard);
            op.snap.clear();
            return;
        }
        for (Button &button : button_list) {
            doActionClick(ui, button, window, mouse, render, goBoard, op);
        }
    }
}

//================================================================================================================================
//For menu 
void Manager :: setupMenuButton(RenderZone &render, std :: vector<Button> &button_list){
    int distance_between_button = 25;
    float width = render.ZONE_SIZE * render.ASPECT_RATIO / 3.0f;
    float height = (2.0f * render.ZONE_SIZE / 3.0f) / 4.0f - distance_between_button;

    float tmp_posX = width, tmp_posY = 1.0f * render.ZONE_SIZE / 3.0f;
    button_list.emplace_back(Button(
        {tmp_posX, tmp_posY}, {width, height}, 
        6, 1, 
        {"Play"}, {sf :: Color(222, 184, 135)}, {0})
    );
    tmp_posY += distance_between_button + height;
    button_list.emplace_back(Button(
        {tmp_posX, tmp_posY}, {width, height}, 
        7, 1, 
        {"Modes"}, {sf :: Color(222, 184, 135)}, {0})
    );

    tmp_posY += distance_between_button + height;
    button_list.emplace_back(Button(
        {tmp_posX, tmp_posY}, {width, height}, 
        8, 1, 
        {"Settings"}, {sf :: Color(222, 184, 135)}, {0})
    );

    tmp_posY += distance_between_button + height;
    button_list.emplace_back(Button(
        {tmp_posX, tmp_posY}, {width, height}, 
        9, 1, 
        {"Exit"}, {sf :: Color(222, 184, 135)}, {0})
    );
}

void Manager :: setupModeButton(RenderZone &render, std :: vector<Button> &button_list){
    int distance_between_button = 25;
    float width = render.ZONE_SIZE * render.ASPECT_RATIO / 3.0f;
    float height = (2.0f * render.ZONE_SIZE / 3.0f) / 5.0f - distance_between_button;

    float tmp_posX = width, tmp_posY = 1.0f * render.ZONE_SIZE / 3.0f;
    button_list.emplace_back(Button(
        {tmp_posX, tmp_posY}, {width, height}, 
        10, 3, 
        {"9x9", "13x13", "19x19"}, {sf :: Color(222, 184, 135), sf :: Color(222, 184, 135), sf :: Color(222, 184, 135)}, {9, 13, 19})
    );
    tmp_posY += distance_between_button + height;
    button_list.emplace_back(Button(
        {tmp_posX, tmp_posY}, {width, height}, 
        11, 2, 
        {"Play Human", "Play Bot"}, {sf :: Color(222, 184, 135), sf :: Color(222, 184, 135)}, {0, 1})
    );

    tmp_posY += distance_between_button + height;
    button_list.emplace_back(Button(
        {tmp_posX, tmp_posY}, {width, height}, 
        12, 3, 
        {"Easy", "Medium", "Hard"}, {sf :: Color(222, 184, 135), sf :: Color(222, 184, 135), sf :: Color(222, 184, 135)}, {0, 1, 2})
    );

    tmp_posY += distance_between_button + height;
    button_list.emplace_back(Button(
        {tmp_posX, tmp_posY}, {width, height}, 
        13, 2, 
        {"Play Black", "Play White"}, {sf :: Color(222, 184, 135), sf :: Color(222, 184, 135)}, {0, 1})
    );

    tmp_posY += distance_between_button + height;
    button_list.emplace_back(Button(
        {tmp_posX, tmp_posY}, {width, height}, 
        5, 1, 
        {"Save and return"}, {sf :: Color(222, 184, 135)}, {0})
    );
}

void Manager :: setupSettingButton(RenderZone &render, std :: vector<Button> &button_list){
    int distance_between_button = 25;
    float width = render.ZONE_SIZE * render.ASPECT_RATIO / 3.0f;
    float height = (2.0f * render.ZONE_SIZE / 3.0f) / 5.0f - distance_between_button;

    float tmp_posX = width, tmp_posY = 1.0f * render.ZONE_SIZE / 3.0f;
    button_list.emplace_back(Button(
        {tmp_posX, tmp_posY}, {width, height}, 
        14, 2, 
        {"Music On", "Music Off"}, {sf :: Color(222, 184, 135), sf :: Color(222, 184, 135)}, {1, 0})
    );
    tmp_posY += distance_between_button + height;
    button_list.emplace_back(Button(
        {tmp_posX, tmp_posY}, {width, height}, 
        15, 2, 
        {"Sounds On", "Sounds Off"}, {sf :: Color(222, 184, 135), sf :: Color(222, 184, 135)}, {1, 0})
    );

    tmp_posY += distance_between_button + height;
    button_list.emplace_back(Button(
        {tmp_posX, tmp_posY}, {width, height}, 
        16, 3, 
        {"Volume down", "placeholder", "Volume up"}, {sf :: Color(222, 184, 135), sf :: Color(222, 184, 135), sf :: Color(222, 184, 135)}, {-5, 0, 5})
    );

    tmp_posY += distance_between_button + height;
    button_list.emplace_back(Button(
        {tmp_posX, tmp_posY}, {width, height}, 
        17, 3, 
        {"Classic", "Futuristic", "Magical"}, {sf :: Color(222, 184, 135), sf :: Color(222, 184, 135), sf :: Color(222, 184, 135)}, {0, 1, 2})
    );

    tmp_posY += distance_between_button + height;
    button_list.emplace_back(Button(
        {tmp_posX, tmp_posY}, {width, height}, 
        5, 1, 
        {"Save and return"}, {sf :: Color(222, 184, 135)}, {0})
    );
}

void Manager :: drawMenu(sf :: RenderWindow &window, GoBoard& goBoard, RenderZone&render, std :: vector<Button> &button_list){
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
        button.drawButton(window);
    }    
}

void Manager :: MenuManager(Manager &ui, sf :: RenderWindow &window, std :: vector<Button> button_list, RenderZone&render, MouseInput& mouse, GoBoard& goBoard, Operation& op, sf :: Event event){
    if(event.type == sf :: Event :: MouseButtonPressed){
        for (Button &button : button_list) {
            doActionClick(ui, button, window, mouse, render, goBoard, op);
        }
    }
}