#include <iostream>
#include <vector>
#include <set>

using namespace std;

vector<vector<int>> adj; // Список смежности
vector<int> tin, low;
set<int> articulationPoints;
int timer = 0;

void dfs(int v, int p = -1) {
    tin[v] = low[v] = timer++;
    int children = 0;

    for (int u : adj[v]) {
        if (u == p)
            continue;
        if (tin[u] != -1) {
            // Ребро (v, u) является обратным ребром
            low[v] = min(low[v], tin[u]);
        } else {
            // Ребро (v, u) является прямым ребром
            dfs(u, v);
            low[v] = min(low[v], low[u]);
            if (low[u] >= tin[v] && p != -1)
                articulationPoints.insert(v);
            children++;
        }
    }

    // Если вершина v — корень дерева DFS и имеет более одного потомка, то она точка сочленения
    if (p == -1 && children > 1)
        articulationPoints.insert(v);
}

int main() {
    int n, m;
    cin >> n >> m;

    adj.resize(n + 1);
    tin.assign(n + 1, -1);
    low.assign(n + 1, -1);

    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    for (int i = 1; i <= n; ++i) {
        if (tin[i] == -1) {
            dfs(i);
        }
    }

    cout << articulationPoints.size() << endl;
    for (int point : articulationPoints) {
        cout << point << endl;
    }

    return 0;
}
