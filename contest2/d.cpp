#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

class Graph {
public:
    Graph(int verticesCount) : verticesCount(verticesCount), graph(verticesCount + 1),
                    reverseGraph(verticesCount + 1), visited(verticesCount + 1, false),
                    componentLabels(verticesCount + 1, -1), currentLabel(0) {}
        
        void addEdge(int from, int to) {
        graph[from].push_back(to);
        reverseGraph[to].push_back(from);
    }

    void kosaraju() {
        for (int i = 1; i <= verticesCount; ++i) {
            if (!visited[i]) {
                dfsVisit(i);
            }
        }

        std::fill(visited.begin(), visited.end(), false);

        while (!resultStack.empty()) {
            int node = resultStack.top();
            resultStack.pop();

            if (!visited[node]) {
                dfsAssignLabels(node);
                currentLabel++;
            }
        }
    }
    std::vector<int> componentLabels;
    std::stack<int> resultStack;
    int currentLabel;

private:
    void dfsVisit(int node) {
        visited[node] = true;
        for (int neighbor : graph[node]) {
            if (!visited[neighbor]) {
                dfsVisit(neighbor);
            }
        }
        resultStack.push(node);
    }
    void dfsAssignLabels(int node) {
        visited[node] = true;
        componentLabels[node] = currentLabel;
        for (int neighbor : reverseGraph[node]) {
            if (!visited[neighbor]) {
                dfsAssignLabels(neighbor);
            }
        }
    }

    int verticesCount;
    std::vector<std::vector<int>> graph;
    std::vector<std::vector<int>> reverseGraph;
    std::vector<bool> visited;
};

int main() {
    int n, m;
    std::cin >> n >> m;

    Graph graph(n);

    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        graph.addEdge(u, v);
    }

    graph.kosaraju();

    std::cout << graph.currentLabel << "\n";
    for (int i = 1; i <= n; ++i) {
        std::cout << graph.componentLabels[i] + 1 << " ";
    }
    std::cout << "\n";

    return 0;
}
