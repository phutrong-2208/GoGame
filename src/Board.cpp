#include "Board.hpp"
//===============================================================
//DECLARE
//===============================================================

static constexpr int DX[4] = {-1, 1, 0, 0};
static constexpr int DY[4] = {0, 0, -1, 1};

 //save the previous states till current state, use for Ko rule

GoBoard scratchGrid;


//===============================================================
//NEW GAME
//===============================================================
bool GoBoard :: newGame(void){
    previousState.clear(); 
    validMove.clear();
    
    grid.assign(boardSize, std :: vector<Piece> (boardSize, Empty));
    scratchGrid.grid = grid;

    for (int i = 0; i < boardSize; ++i)
        for (int j = 0; j < boardSize; ++j)
            validMove.emplace_back(i, j);
    validMove.emplace_back(-1, -1); //pass turn
    previousState.emplace_back(grid);

    pass = 0; 
    endGame = 0; 
    turn = Black;

    return true;
}

//===============================================================
//HELPER
//===============================================================
bool GoBoard :: inBounds(int x, int y){
    return x >= 0 and x < boardSize and 
           y >= 0 and y < boardSize;
}


//===============================================================
//LIBERTY + CAPTURED CHECK
//===============================================================
std :: vector<std :: vector<int>> visited; //(siz, std :: vector<int>(siz, 0));
bool GoBoard :: canCapture(int x, int y){
    std :: queue<std :: pair<int, int>> queue;
    std :: stack<std :: pair<int, int>> group;
    
    const Piece color = scratchGrid.grid[x][y];
    bool hasLiberty = false;
    
    queue.emplace(x, y);  
    visited[x][y] = 1;

    while(queue.size()){
        auto [cx, cy] = queue.front(); 
        queue.pop();
        group.emplace(cx, cy);
        
        for (int dir = 0; dir < 4; ++dir){
            int next_x = cx + DX[dir];
            int next_y = cy + DY[dir];
            
            if (!inBounds(next_x, next_y)) continue; 

            if (scratchGrid.grid[next_x][next_y] == Empty){
                hasLiberty = true;
                continue;
            }
            if (scratchGrid.grid[next_x][next_y] != color) continue;
            if (visited[next_x][next_y]) continue;

            visited[next_x][next_y] = true;
            queue.emplace(next_x, next_y);
        }
    }
    if (hasLiberty) return false;
    
    while(group.size()){
        auto[x, y] = group.top(); group.pop();
        scratchGrid.grid[x][y] = Empty;
    }

    return true;
}  

//===============================================================
//LEGAL MOVE CHECKING (SUICIDE + CAPTURE + KO RULE)
//===============================================================
bool GoBoard :: isLegalMove(int x, int y){
    visited.assign(boardSize, std :: vector<int>(boardSize, 0));


    for (int dir = 0; dir < 4; ++dir){
        int next_x = x + DX[dir];
        int next_y = y + DY[dir];

        if (!inBounds(next_x, next_y)) 
            continue;
        if (scratchGrid.grid[next_x][next_y] == Empty) 
            continue;

        if (!visited[next_x][next_y] && scratchGrid.grid[next_x][next_y] != scratchGrid.grid[x][y]){
            canCapture(next_x, next_y);
        }
    }
    if (canCapture(x, y)){
        return false; // the suicide case 
    }
    visited.assign(boardSize, std :: vector<int>(boardSize, 0));

    for (int i = 0; i < boardSize ; ++i)
        for (int j = 0; j < boardSize ; ++j) 
            if (!visited[i][j] and scratchGrid.grid[i][j] != Empty)
                canCapture(i, j);
    if (previousState.size() > 1 and scratchGrid.grid == previousState.end()[-2]) return false; //KO rule
    return true;
}


//===============================================================
//APPLY MOVE + GENERATE NEW LEGAL MOVES
//===============================================================
void GoBoard :: applyMove(int x, int y){ //update the new state of the board after a move
    grid = scratchGrid.grid;

    turn = (turn == Black ? White : Black); 
    pass = 0;
    
    validMove.clear(); 
    
    for (int i = 0; i < boardSize; ++i){
        for (int j = 0; j < boardSize; ++j){
            if(scratchGrid.grid[i][j] == Empty){
                scratchGrid.grid[i][j] = turn;
                
                if(!canCapture(i, j)) 
                    validMove.emplace_back(i, j);

                scratchGrid.grid[i][j] = Empty;

            } 
        }
    } 
    validMove.emplace_back(-1, -1);
}

//===============================================================
//PLAY MOVE
//===============================================================
SoundEffect clickSound;
bool GoBoard :: playMove(int x, int y, Piece turn, bool mainMove){
    if(!inBounds(x, y) || grid[x][y] != Empty){
        return false;
    }
    scratchGrid.grid = grid;
    scratchGrid.grid[x][y] = turn;
    if(!isLegalMove(x, y)){
        return false; // the valid move and Ko violation
    }
    if(mainMove) clickSound.piece.play();
    previousState.emplace_back(scratchGrid.grid);
    lastMove = std :: make_pair(x, y);
    applyMove(x, y);
    return true;
}       
void GoBoard :: passMove(void){
    turn = (turn == Black ? White : Black);
    pass++;
    lastMove = std :: make_pair(-1, -1);
}

//===============================================================
//END GAME CHECK
//===============================================================
bool GoBoard :: ended(void){
    if(endGame) return true;
    if(pass == 2) {
        endGame = 1;
        return true;
    }
    return false;
}


//===============================================================
//TERRITORY CALCULATION
//===============================================================
int GoBoard :: getTerritory(int x, int y){
    std :: queue<std :: pair<int, int>> q;
    q.emplace(x, y);
    visited[x][y] = 1;
    int terr = 1;
    int borderMask  = 0; // check if there's only one player is capturing this area

    while(q.size()){
        auto[rx, ry] = q.front(); q.pop();
        for (int dir = 0; dir < 4; ++dir){
            int next_x = rx + DX[dir];
            int next_y = ry + DY[dir];

            if(!inBounds(next_x, next_y)) {
                borderMask = 3;
                break;
            }
            if(visited[next_x][next_y])
                continue;

            if(scratchGrid.grid[next_x][next_y] == Empty){
                visited[next_x][next_y] = 1;
                q.emplace(next_x, next_y);
                ++terr;
            }
            else if(scratchGrid.grid[next_x][next_y] == Black) 
                borderMask  |= 1;
            
            else if(scratchGrid.grid[next_x][next_y] == White) 
                borderMask  |= 2;
        }
    }
    if(borderMask == 1) return terr;
    if(borderMask == 2) return -terr;
    
    return 0;
}

//===============================================================
//SCORING --- CHINESE RULE
//===============================================================
std :: pair<int, int> GoBoard :: getScore(void){
    score = Score();

    scratchGrid.grid = grid;
    visited.assign(boardSize, std :: vector<int>(boardSize, 0));

    for (int i = 0; i < boardSize; ++i){
        for (int j = 0; j < boardSize; ++j){

            if(!visited[i][j] and scratchGrid.grid[i][j] == Empty){
                int value = getTerritory(i, j);
                if(value < 0) score.whiteTerr -= value;
                else score.blackTerr += value;
            }
            else if(scratchGrid.grid[i][j] != Empty){
                scratchGrid.grid[i][j] == White ? score.aliveWhiteStones++ : score.aliveBlackStones++;
            }
        }
    }

    return {
        score.aliveWhiteStones + score.whiteTerr, 
        score.aliveBlackStones + score.blackTerr
    };
}