#include "button.hpp"

void Button :: drawButton(sf :: RenderWindow &window){
    //set the position , color and the size of the boxes
    box.setPosition(position);
    box.setSize(siz);
    box.setFillColor(color);
    
    //set the color of outline and the thinkness
    box.setOutlineThickness(2);
    box.setOutlineColor(sf :: Color :: Black);
    box.setOrigin(siz.x / 2, siz.y / 2);
    //set words font of the texts on each button
    sf :: Font font;

    if(!font.loadFromFile("font\\arial.ttf")){
        std :: cout << "The font doesn't exist!";
        assert(false);
    }
    sf :: Text label(Text, font, 36);
    label.setColor(sf :: Color :: Black);

    sf :: FloatRect textBounds = label.getGlobalBounds();
    sf :: FloatRect boxBounds = box.getGlobalBounds();
    //centering the text in the box
    label.setOrigin(textBounds.left + textBounds.width / 2.0, textBounds.top + textBounds.height / 2.0);
    label.setPosition(position.x, position.y);

    float width_ratio = (boxBounds.width * 0.6f) / textBounds.width;
    float height_ratio = (boxBounds.height * 0.2f) / textBounds.height;

    label.setScale(width_ratio, height_ratio); // resize the text bounds for fitting with the box

    window.draw(box);
    window.draw(label);
}

void Button :: setupButtonOpertation(RenderZone &render, std :: vector<Button> &button_list){
    float height = (render.ZONE_SIZE - 2 * render.SHIFT_CONST - 5 * render.CONTROL_SHIFT) / 4.0f;
    float width = render.ZONE_SIZE * (render.ASPECT_RATIO - 1) - render.SHIFT_CONST - 2 * render.CONTROL_SHIFT; 

    button_list.emplace_back(
        Button({render.ZONE_SIZE + render.CONTROL_SHIFT + width / 4.0f, render.SHIFT_CONST + 1 * render.CONTROL_SHIFT + height / 2.0f}, 
        {width  / 2, height}, "Undo", sf :: Color(222, 184, 135), 0)
    );
    button_list.emplace_back(
        Button({render.ZONE_SIZE + render.CONTROL_SHIFT + width / 2.0f + width / 4.0f, render.SHIFT_CONST + 1 * render.CONTROL_SHIFT + height / 2.0f},
        {width / 2, height}, "Redo", sf :: Color(222, 184, 135), 1)
    );
    button_list.emplace_back(
        Button({render.ZONE_SIZE + render.CONTROL_SHIFT + width / 2.0f, render.SHIFT_CONST + 2 * render.CONTROL_SHIFT + height / 2.0f + 1 * height}, 
        {width, height}, "Resign", sf :: Color(222, 184, 135), 2)
    );
    button_list.emplace_back(
        Button({render.ZONE_SIZE + render.CONTROL_SHIFT + width / 2.0f, render.SHIFT_CONST + 3 * render.CONTROL_SHIFT + height / 2.0f + 2 * height}, 
        {width, height}, "New Game", sf :: Color(222, 184, 135), 3)
    );
    button_list.emplace_back(
        Button({render.ZONE_SIZE + render.CONTROL_SHIFT + width / 2.0f, render.SHIFT_CONST + 4 * render.CONTROL_SHIFT + height / 2.0f + 3 * height}, 
        {width, height}, "Pass Turn", sf :: Color(222, 184, 135), 4)
    );
}


bool Button :: detectHover(sf :: RenderWindow &window, MouseInput& mouse, RenderZone& render) {
    auto [mouseX, mouseY] = mouse.getPosition(window, render);
    if (mouseX < position.x - siz.x * 0.5f) return 0;
    if (mouseX > position.x + siz.x * 0.5f) return 0;
    if (mouseY < position.y - siz.y * 0.5f) return 0;
    if (mouseY > position.y + siz.y * 0.5f) return 0;
    return 1;
}

void Button :: doActionStall(void) {
    // siz.x = (siz.x * 20 + 90) / 21.0L;
    // siz.y = (siz.y * 20 + 110) / 21.0L;
    color = sf :: Color(222, 184, 135);
}

void Button :: doActionHover(void) {
    // siz.x = (siz.x * 20 + 100) / 21.0L;
    // siz.y = (siz.y * 20 + 120) / 21.0L;
    color = sf :: Color(153, 101, 60);
}

void Button :: doActionClick(GoBoard &goBoard, Operation& op) {
    switch (type){
        case 0: //Undo
            op.Rollback(goBoard, 0);
            break; 
        case 1: //Redo
            op.Rollback(goBoard, 1);
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
    }
}