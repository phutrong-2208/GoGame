#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include <tuple>
#include <queue>
#include <stack>
#include <iostream>

#include "scoring.hpp"
#include "soundEffect.hpp"
#include "metaControls.hpp"

enum Piece {
    Empty, 
    Black, 
    White
};

class GoBoard{
    public:
        int boardSize;
        Piece turn;
        int pass;
        int endGame;
        std :: vector<std :: vector<Piece>> grid;
        std :: vector<std :: pair<int, int>> validMove;
        std :: vector<std :: vector<std :: vector<Piece>>> previousState;
        std :: pair<int, int> lastMove;

        void setSize(int _boardSize) {
            boardSize  = _boardSize ;
            grid.assign(boardSize , std :: vector<Piece>(boardSize , Empty));
        }
        GoBoard(int _boardSize = 9) {
            setSize(_boardSize); 
            endGame = 0; 
            pass = 0;
        }
    GoBoard operator = (const GoBoard& other) {
        boardSize = other.boardSize;
        grid = other.grid;
        turn = other.turn;
        pass = other.pass;
        endGame = other.endGame;
        validMove = other.validMove;
        lastMove = other.lastMove;  
        previousState = other.previousState;
        return *this;
    }
    bool newGame(void);
    bool playMove(int x, int y, Piece color, bool mainMove);
    std :: pair<int, int> getScore(void);
    bool ended(void);
    void passMove(void);
        
    private: //internal helps
        bool inBounds(int x, int y);
        bool canCapture(int x, int y);
        bool isLegalMove(int x, int y);
        void applyMove(int x, int y);
        int getTerritory(int x, int y);
};
#endif