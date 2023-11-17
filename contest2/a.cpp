#include <iostream>
#include <vector>
#include <string>

/**
 * @brief Function to perform DFS and find a cycle

 * 
 * @param graph 
 * @param s 
 * @param color 0 - не посещенная, 2 - посещенная, 1 - в работе
 * @param parents 
 * @param flag 
 * @param answer 
 * @param parent 
 */
void dfs(const std::vector<std::vector<int>>& graph, int s, std::vector<int>& color, 
        std::vector<int>& parents, bool& flag, std::vector<int>& answer, int parent = -1) {
    color[s] = 1;
    parents[s] = parent;

    for (int to : graph[s]) {
        if (color[to] == 0) {
            dfs(graph, to, color, parents, flag, answer, s);
        }
        else if (color[to] == 1) {
            if (flag) {
                return;
            }

            flag = true;

            int number = parents[s];
            answer.push_back(s);

            while (number != to) {
                answer.push_back(number);
                number = parents[number];
            }

            answer.push_back(to);

            return;
        }
    }

    color[s] = 2;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);

    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<int>> graph(n + 1);
    std::vector<int> color(n + 1, 0);
    std::vector<int> parents(n + 1);

    for (int i = 1; i <= m; i++) {
        int first, second;
        std::cin >> first >> second;
        graph[first].push_back(second);
    }

    bool flag = false;
    std::vector<int> answer;

    for (int i = 1; i <= n; ++i) {
        if (flag) {
            break;
        }

        if (color[i] != 2) {
            dfs(graph, i, color, parents, flag, answer);
        }
    }

    if (!flag) {
        std::cout << "NO" << '\n';
    }
    else {
        std::cout << "YES" << '\n';

        for (int i = answer.size() - 1; i >= 0; i--) {
            std::cout << answer[i] << ' ';
        }

        std::cout << '\n';
    }
}
