#include "button.hpp"

void Button :: drawButton(sf :: RenderWindow &window){
    for (int i = 0; i < cnt; ++i) {
        //set the position , color and the size of the boxes
        box.setPosition({position.x + 1.0f * i * siz.x / cnt, position.y});
        box.setSize({1.0f * siz.x / cnt, siz.y});
        box.setFillColor(color[i]);
        
        //set the color of outline and the thinkness
        box.setOutlineThickness(2);
        box.setOutlineColor(sf :: Color :: Black);
        // box.setOrigin(siz.x * 0.5f / cnt, siz.y * 0.5f);
        window.draw(box);

        //set words font of the texts on each button
        sf :: Font font;

        if(!font.loadFromFile("font\\arial.ttf")){
            std :: cout << "The font doesn't exist!";
            assert(false);
        }

        sf :: Text label(Text[i], font, 36);

        label.setColor(sf :: Color :: Black);

        sf :: FloatRect textBounds = label.getGlobalBounds();
        sf :: FloatRect boxBounds = box.getGlobalBounds();
        // do not use textBounds.height
        float realHeight = (sf :: Text){"o", font, 36}.getGlobalBounds().height;

        //centering the text in the box
        label.setOrigin(textBounds.left + textBounds.width / 2.0, textBounds.top + realHeight / 2.0);
        label.setPosition(boxBounds.left + siz.x / 2.0f / cnt, boxBounds.top + siz.y / 2.0f);

        float fit_ratio = std :: min((boxBounds.width * 0.70f) / textBounds.width, 
                                    (boxBounds.height * 0.35f) / realHeight);

        label.setScale(fit_ratio, fit_ratio); // resize the text bounds for fitting with the box

        window.draw(label);
    }
}

void Button :: setupButtonOperation(RenderZone &render, std :: vector<Button> &button_list){
    int button_count = 11;
    float height = 1.0f * (render.ZONE_SIZE - 2 * render.SHIFT_CONST - (button_count + 1) * render.CONTROL_SHIFT) / button_count;
    float width = render.ZONE_SIZE * (render.ASPECT_RATIO - 1) - render.SHIFT_CONST - 2 * render.CONTROL_SHIFT; 

    float tmp_posX = render.ZONE_SIZE + render.CONTROL_SHIFT;
    float tmp_posY = render.SHIFT_CONST + render.CONTROL_SHIFT;

    button_list.emplace_back(Button(
        {tmp_posX, tmp_posY}, {width, height}, 
        1, 2, 
        {"Undo", "Redo"}, {sf :: Color(222, 184, 135), sf :: Color(222, 184, 135)}, {0, 1})
    );

    tmp_posY += render.CONTROL_SHIFT + height;
    button_list.emplace_back(Button(
        {tmp_posX, tmp_posY}, {width, height}, 
        2, 1, 
        {"Resign"}, {sf :: Color(222, 184, 135)}, {0})
    );

    tmp_posY += render.CONTROL_SHIFT + height;
    button_list.emplace_back(Button(
        {tmp_posX, tmp_posY}, {width, height}, 
        3, 1, 
        {"Reset Game"}, {sf :: Color(222, 184, 135)}, {0})
    );

    tmp_posY += render.CONTROL_SHIFT + height;
    button_list.emplace_back(Button(
        {tmp_posX, tmp_posY}, {width, height}, 
        4, 1, 
        {"Pass Turn"}, {sf :: Color(222, 184, 135)}, {0})
    );

    tmp_posY += render.CONTROL_SHIFT + height;
    button_list.emplace_back(Button(
        {tmp_posX, tmp_posY}, {width, height}, 
        5, 2, 
        {"Import", "Export"}, {sf :: Color(222, 184, 135), sf :: Color(222, 184, 135)}, {0, 1})
    );

    tmp_posY += render.CONTROL_SHIFT + height;
    button_list.emplace_back(Button(
        {tmp_posX, tmp_posY}, {width, height}, 
        6, 2, 
        {"1-player", "2-player"}, {sf :: Color(222, 184, 135), sf :: Color(222, 184, 135)}, {0, 1})
    );

    tmp_posY += render.CONTROL_SHIFT + height;
    button_list.emplace_back(Button(
        {tmp_posX, tmp_posY}, {width, height}, 
        7, 3, 
        {"Easy", "Medium", "Hard"}, {sf :: Color(222, 184, 135), sf :: Color(222, 184, 135), sf :: Color(222, 184, 135)}, {0, 1, 2})
    );

    tmp_posY += render.CONTROL_SHIFT + height;
    button_list.emplace_back(Button(
        {tmp_posX, tmp_posY}, {width, height}, 
        8, 2, 
        {"Play as Black", "Play as White"}, {sf :: Color(222, 184, 135), sf :: Color(222, 184, 135)}, {0, 1})
    );

    tmp_posY += render.CONTROL_SHIFT + height;
    button_list.emplace_back(Button(
        {tmp_posX, tmp_posY}, {width, height}, 
        9, 3, 
        {"9x9", "13x13", "19x19"}, {sf :: Color(222, 184, 135), sf :: Color(222, 184, 135), sf :: Color(222, 184, 135)}, {9, 13, 19})
    );

    tmp_posY += render.CONTROL_SHIFT + height;
    button_list.emplace_back(Button(
        {tmp_posX, tmp_posY}, {width, height}, 
        10, 2, 
        {"Music off", "Music on"}, {sf :: Color(222, 184, 135), sf :: Color(222, 184, 135)}, {0, 1})
    );

    tmp_posY += render.CONTROL_SHIFT + height;
    button_list.emplace_back(Button(
        {tmp_posX, tmp_posY}, {width, height}, 
        11, 2, 
        {"Sounds off", "Sounds on"}, {sf :: Color(222, 184, 135), sf :: Color(222, 184, 135)}, {0, 1})
    );

    assert(button_list.size() == button_count);
}

void Button :: doActionHover(sf :: RenderWindow &window, MouseInput& mouse, RenderZone& render) {
    auto [mouseX, mouseY] = mouse.getPosition(window, render);
    float tmpSpace = 1.0f * siz.x / cnt;
    for (int i = 0; i < cnt; ++i) {
        color[i] = sf :: Color(222, 184, 135);
        if (position.x + tmpSpace * i >= mouseX) continue;
        if (position.x + tmpSpace * (i + 1) <= mouseX) continue;
        if (position.y >= mouseY || mouseY >= position.y + siz.y) continue;
        color[i] = sf :: Color(153, 101, 60);
    }
}

void Button :: doActionClick(sf :: RenderWindow &window, MouseInput& mouse, RenderZone& render, GoBoard &goBoard, Operation& op) {
    auto [mouseX, mouseY] = mouse.getPosition(window, render);
    float tmpSpace = 1.0f * siz.x / cnt;
    for (int i = 0; i < cnt; ++i) {
        if (position.x + tmpSpace * i >= mouseX) continue;
        if (position.x + tmpSpace * (i + 1) <= mouseX) continue;
        if (position.y >= mouseY || mouseY >= position.y + siz.y) continue;
        switch (type){
            case 1: // Undo / Redo
                op.Rollback(goBoard, attr[i]);
                break;
            case 2:
                op.Resign(goBoard);
                break;
            case 3:
                op.NewGame(goBoard);
                break;
            case 4:
                op.Pass(goBoard);
                break;
            case 5: 
                // Import / Export game position
                break;
            case 6:
                // Gamemode (1/2-player) 
                break;
            case 7:
                // Difficulty (Easy/Medium/Hard, 2-player only) 
                break;
            case 8:
                // Starting side (Black/White, 1-player only)
                break;
            case 9:
                op.SetSize(goBoard, attr[i]);
                // Board size (9x9/13x13/19x19)
                break;
            case 10:
                // Toggle music
                break;
            case 11:
                // Toggle sounds
                break;
        }
    }
}