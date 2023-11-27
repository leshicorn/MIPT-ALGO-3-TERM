#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

const int MAXN = 100000;

vector<int> graph[MAXN + 1];
vector<bool> visited(MAXN + 1, false);
vector<bool> onStack(MAXN + 1, false);
stack<int> resultStack;

bool dfs(int node) {
    visited[node] = true;
    onStack[node] = true;

    for (int neighbor : graph[node]) {
        if (!visited[neighbor]) {
            if (dfs(neighbor)) {
                return true;
            }
        } else if (onStack[neighbor]) {
            return true;
        }
    }

    onStack[node] = false;
    resultStack.push(node);
    return false;
}

bool topologicalSort(int n) {
    for (int i = 1; i <= n; ++i) {
        if (!visited[i]) {
            if (dfs(i)) {
                return false; // Graph has a cycle, cannot perform topological sort
            }
        }
    }
    return true;
}

int main() {
    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
    }

    if (topologicalSort(n)) {
        while (!resultStack.empty()) {
            cout << resultStack.top() << " ";
            resultStack.pop();
        }
        cout << endl;
    } else {
        cout << -1 << endl; // Graph has a cycle
    }

    return 0;
}


// Построение графа:

    // Граф представлен в виде списка смежности, где graph[u] содержит список вершин, соединённых ребрами с вершиной u.

// Алгоритм топологической сортировки:

    // Используется модифицированный алгоритм обхода в глубину (DFS).
    // Функция dfs рекурсивно обходит граф, помечая вершины как посещённые и добавляя их в стек resultStack.
    // Если обнаруживается обратное ребро (цикл), то функция возвращает true, указывая наличие цикла в графе.

// Проверка наличия цикла:

    // В функции topologicalSort вызывается dfs для каждой вершины, если она не была посещена ранее.
    // Если при обходе графа обнаруживается цикл, то возвращается false, и программа выводит -1.
    // В противном случае возвращается true, и программа выводит топологический порядок вершин.

// Вывод результата:

    // Если граф не содержит циклов, программа выводит топологический порядок вершин, который хранится в стеке resultStack.