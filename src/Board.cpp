#include "Board.hpp"

//===============================================================================

//starting new game
bool GoBoard :: newGame(void){
    for (int i = 0; i < 9; ++i) for (int j = 0; j < 9; ++j){
        GoBoard :: grid[i][j] = Empty;
    }
    last_grid[0].resize(BOARD_SIZE, std :: vector<Piece>(BOARD_SIZE));
    last_grid[1].resize(BOARD_SIZE, std :: vector<Piece>(BOARD_SIZE));
    GoBoard :: turn = Black;
    return true;
}

//===============================================================================
bool inside(int x, int y){
    return x >= 0 and x < BOARD_SIZE and y >= 0 and y < BOARD_SIZE;
}

GoBoard temp;
const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};
std :: vector<std :: vector<bool>> vis(BOARD_SIZE, std :: vector<bool>(BOARD_SIZE, false));

bool GoBoard :: eatable(int x, int y, Piece color){
    std :: queue<std :: pair<int, int>> q;
    q.emplace(x, y);    
    vis[x][y] = true;

    while(q.size()){
        auto [rx, ry] = q.front(); q.pop();
        for (int dir = 0; dir < 4; ++dir){
            int nx = rx + dx[dir];
            int ny = ry + dy[dir];
            if(!inside(nx, ny) or vis[nx][ny]) continue;

            if(GoBoard :: grid[nx][ny] == Empty) return false;
            if(GoBoard :: grid[nx][ny] != color){
                q.emplace(nx, ny);
                vis[nx][ny] = true;
            }
        }
    }
    return true;
}  


//===============================================================================

std :: vector<std :: vector<Piece>> last_grid[2];
void GoBoard :: newState(int x, int y){
    GoBoard :: grid[x][y] = turn;
    GoBoard :: turn = (GoBoard :: turn == Black ? White : Black);   
    last_grid[0] = last_grid[1];
    last_grid[1] = GoBoard :: grid;
}


bool GoBoard :: newStep(int x, int y, Piece turn){
    if(!inside(x,  y) or GoBoard :: grid[x][y] != Empty) return false;

    if(GoBoard :: grid == last_grid[0]) return false;
    temp.grid = GoBoard :: grid;

    newState(x, y);
    
    return true;
}       

//===============================================================================