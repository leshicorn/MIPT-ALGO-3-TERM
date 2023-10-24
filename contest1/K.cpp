#include <iostream>
#include <vector>

std::vector<long long> read_vector(long long size) {
    std::vector<long long> v(size);
    for (long long i = 0; i < size; i++) {
        std::cin >> v[i];
    }
    return v;
}

std::vector<std::vector<long long>> create_dp_table(long long n, long long m) {
    return std::vector<std::vector<long long>>(n + 2, std::vector<long long>(m + 2));
}

void fill_dp_table(std::vector<std::vector<long long>>& dp, const std::vector<long long>& a, const std::vector<long long>& b) {
    long long n = a.size(), m = b.size();
    for (long long i = 0; i < n; i++) {
        long long max = 0;
        for (long long j = 0; j < m; j++) {
            if (a[i] == b[j] && (i == 0 || dp[i - 1][j] < (max + 1))) {
                dp[i][j] = max + 1;
            }
            else if (i != 0) {
                dp[i][j] = dp[i - 1][j];
            }
            if (i != 0 && a[i] > b[j] && dp[i - 1][j] > max) {
                max = dp[i - 1][j];
            }
        }
    }
}

long long find_longest_common_subsequence(const std::vector<long long>& a, const std::vector<long long>& b) {
    long long n = a.size(), m = b.size();
    std::vector<std::vector<long long>> dp = create_dp_table(n, m);
    fill_dp_table(dp, a, b);
    long long maxi = 0;
    for (long long i = 0; i < m; ++i) {
        maxi = std::max(maxi, dp[n - 1][i]);
    }
    return maxi;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);

    // Read input
    long long n, m;
    std::cin >> n >> m;
    std::vector<long long> a = read_vector(n);
    std::vector<long long> b = read_vector(m);

    // Compute and output result
    std::cout << find_longest_common_subsequence(a, b);
}