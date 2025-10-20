#include "Board.hpp"
#include <iostream>
#include <stack>
//===============================================================================
std :: vector<std :: vector<Piece>> last_grid[2]; //save the last two state of the board 

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
std :: vector<std :: vector<int>> vis(BOARD_SIZE, std :: vector<int>(BOARD_SIZE, 0));

bool eatable(int x, int y){
    std :: queue<std :: pair<int, int>> q;
    std :: stack<std :: pair<int, int>> st;
    
    Piece color = temp.grid[x][y];
    
    q.emplace(x, y);
    st.emplace(x, y);    
    vis[x][y] = 1;
    int air_flag = 0;
    while(q.size()){
        auto [rx, ry] = q.front(); q.pop();
        for (int dir = 0; dir < 4; ++dir){
            int nx = rx + dx[dir];
            int ny = ry + dy[dir];
            if(!inside(nx, ny) or vis[nx][ny]) continue;
            if(temp.grid[nx][ny] == Empty) air_flag = 1;
            if(temp.grid[nx][ny] != color) continue;
            q.emplace(nx, ny);
            st.emplace(nx, ny);
            vis[nx][ny] = 1;
        }
    }
    if (air_flag) return false;
    
    while(st.size()){
        auto[x, y] = st.top(); st.pop();
        temp.grid[x][y] = Empty;
    }
    return true;
}  

void move_check(void){
    vis.assign(BOARD_SIZE, std :: vector<int>(BOARD_SIZE, 0));

    for (int i = 0; i < BOARD_SIZE; ++i){
        for (int j = 0; j < BOARD_SIZE; ++j) if(!vis[i][j] and temp.grid[i][j] != Empty){
            eatable(i, j);
        }
    }
}


//===============================================================================

void GoBoard :: newState(int x, int y){
    last_grid[0] = last_grid[1];
    last_grid[1] = grid;
    swap(GoBoard :: grid, temp.grid);
    GoBoard :: turn = (GoBoard :: turn == Black ? White : Black);   
}


bool GoBoard :: newStep(int x, int y, Piece turn){
    if(!inside(x,  y) or GoBoard :: grid[x][y] != Empty) return false;

    temp.grid = GoBoard :: grid;
    temp.grid[x][y] = turn;
    move_check();
    if(temp.grid == last_grid[0]) return false;

    newState(x, y);
    
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            std :: cout << vis[i][j] << " ";
        }
        std :: cout << "\n";
    }
    std :: cout << "\n";

    return true;
}       

//===============================================================================