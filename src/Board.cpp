
#include <Board.h>
bool GoBoard :: reset(void){
    for (int i = 0; i < 9; ++i) for (int j = 0; j < 9; ++j){
          GoBoard :: grid[i][j] = Empty;
    }
    return true;
}

bool inside(int x, int y){
    return x >= 0 and x < BOARD_SIZE and y >= 0 and y < BOARD_SIZE;
}

bool GoBoard :: newStep(int x, int y, Piece color){
    if(!inside(x,  y) or grid[x][y] == Empty) return false;

    grid[x][y] = color;
    return true;
}