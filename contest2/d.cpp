#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

const int MAXN = 20000;

std::vector<int> graph[MAXN + 1];
std::vector<int> reverseGraph[MAXN + 1];
std::vector<bool> visited(MAXN + 1, false);
std::stack<int> resultStack;
std::vector<int> componentLabels(MAXN + 1, -1);
int currentLabel = 0;

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

void kosaraju(int n) {
    for (int i = 1; i <= n; ++i) {
        if (!visited[i]) {
            dfsVisit(i);
        }
    }

    fill(visited.begin(), visited.end(), false);

    while (!resultStack.empty()) {
        int node = resultStack.top();
        resultStack.pop();

        if (!visited[node]) {
            dfsAssignLabels(node);
            currentLabel++;
        }
    }
}

int main() {
    int n, m;
    std::cin >> n >> m;

    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        graph[u].push_back(v);
        reverseGraph[v].push_back(u); // Добавим обратные рёбра для алгоритма Косараю
    }

    kosaraju(n);

    std::cout << currentLabel << "\n";
    for (int i = 1; i <= n; ++i) {
        std::cout << componentLabels[i] + 1 << " ";
    }
    std::cout << "\n";

    return 0;
}
