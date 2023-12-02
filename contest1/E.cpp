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
            for (int middle = l; middle <= r; middle++) {
                mid_distances[l][r] += abs(houses[middle] - mid);
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
 * @param table_for_dynamic_prog The dynamic programming table.
 * @param pred The predecessor table.
 * @return The minimum total distance and the positions of the new houses.
 */
std::pair<int, std::vector<int>> find_optimal_location(const std::vector<int>& houses, const std::vector<std::vector<int>>& mid_distances, int m, std::vector<std::vector<int>>& table_for_dynamic_prog, std::vector<std::vector<std::pair<int, int>>>& pred) {
    int n = houses.size() - 1;
    std::vector<int> ans;

    table_for_dynamic_prog[0][0] = 0;
    for (int new_house = 0; new_house < m; new_house++) {
        for (int last_house = 0; last_house <= n; last_house++) {
            for (int right_house = last_house + 1; right_house <= n; right_house++) {
                if (table_for_dynamic_prog[new_house + 1][right_house] > table_for_dynamic_prog[new_house][last_house] + mid_distances[last_house + 1][right_house]) {
                    table_for_dynamic_prog[new_house + 1][right_house] = table_for_dynamic_prog[new_house][last_house] + mid_distances[last_house + 1][right_house];
                    pred[new_house + 1][right_house] = { last_house, right_house };
                }
            }
        }
    }

    int new_house = m;
    int last_house = n;
    while (new_house != 0) {
        int left_house = pred[new_house][last_house].first;
        int right_house = pred[new_house][last_house].second;
        int middle_house = (left_house + right_house) / 2;
        if ((left_house + right_house) % 2) {
            middle_house++;
        }
        ans.push_back(houses[middle_house]);
        last_house = left_house;
        new_house--;
    }
    reverse(ans.begin(), ans.end());

    return { table_for_dynamic_prog[m][n], ans };
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

    std::vector<std::vector<int>> table_for_dynamic_prog(m + 1, std::vector<int>(n + 1, INF));
    std::vector<std::vector<std::pair<int, int>>> pred(m + 1, std::vector<std::pair<int, int>>(n + 1, BASE_FOR_PAIR));
    auto [min_distance, new_houses] = find_optimal_location(houses, mid_distances, m, table_for_dynamic_prog, pred);

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
