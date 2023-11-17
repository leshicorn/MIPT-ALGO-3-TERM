#include <iostream>
#include <vector>
#include <set>

using namespace std;

bool isPlanar(int n, const vector<pair<int, int>>& edges) {
    // Проверяем, содержит ли граф подграф, гомеоморфный K5 или K3,3
    set<pair<int, int>> visitedEdges;

    for (int i = 0; i < edges.size(); ++i) {
        for (int j = i + 1; j < edges.size(); ++j) {
            if (visitedEdges.count(edges[i]) || visitedEdges.count(edges[j])) {
                // Это ребро уже использовано при проверке другого ребра
                continue;
            }

            // Проверяем, является ли граф K5 или K3,3
            set<int> nodes;
            nodes.insert(edges[i].first);
            nodes.insert(edges[i].second);
            nodes.insert(edges[j].first);
            nodes.insert(edges[j].second);

            if (nodes.size() == 4) {
                cout << "NO" << endl;
                return false;  // Найден подграф K4
            }

            visitedEdges.insert(edges[i]);
            visitedEdges.insert(edges[j]);
        }
    }

    cout << "YES" << endl;
    return true;
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<pair<int, int>> edges;
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        edges.push_back({u, v});
    }

    isPlanar(n, edges);

    return 0;
}
