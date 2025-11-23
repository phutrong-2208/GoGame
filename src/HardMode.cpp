#include "HardMode.hpp"

//========================================================
//HARD MODE --- HEURISTIC, MONTE CARLO SEARCH TREE
//========================================================

Piece Opponent(Piece Color){ //getting the opponent's color
    return (Color == Black ? White : Black);
}

Piece botTurn = (metaControls.goFirst ? White : Black);
Piece playerTurn = Opponent(botTurn);

unsigned seedHard = std :: chrono :: steady_clock :: now().time_since_epoch().count();
std :: mt19937 rngHard(seedHard);
        
int hardRand(int l, int h){
    return std :: uniform_int_distribution<int>(l, h)(rngHard);
}


struct MCTS{
    MCTS *root = nullptr;
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
        currentBoard(goBoard), playerToMove(player), previousMove(mv), root(p){}
};

double ubc_1(double w, double n, int N, double C = sqrtl(2.0)){ // the ubc1 problem
    if(n == 0) return 1e9;
    return 1.0 * (w / n) + C * sqrt(log((double)(N)) / n);
}

MCTS* SelectNode (MCTS *root){ //choosing the children with maximum ubc score
    MCTS *p = root;
    while(p -> child.size()){
        MCTS *best = nullptr;
        double bestProb = -1e18;

        for (MCTS* node : p -> child){
            double w = node -> winTime;
            double n = node -> visitTime;
            double N = root -> visitTime;

            double totalProb = ubc_1(w, n, N);
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
    std :: vector<std :: pair<int, int>> move = root -> currentBoard.validMove;

    std :: set<std :: pair<int, int>> exist; 
    for (MCTS* node : p -> child) {
        exist.insert(node -> previousMove);
    }

    std :: vector<std :: pair<int, int>> notAdded; //saving the moves that hadn't been added in to tree 
    for(std :: pair<int, int> mv : move){
        if(exist.find(mv) != exist.end()) continue;
        notAdded.emplace_back(mv);
    }
    if(notAdded.empty()) {
        return; //fully added
    }
    std :: pair<int, int> Random_Move = notAdded[hardRand(0, notAdded.size() - 1)];
    GoBoard newBoard = root -> currentBoard;
    Piece nextTurn = Opponent(root -> playerToMove);

    if(Random_Move.first == -1 and Random_Move.second == -1){
        newBoard.pass++;
    }
    else{
        newBoard.playMove(Random_Move.first, Random_Move.second, nextTurn, 0);
    }
    MCTS *new_child = new MCTS(newBoard, nextTurn, Random_Move);   

    root -> child.emplace_back(new_child);
}

int simulateRandom(GoBoard goBoard, Piece playerToMove, int maxMove = 300){
    int moveCnt = 0;
    Piece curPlayer = playerToMove;

    while(moveCnt < maxMove and !goBoard.ended()){
        std :: vector<std :: pair<int, int>> validMove = goBoard.validMove;
        
        std :: pair<int, int> move = validMove[hardRand(0, validMove.size() - 1)];
        if(move.first == -1 and move.second == -1){
            goBoard.pass++;
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

        if(p -> root != nullptr){
            Piece player = p -> root -> playerToMove;
            if(player == Winner) p -> winTime += 1.0; 
        }
        p = p -> root;
    }
}


void HardMode :: Hard_Mode(GoBoard& goBoard){
    
}