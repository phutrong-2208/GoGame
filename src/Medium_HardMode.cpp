#include "Medium_HardMode.hpp"


//========================================================
//HARD + MEDIUM MODE --- KATAGO MODEL, API CONNECTION
//========================================================
std::string trimAnswer(std::string s){ //remove space and endline characters
    if(!s.empty() && s[0] == '=') s = s.substr(1);

    s.erase(0, s.find_first_not_of(" \t\n\r"));
    s.erase(s.find_last_not_of(" \t\n\r") + 1);

    return s;
}
void HardMode :: Move(GoBoard& goBoard){
    std :: string color = (goBoard.turn == Black ? "black" : "white");
    katago.sendCommand("genmove " + color);
    std :: string answer = katago.readCommand();
    answer = trimAnswer(answer);

    
    katago.sendCommand("showboard");

    //DEBUG
    std :: cerr << answer << '\n';
    std :: string boardVisual = katago.readCommand();
    std :: cerr << "BOT VISIBLE\n";
    std :: cerr << boardVisual << '\n';
    
    if(answer.empty() || answer == "pass"){
        std :: string color = (goBoard.turn == Black ? "Black" : "White");
        logbox.insertText(color + "Passed!");
        goBoard.passMove();
        return;
    }
    auto move = metaControls.decode(answer);

    goBoard.playMove(move.first, move.second, goBoard.turn, 1);
}

