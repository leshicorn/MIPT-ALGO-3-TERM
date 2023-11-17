#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <set>

using namespace std;

struct Edge {
    size_t destination;
    size_t id;

    Edge(size_t dest, size_t i) : destination(dest), id(i) {}
};

struct Graph {
    size_t timer = 0;
    size_t INF = 1e9;
    vector<vector<Edge>> adjacency_list;
    vector<bool> visited;
    vector<size_t> entry_time;
    vector<size_t> exit_time;
    vector<size_t> parents;
    set<size_t> bridges;
    size_t bridge_count = 0;

    Graph(size_t n) : adjacency_list(n + 1), visited(n + 1, false), entry_time(n + 1, 0), exit_time(n + 1, 0), parents(n + 1, 0) {}

    void addEdge(size_t from, size_t to, size_t id) {
        adjacency_list[from].emplace_back(to, id);
        adjacency_list[to].emplace_back(from, id);
    }

    void dfs(size_t current, size_t parent = -1) {
        parents[current] = parent;
        entry_time[current] = timer++;
        exit_time[current] = entry_time[current];
        visited[current] = true;

        for (size_t i = 0; i < adjacency_list[current].size(); ++i) {
            Edge neighbor = adjacency_list[current][i];

            if (neighbor.destination == parent) {
                continue;
            }

            if (visited[neighbor.destination]) {
                exit_time[current] = min(exit_time[current], entry_time[neighbor.destination]);
            } else {
                dfs(neighbor.destination, current);
                exit_time[current] = min(exit_time[current], exit_time[neighbor.destination]);

                if (exit_time[neighbor.destination] == entry_time[neighbor.destination]) {
                    bridges.insert(neighbor.id);
                    bridge_count++;
                }
            }
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    size_t num_vertices, num_edges;
    cin >> num_vertices >> num_edges;

    Graph graph(num_vertices);

    for (size_t i = 1; i <= num_edges; i++) {
        size_t first, second;
        cin >> first >> second;
        graph.addEdge(first, second, i);
    }

    for (size_t i = 1; i <= num_vertices; i++) {
        if (!graph.visited[i]) {
            graph.dfs(i);
        }
    }

    cout << graph.bridge_count << '\n';

    for (auto bridge : graph.bridges) {
        cout << bridge << ' ';
    }

    return 0;
}
