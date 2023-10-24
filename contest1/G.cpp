#include <iostream>
#include <vector>

using namespace std;

vector<vector<long long int>> computeCombinations(size_t n) {
    vector<vector<long long int>> combinations(n + 1, vector<long long int>(n + 1));
    for (size_t i = 1; i <= n; i++) {
        combinations[1][i] = 1;
        combinations[0][i] = 1;
    }
    for (size_t i = 2; i <= n; i++) {
        for (size_t j = 1; j <= n; j++) {
            combinations[i][j] = combinations[i][j - 1];
            if (i >= j) {
                combinations[i][j] += combinations[i - j][j / 2];
            }
        }
    }
    return combinations;
}

void printCombinations(size_t n) {
    vector<vector<long long int>> combinations = computeCombinations(n);
    cout << combinations[n][n] << '\n';
}

int main() {
    size_t n;
    cin >> n;
    printCombinations(n);
    return 0;
}
