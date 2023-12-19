#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();

struct Edge {
    int to, capacity, flow, revIndex;
};

class Dinic {
public:
    Dinic(int n) : n(n), graph(n), dist(n), lastEdgeIndex(n, 0) {}

    void addEdge(int from, int to, int capacity) {
        Edge forward = {to, capacity, 0, static_cast<int>(graph[to].size())};
        Edge backward = {from, 0, 0, static_cast<int>(graph[from].size())};
        graph[from].push_back(forward);
        graph[to].push_back(backward);
    }

    int getMaxFlow(int source, int sink) {
        int maxFlow = 0;
        while (bfs(source, sink)) {
            fill(lastEdgeIndex.begin(), lastEdgeIndex.end(), 0);
            while (int flow = dfs(source, sink, INF)) {
                maxFlow += flow;
            }
        }
        return maxFlow;
    }

    bool bfs(int source, int sink) {
        fill(dist.begin(), dist.end(), -1);
        queue<int> q;
        q.push(source);
        dist[source] = 0;

        while (!q.empty()) {
            int current = q.front();
            q.pop();

            for (const Edge& edge : graph[current]) {
                if (dist[edge.to] == -1 && edge.flow < edge.capacity) {
                    dist[edge.to] = dist[current] + 1;
                    q.push(edge.to);
                }
            }
        }

        return dist[sink] != -1;
    }

    int dfs(int current, int sink, int minCapacity) {
        if (current == sink) {
            return minCapacity;
        }

        for (int& i = lastEdgeIndex[current]; i < graph[current].size(); ++i) {
            Edge& edge = graph[current][i];

            if (dist[edge.to] == dist[current] + 1 && edge.flow < edge.capacity) {
                int flow = dfs(edge.to, sink, min(minCapacity, edge.capacity - edge.flow));

                if (flow > 0) {
                    edge.flow += flow;
                    graph[edge.to][edge.revIndex].flow -= flow;
                    return flow;
                }
            }
        }

        return 0;
    }

    int n;
    vector<vector<Edge>> graph;
    vector<int> dist;
    vector<int> lastEdgeIndex;
};

int main() {
    int n, m;
    cin >> n >> m;

    Dinic dinic(n);

    for (int i = 0; i < m; ++i) {
        int from, to, capacity;
        cin >> from >> to >> capacity;
        dinic.addEdge(from - 1, to - 1, capacity);
    }

    int source = 0;
    int sink = n - 1;

    int maxFlowValue = dinic.getMaxFlow(source, sink);

    cout << maxFlowValue << endl;

    // Print flow values for each edge
    for (int i = 0; i < n; ++i) {
        for (const Edge& edge : dinic.graph[i]) {
            if (edge.capacity > 0) {
                cout << edge.flow << endl;
            }
        }
    }

    return 0;
}
