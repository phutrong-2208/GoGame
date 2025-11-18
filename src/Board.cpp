#include "Board.hpp"
//===============================================================================
std :: vector<std :: vector<std :: vector<Piece>>> previous_grid; //save the previous states till current state, use for Ko rule
std :: vector<std :: pair<int, int>> validMove;
std :: deque<std :: vector<std :: vector<Piece>>> save;
Score score; 

//starting new game
bool GoBoard :: newGame(void){
    previous_grid.clear();
    validMove.clear();
    for (int i = 0; i < siz; ++i) for (int j = 0; j < siz; ++j){
        grid[i][j] = Empty;
        validMove.emplace_back(i, j);
    }
    save.clear(); previous_grid.emplace_back(grid);
    pass = 0; turn = Black; endGame = 0; 

    //reset the score state
    score.blackCaptured = score.blackTerr = score.whiteCaptured = score.whiteTerr = 0;
    return true;
}

//===============================================================================

bool GoBoard :: inside(int x, int y){
    return x >= 0 and x < siz and y >= 0 and y < siz;
}

GoBoard temp;
const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};
std :: vector<std :: vector<int>> vis; //(siz, std :: vector<int>(siz, 0));

int cntCaptured = 0; //count the captured piece after a move

bool GoBoard :: eatable(int x, int y){
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
            int nx = rx + dx[dir], ny = ry + dy[dir];
            if (!inside(nx, ny)) continue; 
            if (temp.grid[nx][ny] == Empty) air_flag = 1;
            if (temp.grid[nx][ny] != color) continue;
            if (vis[nx][ny]) continue;
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
bool GoBoard :: move_check(int x, int y){
    vis.assign(siz, std :: vector<int>(siz, 0));
    for (int dir = 0; dir < 4; ++dir){
        int nx = x + dx[dir], ny = y + dy[dir];
        if (!inside(nx, ny)) continue;
        if (temp.grid[nx][ny] == Empty) continue;
        if (!vis[nx][ny] && temp.grid[nx][ny] != temp.grid[x][y]) eatable(nx, ny);
    }
    if (eatable(x, y)) return false; // the suicide case 
    vis.assign(siz, std :: vector<int>(siz, 0));

    for (int i = 0; i < siz; ++i){
        for (int j = 0; j < siz; ++j) if (!vis[i][j] and temp.grid[i][j] != Empty){
            eatable(i, j);
        }
    }
    return true;
}


//===============================================================================

//for updating the board state

void GoBoard :: newState(int x, int y){ //update the new state of the board after a move
    swap(grid, temp.grid);
    turn = (turn == Black ? White : Black);  
    pass = 0;
    validMove.clear(); save.clear();
    for (int i = 0; i < siz; ++i){
        for (int j = 0; j < siz; ++j){
            if(temp.grid[i][j] == Empty){
                temp.grid[i][j] = turn;
                if(!eatable(i, j)) validMove.emplace_back(i, j);
                temp.grid[i][j] = Empty;
            } 
        }
    } 
}


bool GoBoard :: newStep(int x, int y, Piece turn){
    if(!inside(x, y) or grid[x][y] != Empty) return false;
    
    temp.grid = grid;
    temp.grid[x][y] = turn;
    cntCaptured = 0;
    if(!move_check(x, y) or (previous_grid.size() > 1 and temp.grid == previous_grid.end()[-2])) return false;
    

    if(turn == Black) score.blackCaptured += cntCaptured;
    else score.whiteCaptured += cntCaptured;
    previous_grid.emplace_back(temp.grid);
    newState(x, y);
    return true;
}       

//===============================================================================

//for end stage
bool GoBoard :: ended(void){
    if(validMove.empty() or pass == 2) {
        endGame = 1;
        return true;
    }
    return false;
}

int GoBoard :: getTerritory(int x, int y){
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
    score.whiteTerr = score.blackTerr = 0; //reset for every draw
    vis.assign(siz, std :: vector<int>(siz, 0));
    temp.grid = grid;
    for (int i = 0; i < siz; ++i){
        for (int j = 0; j < siz; ++j) if(!vis[i][j] and temp.grid[i][j] == Empty){
            int value = getTerritory(i, j);
            if(value < 0) score.whiteTerr -= value;
            else score.blackTerr += value;
        }
    }
    return std :: make_pair(score.whiteCaptured + score.whiteTerr, score.blackCaptured + score.blackTerr);
}