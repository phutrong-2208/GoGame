#include <iostream>
#include <vector>


//including header file

#include "soundEffect.hpp"
#include "SFML/Graphics.hpp"
#include "mouseInput.hpp"
#include "roundedRectangle.hpp"
#include "Board.hpp"
#include "button.hpp"
#include "renderZone.hpp"
#include "fileOperation.hpp"
#include "boardOperation.hpp"
#include "UIManager.hpp"
#include "ModeManager.hpp"
#include "SettingManager.hpp"
#include "MenuManager.hpp"
#include "ScoreRevealManager.hpp"
#include "BotLogic.hpp"
#include "EasyMode.hpp"
#include "MediumMode.hpp"
#include "HardMode.hpp"
#include "modelEngine.hpp"

SoundEffect backGround;
Operation op; 
MetaControls metaControls;
MouseInput mouse;
Button setup;
GoBoard goBoard;
RenderZone render;
Score score;


//UIs Manager 
Manager ui;
Mode ModeUI;
Setting SettingUI;
Menu MenuUI;
ScoreReveal ScoreUI;
std :: vector<Button> button_list[5];   // save board button


//Game Modes
GoBot botMode;
EasyMode easy;
MediumMode medium;
HardMode hard;

//Models
KataGo katago;


int main(){
    sf :: RenderWindow window(sf :: VideoMode({1200, 800}), "GoGame");
    render.initSize(window);
    setup.setupButtonOperation(button_list[0]);
    MenuUI.setupMenuButton(button_list[1]);
    SettingUI.setupSettingButton(button_list[2]);
    ModeUI.setupModeButton(button_list[3]);
    ScoreUI.setupScoreButton(button_list[4]);

    backGround.Background.setLoop(true);
    backGround.Background.play();

    logbox.reset();
    std :: string exe = "C:\\Users\\ADMIN\\OneDrive - KonTum01\\Desktop\\GoGame\\KataGo\\katago.exe"; 
    std :: string model = "C:\\Users\\ADMIN\\OneDrive - KonTum01\\Desktop\\GoGame\\KataGo\\model.gz"; 
    std :: string config = "C:\\Users\\ADMIN\\OneDrive - KonTum01\\Desktop\\GoGame\\KataGo\\default_gtp.cfg"; 
    if (!katago.startProcess(exe, model, config)) {
        std :: cerr << "Can't start katago process!\n";
        return 0;
    }
    katago.sendCommand("boardsize 9"); //set the default size of the game


    while(window.isOpen()){
        sf :: Event event; 
        while(window.pollEvent(event)){  //get the value and pop it from the queue
            if(event.type == sf :: Event :: Closed){
                window.close();
                continue;
            }
            if(event.type == sf :: Event :: Resized){ // normalize window size
                render.normalizeSize(window);
                continue;
            }
            if(ui.State == BOARD){
                ui.boardManager(window, goBoard, button_list[0], event);
                if(goBoard.ended()){
                    ui.State = SCORE;
                }
                continue;
            }
            op.history.clear();
            op.snap.clear();
            logbox.reset();

            katago.sendCommand("clear_board");
            katago.readCommand();

            if(ui.State != SCORE){
                goBoard.newGame();
                op.history.emplace_back(goBoard);
            }
            ui.MenuManager(window, button_list[ui.State], goBoard, event);
        }
        window.clear();
        if(ui.State == BOARD) ui.drawBoard(window, goBoard, button_list[BOARD]);
        else if(ui.State == SCORE){
            ui.drawBoard(window, goBoard, button_list[BOARD]);
            ScoreUI.drawScoreReveal(window, goBoard);
            ui.drawScore(window, button_list[SCORE], "font\\Bungee_Regular.ttf");
        }
        else ui.drawMenu(window, button_list[ui.State], "font\\Bungee_Regular.ttf");

        for (Button &button : button_list[ui.State]) {
            ui.doActionHover(button, window);
        }
        window.display();
    }
    
}