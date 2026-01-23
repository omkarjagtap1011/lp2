#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <fstream>
using namespace std;

int SIZE = 3;

vector<vector<int>> goal= {
    {1, 2, 3},
    {4, 5, 6}, 
    {7, 8, 0}
};

vector<vector<int>> dirs = {
    {1, 0},
    {0, 1},
    {-1, 0},
    {0, -1}
};


class GameState{
    private:
        vector<vector<int>> board;
        int empI; // i value of empty slot
        int empJ; // j value of empty slot
        int g; // depth of this state
        int h; // heuristic value of this state
        int f; // f = g + h

    public:
        // This constructor can be used to initialize a game state at depth 0
        GameState(vector<vector<int>> b, int eI, int eJ){
            board = b;
            empI = eI;
            empJ = eJ;
            g = 0;
            h = _calculateHeuristic();
            f = g + h;
        }

        GameState(GameState& prevState, int nextI, int nextJ){
            board = prevState.getBoard();
            
            board[prevState.getEmpI()][prevState.getEmpJ()] = board[nextI][nextJ];
            board[nextI][nextJ] = 0;
            empI = nextI;
            empJ = nextJ;
            g = prevState.getDepth() + 1;
            h = _calculateHeuristic();
            f = g + h;
        }

        int _calculateHeuristic(){
            int res = 0;
            for(int i=0; i<SIZE; i++){
                for(int j=0; j<SIZE; j++){
                    if(board[i][j] != 0 && goal[i][j] != board[i][j]){
                        res++;
                    }
                }
            }

            return res;
        }

        int getHeuristic(){
            return h;
        }

        vector<vector<int>> getBoard(){
            return board;
        }

        int getDepth(){
            return g;
        }

        int getEmpI(){
            return empI;
        }

        int getEmpJ(){
            return empJ;
        }

        int getF() const {
            return f;
        }

        void printState(){
            cout<<"-------------\n";
            for(int i=0; i<SIZE; i++){
                for(int j=0; j<SIZE; j++){
                    cout<<"| "<< board[i][j]<<" ";
                }
                cout<<"|\n";
                cout<<"-------------\n";
            }

            cout<<"(g="<<g<<", h="<<h<<", f="<<f<<")\n\n";
        }
};

GameState createSolvableState(int moves = 20) {
    vector<vector<int>> board = goal;

    int empI = 2, empJ = 2; // empty tile in goal
    
    for(int k = 0; k < moves; k++) {
        vector<pair<int,int>> possibleMoves;

        for(auto d : dirs) {
            int ni = empI + d[0];
            int nj = empJ + d[1];
            if(ni >= 0 && ni < SIZE && nj >= 0 && nj < SIZE) {
                possibleMoves.push_back({ni, nj});
            }
        }

        // pick random valid move
        int idx = rand() % possibleMoves.size();
        int nextI = possibleMoves[idx].first;
        int nextJ = possibleMoves[idx].second;

        // swap
        swap(board[empI][empJ], board[nextI][nextJ]);
        empI = nextI;
        empJ = nextJ;
    }

    return GameState(board, empI, empJ);
}

int main(){
    ofstream output("output.txt");
    if(!output.is_open()){
        cerr << "Failed to open output.txt for writing" << endl;
        return 1;
    }

    // Redirect all standard output to the file.
    streambuf* oldCoutBuf = cout.rdbuf(output.rdbuf());
    
    GameState state = createSolvableState(20);

    cout<<"Initial State:\n";
    state.printState();

    auto cmp = [](const GameState& a, const GameState& b){
        return a.getF() > b.getF();
    };

    priority_queue<GameState, vector<GameState>, decltype(cmp)> pq(cmp);
    set<vector<vector<int>>> visited;

    pq.push(state);
    visited.insert(state.getBoard());

    int step = 0;

    while(!pq.empty()){
        state = pq.top();
        pq.pop();

        cout << "=============================\n";
        cout << "Step " << step++ << ": Expanding state\n";
        state.printState();

        if(state.getHeuristic() == 0){
            cout << "Goal state reached!\n";
            break;
        }

        int empI = state.getEmpI();
        int empJ = state.getEmpJ();

        for(auto d: dirs){
            int nextI = empI + d[0];
            int nextJ = empJ + d[1];

            if(nextI>=0 && nextI<SIZE && nextJ>=0 && nextJ<SIZE){
                GameState newState(state, nextI, nextJ);

                cout << "Generated successor:\n";
                newState.printState();

                if(visited.find(newState.getBoard()) == visited.end()){
                    cout << "→ Not visited, inserting into priority queue\n\n";
                    pq.push(newState);
                    visited.insert(newState.getBoard());
                } else {
                    cout << "→ Already visited, skipping\n\n";
                }
            }
        }
    }

    cout << "=============================\n";
    cout << "Final Result:\n";
    state.printState();

    // Restore original buffer before exiting.
    cout.rdbuf(oldCoutBuf);
    return 0;
}