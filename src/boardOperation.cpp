#include <boardOperation.hpp>

void Operation :: reset(void){
    history.clear();
    snap.clear();
}
void Operation :: Rollback(GoBoard &goBoard, int t){
    
    for (int i = 0; i < (metaControls.playWithBot ? 2 : 1); ++i){
        if(t == 0) { //undo case
            if(metaControls.difficulty == 2){  //for model undo operation
                katago.sendCommand("undo");
                katago.readCommand();
            }

            if(history.size() <= 1) return;
            snap.emplace_back(history.back());
            history.pop_back();
            goBoard = history.back();
        }
        else { //redo case
            if(snap.empty()) return;
            history.emplace_back(snap.back());
            std :: string turn = (i == 0 ? "black" : "white");
            auto move = snap.back().lastMove;
            katago.sendCommand("play " + turn + " " + metaControls.encode(move.first, move.second));
            katago.readCommand();

            goBoard = snap.back();
            snap.pop_back();
        }
    }
}
void Operation :: NewGame(GoBoard &goBoard){
    goBoard.newGame();
    logbox.reset();
    op.history.clear();
    op.snap.clear();
    op.history.emplace_back(goBoard);
}
void Operation :: Resign(GoBoard &goBoard){
    std :: string color = (goBoard.turn == Black ? "Black" : "White");
    logbox.insertText(color + " Resigned!");
    goBoard.endGame = 2;
}
void Operation :: Pass(GoBoard &goBoard){
    goBoard.pass++;
    std :: string color = (goBoard.turn == Black ? "Black" : "White");
    logbox.insertText(color + " Passed!");
    goBoard.turn = (goBoard.turn == Black ? White : Black);
}
void Operation :: SetSize(GoBoard &goBoard, int boardSize){
    goBoard.boardSize = boardSize;
    goBoard.grid.assign(boardSize, std :: vector<Piece>(boardSize, Empty));
    goBoard.newGame();
}
void Operation :: File(GoBoard &goBoard, int attr){
    if (attr) {
        fop.exportBoard(goBoard); 
    } else {
        fop.importBoard(goBoard);
        reset();
    }
}