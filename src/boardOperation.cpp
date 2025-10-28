#include <boardOperation.hpp>


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
    std :: cout << (goBoard.turn == Black ? "White " : "Black ") << " win by resignation!!\n";
    goBoard.newGame();
}
void Operation :: Pass(GoBoard &goBoard){
    std :: cout << (goBoard.turn == Black ? "Black " : "White ") << " Pass the turn!\n";
    goBoard.pass++;
    goBoard.turn = (goBoard.turn == Black ? White : Black);
}
void Operation :: SetSize(GoBoard &goBoard, int siz){
    std :: cout << "Size set to " << siz << "x" << siz << "\n";
    goBoard.siz = siz;
    goBoard.grid.assign(siz, std :: vector<Piece>(siz, Empty));
    goBoard.newGame();
}