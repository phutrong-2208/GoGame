#include "Game.hpp"


sf :: RenderWindow window;

// Core systems
SoundEffect backGround;
Operation op;
MetaControls metaControls;
MouseInput mouse;
Button setup;
GoBoard goBoard;
RenderZone render;
Score score;

// UI
Manager ui;
Mode ModeUI;
Setting SettingUI;
Menu MenuUI;
ScoreReveal ScoreUI;
std::vector<Button> button_list[5];

// Bot
GoBot botMode;
EasyMode easy;
HardMode medium_and_hard;

// Engine
KataGo katago[3];

void Game :: run() {
    sf::RenderWindow window(sf::VideoMode({1200, 800}), "GoGame");
    render.initSize(window);

    setup.setupButtonOperation(button_list[0]);
    MenuUI.setupMenuButton(button_list[1]);
    SettingUI.setupSettingButton(button_list[2]);
    ModeUI.setupModeButton(button_list[3]);
    ScoreUI.setupScoreButton(button_list[4]);

    backGround.Background.setLoop(true);
    backGround.Background.play();

    
    char buffer[260];
    
    GetModuleFileNameA(NULL, buffer, 260);
    auto currentPath = std :: filesystem :: path(buffer).parent_path();
    std :: string exe     = (currentPath / "KataGo\\katago.exe").string(); 
    std :: string model   = (currentPath / "KataGo\\final.gz").string(); 
    std :: string config  = (currentPath / "KataGo\\default_gtp.cfg").string();

    for (int i = 0; i < 3; ++i){
        if (!katago[i].startProcess(exe, model, config)) {
            std :: cerr << "Can't start katago process!\n";
            return;
        }
    }

    katago[0].sendCommand("boardsize 9"); // default board size
    katago[1].sendCommand("boardsize 13");
    katago[2].sendCommand("boardsize 19");

    logbox.reset();

    // ===================== MAIN LOOP =====================
    while(window.isOpen()) {

        sf::Event event; 
        while(window.pollEvent(event)) {

            if (event.type == sf::Event::Closed) {
                window.close();
                continue;
            }

            if (event.type == sf::Event::Resized) {
                render.normalizeSize(window);
                continue;
            }

            if (ui.State == BOARD) {

                ui.boardManager(window, goBoard, button_list[0], event);

                if (goBoard.ended()) {
                    ui.State = SCORE;
                }

                continue;
            }

            op.history.clear();
            op.snap.clear();
            logbox.reset();

            katago[metaControls.boardType].sendCommand("clear_board");
            katago[metaControls.boardType].readCommand();

            if (ui.State != SCORE) {
                goBoard.newGame();
                op.history.emplace_back(goBoard);
            }

            ui.MenuManager(window, button_list[ui.State], goBoard, event);
        }


        // ===================== RENDER =====================

        window.clear();

        if (ui.State == BOARD) {
            ui.drawBoard(window, goBoard, button_list[BOARD]);
        }
        else if (ui.State == SCORE) {
            ui.drawBoard(window, goBoard, button_list[BOARD]);
            ScoreUI.drawScoreReveal(window, goBoard);
            ui.drawScore(window, button_list[SCORE], "font\\Bungee_Regular.ttf");
        }
        else{
            ui.drawMenu(window, button_list[ui.State], "font\\Bungee_Regular.ttf");
        }


        for (Button &button : button_list[ui.State]) {
            ui.doActionHover(button, window);
        }

       window.display();
    }
    for (int i = 0; i < 3; ++i){
        katago[i].stopProcess();
    }
}