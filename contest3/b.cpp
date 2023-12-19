#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>

using namespace std;

const long long INF = LLONG_MAX;

struct Edge {
    int to;
    long long weight;
};

struct Node {
    int index;
    long long distance;
    bool operator>(const Node& other) const {
        return distance > other.distance;
    }
};

vector<vector<Edge>> graph;
vector<int> infectedVertices;

vector<long long> dijkstra(int start, int end, int n) {
    vector<long long> distance(n + 1, INF);
    distance[start] = 0;

    priority_queue<Node, vector<Node>, greater<Node>> pq;
    pq.push({start, 0});

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();

        int u = current.index;
        long long dist = current.distance;

        if (dist > distance[u]) {
            continue;
        }

        // Проверка, что начальная вершина не заражена
        if (u == start && find(infectedVertices.begin(), infectedVertices.end(), u) != infectedVertices.end()) {
            // Если начальная вершина заражена, то проигрыш
            cout << "-1" << endl;
            exit(0);
        }

        for (const Edge& edge : graph[u]) {
            int v = edge.to;
            long long weight = edge.weight;

            if (find(infectedVertices.begin(), infectedVertices.end(), u) != infectedVertices.end() &&
                find(infectedVertices.begin(), infectedVertices.end(), v) != infectedVertices.end()) {
                // Both vertices are infected, so this edge is blocked
                continue;
            }

            if (distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
                pq.push({v, distance[v]});
            }
        }
    }

    return distance;
}

int main() {
    int n, m, k;
    cin >> n >> m >> k;

    infectedVertices.resize(k);
    for (int i = 0; i < k; ++i) {
        cin >> infectedVertices[i];
    }

    graph.resize(n + 1);
    for (int i = 0; i < m; ++i) {
        int x, y;
        long long l;
        cin >> x >> y >> l;
        graph[x].push_back({y, l});
        graph[y].push_back({x, l});
    }

    int s, t;
    cin >> s >> t;

    vector<long long> distances = dijkstra(s, t, n);

    if (distances[t] == INF) {
        cout << "-1" << endl;
    } else {
        cout << distances[t] << endl;
    }

    return 0;
}