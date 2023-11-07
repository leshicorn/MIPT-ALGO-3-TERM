#include <iostream>
#include <vector>

using namespace std;
void print_board(vector < vector < char >> & board) {
    for (auto & row: board) {
        for (auto & cell: row) {
            cout << cell << " ";
        }
        cout << endl;
    }
}

vector < vector < char >> construct_board(istream & in) {
    int n, m;
    in >> n >> m;
    vector < vector < char >> board(n, vector < char > (m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            in >> board[i][j];
        }
    }
    return board;
}

long long calculate_ways(vector < vector < char >> & board) {
    int n = board.size();
    int m = board[0].size();
    long long mod = 1000000007;
    // Construct dynamic programming tables
    vector < vector < long long >> dp(n + 1, vector < long long > (m + 1, 0));
    dp[0][0] = 1;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (board[i][j] == '+') {
                continue;
            }
            dp[i + 1][j + 1] = (dp[i + 1][j + 1] + dp[i][j + 1] + dp[i + 1][j]) % mod;
            if (board[i][j] == '-') {
                dp[i + 1][j + 1] = 0;
            }
        }
    }

    return dp[n][m];
}

int main() {
    auto board = construct_board(cin);
    print_board(board);
    cout << calculate_ways(board) << endl;
    return 0;
}