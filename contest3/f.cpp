#include <iostream>
#include <vector>

using namespace std;

void transitiveClosure(vector<vector<int>>& graph, int N) {
    for (int k = 0; k < N; ++k) {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                graph[i][j] = graph[i][j] || (graph[i][k] && graph[k][j]);
            }
        }
    }
}

int main() {
    int N;
    cin >> N;

    // Чтение матрицы смежности
    vector<vector<int>> graph(N, vector<int>(N));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> graph[i][j];
        }
    }

    // Построение транзитивного замыкания
    transitiveClosure(graph, N);

    // Вывод результата
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << graph[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
