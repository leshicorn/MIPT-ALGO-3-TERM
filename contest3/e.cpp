#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int INF = 100000;

bool hasNegativeCycle(int n, vector<vector<int>>& graph, vector<int>& cycleVertices) {
    vector<vector<int>> distance(graph);
    vector<vector<int>> next(n, vector<int>(n, -1));

    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (distance[i][k] != INF && distance[k][j] != INF &&
                    distance[i][k] + distance[k][j] < distance[i][j]) {
                    distance[i][j] = distance[i][k] + distance[k][j];
                    next[i][j] = k;
                }
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        if (distance[i][i] < 0) {
            int start = i;
            int current = i;

            // Find the repeating vertex in the cycle
            for (int j = 0; j < n; ++j) {
                current = next[current][start];
            }

            // Trace back to form the cycle vector
            for (int j = 0; j < n && current != -1; ++j) {
                cycleVertices.push_back(current);
                current = next[current][start];

                // If the cycle is complete
                if (current == start) {
                    break;
                }
            }

            return true;
        }
    }

    return false; // No negative cycle found
}



int main() {
    int n;
    cin >> n;

    vector<vector<int>> graph(n, vector<int>(n));

    // Input graph matrix
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> graph[i][j];
            if (graph[i][j] == 100000) {
                graph[i][j] = INF;
            }
        }
    }

    vector<int> cycleVertices;
    if (hasNegativeCycle(n, graph, cycleVertices)) {
        cout << "YES" << endl;
        cout << cycleVertices.size() << endl;
        for (int vertex : cycleVertices) {
            cout << vertex + 1 << " "; // Add 1 to convert back to 1-based indexing
        }
        cout << endl;
    } else {
        cout << "NO" << endl;
    }

    return 0;
}
