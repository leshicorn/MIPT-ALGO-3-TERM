#include <iostream>
#include <vector>
#include <string>

using namespace std;

int solve(size_t n, size_t k);
int findOptimalSplit(const vector<vector<int>>& dp, int i, int j);
vector<vector<int>> initializeDP(size_t n, size_t k);

int main() {
    size_t n, k;
    cin >> n >> k;
    cout << solve(n, k) << '\n';
    return 0;
}

int solve(size_t n, size_t k) {
    k = min((size_t)18, k);
    if (k == 0) {
        if (n == 1) {
            return 0;
        } else {
            return -1;
        }
    }
    vector<vector<int>> dp = initializeDP(n, k);
    for (int i = 2; i <= k; ++i) {
        for (int j = 1; j <= n; ++j) {
            int ans = findOptimalSplit(dp, i, j);
            dp[i][j] = max(dp[i - 1][ans - 1], dp[i][j - ans + 1]) + 1;
        }
    }
    return dp[k][n];
}

int findOptimalSplit(const vector<vector<int>>& dp, int i, int j) {
    int l = 1;
    int r = j;
    while (l + 1 < r) {
        int mid = (l + r) >> 1;
        if (dp[i - 1][mid - 1] <= dp[i][j - mid + 1]) {
            l = mid;
        } else {
            r = mid;
        }
    }
    int ans = l;
    if (abs(dp[i - 1][r - 1] - dp[i][j - r + 1]) < abs(dp[i - 1][l - 1] - dp[i][j - l + 1])) {
        ans = r;
    }
    return ans;
}

vector<vector<int>> initializeDP(size_t n, size_t k) {
    vector<vector<int>> dp(k + 1, vector<int>(n + 1));
    for (int i = 1; i <= n; ++i) {
        dp[1][i] = i - 1;
    }
    return dp;
}
