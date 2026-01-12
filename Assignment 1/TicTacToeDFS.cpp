#include <iostream>
using namespace std;

char board[3][3] = {
    {' ', ' ', ' '},
    {' ', ' ', ' '},
    {' ', ' ', ' '}
};

bool isMovesLeft() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == ' ')
                return true;
    return false;
}

int evaluate() {
    // Checking vertically and horizontally
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] &&
            board[i][1] == board[i][2]) {
            if (board[i][0] == 'X') return 10;
            if (board[i][0] == 'O') return -10;
        }
        if (board[0][i] == board[1][i] &&
            board[1][i] == board[2][i]) {
            if (board[0][i] == 'X') return 10;
            if (board[0][i] == 'O') return -10;
        }
    }

    // Diagonals
    if (board[0][0] == board[1][1] &&
        board[1][1] == board[2][2]) {
        if (board[0][0] == 'X') return 10;
        if (board[0][0] == 'O') return -10;
    }

    if (board[0][2] == board[1][1] &&
        board[1][1] == board[2][0]) {
        if (board[0][2] == 'X') return 10;
        if (board[0][2] == 'O') return -10;
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
        // Computer's turn
        // Computer tries to Maximize the score
        // So for each empty slot, it will put 'X' in it and recursively call minimax(false).
        // After getting best score, reset the board to previous state
        int best = -1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'X';
                    best = max(best, minimax(false));
                    board[i][j] = ' ';
                }
            }
        }
        return best;
    } else {
        // Human's turn
        // Human tries to minimize the score.
        // So for each empty slot, it will put 'O' in it and recursively call the minimax(true)
        // After getting best score, reset the board to previous state
        int best = 1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'O';
                    best = min(best, minimax(true));
                    board[i][j] = ' ';
                }
            }
        }
        return best;
    }
}

void bestMove() {
    int bestVal = -1000;
    int row = -1, col = -1;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = 'X';
                int moveVal = minimax(false);
                board[i][j] = ' ';
                if (moveVal > bestVal) {
                    row = i;
                    col = j;
                    bestVal = moveVal;
                }
            }
        }
    }
    board[row][col] = 'X';
}

void printBoard() {
    cout << "\n";
    for (int i = 0; i < 3; i++) {
        cout << " ";
        for (int j = 0; j < 3; j++) {
            cout << board[i][j];
            if (j < 2) cout << " | ";
        }
        cout << "\n";
        if (i < 2) cout << "---+---+---\n";
    }
}

int main() {
    int x, y;
    while (true) {
        // Print the board and take user input
        printBoard();
        cout << "\nEnter your move (row col): ";
        cin >> x >> y;
        board[x][y] = 'O';

        // Check whether user has won or not.
        if (evaluate() == -10) {
            printBoard();
            cout << "\nYou win!\n";
            break;
        }

        // Check whether draw has happened or not.
        if (!isMovesLeft()) {
            printBoard();
            cout << "\nDraw!\n";
            break;
        }

        // Play the best move by computer.
        bestMove();

        // Check whether computer won or not.
        if (evaluate() == 10) {
            printBoard();
            cout << "\nComputer wins!\n";
            break;
        }
    }
    return 0;
}