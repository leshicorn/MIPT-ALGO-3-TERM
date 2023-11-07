#include <iostream>
#include <vector>

using namespace std;

vector<long long> read_vector(long long size) {
    vector<long long> v(size);
    for (long long i = 0; i < size; i++) {
        cin >> v[i];
    }
    return v;
}

vector<vector<long long>> create_dp_table(long long n, long long m) {
    return vector<vector<long long>>(n + 2, vector<long long>(m + 2));
}

void fill_dp_table(vector<vector<long long>>& dp, const vector<long long>& a, const vector<long long>& b) {
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

long long find_longest_common_subsequence(const vector<long long>& a, const vector<long long>& b) {
    long long n = a.size(), m = b.size();
    vector<vector<long long>> dp = create_dp_table(n, m);
    fill_dp_table(dp, a, b);
    long long maxi = 0;
    for (long long i = 0; i < m; ++i) {
        maxi = max(maxi, dp[n - 1][i]);
    }
    return maxi;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    long long n, m;
    cin >> n >> m;
    vector<long long> a = read_vector(n);
    vector<long long> b = read_vector(m);
    cout << find_longest_common_subsequence(a, b);
}