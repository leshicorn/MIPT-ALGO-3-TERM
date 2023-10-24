#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

#define inf 1e18

/**
 * Reads the names and preferences of men from standard input and stores them in a map and a vector.
 * 
 * @param n The number of men.
 * @param men_str A map that stores the names of the men.
 * @param men A vector that stores the preferences of the men.
 *            Each element is a pair of the form (preference, index), where preference is the preference number of the man
 *            and index is the index of the man in the men_str map.
 *            The first element of the vector is (-1, -1) and is not used.
 */
void read_men(long long n, std::map<long long, std::string>& men_str, std::vector<std::pair<long long, long long>>& men) {
    men.push_back({ -1, -1 });
    for (long long i = 0; i < n; i++) {
        std::string s;
        long long x;
        std::cin >> s >> x;
        men_str[i + 1] = s;
        men.push_back({ x, i + 1 });
    }
}

/**
 * Reads the names and preferences of women from standard input and stores them in a map and a vector.
 * 
 * @param m The number of women.
 * @param women_str A map that stores the names of the women.
 * @param women A vector that stores the preferences of the women.
 *              Each element is a pair of the form (x, i+1), where x is the preference of the i-th woman and i+1 is her index.
 *              The first element of the vector is (-1, -1) and is used as a placeholder.
 */
void read_women(long long m, std::map<long long, std::string>& women_str, std::vector<std::pair<long long, long long>>& women) {
    women.push_back({ -1, -1 });
    for (long long i = 0; i < m; i++) {
        std::string s;
        long long x;
        std::cin >> s >> x;
        women_str[i + 1] = s;
        women.push_back({ x, i + 1 });
    }
}

/**
 * @brief Solves the taxi problem.
 * @param n Number of men.
 * @param m Number of women.
 * @param men_str Map of men's names.
 * @param women_str Map of women's names.
 * @param men Vector of men's ratings and indices.
 * @param women Vector of women's ratings and indices.
 * @return void
 */
void solve(long long n, long long m, std::map<long long, std::string>& men_str, std::map<long long, std::string>& women_str, std::vector<std::pair<long long, long long>>& men, std::vector<std::pair<long long, long long>>& women) {
    std::sort(men.begin(), men.end());
    std::sort(women.begin(), women.end());

    std::vector<std::vector<long long>> dp(n + 1, std::vector<long long>(m + 1, inf));
    std::vector<std::vector<std::pair<long long, long long>>> prev(n + 1, std::vector<std::pair<long long, long long>>(m + 1, { -1, -1 }));
    dp[0][0] = 0;
    for (long long i = 0; i <= n; i++) {
        for (long long j = 0; j <= m; j++) {
            for (long long u = 1; u <= 4; u++) {
                if (i + u > n) break;
                long long nw = men[i + u].first;
                for (long long v = 0; v <= 3 && u + v <= 4; v++) {
                    if (j + v > m) break;
                    if (v != 0) nw = std::max(nw, women[j + v].first);
                    if (dp[i + u][j + v] >= dp[i][j] + nw) {
                        prev[i + u][j + v] = { i, j };
                        dp[i + u][j + v] = dp[i][j] + nw;
                    }
                }
            }
        }
    }
    std::vector<std::vector<std::pair<long long, long long>>> ans;
    long long i = n;
    long long j = m;
    std::pair<long long, long long> end = { -1, -1 };
    while (prev[i][j] != end) {
        long long newi = prev[i][j].first;
        long long newj = prev[i][j].second;
        std::vector<std::pair<long long, long long>> nums;
        for (long long u = newi + 1; u <= i; ++u) nums.push_back({ 1, men[u].second });
        for (long long u = newj + 1; u <= j; ++u) nums.push_back({ 2, women[u].second });

        ans.push_back(nums);
        i = newi;
        j = newj;
    }
    std::cout << dp[n][m] << '\n' << ans.size() << '\n';
    for (long long i = 0; i < ans.size(); i++) {
        std::cout << "Taxi " << i + 1 << ": ";
        for (long long j = 0; j < ans[i].size(); j++) {
            if (ans[i][j].first == 1) std::cout << men_str[ans[i][j].second];
            else std::cout << women_str[ans[i][j].second];

            if (j == ans[i].size() - 1) std::cout << ".\n";
            else if (j == ans[i].size() - 2) std::cout << " and ";
            else std::cout << ", ";
        }
    }
}

/**
 * @brief The main function that reads input, solves the problem and returns 0.
 * 
 * @return int 
 */
int main(){
    long long n;
    std::cin >> n;
    std::map<long long, std::string> men_str;
    std::vector<std::pair<long long, long long>> men;
    read_men(n, men_str, men);

    long long m;
    std::cin >> m;
    std::map<long long, std::string> women_str;
    std::vector<std::pair<long long, long long>> women;
    read_women(m, women_str, women);

    solve(n, m, men_str, women_str, men, women);
    return 0;
}