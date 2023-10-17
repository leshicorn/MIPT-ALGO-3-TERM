#include <iostream>
#include <algorithm>
#include <vector>

#define MOD 1000003
#define mod(a) ((a) % MOD)
/**
 * @brief Произведение матриц 2*2
 * 
 * @param a 
 * @param b 
 * @return std::vector<std::vector<int>> 
 */
std::vector<std::vector<unsigned long long>> matrix_mul(std::vector<std::vector<unsigned long long>> a, 
    std::vector<std::vector<unsigned long long>> b) {
    std::vector<std::vector<unsigned long long>> result = {{0, 0}, {0, 0}};
    for (unsigned long long i = 0; i < 2; ++i) {
        for (unsigned long long j = 0; j < 2 ; ++j) {
            for (unsigned long long k = 0; k < 2; ++k) {
                result[i][j] += mod(a[i][k]) * mod(b[k][j]);
                result[i][j] %= MOD;
            }
        }
    }
    return result;
}

/**
 * @brief Число Фиббоначи методом матричного возведения в степень.
 * 
 * @param n - порядок числа фиббоначи
 * @return int - число фиббоначи под модулю 1000003
 */
unsigned long long fibbonaci(unsigned long long n) {
    std::vector<std::vector<unsigned long long>> matrix = {{1, 1}, {1, 0}};
    std::vector<std::vector<unsigned long long>> result = {{1, 0}, {0, 1}};
    while (n > 0) {
        if (n % 2 == 1) {
            result = matrix_mul(result, matrix);
        }
        matrix = matrix_mul(matrix, matrix);
        n /= 2;
    }
    return mod(result[1][1]);
}

int main() {

    unsigned long long n;
    std::cin >> n;
    unsigned long long res = fibbonaci(n);
    std::cout << res << std::endl;
    
    return 0;
}