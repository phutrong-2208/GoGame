
#define BOARD_H

const int  BOARD_SIZE = 9;

enum Piece {Black, White, Empty};

class GoBoard{
    public:
        Piece grid[BOARD_SIZE][BOARD_SIZE];
    private:
        bool reset(void);
        bool newStep(int x, int y, Piece color);
};