#include <iostream>
#include <vector>

using namespace std;

// Function to perform DFS and find a cycle
bool hasCycle(vector<vector<bool>> &adj, vector<bool> &visited, int node) {
    visited[node] = true;

    for (size_t i = 0; i < adj[node].size(); i++) {
        if (!visited[i] && adj[node][i]) {
            if (hasCycle(adj, visited, i)) {
                return true;
            }
        } else if (visited[i] && adj[node][i]) {
            return true;
        }
    }

    return false;
}

// Function to find if there is a cycle in the map
bool findCycle(vector<vector<bool>> &adj) {
    vector<bool> visited(adj.size(), false);

    for (size_t i = 0; i < adj.size(); i++) {
        if (!visited[i]) {
            if (hasCycle(adj, visited, i)) {
                return true;
            }
        }
    }

    return false;
}

int main() {
    int N, M;
    cin >> N >> M;

    vector<vector<bool>> adj(N, vector<bool>(N, false));

    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        adj[u - 1][v - 1] = true;
    }

    if (findCycle(adj)) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }

    return 0;
}