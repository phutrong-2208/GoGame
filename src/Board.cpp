#include "Board.hpp"
#include "scoring.hpp"

//===============================================================================
std :: vector<std :: vector<std :: vector<Piece>>> previous_grid; //save the previous states, use for rollback operation
std :: vector<std :: pair<int, int>> validMove;

//starting new game
bool GoBoard :: newGame(void){
    for (int i = 0; i < 9; ++i) for (int j = 0; j < 9; ++j){
        GoBoard :: grid[i][j] = Empty;
        validMove.emplace_back(i, j);
    }
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

int cntCaptured = 0; //count the captured piece after a move

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
    cntCaptured += st.size();
    while(st.size()){
        auto[x, y] = st.top(); st.pop();
        temp.grid[x][y] = Empty;
    }
    return true;
}  

//check that if the move legal
bool move_check(int x, int y){
    vis.assign(BOARD_SIZE, std :: vector<int>(BOARD_SIZE, 0));
    if(eatable(x, y)) return false; // the suicide case 
    vis.assign(BOARD_SIZE, std :: vector<int>(BOARD_SIZE, 0));

    for (int i = 0; i < BOARD_SIZE; ++i){
        for (int j = 0; j < BOARD_SIZE; ++j) if(!vis[i][j] and temp.grid[i][j] != Empty){
            eatable(i, j);
        }
    }
    return true;
}


//===============================================================================

//for updating the board state
Score score; 

void GoBoard :: newState(int x, int y){ //update the new state of the board after a move
    previous_grid.emplace_back(grid);
    swap(GoBoard :: grid, temp.grid);
    GoBoard :: turn = (GoBoard :: turn == Black ? White : Black);  
    validMove.clear();
    for (int i = 0; i < BOARD_SIZE; ++i){
        for (int j = 0; j < BOARD_SIZE; ++j){
            if(temp.grid[i][j] == Empty){
                temp.grid[i][j] = GoBoard :: turn;
                if(!eatable(i, j)) validMove.emplace_back(i, j);
                temp.grid[i][j] = Empty;
            } 
        }
    } 
}


bool GoBoard :: newStep(int x, int y, Piece turn){
    if(!inside(x,  y) or GoBoard :: grid[x][y] != Empty) return false;
    
    temp.grid = GoBoard :: grid;
    temp.grid[x][y] = turn;
    cntCaptured = 0;
    if(!move_check(x, y) or (previous_grid.size() > 1 and temp.grid == previous_grid.end()[-2])) return false;
    if(turn == Black) score.blackCaptured += cntCaptured;
    else score.whiteCaptured += cntCaptured;
    newState(x, y);
    return true;
}       

//===============================================================================

//for end stage

int pass = 0; //save the number consecutive passes of both players, if both people skip their turn, the game will end
bool GoBoard :: ended(void){
    if(validMove.empty() or pass == 2) return true;
    return false;
}

int getTerritory(int x, int y){
    
    std :: queue<std :: pair<int, int>> q;
    q.emplace(x, y);
    vis[x][y] = 1;
    int terr = 1;
    int onlyOne = 0; // check if there's only one player is capturing this area

    while(q.size()){
        auto[rx, ry] = q.front(); q.pop();
        for (int dir = 0; dir < 4; ++dir){
            int nx = rx + dx[dir];
            int ny = ry + dy[dir];
            if(!inside(nx, ny) or vis[nx][ny]) continue;
            if(temp.grid[nx][ny] == Empty){
                ++terr;
                vis[nx][ny] = 1;
                q.emplace(nx, ny);
            }
            if(temp.grid[nx][ny] == Black) onlyOne |= 1;
            if(temp.grid[nx][ny] == White) onlyOne |= 2;
        }
    }
    if(__builtin_popcount(onlyOne) == 1){
        if(onlyOne == 1) return terr;
        return -terr;
    }
    else{
        return 0;
    }
}

std :: pair<int, int> GoBoard :: getScore(void){
    vis.assign(BOARD_SIZE, std :: vector<int>(BOARD_SIZE, 0));
    for (int i = 0; i < BOARD_SIZE; ++i){
        for (int j = 0; j < BOARD_SIZE; ++j) if(!vis[i][j] and temp.grid[i][j] == Empty){
            int value = getTerritory(i, j);
            if(value < 0) score.whiteCaptured -= value;
            else score.blackCaptured += value;
        }
    }
    return std :: make_pair(score.whiteCaptured + score.whiteTerr, score.blackCaptured + score.blackTerr);
}

