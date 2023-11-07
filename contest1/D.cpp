#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define INF 1e17
string first;
string second;

/**
 * Reads input from standard input stream and returns a vector of long long integers.
 * @param n The number of elements to read from the input stream.
 * @return A vector of long long integers read from the input stream.
 */
vector<long long> read_input(long long n) {
    vector<long long> array(n);
    for (long long i = 0; i < n; i++) {
        cin >> array[i];
    }
    return array;
}

/**
 * Finds the longest increasing subsequence of a given array.
 * @param array The input array.
 * @return A vector containing the indices of the longest increasing subsequence.
 */
vector<long long> find_LIS(vector<long long>& array) {
    long long n = array.size();
    vector<long long> dp(n + 1, INF);
    vector<long long> prev(n + 1);
    vector<long long> pos(n + 1);
    pos[0] = -1;
    dp[0] = -INF;
    reverse(array.begin(), array.end());
    for (int i = 0; i < n; i++) {
        int j = int(upper_bound(dp.begin(), dp.end(), array[i]) - dp.begin());
        if (dp[j - 1] < array[i] && array[i] < dp[j]) {
            dp[j] = array[i];
            pos[j] = i;
            prev[i] = pos[j - 1];
        }
    }
    long long maximum = dp[0];
    for (long long k = 1; k <= n; k++) {
        if (dp[k] != INF) {
            maximum = max(maximum, k);
        }
    }
    vector<long long> answer;
    long long p = pos[maximum];
    while (p != -1) {
        answer.push_back(p);
        p = prev[p];
    }
    reverse(answer.begin(), answer.end());
    return answer;
}

/**
 * @brief Prints the output of the program.
 * 
 * @param n The input number.
 * @param answer The vector containing the answer.
 */
void print_output(long long n, vector<long long>& answer) {
    for (size_t i = 0; i < answer.size(); i++) {
        answer[i] = n - answer[i];
    }

    reverse(answer.begin(), answer.end());

    cout << answer.size() << endl;
    for (size_t i = 0; i < answer.size(); i++) {
        cout << answer[i] << ' ';
    }
    cout << '\n';
}

/**
 * The main function that reads input, finds the longest increasing subsequence (LIS) of the input array,
 * and prints the output.
 * @return 0 upon successful completion
 */
int main() {
    long long n;
    cin >> n;
    vector<long long> array = read_input(n);
    vector<long long> answer = find_LIS(array);
    print_output(n, answer);
    return 0;
}