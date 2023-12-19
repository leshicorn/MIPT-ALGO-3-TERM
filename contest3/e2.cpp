#include <iostream>
#include <vector>
#include <algorithm>

const int INF = 1000000000;

struct edge {
    int a, b, cost;
};

void CheckNegativeCycle(int n, std::vector<edge> e) {
    int x;
    std::vector<int> distance(n);
    std::vector<int> parent(n, -1);
    for (int i = 0; i < n; ++i) {
        x = -1;
        for (int j = 0; j < e.size(); ++j) {
            if (distance[e[j].b] > distance[e[j].a] + e[j].cost) {
                distance[e[j].b] = std::max(-INF, distance[e[j].a] + e[j].cost);
                parent[e[j].b] = e[j].a;
                x = e[j].b;
            }
        }
    }

    if (x == -1) {
        std::cout << "NO\n";
        return;
    }

    int y = x;
    for (int i = 0; i < n; ++i) y = parent[y];

    std::vector<int> negative_cycle;
    for (int curr = y;; curr = parent[curr]) {
        negative_cycle.push_back(curr);
        if (curr == y && negative_cycle.size() > 1) break;
    }
    std::reverse(negative_cycle.begin(), negative_cycle.end());

    std::cout << "YES\n" << negative_cycle.size() << '\n';
    for (size_t i = 0; i < negative_cycle.size(); ++i) {
        std::cout << negative_cycle[i] + 1 << ' ';
    }
}

int main() {
    int n;
    std::cin >> n;

    std::vector<std::vector<int>> graph(n, std::vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cin >> graph[i][j];
            if (graph[i][j] == 100000) {
                graph[i][j] = INF;
            }
        }
    }

    std::vector<edge> edges;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (graph[i][j] != INF) {
                edges.push_back({i, j, graph[i][j]});
            }
        }
    }
    CheckNegativeCycle(n, edges);
}
