#ifndef BOARD_HPP
#define BOARD_HPP

const int BOARD_SIZE = 9;

enum Piece {Empty, Black, White};

class GoBoard{
    private: 
    public:
        Piece grid[BOARD_SIZE][BOARD_SIZE];
        int static turn;
        bool reset(void){
            for (int i = 0; i < 9; ++i) for (int j = 0; j < 9; ++j){
                GoBoard :: grid[i][j] = Empty;
            }
            return true;
        }

        bool inside(int x, int y){
            return x >= 0 and x < BOARD_SIZE and y >= 0 and y < BOARD_SIZE;
        }

        bool newStep(int x, int y, Piece color){
            if(!inside(x,  y)) return false;

            grid[x][y] = color;
            return true;
        }
};
#endif BOARD_HPP