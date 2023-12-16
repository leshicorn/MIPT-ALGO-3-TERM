#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

class DFS {
public:
    DFS(const std::vector<std::vector<int>>& graph, const std::vector<std::vector<int>>& reverseGraph,
        std::vector<bool>& visited, std::stack<int>& resultStack, std::vector<int>& componentLabels,
        int& currentLabel)
        : graph(graph), reverseGraph(reverseGraph), visited(visited), resultStack(resultStack),
          componentLabels(componentLabels), currentLabel(currentLabel) {}

    void runDFS() {
        for (size_t i = 1; i <= graph.size(); ++i) {
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

private:
    const std::vector<std::vector<int>>& graph;
    const std::vector<std::vector<int>>& reverseGraph;
    std::vector<bool>& visited;
    std::stack<int>& resultStack;
    std::vector<int>& componentLabels;
    int& currentLabel;

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
};

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
        DFS dfs(graph, reverseGraph, visited, resultStack, componentLabels, currentLabel);
        dfs.runDFS();
    }

    int getCurrentLabel() const {
        return currentLabel;
    }

    const std::vector<int>& getComponentLabels() const {
        return componentLabels;
    }

private:
    int verticesCount;
    std::vector<std::vector<int>> graph;
    std::vector<std::vector<int>> reverseGraph;
    std::vector<bool> visited;
    std::stack<int> resultStack;
    std::vector<int> componentLabels;
    int currentLabel;
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

    std::cout << graph.getCurrentLabel() << "\n";
    for (int label : graph.getComponentLabels()) {
        std::cout << label + 1 << " ";
    }
    std::cout << "\n";

    return 0;
}
