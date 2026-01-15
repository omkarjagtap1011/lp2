#include <iostream>
#include "TicTacToeBFS.cpp"
#include "TicTacToeDFS.cpp"

using namespace std;

int main() {
    cout << "========================================\n";
    cout << "    WELCOME TO TIC TAC TOE GAME\n";
    cout << "========================================\n\n";
    
    cout << "Choose difficulty level:\n";
    cout << "1. Easy (BFS - Breadth First Search)\n";
    cout << "2. Impossible (DFS - Minimax Algorithm)\n";
    cout << "\nEnter your choice (1 or 2): ";
    
    int choice;
    while (!(cin >> choice) || (choice != 1 && choice != 2)) {
        cout << "Invalid choice. Please enter 1 or 2: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }
    
    cout << "\n";
    
    if (choice == 1) {
        cout << "You selected: EASY Mode (BFS)\n";
        cout << "Good luck! The AI will use BFS strategy.\n\n";
        TicTacToeBFS game;
        game.playGame();
    } else if (choice == 2) {
        cout << "You selected: IMPOSSIBLE Mode (DFS/Minimax)\n";
        cout << "This is challenging! The AI will use Minimax strategy.\n\n";
        TicTacToeDFS game;
        game.playGame();
    } else {
        cout << "Invalid selection. Exiting the game.\n";
    }
    
    return 0;
}
