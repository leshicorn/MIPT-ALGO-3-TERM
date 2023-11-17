#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

void dfs(int current, const vector<vector<int>>& graph, vector<bool>& visited, unordered_set<int>& current_group) {
    visited[current] = true;
    current_group.insert(current);

    for (int neighbor : graph[current]) {
        if (!visited[neighbor]) {
            dfs(neighbor, graph, visited, current_group);
        }
    }
}

int main() {
    int N, M;
    cin >> N >> M;

    vector<vector<int>> graph(N + 1);  // Используем индексацию с 1
    vector<bool> visited(N + 1, false);

    for (int i = 0; i < M; ++i) {
        int clone1, clone2;
        cin >> clone1 >> clone2;
        graph[clone1].push_back(clone2);
        graph[clone2].push_back(clone1);
    }

    vector<unordered_set<int>> squads;

    for (int i = 1; i <= N; ++i) {
        if (!visited[i]) {
            unordered_set<int> current_group;
            dfs(i, graph, visited, current_group);
            squads.push_back(current_group);
        }
    }

    cout << squads.size() << endl;

    for (const auto& squad : squads) {
        cout << squad.size() << endl;
        for (int clone : squad) {
            cout << clone << " ";
        }
        cout << endl;
    }

    return 0;
}
