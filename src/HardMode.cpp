#include "HardMode.hpp"


//========================================================
//HARD MODE --- KATAGO MODEL, API CONNECTION
//========================================================
std::string trimAnswer(std::string s){
    if(!s.empty() && s[0] == '=') s = s.substr(1);

    s.erase(0, s.find_first_not_of(" \t\n\r"));
    s.erase(s.find_last_not_of(" \t\n\r") + 1);

    return s;
}
void HardMode :: Hard_Mode(GoBoard& goBoard){
    std :: string color = (goBoard.turn == Black ? "black" : "white");
    katago.sendCommand("genmove " + color);
    std :: string answer = katago.readCommand();
    answer = trimAnswer(answer);

    std :: cout << answer << '\n';

    katago.sendCommand("showboard");
    std :: string boardVisual = katago.readCommand();
    std :: cout << "BOT VISIBLE\n";
    std :: cout << boardVisual << '\n';
    
    if(answer.empty() || answer == "pass"){
        goBoard.pass++;
        goBoard.turn = (goBoard.turn == Black ? White : Black);
        return;
    }
    auto move = metaControls.decode(answer);

    goBoard.playMove(move.first, move.second, goBoard.turn, 1);
}

