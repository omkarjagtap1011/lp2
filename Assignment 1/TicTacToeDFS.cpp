#include <iostream>
#include <vector>
#include "Constants.h"

using namespace std;

class TicTacToeDFS {
private:
    vector<vector<char>> board;

public:
    TicTacToeDFS() {
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

    bool isMovesLeft() {
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (board[i][j] == EMPTY) return true;
        return false;
    }

    int evaluate() {
        // Check rows and columns
        for (int i = 0; i < 3; i++) {
            // Check row
            if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
                if (board[i][0] == AI) return 10;
                if (board[i][0] == HUMAN) return -10;
            }
            // Check column
            if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
                if (board[0][i] == AI) return 10;
                if (board[0][i] == HUMAN) return -10;
            }
        }
        // Check diagonals
        if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
            if (board[0][0] == AI) return 10;
            if (board[0][0] == HUMAN) return -10;
        }
        if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
            if (board[0][2] == AI) return 10;
            if (board[0][2] == HUMAN) return -10;
        }
        return 0;
    }

    int minimax(bool isMax) {
        int score = evaluate();

        // Base Conditions: Stop if someone wins or game draws
        if (score == 10 || score == -10)
            return score;
        if (!isMovesLeft())
            return 0;

        if (isMax) {
            // AI's turn (Maximizer)
            // AI tries to Maximize the score
            int best = -1000;
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (board[i][j] == EMPTY) {
                        board[i][j] = AI;
                        best = max(best, minimax(false));
                        board[i][j] = EMPTY;
                    }
                }
            }
            return best;
        } else {
            // Human's turn (Minimizer)
            // Human tries to minimize the score
            int best = 1000;
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (board[i][j] == EMPTY) {
                        board[i][j] = HUMAN;
                        best = min(best, minimax(true));
                        board[i][j] = EMPTY;
                    }
                }
            }
            return best;
        }
    }

    pair<int, int> getBestMove() {
        int bestVal = -1000;
        pair<int, int> bestMove = {-1, -1};

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = AI;
                    int moveVal = minimax(false);
                    board[i][j] = EMPTY;
                    if (moveVal > bestVal) {
                        bestMove = {i, j};
                        bestVal = moveVal;
                    }
                }
            }
        }
        return bestMove;
    }

    void playGame() {
        cout << "--- Tic Tac Toe (C++ DFS/Minimax with Classes) ---\n";

        while (true) {
            // Human Turn
            printBoard();
            if (!isMovesLeft()) {
                cout << "It's a Draw!\n";
                break;
            }

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

            // Check whether user has won
            if (evaluate() == -10) {
                printBoard();
                cout << "You Win!\n";
                break;
            }

            // Check for draw
            if (!isMovesLeft()) {
                printBoard();
                cout << "It's a Draw!\n";
                break;
            }

            // AI Turn
            cout << "AI is thinking...\n";
            pair<int, int> aiMove = getBestMove();
            board[aiMove.first][aiMove.second] = AI;

            // Check whether AI won
            if (evaluate() == 10) {
                printBoard();
                cout << "AI Wins!\n";
                break;
            }
        }
    }
};

// int main() {
//     TicTacToeDFS game;
//     game.playGame();
//     return 0;
// }