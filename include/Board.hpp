#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include <tuple>
#include <queue>
#include <stack>
#include <iostream>

const int BOARD_SIZE = 9;

enum Piece {Empty, Black, White};

class GoBoard{
    private: 
    public:
        Piece turn;
        int pass; //save the number consecutive passes of both players, if both people skip their turn, the game will end
        std :: vector<std :: vector<Piece>> grid;
        GoBoard(){
            grid.resize(BOARD_SIZE, std :: vector<Piece>(BOARD_SIZE));
        }
        bool newGame(void);
        bool newStep(int x, int y, Piece color);
        void newState(int x, int y);
        bool ended(void);
        std :: pair<int, int> getScore(void);
};
#endif
