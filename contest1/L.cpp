#include <iostream>
#include <vector>

using namespace std;
void knapsack(int capacity, const vector<int>& weights, const vector<int>& values) {
    int n = weights.size();

    vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));

    for (int i = 1; i <= n; ++i) {
        for (int w = 1; w <= capacity; ++w) {
            if (weights[i - 1] <= w) {
                dp[i][w] = max(dp[i - 1][w], values[i - 1] + dp[i - 1][w - weights[i - 1]]);
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    int i = n, j = capacity;
    vector<int> selectedItems;
    while (i > 0 && j > 0) {
        if (dp[i][j] != dp[i - 1][j]) {
            selectedItems.push_back(i);
            j -= weights[i - 1];
        }
        --i;
    }

    for (int i = selectedItems.size() - 1; i >= 0; --i) {
        cout << selectedItems[i] << " ";
    }
    cout << endl;
}

int main() {
    int N, M;
    cin >> N >> M;

    vector<int> weights(N);
    vector<int> values(N);

    for (int i = 0; i < N; ++i) {
        cin >> weights[i];
    }

    for (int i = 0; i < N; ++i) {
        cin >> values[i];
    }

    knapsack(M, weights, values);

    return 0;
}
