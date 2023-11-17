#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 100005;
const int LOGN = 20; // Логарифм от максимального числа вершин

vector<int> tree[MAXN];
int depth[MAXN];
int parent[MAXN][LOGN];

// DFS для построения дерева
void dfs(int u, int p, int d) {
    depth[u] = d;
    parent[u][0] = p;

    for (int v : tree[u]) {
        if (v != p) {
            dfs(v, u, d + 1);
        }
    }
}

// Подготовка данных для LCA
void prepareLCA(int n) {
    for (int j = 1; j < LOGN; j++) {
        for (int i = 1; i <= n; i++) {
            if (parent[i][j - 1] != -1) {
                parent[i][j] = parent[parent[i][j - 1]][j - 1];
            }
        }
    }
}

// Нахождение LCA
int findLCA(int u, int v) {
    if (depth[u] < depth[v]) {
        swap(u, v);
    }

    for (int i = LOGN - 1; i >= 0; i--) {
        if (depth[u] - (1 << i) >= depth[v]) {
            u = parent[u][i];
        }
    }

    if (u == v) {
        return u;
    }

    for (int i = LOGN - 1; i >= 0; i--) {
        if (parent[u][i] != parent[v][i]) {
            u = parent[u][i];
            v = parent[v][i];
        }
    }

    return parent[u][0];
}

// Нахождение расстояния между вершинами в дереве
int findDistance(int u, int v) {
    int lca = findLCA(u, v);
    return depth[u] + depth[v] - 2 * depth[lca];
}

int main() {
    int n;
    cin >> n;

    for (int i = 1; i <= n; i++) {
        tree[i].clear();
    }

    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }

    // Инициализация массива parent
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < LOGN; j++) {
            parent[i][j] = -1;
        }
    }

    // Построение дерева
    dfs(1, -1, 0);

    // Подготовка данных для LCA
    prepareLCA(n);

    int q;
    cin >> q;

    for (int i = 0; i < q; i++) {
        int u, v;
        cin >> u >> v;
        int distance = findDistance(u, v);
        cout << distance << endl;
    }

    return 0;
}
