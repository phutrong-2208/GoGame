#include <fileOperation.hpp>

void FileOperation :: importBoard(GoBoard& goBoard) {
    std :: ifstream boardf("saves/gogame.sav");
    int tmp;
    boardf >> goBoard.boardSize;
    boardf >> tmp; goBoard.turn = Piece(tmp);
    boardf >> goBoard.pass;
    boardf >> goBoard.endGame;
    boardf >> tmp; goBoard.grid.resize(tmp);
    for (auto &t: goBoard.grid) {
        boardf >> tmp; t.resize(tmp);
        for (Piece &x: t) {
            boardf >> tmp;
            x = Piece(tmp);
        }
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