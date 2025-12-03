#include <boardOperation.hpp>

void Operation :: reset(void){
    history.clear();
    snap.clear();
}
void Operation :: Rollback(GoBoard &goBoard, int t){
    
    for (int i = 0; i < (metaControls.playWithBot ? 2 : 1); ++i){
        if(t == 0) { //undo case
            if(metaControls.difficulty > 0){  //for model undo operation
                katago[metaControls.boardType].sendCommand("undo");
                katago[metaControls.boardType].readCommand();
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
            
            if(metaControls.difficulty > 2){
                katago[metaControls.boardType].sendCommand("play " + turn + " " + metaControls.encode(move.first, move.second));
                katago[metaControls.boardType].readCommand();
            }

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
    std :: string color = (goBoard.turn == Black ? "Black" : "White");
    logbox.insertText(color + " Passed!");
    goBoard.passMove();
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