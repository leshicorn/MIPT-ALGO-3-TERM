#include <iostream>
#include <vector>
#include <algorithm>

unsigned long long longest_alternating_sequence(std::vector<std::vector<unsigned long long>>& dp, const std::vector<long long>& arr, std::vector<unsigned long long>& prev_increasing, std::vector<unsigned long long>& prev_decreasing, unsigned long long n, bool& flag) {
    flag = false;
    for (unsigned long long i = 0; i < n; i++) {
        dp[i][0] = dp[i][1] = 1;
    }
    unsigned long long res = 1;
    for (unsigned long long i = 1; i < n; i++) {
        for (unsigned long long j = 0; j < i; j++) {
            if (arr[j] < arr[i] && dp[i][0] < dp[j][1] + 1) {
                dp[i][0] = dp[j][1] + 1;
                prev_increasing[i] = j;
            }
            if (arr[j] > arr[i] && dp[i][1] < dp[j][0] + 1) {
                dp[i][1] = dp[j][0] + 1;
                prev_decreasing[i] = j;
            }
        }
        if (res < std::max(dp[i][0], dp[i][1])) {
            if (dp[i][0] > dp[i][1]) {
                res = dp[i][0];
                flag = false;
            }
            else {
                res = dp[i][1];
                flag = true;
            }
        }
    }
    return res;
}

std::vector<long long> read_input(unsigned long long n) {
    std::vector<long long> arr;
    for (unsigned long long i = 0; i < n; i++) {
        unsigned long long number;
        std::cin >> number;
        arr.push_back(number);
    }
    return arr;
}

void print_output(const std::vector<long long>& arr, const std::vector<size_t>& answer) {
    if (answer.size() == 2) {
        if (answer[0] == answer[1]) {
            std::cout << 1 << std::endl << arr[answer[0]];
            return;
        }
    }
    std::cout << answer.size() << std::endl;
    for (auto a : answer) {
        std::cout << arr[a] << ' ';
    }
}

std::vector<size_t> get_answer(const std::vector<std::vector<unsigned long long>>& dp, const std::vector<unsigned long long>& prev_increasing, const std::vector<unsigned long long>& prev_decreasing, unsigned long long n, bool flag) {
    std::vector<size_t> answer;
    unsigned long long max_increasing = 0;
    unsigned long long id_increasing = 0;
    for (unsigned long long i = 0; i < n; i++) {
        if (dp[i][0] > max_increasing) {
            max_increasing = dp[i][0];
            id_increasing = i;
        }
    }
    unsigned long long max_decreasing = 0;
    unsigned long long id_decreasing = 0;
    for (unsigned long long i = 0; i < n; i++) {
        if (dp[i][1] > max_decreasing) {
            max_decreasing = dp[i][1];
            id_decreasing = i;
        }
    }
    if (!flag) {
        unsigned long long dd = 0;
        answer.push_back(id_increasing);
        id_increasing = prev_increasing[id_increasing];
        while (id_increasing != 0) {
            answer.push_back(id_increasing);
            if (dd == 0) {
                id_increasing = prev_decreasing[id_increasing];
                dd = 1;
            }
            else {
                id_increasing = prev_increasing[id_increasing];
                dd = 0;
            }
        }
        answer.push_back(id_increasing);
    }
    else {
        unsigned long long dd = 0;
        answer.push_back(id_decreasing);
        id_decreasing = prev_decreasing[id_decreasing];
        while (id_decreasing != 0) {
            answer.push_back(id_decreasing);
            if (dd == 0) {
                id_decreasing = prev_increasing[id_decreasing];
                dd = 1;
            }
            else {
                id_decreasing = prev_decreasing[id_decreasing];
                dd = 0;
            }
        }
        answer.push_back(id_decreasing);
    }
    std::reverse(answer.begin(), answer.end());
    return answer;
}

int main() {
    unsigned long long n;
    std::cin >> n;
    if (n == 1) {
        std::cout << 1 << std::endl;
        std::cin >> n;
        std::cout << n;
        return 0;
    }
    std::vector<long long> arr = read_input(n);
    std::vector<std::vector<unsigned long long>> dp((n), std::vector<unsigned long long>(2));
    std::vector<unsigned long long> prev_increasing(n + 2, 0);
    std::vector<unsigned long long> prev_decreasing(n + 2, 0);
    bool flag = true;
    longest_alternating_sequence(dp, arr, prev_increasing, prev_decreasing, n, flag);
    std::vector<size_t> answer = get_answer(dp, prev_increasing, prev_decreasing, n, flag);
    print_output(arr, answer);
}
