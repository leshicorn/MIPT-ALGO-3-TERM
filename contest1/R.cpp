#include <iostream>	
#include <vector>
#include <algorithm>

#define INF 1e9+44

bool bit(long long mask, long long u) {
    return (mask >> u) & 1;
}

void read_computers(long long n, std::vector<std::string>& computers) {
    for (long long i = 0; i < n; i++) {
        std::cin >> computers[i];
    }
}

void initialize_dp(long long n, std::vector<std::vector<long long>>& dp) {
    for (long long i = 0; i < n; i++) {
        dp[i][0] = 0;
    }
}

void update_dp(long long i, long long mask, long long j, long long newmask, std::vector<std::vector<long long>>& dp, const std::vector<std::string>& computers) {
    if (!((1 << j) & mask)) {
        newmask |= mask | (1 << j) | (1 << (i + 1));
        if (computers[i + 1][j] == 'Y') {
            dp[i + 1][newmask] = std::max(dp[i + 1][newmask], dp[i][mask] + 2);
        }
    }
}

long long compute_maxi(long long n, const std::vector<std::vector<long long>>& dp) {
    long long maxi = dp[n - 1][0];
    for (long long i = 0; i < (1 << n); i++) {
        maxi = std::max(dp[n - 1][i], maxi);
    }
    return maxi;
}

void solve() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    long long n;
    std::cin >> n;
    std::vector<std::string> computers(n);
    read_computers(n, computers);
    std::vector<std::vector<long long >> dp(n, std::vector<long long >(1 << n, -INF));
    initialize_dp(n, dp);
    for (long long i = 0; i < n - 1; i++) {
        for (long long mask = 0; mask < (1 << (i + 1)); mask++) {
            dp[i + 1][mask] = std::max(dp[i + 1][mask], dp[i][mask]);
            for (long long j = 0; j <= i; j++) {
                update_dp(i, mask, j, 0, dp, computers);
            }
        }
    }
    std::cout << compute_maxi(n, dp);
}

int main() {
    solve();
    return 0;
}