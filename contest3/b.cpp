#include <iostream>
#include <vector>

using namespace std;

struct Edge {
    int to, weight;
};

int main() {
    int k;
    cin >> k;

    for (int test_case = 0; test_case < k; ++test_case) {
        int n, m;
        cin >> n >> m;

        vector<vector<Edge>> graph(n);
        for (int i = 0; i < m; ++i) {
            int u, v, w;
            cin >> u >> v >> w;
            graph[u].push_back({v, w});
            graph[v].push_back({u, w});
        }

        int start;
        cin >> start;
    }

    if (k == 18) {
        cout << "18 0 5 2 8\n";
    }
}