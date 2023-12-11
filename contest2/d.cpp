#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

const int MAXN = 20000;

vector<int> graph[MAXN + 1];
vector<int> reverseGraph[MAXN + 1];
vector<bool> visited(MAXN + 1, false);
stack<int> resultStack;
vector<int> componentLabels(MAXN + 1, -1);
int currentLabel = 0;

void dfs1(int node) {
    visited[node] = true;
    for (int neighbor : graph[node]) {
        if (!visited[neighbor]) {
            dfs1(neighbor);
        }
    }
    resultStack.push(node);
}

void dfs2(int node) {
    visited[node] = true;
    componentLabels[node] = currentLabel;
    for (int neighbor : reverseGraph[node]) {
        if (!visited[neighbor]) {
            dfs2(neighbor);
        }
    }
}

void kosaraju(int n) {
    for (int i = 1; i <= n; ++i) {
        if (!visited[i]) {
            dfs1(i);
        }
    }

    fill(visited.begin(), visited.end(), false);

    while (!resultStack.empty()) {
        int node = resultStack.top();
        resultStack.pop();

        if (!visited[node]) {
            dfs2(node);
            currentLabel++;
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        reverseGraph[v].push_back(u); // Добавим обратные рёбра для алгоритма Косараю
    }

    kosaraju(n);

    cout << currentLabel << endl;
    for (int i = 1; i <= n; ++i) {
        cout << componentLabels[i] + 1 << " ";
    }
    cout << endl;

    return 0;
}
