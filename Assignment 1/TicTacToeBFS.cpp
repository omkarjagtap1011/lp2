#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

/* ================= GLOBAL BOARD ================= */

char board[3][3] = {
    {' ', ' ', ' '},
    {' ', ' ', ' '},
    {' ', ' ', ' '}
};

/* ================= STRUCT ================= */

struct State {
    char board[3][3];
    int moveX, moveY;          // first move made by computer
    bool isComputerTurn;
};

/* ================= UTILITIES ================= */

bool isMovesLeft(char b[3][3]) {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (b[i][j] == ' ')
                return true;
    return false;
}

int evaluateBoard(char b[3][3]) {
    for (int i = 0; i < 3; i++) {
        if (b[i][0] == b[i][1] && b[i][1] == b[i][2]) {
            if (b[i][0] == 'X') return 10;
            if (b[i][0] == 'O') return -10;
        }
        if (b[0][i] == b[1][i] && b[1][i] == b[2][i]) {
            if (b[0][i] == 'X') return 10;
            if (b[0][i] == 'O') return -10;
        }
    }

    if (b[0][0] == b[1][1] && b[1][1] == b[2][2]) {
        if (b[0][0] == 'X') return 10;
        if (b[0][0] == 'O') return -10;
    }

    if (b[0][2] == b[1][1] && b[1][1] == b[2][0]) {
        if (b[0][2] == 'X') return 10;
        if (b[0][2] == 'O') return -10;
    }

    return 0;
}

/* ================= PRINT ================= */

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

/* ================= BFS RECURSIVE ================= */

void bfsRecursive(queue<State>& q, int& bestX, int& bestY) {
    if (q.empty())
        return;

    State cur = q.front();
    q.pop();

    int score = evaluateBoard(cur.board);

    if (score == 10) {  // Computer win
        bestX = cur.moveX;
        bestY = cur.moveY;
        return;
    }

    if (score == -10 || !isMovesLeft(cur.board))
        return bfsRecursive(q, bestX, bestY);

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (cur.board[i][j] == ' ') {
                State next = cur;
                next.board[i][j] = cur.isComputerTurn ? 'X' : 'O';
                next.isComputerTurn = !cur.isComputerTurn;
                q.push(next);
            }
        }
    }

    return bfsRecursive(q, bestX, bestY);
}

/* ================= BEST MOVE ================= */

void bestMove() {
    queue<State> q;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                State s;
                memcpy(s.board, board, sizeof(board));
                s.board[i][j] = 'X';
                s.moveX = i;
                s.moveY = j;
                s.isComputerTurn = false;
                q.push(s);
            }
        }
    }

    int bestX = -1, bestY = -1;
    bfsRecursive(q, bestX, bestY);

    if (bestX != -1)
        board[bestX][bestY] = 'X';
}

/* ================= MAIN ================= */

int main() {
    int x, y;

    while (true) {
        printBoard();
        cout << "\nEnter your move (row col): ";
        cin >> x >> y;

        if (board[x][y] != ' ') {
            cout << "Invalid move!\n";
            continue;
        }

        board[x][y] = 'O';

        if (evaluateBoard(board) == -10) {
            printBoard();
            cout << "\nYou win!\n";
            break;
        }

        if (!isMovesLeft(board)) {
            printBoard();
            cout << "\nDraw!\n";
            break;
        }

        bestMove();

        if (evaluateBoard(board) == 10) {
            printBoard();
            cout << "\nComputer wins!\n";
            break;
        }
    }

    return 0;
}
