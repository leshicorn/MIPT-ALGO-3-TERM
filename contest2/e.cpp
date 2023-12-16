#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <set>

class Edge {
public:
    size_t destination;
    size_t id;

    Edge(size_t dest, size_t i) : destination(dest), id(i) {}
};

class Graph {
public:
    size_t timer = 0;
    size_t INF = 1e9;
    std::vector<std::vector<Edge>> adjacency_list;
    std::vector<bool> visited;
    std::vector<size_t> entry_time;
    std::vector<size_t> exit_time;
    std::vector<size_t> parents;

    Graph(size_t n) : adjacency_list(n + 1), visited(n + 1, false), entry_time(n + 1, 0), exit_time(n + 1, 0), parents(n + 1, 0) {}

    void addEdge(size_t from, size_t to, size_t id) {
        adjacency_list[from].emplace_back(to, id);
        adjacency_list[to].emplace_back(from, id);
    }
};

class BridgeSearcher {
public:
    std::set<size_t> bridges;
    size_t bridge_count = 0;
    
    void dfs(Graph& graph, size_t current, size_t parent = -1) {
        graph.parents[current] = parent;
        graph.entry_time[current] = graph.timer++;
        graph.exit_time[current] = graph.entry_time[current];
        graph.visited[current] = true;

        for (size_t i = 0; i < graph.adjacency_list[current].size(); ++i) {
            Edge neighbor = graph.adjacency_list[current][i];

            if (neighbor.destination == parent) {
                continue;
            }

            if (graph.visited[neighbor.destination]) {
                graph.exit_time[current] = std::min(graph.exit_time[current], graph.entry_time[neighbor.destination]);
            } else {
                dfs(graph, neighbor.destination, current);
                graph.exit_time[current] = std::min(graph.exit_time[current], graph.exit_time[neighbor.destination]);

                if (graph.exit_time[neighbor.destination] == graph.entry_time[neighbor.destination]) {
                    bridges.insert(neighbor.id);
                    bridge_count++;
                }
            }
        }
    }
};

int main() {
    size_t num_vertices, num_edges;
    std::cin >> num_vertices >> num_edges;

    Graph graph(num_vertices);
    BridgeSearcher bridgeSearcher;

    for (size_t i = 1; i <= num_edges; i++) {
        size_t first, second;
        std::cin >> first >> second;
        graph.addEdge(first, second, i);
    }

    for (size_t i = 1; i <= num_vertices; i++) {
        if (!graph.visited[i]) {
            bridgeSearcher.dfs(graph, i);
        }
    }

    std::cout << bridgeSearcher.bridge_count << '\n';

    for (auto bridge : bridgeSearcher.bridges) {
        std::cout << bridge << ' ';
    }
    std::cout << '\n';

    return 0;
}
