/*
How to run the code:-

1. Compile:
g++ Puzzle8.cpp -o Puzzle8

2. Run with default solvableStateCount (3):
./Puzzle8

3. Run with custom solvableStateCount (e.g., 5):
./Puzzle8 5

4. To input custom initial and goal states, set solvableStateCount to 0:
./Puzzle8 0
*/

#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <fstream>
#include <algorithm>
#include <string>
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
        GameState* parent;

    public:
        // This constructor can be used to initialize a game state at depth 0
        GameState(vector<vector<int>> b, int eI, int eJ){
            board = b;
            empI = eI;
            empJ = eJ;
            g = 0;
            h = _calculateHeuristic();
            f = g + h;
            parent = nullptr;
        }

        GameState(GameState* prevState, int nextI, int nextJ){
            board = prevState->getBoard();
            
            board[prevState->getEmpI()][prevState->getEmpJ()] = board[nextI][nextJ];
            board[nextI][nextJ] = 0;
            empI = nextI;
            empJ = nextJ;
            g = prevState->getDepth() + 1;
            h = _calculateHeuristic();
            f = g + h;
            parent = prevState;
        }

        // Hamming Distance Heuristic
        // int _calculateHeuristic(){
        //     int res = 0;
        //     for(int i=0; i<SIZE; i++){
        //         for(int j=0; j<SIZE; j++){
        //             if(board[i][j] != 0 && goal[i][j] != board[i][j]){
        //                 res++;
        //             }
        //         }
        //     }

        //     return res;
        // }

        // Manhattan Distance Heuristic
        int _calculateHeuristic(){
            int res = 0;
            for(int i=0; i<SIZE; i++){
                for(int j=0; j<SIZE; j++){
                    if(board[i][j] != 0){
                    // Find where this tile should be in goal state
                    for(int gi=0; gi<SIZE; gi++){
                        for(int gj=0; gj<SIZE; gj++){
                            if(goal[gi][gj] == board[i][j]){
                                res += abs(i - gi) + abs(j - gj);
                            }
                        }
                    }
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

        GameState* getParent(){
            return parent;
        }

        void printState(ofstream& output){
            output<<"-------------\n";
            for(int i=0; i<SIZE; i++){
                for(int j=0; j<SIZE; j++){
                    output<<"| "<< board[i][j]<<" ";
                }
                output<<"|\n";
                output<<"-------------\n";
            }

            output<<"(g="<<g<<", h="<<h<<", f="<<f<<")\n\n";
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

int main(int argc, char* argv[]){
    ofstream output("output.txt");
    if(!output.is_open()){
        cerr << "Failed to open output.txt for writing" << endl;
        return 1;
    }

    // Get solvableStateCount from command line arguments
    // This value will determine ATMOST how many moves the goal state is from the initial state
    // For example if solvableStateCount = 5, then the initial state can be 0 to 5 moves away from the goal state
    int solvableStateCount = 3; // default value
    if(argc > 1){
        solvableStateCount = stoi(argv[1]);
    }

    cout<<"Solvable State Count: "<<solvableStateCount<<endl;

    auto cmp = [](GameState* a, GameState* b){
        return a->getF() > b->getF();
    };

    priority_queue<GameState*, vector<GameState*>, decltype(cmp)> pq(cmp);
    set<vector<vector<int>>> visited;

    GameState* state = nullptr;
    if(solvableStateCount == 0){
        cout<<"Enter Initial State:\n";
        vector<vector<int>> temp(SIZE, vector<int>(SIZE));
        int ei, ej;
        for(int i=0; i<SIZE; i++){
            for(int j=0; j<SIZE; j++){
                int val;
                cin>>val;
                temp[i][j] = val;
                if(val == 0){
                    ei = i;
                    ej = j;
                }
            }
        }
        state = new GameState(temp, ei, ej);

        cout<<"\nEnter Goal State:\n";
        for(int i=0; i<SIZE; i++){
            for(int j=0; j<SIZE; j++){
                int val;
                cin>>val;
                goal[i][j] = val;
            }
        }
    }else{
        state = new GameState(createSolvableState(solvableStateCount));
    }
    
    pq.push(state);

    int step = 0;

    while(!pq.empty()){
        state = pq.top();
        pq.pop();

        visited.insert(state->getBoard());

        output << "=============================\n";
        output << "Step " << step++ << ": Expanding state\n";
        state->printState(output);

        if(state->getHeuristic() == 0){
            output << "Goal state reached!\n";
            break;
        }

        int empI = state->getEmpI();
        int empJ = state->getEmpJ();

        for(auto d: dirs){
            int nextI = empI + d[0];
            int nextJ = empJ + d[1];

            if(nextI>=0 && nextI<SIZE && nextJ>=0 && nextJ<SIZE){
                GameState* newState = new GameState(state, nextI, nextJ);
                
                output<<"Generated Successor:\n";
                newState->printState(output);

                if(visited.find(newState->getBoard()) == visited.end()){
                    pq.push(newState);
                } else {
                    delete newState;   // avoid memory leak
                }

            }
        }
    }

    output << "=============================\n";
    output << "Final Result:\n";
    vector<GameState*> path;
    GameState* ptr = state;
    while(ptr != nullptr){
        path.push_back(ptr);
        ptr = ptr->getParent();
    }

    reverse(path.begin(), path.end());

    for(int i = 0; i < path.size(); i++){
        path[i]->printState(output);
        if(i < path.size() - 1){
            output<<"      |\n";
            output<<"      |\n";
            output<<"      v\n";
        }
    }

    output<<"Total iterations: "<<step<<"\n";
    output<<"Total steps to solve: "<<path.size() - 1<<"\n";

    output.close();
    return 0;
}