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

class BridgeSearcher {
public:
    std::vector<size_t> bridges;  // Change to vector
    size_t bridge_count = 0;
    size_t timer = 0;
    std::vector<bool> visited;
    std::vector<size_t> entry_time;
    std::vector<size_t> exit_time;
    std::vector<size_t> parents;

    std::vector<size_t> dfs(std::vector<std::vector<Edge>>& adjacency_list, size_t current, size_t parent = -1) {
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
                exit_time[current] = std::min(exit_time[current], entry_time[neighbor.destination]);
            } else {
                dfs(adjacency_list, neighbor.destination, current);
                exit_time[current] = std::min(exit_time[current], exit_time[neighbor.destination]);

                if (exit_time[neighbor.destination] == entry_time[neighbor.destination]) {
                    bridges.push_back(neighbor.id);  // Change to push_back
                    bridge_count++;
                }
            }
        }

        return bridges;  // Return the vector of bridges
    }
};

class Graph {
public:
    size_t timer = 0;
    size_t INF = 1e9;
    std::vector<std::vector<Edge>> adjacency_list;

    Graph(size_t n) : adjacency_list(n + 1) {}

    void addEdge(size_t from, size_t to, size_t id) {
        adjacency_list[from].emplace_back(to, id);
        adjacency_list[to].emplace_back(from, id);
    }
};

int main() {
    size_t num_vertices, num_edges;
    std::cin >> num_vertices >> num_edges;

    Graph graph(num_vertices);
    BridgeSearcher bridgeSearcher;
    bridgeSearcher.visited.resize(num_vertices + 1, false);
    bridgeSearcher.entry_time.resize(num_vertices + 1, 0);
    bridgeSearcher.exit_time.resize(num_vertices + 1, 0);
    bridgeSearcher.parents.resize(num_vertices + 1, 0);

    for (size_t i = 1; i <= num_edges; i++) {
        size_t first, second;
        std::cin >> first >> second;
        graph.addEdge(first, second, i);
    }

    std::vector<size_t> result;

    for (size_t i = 1; i <= num_vertices; i++) {
        if (!bridgeSearcher.visited[i]) {
            result = bridgeSearcher.dfs(graph.adjacency_list, i);
        }
    }

    std::cout << bridgeSearcher.bridge_count << '\n';
    for (auto bridge : result) {
        std::cout << bridge << ' ';
    }
    std::cout << std::endl;

    return 0;
}
