#ifdef BOARD_H
#define BOARD_H

const int  BOARD_SIZE = 9;

enum Stone = {Black, White, Empty};

class GoBoard{
    public:
        Stone grid[BOARD_SIZE][BOARD_SIZE];
    private:
}
#endif