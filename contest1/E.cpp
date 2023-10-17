#include <iostream>
#include <vector>
#include <algorithm>

#define INF 1e9
#define BASE_FOR_PAIR { -1, -1 }

/**
 * @brief Calculates the mid_distances between all pairs of houses.
 * 
 * @param houses The positions of the existing houses.
 * @param mid_distances The mid_distances between all pairs of houses.
 * @return None
 */
void calculate_mid_distances(const std::vector<int>& houses, std::vector<std::vector<int>>& mid_distances) {
    int n = houses.size() - 1;
    for (int l = 1; l <= n; l++) {
        for (int r = l; r <= n; r++) {
            int mid = houses[(l + r) >> 1];
            for (int u = l; u <= r; u++) {
                mid_distances[l][r] += abs(houses[u] - mid);
            }
        }
    }
}

/**
 * @brief Uses dynamic programming to find the optimal location of the new houses.
 * 
 * @param houses The positions of the existing houses.
 * @param mid_distances The mid_distances between all pairs of houses.
 * @param m The number of new houses to be built.
 * @param dp The dynamic programming table.
 * @param pred The predecessor table.
 * @return The minimum total distance and the positions of the new houses.
 */
std::pair<int, std::vector<int>> dynamic_programming(const std::vector<int>& houses, const std::vector<std::vector<int>>& mid_distances, int m, std::vector<std::vector<int>>& dp, std::vector<std::vector<std::pair<int, int>>>& pred) {
    int n = houses.size() - 1;
    std::vector<int> ans;

    dp[0][0] = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j <= n; j++) {
            for (int r = j + 1; r <= n; r++) {
                if (dp[i + 1][r] > dp[i][j] + mid_distances[j + 1][r]) {
                    dp[i + 1][r] = dp[i][j] + mid_distances[j + 1][r];
                    pred[i + 1][r] = { j, r };
                }
            }
        }
    }

    int i = m;
    int j = n;
    while (i != 0) {
        int l = pred[i][j].first;
        int r = pred[i][j].second;
        int u = (l + r) / 2;
        if ((l + r) % 2) {
            u++;
        }
        ans.push_back(houses[u]);
        j = l;
        i--;
    }
    reverse(ans.begin(), ans.end());

    return { dp[m][n], ans };
}

/**
 * @brief Solves the problem of finding the optimal location of a new house in a given set of existing houses.
 * 
 * @details The function takes two integers n and m as input, where n is the number of existing houses and m is the number of new houses to be built.
 * It then takes n integers as input, representing the positions of the existing houses.
 * The function calculates the mid_distances between all pairs of houses and uses dynamic programming to find the optimal location of the new houses.
 * The function outputs the minimum total distance and the positions of the new houses.
 * 
 * @param None
 * @return None
 */
void solve() {
    int n, m;
    std::vector<int> houses;

    // Input
    std::cin >> n >> m;
    houses.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        std::cin >> houses[i];
    }

    std::vector<std::vector<int>> mid_distances(n + 1, std::vector<int>(n + 1));
    calculate_mid_distances(houses, mid_distances);

    std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, INF));
    std::vector<std::vector<std::pair<int, int>>> pred(m + 1, std::vector<std::pair<int, int>>(n + 1, BASE_FOR_PAIR));
    auto [min_distance, new_houses] = dynamic_programming(houses, mid_distances, m, dp, pred);

    // Output
    std::cout << min_distance << '\n';
    for (auto house : new_houses) {
        std::cout << house << ' ';
    }
    std::cout << '\n';
}

int main() {
    solve();
    return 0;
}