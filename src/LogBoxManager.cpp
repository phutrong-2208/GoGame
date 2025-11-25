#include "LogBoxManager.hpp"

const int MAX_LINES = 8;
const double coeff_shift = 10.0f;
const double fudge = 0.8f;
const double terminal_size = 40.0f;

int constant = 10;
//the position of the log box
float posX = metaControls.ZONE_SIZE + metaControls.CONTROL_SHIFT;
float posY = metaControls.SHIFT_CONST + metaControls.CONTROL_SHIFT + 6.0f * (metaControls.CONTROL_SHIFT + 
    1.0f * (metaControls.ZONE_SIZE - 2 * metaControls.SHIFT_CONST - (constant + 1) * metaControls.CONTROL_SHIFT) / constant);

//the length of the log box
float width = metaControls.ZONE_SIZE * (metaControls.ASPECT_RATIO - 1) - metaControls.SHIFT_CONST - 2 * metaControls.CONTROL_SHIFT; 
float height = metaControls.ZONE_SIZE - metaControls.CONTROL_SHIFT - metaControls.SHIFT_CONST - posY;

void LogBox :: drawLogBox(sf :: RenderWindow& window){
    customPanelRender(window, {posX, posY}, {posX + width, posY + height}, metaControls.logboxColor);
}

// void LogBox :: drawConfigDialog(sf :: RenderWindow& window, GoBoard &goBoard){
//     float coordX = posX + width / 2.0f;
//     float coordY = posY + coeff_shift + (5 + (height / MAX_LINES) * fudge * fudge) * MAX_LINES;
//     Button config({coordX, coordY}, {width - 2 * coeff_shift, (height / MAX_LINES) * fudge}, 
//         20, 2, {"Yes", "No"}, 
//         {metaControls.Button_Color, metaControls.Button_Color}, {0, 1}, {}
//     );
//     std :: string fontLink = "font\\Bungee_Regular.ttf";
//     std :: string imageLink = "";
//     config.drawButton(window, fontLink, imageLink);

//     ui.doActionHover(config, window);
//     ui.doActionClick(goBoard, config, window);
// }

std :: string getCurrentTime(){
    auto now = std :: chrono :: system_clock :: now();
    std :: time_t now_time = std :: chrono :: system_clock :: to_time_t(now);
    std :: tm* tm_ptr = std :: localtime(&now_time);

    std :: ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << tm_ptr -> tm_hour << ":"
        << std::setfill('0') << std::setw(2) << tm_ptr -> tm_min << ":"
        << std::setfill('0') << std::setw(2) << tm_ptr -> tm_sec << ": ";
    return oss.str();
}

void LogBox :: insertText(std :: string notif){
    sf :: Text label, time;
    std :: string currentTime = getCurrentTime();
    int textSize = (height / MAX_LINES) * fudge;
    
    time.setCharacterSize(textSize);
    time.setString(currentTime);
    time.setColor(sf :: Color :: Black);
    time.setFont(font);
    time.setStyle(sf :: Text :: Bold);
    
    label.setCharacterSize(textSize);
    label.setString(notif);
    label.setColor(sf :: Color :: Black);
    label.setFont(font);
    notification.emplace_back(time, label);

    if((int)notification.size() > MAX_LINES) ++index;
}

void LogBox :: drawText(sf :: RenderWindow &window){
    int l = index;
    int r = std :: min((int)notification.size() - 1, index + MAX_LINES - 1);

    double nowHeight = posY + coeff_shift;
    for (int i = l; i <= r; ++i){
        notification[i].first.setPosition(posX + coeff_shift, nowHeight);
        window.draw(notification[i].first);
        notification[i].second.setPosition(posX + coeff_shift + notification[i].first.getGlobalBounds().width, nowHeight);
        window.draw(notification[i].second);
        nowHeight += 5 + notification[i].second.getCharacterSize() * fudge;
    }
}
void LogBox :: scrollUp(void){
    if(index > 0) index--;
}
void LogBox :: scrollDown(void){
    int r = std :: max(0, (int)notification.size() - MAX_LINES);
    if(index < r) ++index;
}

void LogBox :: reset(void){
    notification.clear();
    index = 0;
    insertText("Have fun!");
}
bool LogBox :: inBound(int x, int y){
    if (x < posX || x > posX + width || y < posY || y > posY + height) return false;
    return true;
}