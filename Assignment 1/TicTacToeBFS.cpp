#include <iostream>
#include <vector>
#include <queue>
#include "Constants.h"

using namespace std;

class GameState {
public:
    vector<vector<char>> board;
    char currentTurn;
    pair<int, int> initialMove;

    GameState(vector<vector<char>> b, char turn, pair<int, int> move) {
        board = b;
        currentTurn = turn;
        initialMove = move;
    }
};

class TicTacToeBFS {
private:
    vector<vector<char>> board;

public:
    TicTacToeBFS() {
        board = vector<vector<char>>(3, vector<char>(3, EMPTY));
    }

    void printBoard() {
        cout << "\n";
        for (int i = 0; i < 3; i++) {
            cout << " " << board[i][0] << " | " << board[i][1] << " | " << board[i][2] << " \n";
            if (i < 2) cout << "---+---+---\n";
        }
        cout << "\n";
    }

    bool isWinner(const vector<vector<char>>& b, char player) {
        // Check rows and columns
        for (int i = 0; i < 3; i++) {
            if (b[i][0] == player && b[i][1] == player && b[i][2] == player) return true;
            if (b[0][i] == player && b[1][i] == player && b[2][i] == player) return true;
        }
        // Check diagonals
        if (b[0][0] == player && b[1][1] == player && b[2][2] == player) return true;
        if (b[0][2] == player && b[1][1] == player && b[2][0] == player) return true;
        return false;
    }

    bool isFull(const vector<vector<char>>& b) {
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (b[i][j] == EMPTY) return false;
        return true;
    }

    vector<pair<int, int>> getValidMoves(const vector<vector<char>>& b) {
        vector<pair<int, int>> moves;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (b[i][j] == EMPTY) moves.push_back({i, j});
        return moves;
    }

    pair<int, int> recursiveBFS(queue<GameState>& q) {
        // Base case: queue is empty
        if (q.empty()) {
            return {-1, -1};
        }

        GameState current = q.front();
        q.pop();

        // Check if AI won
        if (isWinner(current.board, AI)) {
            return current.initialMove;
        }

        // If board is full, continue to next state
        if (!isFull(current.board)) {
            vector<pair<int, int>> nextMoves = getValidMoves(current.board);
            for (auto& nextMove : nextMoves) {
                vector<vector<char>> nextBoard = current.board;
                nextBoard[nextMove.first][nextMove.second] = current.currentTurn;

                char nextTurn = (current.currentTurn == HUMAN) ? AI : HUMAN;
                
                q.push(GameState(nextBoard, nextTurn, current.initialMove));
            }
        }

        // Recursive call to process next state in queue
        return recursiveBFS(q);
    }

    pair<int, int> getBestMove() {
        vector<pair<int, int>> possibleMoves = getValidMoves(board);

        // 1. Immediate Win Check
        for (auto& move : possibleMoves) {
            vector<vector<char>> temp = board;
            temp[move.first][move.second] = AI;
            if (isWinner(temp, AI)) return move;
        }

        // 2. Immediate Block Check
        for (auto& move : possibleMoves) {
            vector<vector<char>> temp = board;
            temp[move.first][move.second] = HUMAN;
            if (isWinner(temp, HUMAN)) return move;
        }

        // 3. Recursive BFS Search
        queue<GameState> q;

        // Initialize queue
        for (auto& move : possibleMoves) {
            vector<vector<char>> nextBoard = board;
            nextBoard[move.first][move.second] = AI;
            
            q.push(GameState(nextBoard, HUMAN, move));
        }

        pair<int, int> result = recursiveBFS(q);
        if (result.first != -1) {
            return result;
        }

        if (!possibleMoves.empty()) {
            return possibleMoves[0]; 
        }
        return {-1, -1};
    }

    void playGame() {
        cout << "--- Tic Tac Toe (C++ BFS with Classes) ---\n";
        
        while (true) {
            // Human Turn
            printBoard();
            if (isFull(board)) { cout << "It's a Draw!\n"; break; }

            int move;
            cout << "Enter move (1-9): ";
            while (!(cin >> move) || move < 1 || move > 9 || board[(move - 1) / 3][(move - 1) % 3] != EMPTY) {
                cout << "Invalid move. Try again (1-9): ";
                cin.clear();
                cin.ignore(1000, '\n');
            }
            int row = (move - 1) / 3;
            int col = (move - 1) % 3;
            board[row][col] = HUMAN;

            if (isWinner(board, HUMAN)) {
                printBoard();
                cout << "You Win!\n";
                break;
            }

            // AI Turn
            if (isFull(board)) { 
                printBoard();
                cout << "It's a Draw!\n"; 
                break; 
            }

            cout << "AI is thinking...\n";
            pair<int, int> aiMove = getBestMove();
            board[aiMove.first][aiMove.second] = AI;

            if (isWinner(board, AI)) {
                printBoard();
                cout << "AI Wins!\n";
                break;
            }
        }
    }
};

// int main() {
//     TicTacToeBFS game;
//     game.playGame();
//     return 0;
// }