#include <boardOperation.hpp>

void Operation :: reset(void){
    history.clear();
    snap.clear();
}
void Operation :: Rollback(GoBoard &goBoard, int t){
    if(t == 0) { //undo case
        if(history.size() <= 1) return;
        snap.emplace_back(history.back());
        history.pop_back();
        goBoard = history.back();
    }
    else{ //redo case
        if(snap.empty()) return;

        history.emplace_back(snap.back());
        goBoard = snap.back();
        snap.pop_back();
    }
}
void Operation :: NewGame(GoBoard &goBoard){
    goBoard.newGame();
}
void Operation :: Resign(GoBoard &goBoard){
    goBoard.endGame = 2;
}
void Operation :: Pass(GoBoard &goBoard){
    goBoard.pass++;
    goBoard.turn = (goBoard.turn == Black ? White : Black);
}
void Operation :: SetSize(GoBoard &goBoard, int boardSize){
    goBoard.boardSize = boardSize;
    goBoard.grid.assign(boardSize, std :: vector<Piece>(boardSize, Empty));
    
    goBoard.newGame();
}
void Operation :: File(GoBoard &goBoard, int attr){
    if (attr) FileImport(goBoard); 
    else FileExport(goBoard);
}
void Operation :: FileImport(GoBoard &goBoard){
}
void Operation :: FileExport(GoBoard &goBoard){
}