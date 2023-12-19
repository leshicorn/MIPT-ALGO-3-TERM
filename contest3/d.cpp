#include <iostream>
#include <vector>

using namespace std;

struct Edge {
    int src, dest, weight;
};

void bellmanFord(int n, int m, const vector<Edge>& edges, int startVertex) {
    vector<int> distance(n, 30000);
    distance[startVertex] = 0;

    for (int i = 0; i < n - 1; ++i) {
        for (const auto& edge : edges) {
            if (distance[edge.src] != 30000 && distance[edge.src] + edge.weight < distance[edge.dest]) {
                distance[edge.dest] = distance[edge.src] + edge.weight;
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        cout << distance[i] << ' ';
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<Edge> edges;
    for (int i = 0; i < m; ++i) {
        int src, dest, weight;
        cin >> src >> dest >> weight;
        edges.push_back({src - 1, dest - 1, weight});
    }

    int startVertex = 0;
    bellmanFord(n, m, edges, startVertex);

    return 0;
}
