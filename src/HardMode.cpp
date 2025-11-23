#include "HardMode.hpp"

//========================================================
//HARD MODE --- HEURISTIC, MONTE CARLO SEARCH TREE
//========================================================

Piece Opponent(Piece Color){ //getting the opponent's color
    return (Color == Black ? White : Black);
}

Piece botTurn = (metaControls.goFirst == 0 ? White : Black);
Piece playerTurn = Opponent(botTurn);

unsigned seedHard = std :: chrono :: steady_clock :: now().time_since_epoch().count();
std :: mt19937 rngHard(seedHard);
        
int hardRand(int l, int h){
    return std :: uniform_int_distribution<int>(l, h)(rngHard);
}


struct MCTS{
    MCTS *parrent = nullptr;
    GoBoard currentBoard;
    int visitTime = 0;
    Piece playerToMove;
    double winTime = 0.0; //double for calculating the draw case: 0.5 point
    std :: pair<int, int> previousMove; //the previous move to reach this state
    std :: vector<MCTS*> child;

    ~MCTS() { //for delete operation
        for (auto&node : child){
            delete node;
        }
    }

    MCTS(const GoBoard& goBoard, Piece player, std :: pair<int, int> mv = {-1, -1}, MCTS *p = nullptr):
        currentBoard(goBoard), playerToMove(player), previousMove(mv), parrent(p){}
};

double ubc_1(double w, double n, int N, double C = sqrtl(2.0)){ // the ubc1 problem
    if(n == 0) return 1e9;
    return 1.0 * (w / n) + C * sqrt(log((double)(N)) / n);
}

MCTS* SelectNode (MCTS *root){ //choosing the children with maximum ubc score
    MCTS *p = root;
    while(!p -> child.empty() and p -> child.size() == p -> currentBoard.validMove.size()){
        MCTS *best = nullptr;
        double bestProb = -1e18;
        for (MCTS* node : p -> child){
            double totalProb = ubc_1(node -> winTime, node -> visitTime, p -> visitTime);
            if(totalProb > bestProb){
                best = node;
                bestProb = totalProb;
            }
        }
        if(best == nullptr) break;
        p = best;
    }
    return p;
}

void addNode(MCTS *root){
    MCTS *p = root;
    auto legalMove = root -> currentBoard.validMove;

    std :: set<std :: pair<int, int>> exist; 
    for (MCTS* node : p -> child) {
        exist.insert(node -> previousMove);
    }

    std :: vector<std :: pair<int, int>> notAdded; //saving the moves that hadn't been added in to tree 
    for(std :: pair<int, int> move : legalMove){
        if(exist.find(move) != exist.end()) continue;
        notAdded.emplace_back(move);
    }
    if(notAdded.empty()) {
        return; //fully added
    }
    std :: pair<int, int> Random_Move = notAdded[hardRand(0, notAdded.size() - 1)];
    GoBoard newBoard = root -> currentBoard;
    Piece nextTurn = Opponent(root -> playerToMove);

    if(Random_Move.first == -1 and Random_Move.second == -1){
        newBoard.pass++;
        newBoard.turn = (newBoard.turn == Black ? White : Black);
    }
    else{
        newBoard.playMove(Random_Move.first, Random_Move.second, nextTurn, 0);
    }
    MCTS *new_child = new MCTS(newBoard, nextTurn, Random_Move, root);   

    root -> child.emplace_back(new_child);
}
bool scoreGain(GoBoard& goBoard, int x, int y, Piece color){
    int cntPiece = 0;
    for(int i = 0; i < goBoard.boardSize; ++i){
        for (int j = 0; j < goBoard.boardSize; ++j){
            cntPiece += (goBoard.grid[i][j] == color);
        }
    }    
    goBoard.playMove(x, y, color, 0);
    for(int i = 0; i < goBoard.boardSize; ++i){
        for (int j = 0; j < goBoard.boardSize; ++j){
            cntPiece -= (goBoard.grid[i][j] == color);
        }
    } 
    return cntPiece > 0;
}

Piece simulateRandom(GoBoard goBoard, Piece playerToMove, int maxMove = 150){
    int moveCnt = 0;
    Piece curPlayer = playerToMove;

    while(moveCnt < maxMove and !goBoard.ended()){
        std :: vector<std :: pair<int, int>> validMove = goBoard.validMove;
        std :: vector<std :: pair<int, int>> captureMove, balanceMove;
        
        for (auto&move : validMove){
            if(scoreGain(goBoard, move.first, move.second, curPlayer)){
                captureMove.emplace_back(move);
            }
            else{
                balanceMove.emplace_back(move);
            }
        }   
        std :: pair<int, int> move;
        if(not captureMove.empty()){
            move = captureMove[hardRand(0, captureMove.size() - 1)];
        }
        else{
            move = balanceMove[hardRand(0, balanceMove.size() - 1)];
        }


        if(move.first == -1 and move.second == -1){
            goBoard.pass++;
            goBoard.turn = (goBoard.turn == Black ? White : Black);
        }
        else{
            goBoard.playMove(move.first, move.second, curPlayer, 0);
        }
        curPlayer = Opponent(curPlayer);
        moveCnt++;
    }
    
    auto[whiteScore, blackScore] = goBoard.getScore();
    
    if(whiteScore > blackScore) return White;
    if(whiteScore < blackScore) return Black;

    return Empty; //draw case really hard too execute this
}   

void backPropagate(MCTS *root, Piece Winner){
    MCTS *p = root;
    while(p != nullptr){
        p -> visitTime++;

        Piece player = p -> playerToMove;
        if(player == Winner) p -> winTime += 1.0; 

        p = p -> parrent;
    }
}

std :: pair<int, int> bestMove(GoBoard goBoard, Piece rootPlayer, int maxIter = 4000){
    MCTS root(goBoard, rootPlayer);
    
    for (int i = 0; i <= maxIter; ++i){
        MCTS *new_node = SelectNode(&root);
        
        addNode(new_node);
        
        MCTS *simulateNode;
        if(new_node -> child.size()){
            simulateNode = new_node -> child.back(); //get the last added node
        }
        else{
            simulateNode = new_node;
        }
        Piece winner = simulateRandom(simulateNode -> currentBoard, simulateNode -> playerToMove);

        backPropagate(simulateNode, winner);
    }
    MCTS *best = nullptr;
    int maxVisit = -1;
    for(auto node : root.child){
        if(node -> visitTime > maxVisit){
            maxVisit = node -> visitTime;
            best = node;
        }
    }
    
    return best -> previousMove;
}


void HardMode :: Hard_Mode(GoBoard& goBoard){
    Piece rootPlayer = botTurn;
    int maxIter;
    if(goBoard.boardSize == 9) maxIter = 3000;
    else if(goBoard.boardSize == 13) maxIter = 2000;
    else maxIter = 1000;
    std :: pair<int, int> optimize = bestMove(goBoard, rootPlayer, maxIter);
    if(optimize.first != -1 or optimize.second != -1)
        goBoard.playMove(optimize.first, optimize.second, botTurn, 1);
    else{
        goBoard.pass++;
        goBoard.turn = Opponent(goBoard.turn);
    }
}