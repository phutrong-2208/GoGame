#include "button.hpp"
#include "metaControls.hpp"
#include <map> 

static std :: map<std :: string, sf :: Font> fontCache; // save for reducing the number time of loading the Font from the file
static std :: map<std :: string, sf :: Texture> textureCache; // save for reducing the number time of loading the Texture from the file

void Button :: drawButton(sf :: RenderWindow &window, std :: string &FontLink, std :: string &ImageLink){
    /*
        ImageLink for the Texture of the buttons
        FontLink for the fonts of texts
    */
    
    sf :: FloatRect textBounds, boxBounds;
    for (int i = 0; i < cnt; ++i) {
        if(ImageLink != ""){
            if(fontCache.find(FontLink) == fontCache.end()){
                sf :: Texture new_texture;
                if(!new_texture.loadFromFile(ImageLink)){
                    std :: cout << "The image doesn't exist!\n";
                    assert(false);
                }
                textureCache[ImageLink] = new_texture;
            }
            sf :: Texture &button = textureCache[ImageLink];
            float image_width = button.getSize().x;
            float image_height = button.getSize().y;
            
            button.setSmooth(true);
            sf :: Sprite sprite(button);
            sprite.setScale(siz.x / image_width, siz.y / image_height);
            sprite.setPosition({position.x + 1.0f * i * siz.x / cnt, position.y});;
            if (hover[i]) sprite.setColor(sf :: Color(200, 200, 200));
            boxBounds = sprite.getGlobalBounds();
            window.draw(sprite);
        }
        else{
            //set the position , color and the size of the boxes
            box.setPosition({position.x + 1.0f * i * siz.x / cnt, position.y});
            box.setSize({1.0f * siz.x / cnt, siz.y});
            if (!hover[i]) box.setFillColor(color[i]);
            else box.setFillColor(color[i] * sf :: Color(200, 200, 200));
            
            //set the color of outline and the thinkness
            box.setOutlineThickness(2);
            box.setOutlineColor(sf :: Color :: Black);
            window.draw(box); 
            boxBounds = box.getGlobalBounds();
        }
        
        //set words font of the texts on each button
        
        if(fontCache.find(FontLink) == fontCache.end()){
            sf :: Font newFont; 
            if(!newFont.loadFromFile(FontLink)){
                std :: cout << "The font doesn't exist!";
                assert(false);
            }
            fontCache[FontLink] = newFont;
        }
        sf :: Font &font = fontCache[FontLink];
        
        
        sf :: Text label(Text[(cnt > 1 ? i : currentSelection)], font, 100);

        label.setColor(sf :: Color :: Black);
        textBounds = label.getGlobalBounds();

        
        // do not use textBounds.height
        float realHeight = (sf :: Text){"o", font, 100}.getGlobalBounds().height;

        //centering the text in the box
        label.setOrigin(textBounds.left + textBounds.width / 2.0, textBounds.top + realHeight / 2.0);
        label.setPosition(boxBounds.left + siz.x / 2.0f / cnt, boxBounds.top + siz.y / 2.0f);

        float fit_ratio = std :: min((boxBounds.width * 0.70f) / textBounds.width, 
                                    (boxBounds.height * 0.35f) / realHeight);

        label.setScale(fit_ratio, fit_ratio); // resize the text bounds for fitting with the box
        window.draw(label);
    }
}

void Button :: setupButtonOperation(std :: vector<Button> &button_list){
    int button_count = 6;
    float height = 1.0f * (render.ZONE_SIZE - 2 * render.SHIFT_CONST - (button_count + 1) * render.CONTROL_SHIFT) / button_count;
    float width = render.ZONE_SIZE * (render.ASPECT_RATIO - 1) - render.SHIFT_CONST - 2 * render.CONTROL_SHIFT; 

    float tmp_posX = render.ZONE_SIZE + render.CONTROL_SHIFT;
    float tmp_posY = render.SHIFT_CONST + render.CONTROL_SHIFT;

    button_list.emplace_back(Button(
        {tmp_posX, tmp_posY}, {width, height}, 
        1, 2, 
        {"Undo", "Redo"}, {metaControls.Button_Color, metaControls.Button_Color}, {0, 1})
    );

    tmp_posY += render.CONTROL_SHIFT + height;
    button_list.emplace_back(Button(
        {tmp_posX, tmp_posY}, {width, height}, 
        2, 1, 
        {"Resign"}, {metaControls.Button_Color}, {0})
    );

    tmp_posY += render.CONTROL_SHIFT + height;
    button_list.emplace_back(Button(
        {tmp_posX, tmp_posY}, {width, height}, 
        3, 1, 
        {"Pass"}, {metaControls.Button_Color}, {0})
    );

    tmp_posY += render.CONTROL_SHIFT + height;
    button_list.emplace_back(Button(
        {tmp_posX, tmp_posY}, {width, height}, 
        4, 1, 
        {"Reset"}, {metaControls.Button_Color}, {0})
    );

    tmp_posY += render.CONTROL_SHIFT + height;
    button_list.emplace_back(Button(
        {tmp_posX, tmp_posY}, {width, height}, 
        5, 1, 
        {"Menu"}, {metaControls.Button_Color}, {0})
    );

    tmp_posY += render.CONTROL_SHIFT + height;
    button_list.emplace_back(Button(
        {tmp_posX, tmp_posY}, {width, height}, 
        18, 2, 
        {"Import","Export"}, {metaControls.Button_Color, metaControls.Button_Color}, {0, 1})
    );
}


