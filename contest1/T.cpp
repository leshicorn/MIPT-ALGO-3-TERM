#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;
const int MOD = 1e9 + 7;
const int MAX_DIMENSION = 20;

// Matrix multiplication
vector<vector<ll>> matrixMultiply(const vector<vector<ll>>& a, const vector<vector<ll>>& b) {
    int n = a.size();
    int m = a[0].size();
    int p = b[0].size();
    
    vector<vector<ll>> result(n, vector<ll>(p, 0));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < p; j++) {
            for (int k = 0; k < m; k++) {
                result[i][j] = (result[i][j] + (a[i][k] * b[k][j]) % MOD) % MOD;
            }
        }
    }

    return result;
}

// Matrix exponentiation
vector<vector<ll>> matrixPower(const vector<vector<ll>>& matrix, ll exponent) {
    int n = matrix.size();
    
    if (exponent == 0) {
        vector<vector<ll>> identity(n, vector<ll>(n, 0));
        for (int i = 0; i < n; i++) {
            identity[i][i] = 1;
        }
        return identity;
    } else if (exponent == 1) {
        return matrix;
    } else {
        vector<vector<ll>> halfPower = matrixPower(matrix, exponent / 2);
        vector<vector<ll>> result = matrixMultiply(halfPower, halfPower);
        
        if (exponent % 2 == 1) {
            result = matrixMultiply(result, matrix);
        }

        return result;
    }
}

int main() {
    ll n, k;
    cin >> n >> k;

    vector<vector<ll>> matrix(MAX_DIMENSION, vector<ll>(1, 0));
    matrix[0][0] = 1;

    for (ll i = 0; i < n; i++) {
        ll a, b, c;
        cin >> a >> b >> c;
        b = min(b, k);

        vector<vector<ll>> transitionMatrix(MAX_DIMENSION, vector<ll>(MAX_DIMENSION, 0));
        for (ll j = c + 1; j < MAX_DIMENSION; j++) {
            matrix[j][0] = 0;
        }

        for (ll j = 0; j <= c; j++) {
            transitionMatrix[j][j] = 1;
            if (j != c) {
                transitionMatrix[j][j + 1] = 1;
            }
            if (j > 0) {
                transitionMatrix[j][j - 1] = 1;
            }
        }

        transitionMatrix = matrixPower(transitionMatrix, b - a);
        matrix = matrixMultiply(transitionMatrix, matrix);
    }

    cout << matrix[0][0] << endl;
    
    return 0;
}
