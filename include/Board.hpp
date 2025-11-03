#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include <tuple>
#include <queue>
#include <stack>
#include <iostream>

#include "scoring.hpp"
#include "soundEffect.hpp"
enum Piece {Empty, Black, White};

class GoBoard{
    public:
        int siz;
        Piece turn;
        int pass; //save the number consecutive passes of both players, if both people skip their turn, the game will end
        std :: vector<std :: vector<Piece>> grid;
        void setSize(int _siz) {
            siz = _siz;
            grid.assign(siz, std :: vector<Piece>(siz, Empty));
        }
        GoBoard(int _siz = 13) {setSize(_siz);}
        bool newGame(void);
        bool newStep(int x, int y, Piece color);
        bool ended(void);
        std :: pair<int, int> getScore(void);
        bool inside(int x, int y);
        bool eatable(int x, int y);
        bool move_check(int x, int y);
        void newState(int x, int y);
        int getTerritory(int x, int y);
};
#endif
