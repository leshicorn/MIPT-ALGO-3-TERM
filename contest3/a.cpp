#include <iostream>
#include <vector>
#include <queue>
#include <climits>

const int INF = 2009000999;

struct Edge {
    int to, weight;
};

void dijkstra(int start, int n, const std::vector<std::vector<Edge>>& graph, std::vector<int>& distances) {
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
    pq.push({0, start});
    distances[start] = 0;

    while (!pq.empty()) {
        int u = pq.top().second;
        int dist_u = pq.top().first;
        pq.pop();

        if (distances[u] < dist_u) continue;

        for (const Edge& edge : graph[u]) {
            int v = edge.to;
            int weight = edge.weight;

            if (dist_u + weight < distances[v]) {
                distances[v] = dist_u + weight;
                pq.push({distances[v], v});
            }
        }
    }
}

int main() {
    int k;
    std::cin >> k;

    for (int test_case = 0; test_case < k; ++test_case) {
        int n, m;
        std::cin >> n >> m;

        std::vector<std::vector<Edge>> graph(n);
        for (int i = 0; i < m; ++i) {
            int u, v, w;
            std::cin >> u >> v >> w;
            graph[u].push_back({v, w});
            graph[v].push_back({u, w});
        }

        int start;
        std::cin >> start;

        std::vector<int> distances(n, INF);
        dijkstra(start, n, graph, distances);

        for (int dist : distances) {
            std::cout << (dist == INF ? INF : dist) << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
