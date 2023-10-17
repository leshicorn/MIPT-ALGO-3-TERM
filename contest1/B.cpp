#include <iostream>
#include <vector>

#define MOD 1000003
#define MATRIX_SIZE 5
#define mod(a) ((a) % MOD)

/**
 * @brief Умножение матриц
 * 
 * @param a 
 * @param b 
 * @return std::vector<std::vector<unsigned long long>> 
 */
std::vector<std::vector<unsigned long long>> matrix_multiply(std::vector<std::vector<unsigned long long>> a, 
    std::vector<std::vector<unsigned long long>> b) {
    std::vector<std::vector<unsigned long long>> result(MATRIX_SIZE, std::vector<unsigned long long>(MATRIX_SIZE, 0));

    for (unsigned long long i = 0; i < MATRIX_SIZE; ++i) {
        for (unsigned long long j = 0; j < MATRIX_SIZE; ++j) {
            for (unsigned long long k = 0; k < MATRIX_SIZE; ++k) {
                result[i][j] += mod(mod((a[i][k]) * mod(b[k][j])));
            }
        }
    }

    return result;
}

unsigned long long matrix_power(unsigned long long degree, std::vector<unsigned long long>& default_vector) {
    std::vector<std::vector<unsigned long long>> base_matrix = {
        {1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0},
        {0, 1, 0, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 1, 0}
    };

    std::vector<std::vector<unsigned long long>> result_matrix = {
        {1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0},
        {0, 1, 0, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 1, 0}
    };
    
    while (degree > 0) {
        if (degree % 2 == 1) {
            result_matrix = matrix_multiply(result_matrix, base_matrix);
        }
        base_matrix = matrix_multiply(base_matrix, base_matrix);
        degree /= 2;
    }

    unsigned long long final_result = 0;
    for (int i = 0; i < MATRIX_SIZE; i++) {
        final_result += mod(result_matrix[1][i] * default_vector[i]);
    }

    return mod(final_result);
}

unsigned long long hare(unsigned long long n) {
    std::vector<std::vector<unsigned long long>> base_matrix = {
        {1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0},
        {0, 1, 0, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 1, 0}
    };

    std::vector<unsigned long long> default_vector = {8, 4, 2, 1, 1};

    if (n < MATRIX_SIZE) {
        return default_vector[MATRIX_SIZE - n];
    }

    return matrix_power(n - MATRIX_SIZE, default_vector);
}

int main() {
    unsigned long long n;
    std::cin >> n;
    unsigned long long result = hare(n);
    std::cout << result << std::endl;
    
    return 0;
}
