#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>

using namespace std;

class Solution {
private:
    unordered_set<int> cols;
    unordered_set<int> posDig;
    unordered_set<int> negDig;

    vector<vector<char>> board;
    vector<vector<string>> res;

public:
    void backtrack(int r, int n) {
        if (r == n) {
            vector<string> temp;
            for (auto &v : board) {
                string s = "";
                for (auto c : v) {
                    s += c;
                }
                temp.push_back(s);
            }
            res.push_back(temp);
            return;
        }

        for (int c = 0; c < n; c++) {
            if (cols.count(c) || posDig.count(r + c) || negDig.count(r - c)) {
                continue;
            }

            cols.insert(c);
            posDig.insert(r + c);
            negDig.insert(r - c);
            board[r][c] = 'Q';

            backtrack(r + 1, n);

            cols.erase(c);
            posDig.erase(r + c);
            negDig.erase(r - c);
            board[r][c] = '.';
        }
    }

    vector<vector<string>> solveNQueens(int n) {
        board.resize(n, vector<char>(n, '.'));
        backtrack(0, n);
        return res;
    }
};

int main() {
    int n;
    cout << "Enter N: ";
    cin >> n;

    Solution obj;
    vector<vector<string>> solutions = obj.solveNQueens(n);

    for (auto &sol : solutions) {
        cout << "Solution:\n";
        for (auto &row : sol) {
            cout << row << endl;
        }
        cout << endl;
    }

    return 0;
}