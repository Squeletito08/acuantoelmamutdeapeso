// O(n^3) para factorizar matrices, pero es O(n^2) por cada b en Ax=b
#include <iostream>
#include <vector>
using namespace std;

const int N = 100; // Max matrix size
double L[N][N], U[N][N];

// Performs LU decomposition of matrix A (n x n)
void lu_decomposition(const vector<vector<double>>& A, int n) {
    for (int i = 0; i < n; ++i) {
        // Upper Triangular
        for (int k = i; k < n; ++k) {
            double sum = 0;
            for (int j = 0; j < i; ++j)
                sum += L[i][j] * U[j][k];
            U[i][k] = A[i][k] - sum;
        }

        // Lower Triangular
        for (int k = i; k < n; ++k) {
            if (i == k)
                L[i][i] = 1; // Diagonal as 1
            else {
                double sum = 0;
                for (int j = 0; j < i; ++j)
                    sum += L[k][j] * U[j][i];
                L[k][i] = (A[k][i] - sum) / U[i][i];
            }
        }
    }
}

// Solves Ly = b (forward substitution)
vector<double> forward_substitution(const vector<double>& b, int n) {
    vector<double> y(n);
    for (int i = 0; i < n; ++i) {
        double sum = 0;
        for (int j = 0; j < i; ++j)
            sum += L[i][j] * y[j];
        y[i] = b[i] - sum;
    }
    return y;
}

// Solves Ux = y (backward substitution)
vector<double> backward_substitution(const vector<double>& y, int n) {
    vector<double> x(n);
    for (int i = n - 1; i >= 0; --i) {
        double sum = 0;
        for (int j = i + 1; j < n; ++j)
            sum += U[i][j] * x[j];
        x[i] = (y[i] - sum) / U[i][i];
    }
    return x;
}

// Solves Ax = b using LU decomposition
vector<double> solve_system(const vector<vector<double>>& A, const vector<double>& b, int n) {
    lu_decomposition(A, n);              // Factorize A into L and U
    vector<double> y = forward_substitution(b, n); 
    vector<double> x = backward_substitution(y, n);
    return x;
}

int main() {
    int n = 3;
    vector<vector<double>> A = {
        {2, -1, -2},
        {-4, 6, 3},
        {-4, -2, 8}
    };

    lu_decomposition(A, n);

    cout << "Lower Triangular Matrix L:\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
            cout << L[i][j] << " ";
        cout << endl;
    }

    cout << "\nUpper Triangular Matrix U:\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
            cout << U[i][j] << " ";
        cout << endl;
    }

    return 0;
}

