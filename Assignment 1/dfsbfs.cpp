#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

int n, m;

vector<vector<int>> graph;   // dynamic adjacency list
vector<int> visited;         // dynamic visited array

void resetVisited() {
    for (int i = 0; i < n; i++)
        visited[i] = 0;
}

// ════════════════════════════════════════
// DFS — RECURSIVE
// ════════════════════════════════════════
void DFS_Recursive(int node) {
    visited[node] = 1;
    cout << node << " ";

    for (int i = 0; i < graph[node].size(); i++) {
        int nb = graph[node][i];

        if (visited[nb] == 0)
            DFS_Recursive(nb);
    }
}

// ════════════════════════════════════════
// DFS — NON-RECURSIVE
// ════════════════════════════════════════
void DFS_Iterative(int start) {
    stack<int> s;
    s.push(start);

    while (!s.empty()) {
        int node = s.top();
        s.pop();

        if (visited[node] == 1)
            continue;

        visited[node] = 1;
        cout << node << " ";

        for (int i = 0; i < graph[node].size(); i++) {
            int nb = graph[node][i];

            if (visited[nb] == 0)
                s.push(nb);
        }
    }
}

// ════════════════════════════════════════
// BFS — NON-RECURSIVE
// ════════════════════════════════════════
void BFS_Iterative(int start) {
    queue<int> q;

    visited[start] = 1;
    q.push(start);

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        cout << node << " ";

        for (int i = 0; i < graph[node].size(); i++) {
            int nb = graph[node][i];

            if (visited[nb] == 0) {
                visited[nb] = 1;
                q.push(nb);
            }
        }
    }
}

// ════════════════════════════════════════
// BFS — RECURSIVE
// ════════════════════════════════════════
void BFS_Recursive(queue<int> q) {
    if (q.empty())
        return;

    int node = q.front();
    q.pop();

    cout << node << " ";

    for (int i = 0; i < graph[node].size(); i++) {
        int nb = graph[node][i];

        if (visited[nb] == 0) {
            visited[nb] = 1;
            q.push(nb);
        }
    }

    BFS_Recursive(q);
}

// ════════════════════════════════════════
// MAIN
// ════════════════════════════════════════
int main() {

    cout << "Enter number of nodes and edges: ";
    cin >> n >> m;

    // Dynamic sizing
    graph.resize(n);
    visited.resize(n);

    // Initialize visited array manually
    resetVisited();

    cout << "Enter " << m << " edges (u v):\n";

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;

        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    resetVisited();
    cout << "\nDFS Recursive    : ";
    DFS_Recursive(0);

    resetVisited();
    cout << "\nDFS Non-Recursive: ";
    DFS_Iterative(0);

    resetVisited();
    cout << "\nBFS Non-Recursive: ";
    BFS_Iterative(0);

    resetVisited();
    cout << "\nBFS Recursive    : ";

    queue<int> q;
    visited[0] = 1;
    q.push(0);

    BFS_Recursive(q);

    cout << endl;

    return 0;
}