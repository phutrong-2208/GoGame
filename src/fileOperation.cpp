#include <fileOperation.hpp>
void FileOperation :: importBoard(GoBoard& goBoard) {
    std :: ifstream boardf("saves/gogame.sav");
    int tmp;
    boardf >> metaControls.playWithBot >> metaControls.difficulty >> metaControls.boardType >> metaControls.goFirst;
    boardf >> goBoard.boardSize;
    boardf >> tmp; goBoard.turn = Piece(tmp);
    boardf >> goBoard.pass;
    boardf >> goBoard.endGame;
    boardf >> tmp; goBoard.grid.resize(tmp);

    if(metaControls.difficulty != 0){
        std :: string maxTime = (metaControls.difficulty == 1 ? "1" : "3");

        katago[metaControls.boardType].sendCommand("clear_board"); //clear board 
        katago[metaControls.boardType].readCommand();

        katago[metaControls.boardType].sendCommand("kata-set-param maxTime " + maxTime); //set difficulty
        katago[metaControls.boardType].readCommand();

        katago[metaControls.boardType].sendCommand("boardsize " + std :: to_string(goBoard.boardSize)); //set board size
        katago[metaControls.boardType].readCommand();
    }
    int i = 0, j = 0;
    for (auto &t: goBoard.grid) {   
        boardf >> tmp; t.resize(tmp);
        for (Piece &x: t) {
            boardf >> tmp;
            x = Piece(tmp);
            std :: string Turn = (x == Black ? "black" : (x == White ? "white" : ""));
            if(Turn != ""){
                std :: cout << "Played " << Turn << " at " << metaControls.encode(i, j) << "\n";
                katago[metaControls.boardType].sendCommand("play " + Turn + " " + metaControls.encode(i, j));
                katago[metaControls.boardType].readCommand();
            }
            j++;
        }
        j = 0;
        i++;
    }
    boardf.close();
}

void FileOperation :: exportBoard(GoBoard& goBoard) {
    char fileName[256];
    time_t now = time(0);
    tm tstruct = *localtime(&now);
    strftime(fileName, sizeof(fileName), "saves/gogame%Y_%m_%d_%X.sav", &tstruct);
    for (char &x: fileName) {
        if (x == ':') x = '_';
    }
    for (int i = 1; i <= 2; i++) {
        std :: cerr << "Exported to " << fileName << std :: endl;
        std :: ofstream boardf(fileName);
        boardf << metaControls.playWithBot << " " << metaControls.difficulty << " " << metaControls.boardType << " " << metaControls.goFirst << "\n";
        boardf << goBoard.boardSize << "\n";
        boardf << goBoard.turn << "\n";
        boardf << goBoard.pass << "\n";
        boardf << goBoard.endGame << "\n";
        boardf << (int)goBoard.grid.size() << "\n";
        for (const auto &t: goBoard.grid) {
            boardf << (int)t.size() << "\n";
            for (int x: t) boardf << x << " ";
            boardf << "\n";
        }
        boardf.close();
        int j = 0;
        for (char x: "saves/gogame.sav") {
            fileName[j] = x;
            ++j;
        }
        fileName[j] = '\0';
    }
}