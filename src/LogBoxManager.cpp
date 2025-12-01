#include "LogBoxManager.hpp"


int constant = 10;
//the position of the log box

void LogBox :: drawLogBox(sf :: RenderWindow& window){
    updatePosition();
    customPanelRender(window, {posX, posY}, {posX + width, posY + height}, metaControls.Color3);
}

// void LogBox :: drawConfigDialog(sf :: RenderWindow& window){
//     float coordX = posX + width / 2.0f;
//     float coordY = posY + coeff_shift + (5 + (height / MAX_LINES) * fudge * fudge) * MAX_LINES;
//     Button config({coordX, coordY}, {width - 2 * coeff_shift, (height / MAX_LINES) * fudge}, 
//         20, 2, {"Yes", "No"}, 
//         {metaControls.Color2, metaControls.Color2}, {0, 1}, {}
//     );
//     std :: string fontLink = "font\\Bungee_Regular.ttf";
//     std :: string imageLink = "";
//     config.drawButton(window, fontLink, imageLink);
// }

std :: string getCurrentTime(){
    auto now = std :: chrono :: system_clock :: now();
    std :: time_t now_time = std :: chrono :: system_clock :: to_time_t(now);
    std :: tm* tm_ptr = std :: localtime(&now_time);

    std :: ostringstream oss;
    oss << std :: setfill('0') << std :: setw(2) << tm_ptr -> tm_hour << ":"
        << std :: setfill('0') << std :: setw(2) << tm_ptr -> tm_min << ":"
        << std :: setfill('0') << std :: setw(2) << tm_ptr -> tm_sec << ": ";
    return oss.str();
}

void LogBox :: insertText(std :: string notif){
    sf :: Text label, time;
    std :: string currentTime = getCurrentTime();
    int textSize = (height / MAX_LINES) * fudge;
    
    time.setCharacterSize(textSize);
    time.setString(currentTime);
    time.setColor(metaControls.Color4);
    time.setFont(font);
    time.setStyle(sf :: Text :: Bold);
    
    label.setCharacterSize(textSize);
    label.setString(notif);
    label.setColor(metaControls.Color4);
    label.setFont(font);
    notification.emplace_back(time, label);

    if((int)notification.size() > MAX_LINES) ++index;
}

void LogBox :: drawText(sf :: RenderWindow &window){
    updatePosition();
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
    updatePosition();
    notification.clear();
    index = 0;
    insertText("Have fun!");
}
bool LogBox :: inBound(int x, int y){
    updatePosition();
    if (x < posX || x > posX + width || y < posY || y > posY + height) return false;
    return true;
}